//=======================================================================
// Author: Donovan Parks
//
// Copyright 2009 Donovan Parks
//
// This file is part of Chameleon.
//
// Chameleon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chameleon is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Chameleon. If not, see <http://www.gnu.org/licenses/>.
//=======================================================================

#include "stdafx.h"

#include "GUI.h"

#include "OpenPhylogenyDlg.hpp"
#include "AutoCollapseDlg.hpp"
#include "OpenDissimilarityMatrixDlg.hpp"
#include "VisualPropertiesDlg.hpp"
#include "Properties.hpp"
#include "PropertiesDlg.hpp"

#include "Log.hpp"

#include "Samples.hpp"
#include "SplitSystem.hpp"
#include "MatrixSystem.hpp"
#include "UniSplit.hpp"
#include "PCoA.hpp"
#include "ISOMAP.hpp"
#include "OrdinationPlots.hpp"
#include "ParallelCoordPlot.hpp"
#include "ResemblanceScatterplot.hpp"
#include "Legends.hpp"

#include "VisualPhylogeny.hpp"
#include "VisualClusterTree.hpp"
#include "VisualMatrix.hpp"

#include "OrdinationPlot.hpp"

#include "ColorMaps.hpp"

#include "StatsUtils.hpp"

#include "NewickIO.hpp"

#include "PlotPicker.hpp"

#include "SeqMetadata.hpp"

GUI::GUI(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), m_splitSystem(new SplitSystem()), m_distMatrixSystem(new MatrixSystem()), m_colorMaps(new ColorMaps())
{
	ui.setupUi(this);

	ReadProperties();
	
	// load color maps
	m_colorMaps->Load();
	m_colorMaps->PopulateComboBox(ui.cboDissimilarityMatrixColorMap);
	m_colorMaps->PopulateComboBox(ui.cboPhylogenySeqMetadataColorMap);

	// setup legends
	m_legends = LegendsPtr(new Legends(ui.legendColor, ui.legendShape, ui.legendSize,
																			ui.groupColorLegend, ui.groupShapeLegend, ui.groupSizeLegend,
																			m_colorMaps));

	QObject::connect(m_legends.data(), SIGNAL(SelectionSetChanged()), this, SLOT(UpdateSelectionSet()));

	m_uniSplit = UniSplitPtr(new UniSplit(m_splitSystem));
	m_visualPhylogeny = VisualPhylogenyPtr(new VisualPhylogeny(m_splitSystem, m_legends, m_colorMaps));
	m_visualClusterTree = VisualClusterTreePtr(new VisualClusterTree(m_legends));

	// setup diversity measure dialog
	m_diversityMeasureDlg = new DiversityMeasureDlg(m_splitSystem, this);
	m_diversityMeasureDlg->setVisible(false);

	addDockWidget(Qt::RightDockWidgetArea, m_diversityMeasureDlg);
	m_diversityMeasureDlg->setFloating(true);	
	
	// event handlers for main menu
	QObject::connect(ui.mnuFileOpenPhylogeny, SIGNAL(triggered()), this, SLOT(OpenPhylogeny()));
	QObject::connect(ui.mnuFileOpenMatrix, SIGNAL(triggered()), this, SLOT(OpenDissimilarityMatrix()));
	QObject::connect(ui.mnuFileSaveRasterImage, SIGNAL(triggered()), this, SLOT(SaveRasterImage()));
	QObject::connect(ui.mnuFileSaveColorLegend, SIGNAL(triggered()), this, SLOT(SaveColorLegend()));
	QObject::connect(ui.mnuFileSaveShapeLegend, SIGNAL(triggered()), this, SLOT(SaveShapeLegend()));
	QObject::connect(ui.mnuFileSaveSizeLegend, SIGNAL(triggered()), this, SLOT(SaveSizeLegend()));
	QObject::connect(ui.mnuFileSaveTable, SIGNAL(triggered()), this, SLOT(SaveTable()));	
	QObject::connect(ui.mnuFileExportPhylogeny, SIGNAL(triggered()), this, SLOT(SavePhylogenyVector()));
	QObject::connect(ui.mnuFileExportPC1vsPC2, SIGNAL(triggered()), this, SLOT(SavePC1vsPC2Vector()));	
	QObject::connect(ui.mnuFileExportPC3vsPC2, SIGNAL(triggered()), this, SLOT(SavePC3vsPC2Vector()));	
	QObject::connect(ui.mnuFileExportPC1vsPC3, SIGNAL(triggered()), this, SLOT(SavePC1vsPC3Vector()));	
	QObject::connect(ui.mnuFileExportScreePlot, SIGNAL(triggered()), this, SLOT(SaveScreePlotVector()));	
	QObject::connect(ui.mnuFileExportParallelCoordPlot, SIGNAL(triggered()), this, SLOT(SaveParallelCoordPlotVector()));	
	QObject::connect(ui.mnuFileExportClusterTree, SIGNAL(triggered()), this, SLOT(SaveClusterTreeVector()));
	QObject::connect(ui.mnuFileExportDissMatrixPlot, SIGNAL(triggered()), this, SLOT(SaveDissMatrixPlotVector()));
	QObject::connect(ui.mnuFileExportResemblanceScatterplot, SIGNAL(triggered()), this, SLOT(SaveResemblanceScatterplotVector()));	
	QObject::connect(ui.mnuFileExportTree, SIGNAL(triggered()), this, SLOT(ExportTreeInNewick()));
	QObject::connect(ui.mnuFileExit, SIGNAL(triggered()), qApp, SLOT(quit()));

	QObject::connect(ui.mnuInspectSequencesPerSample, SIGNAL(triggered()), this, SLOT(InspectSequencesPerSample()));
	QObject::connect(ui.mnuInspectSplitSystem, SIGNAL(triggered()), this, SLOT(InspectSplitSystem()));
	QObject::connect(ui.mnuInspectClearLog, SIGNAL(triggered()), this, SLOT(ClearLogWindow()));

	QObject::connect(m_diversityMeasureDlg, SIGNAL(Run()), this, SLOT(RunDiversityMeasure()));
	QObject::connect(ui.mnuAnalysisDistanceMatrix, SIGNAL(triggered()), this, SLOT(RunDistanceMatrix()));

	QObject::connect(ui.mnuHelpAbout, SIGNAL(triggered()), this, SLOT(ShowAboutDlg()));

	ui.dockLegend->toggleViewAction()->setText("&Legend");
	ui.dockLegend->toggleViewAction()->setShortcut(tr("Ctrl+Shift+L"));
	ui.dockLegend->toggleViewAction()->setStatusTip("Toggle visibility of legend");
	ui.menuView->addAction(ui.dockLegend->toggleViewAction());

	m_diversityMeasureDlg->toggleViewAction()->setText("&Diversity measure");
	m_diversityMeasureDlg->toggleViewAction()->setShortcut(tr("Ctrl+Shift+D"));
	m_diversityMeasureDlg->toggleViewAction()->setStatusTip("Apply diversity measure to data");
	ui.menuAnalysis->addAction(m_diversityMeasureDlg->toggleViewAction());

	// event handlers for GUI elements
	QObject::connect(ui.btnSetVisualProperties, SIGNAL(clicked()), this, SLOT(SetLegendProperties()));
	QObject::connect(ui.chkFitCurve, SIGNAL(clicked()), this, SLOT(SetFittedCurves()));
	QObject::connect(ui.chkShowCurve, SIGNAL(clicked()), this, SLOT(SetParallelCoordCurves()));
	QObject::connect(ui.chkShowVarianceLabels, SIGNAL(clicked()), this, SLOT(ShowVarianceLabels()));
	QObject::connect(ui.chkParallelCoordSelectionTransparency, SIGNAL(clicked()), this, SLOT(SetParrallelCoordSelectionTransparency()));
	QObject::connect(ui.spinParallelCoordDim, SIGNAL(valueChanged(int)), this, SLOT(SetNumDimensions()));
	QObject::connect(ui.chkShowSampleNames, SIGNAL(clicked()), this, SLOT(ShowSampleNames()));
	QObject::connect(ui.chkOrdinationSelectionTransparency, SIGNAL(clicked()), this, SLOT(SetOrdinationSelectionTransparency()));
	QObject::connect(ui.chkDissMatrixSelectionTransparency, SIGNAL(clicked()), this, SLOT(SetDissMatrixSelectionTransparency()));

	// event handlers for sample metadata
	QObject::connect(ui.tbMetadataAddAll, SIGNAL(clicked(bool)), this, SLOT(SetMetadataAll()));
	QObject::connect(ui.tbMetadataRemoveAll, SIGNAL(clicked(bool)), this, SLOT(SetMetadataRemoveAll()));
	QObject::connect(ui.tbMetadataSetSelected, SIGNAL(clicked(bool)), this, SLOT(SetMetadataSelectedSamples()));
	QObject::connect(ui.tbMetadataFilter, SIGNAL(clicked(bool)), this, SLOT(SetMetadataFiltered()));
	QObject::connect(ui.cboMetadataField, SIGNAL(currentIndexChanged(int)), this, SLOT(SetMetadataValues()));

	// event handler for tab widget
	QObject::connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(SetNewTab()));

	// setup statusbar
	m_statusBarTreeInfo.setText("");
	ui.statusBar->showMessage("Ready");
	ui.statusBar->addPermanentWidget(&m_statusBarDiversityMeasureInfo);
	ui.statusBar->addPermanentWidget(&m_statusBarTabInfo);
	ui.statusBar->addPermanentWidget(&m_statusBarTreeInfo);

	// setup tab widget
	for(int i = 0; i < ui.tabWidget->count(); ++i)
		ui.tabWidget->widget(i)->layout()->setContentsMargins(6,6,6,6);

	// setup splitters
	ui.splitterPhylogeny->setStretchFactor(1, 100);

	// setup GUI logging
	ui.txtLog->setFontFamily("Courier");
	Log::Inst().AddTextBrowser(ui.txtLog, ui.tabWidget, ui.tabLog);

	// setup ordination analysis
	m_ordinationAnalysisDlg = new OrdinationAnalysisDlg();
	m_ordinationAnalysisDlg->setVisible(false);
	m_ordinationAnalysisDlg->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, m_ordinationAnalysisDlg);
	m_ordinationAnalysisDlg->setFloating(true);	

	QIcon ordinationAnalysisIcon;
	ordinationAnalysisIcon.addFile(QString::fromUtf8(":/icons/icons/ordination-run.png"), QSize(), QIcon::Normal, QIcon::Off);

	m_ordinationAnalysisDlg->toggleViewAction()->setIcon(ordinationAnalysisIcon);
	m_ordinationAnalysisDlg->toggleViewAction()->setStatusTip("Run dimensionality reduction method"); 
	ui.tbOrdinationMethodRun->setDefaultAction(m_ordinationAnalysisDlg->toggleViewAction());

	QObject::connect(m_ordinationAnalysisDlg, SIGNAL(Run()), this, SLOT(RunDissimilarityMatrixAnalyses()));

	// setup projected coordinates dialog
	m_projectedCoordDlg = new ProjectedCoordDlg();
	m_projectedCoordDlg->setVisible(false);
	m_projectedCoordDlg->setAllowedAreas(Qt::BottomDockWidgetArea);
	addDockWidget(Qt::BottomDockWidgetArea, m_projectedCoordDlg);
	m_projectedCoordDlg->setFloating(true);	

	QIcon projectedCoordIcon;
	projectedCoordIcon.addFile(QString::fromUtf8(":/icons/icons/table_mds.png"), QSize(), QIcon::Normal, QIcon::Off);

	m_projectedCoordDlg->toggleViewAction()->setIcon(projectedCoordIcon);
	m_projectedCoordDlg->toggleViewAction()->setStatusTip("View projected coordinates table");
	ui.tbOrdinationPlotProjectedCoord->setDefaultAction(m_projectedCoordDlg->toggleViewAction());
	ui.tbParallelCoordProjectedCoord->setDefaultAction(m_projectedCoordDlg->toggleViewAction());

	// setup plots
	QList<OrdinationPlot*> plots;
	plots << ui.ordinationPlot1 << ui.ordinationPlot2 << ui.ordinationPlot3 << ui.screePlot;
	m_ordinationPlots = OrdinationPlotsPtr(new OrdinationPlots(plots, m_legends));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), m_ordinationPlots.data(), SLOT(UpdateMarkers()));
		
	m_parallelCoordPlot = ParallelCoordPlotPtr(new ParallelCoordPlot(ui.qwtPlotParallelCoord, m_legends));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), m_parallelCoordPlot.data(), SLOT(UpdateMarkers()));

	m_resemblanceScatterplot = ResemblanceScatterplotPtr(new ResemblanceScatterplot(ui.qwtResemblanceScatterplot));
	QObject::connect(ui.btnScatterplotRun,  SIGNAL(clicked()), this, SLOT(RunResemblanceScatterplot()));
	QObject::connect(ui.spinScatterplotSize, SIGNAL(valueChanged(int)), m_resemblanceScatterplot.data(), SLOT(UpdateMarkers(int)));
	QObject::connect(ui.chkShowBestFit, SIGNAL(stateChanged (int)), m_resemblanceScatterplot.data(), SLOT(ShowBestFitLine(int)));
	
	// setup dissimilarity matrix plot
	m_visualMatrix = VisualMatrixPtr(new VisualMatrix(m_legends, m_colorMaps, ui.lblDissimilarityLabel));
	QObject::connect(ui.chkDissimilarityMatrixFullRange, SIGNAL(clicked()), this, SLOT(SetDissimilarityMatrixRange()));
	QObject::connect(ui.chkDissimilarityMatrixThreshold, SIGNAL(clicked()), this, SLOT(SetDissimilarityMatrixThresholded()));
	QObject::connect(ui.tbDissimilarityMatrixRunSort, SIGNAL(clicked()), this, SLOT(RunDissimilarityMatrixSort()));
	QObject::connect(ui.cboDissimilarityMatrixColorMap, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetDissimilarityColorMap(const QString&)));
	QObject::connect(ui.spinDissimilarityMatrixMinSize, SIGNAL(valueChanged(int)), this, SLOT(SetDissimilarityMatrixMinCellSize(int)));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(UpdateDissimilarityMatrix()));
	
	ui.cboDissimilarityMatrixColorMap->setCurrentIndex(ui.cboDissimilarityMatrixColorMap->findText("White to black (continuous)"));

	// setup box plot	
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(PopulateBoxPlot()));

	// setup log signals
	QObject::connect(ui.btnSaveLog, SIGNAL(clicked()), this, SLOT(SaveLog()));
	QObject::connect(ui.btnClearLog, SIGNAL(clicked()), this, SLOT(ClearLogWindow()));

	// properties dialog
	m_propertiesDlg = new PropertiesDlg();
	m_propertiesDlg->setVisible(false);
	m_propertiesDlg->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, m_propertiesDlg);
	m_propertiesDlg->setFloating(true);	

	m_propertiesDlg->toggleViewAction()->setText("&Properties");
	m_propertiesDlg->toggleViewAction()->setShortcut(tr("Ctrl+Shift+P"));
	m_propertiesDlg->toggleViewAction()->setStatusTip("Set program properties");
	ui.menuSettings->addAction(m_propertiesDlg->toggleViewAction());

	QObject::connect(m_propertiesDlg, SIGNAL(BackgroundColorChanged(const QColor&)), this, SLOT(SetPlotBackgroundColor(const QColor&)));

	// set tables
	ui.tableBoxPlot->verticalHeader()->show();
	ui.tableBoxPlot->horizontalHeader()->show();

	ui.tableDissimilarityMatrix->verticalHeader()->show();
	ui.tableDissimilarityMatrix->horizontalHeader()->show();

	ui.tableMetadata->verticalHeader()->show();
	ui.tableMetadata->horizontalHeader()->show();

	// setup dissimilarty matrix view
	ui.dissMatrixViewport->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
	ui.dissMatrixViewport->setScene(m_visualMatrix->GetScene());
	ui.dissMatrixViewport->show();

	InitPhylogeny();
	InitClusterTree();

	SetPlotBackgroundColor(Properties::Inst().GetBackgroundColor());
}

GUI::~GUI()
{

}

void GUI::closeEvent(QCloseEvent *event)
{
	WriteProperties();
	event->accept();
}

void GUI::WriteProperties()
{
	QSettings settings;

	settings.beginGroup("MainWindow");

	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.setValue("fullScreen", isFullScreen());

	settings.endGroup();
}

void GUI::ReadProperties()
{
	QSettings settings;

	settings.beginGroup("MainWindow");

	resize(settings.value("size", QSize(800, 600)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());

	if(settings.value("fullScreen", false).toBool())
		setWindowState(windowState() ^ Qt::WindowFullScreen);

	settings.endGroup();
}

void GUI::InitPhylogeny()
{
	// enable standard color box for all color pickers
	ui.btnPhylogenyBackgroundColor->setStandardColors();
	ui.btnPhylogenyBackgroundColor->setCurrentColor(Qt::white);
	ui.btnPhylogenyBranchColor->setStandardColors();
	ui.btnPhylogenyNodeColor->setStandardColors();
	ui.btnPhylogenyBranchLabelColor->setStandardColors();
	ui.btnPhylogenyNodeLabelColor->setStandardColors();
	ui.btnPhylogenyScaleLabelColor->setStandardColors();
	ui.btnPhylogenyGradientSingleColor->setStandardColors();
	ui.btnPhylogenyGradientSingleColor->setCurrentColor(Qt::lightGray);

	// setup collapse node wizard	
	m_phylogenyAutoCollapseDlg = new AutoCollapseDlg();
	m_phylogenyAutoCollapseDlg->setVisible(false);

	addDockWidget(Qt::BottomDockWidgetArea, m_phylogenyAutoCollapseDlg);
	m_phylogenyAutoCollapseDlg->setFloating(true);	

	QIcon collapseNodeWizardIcon;
	collapseNodeWizardIcon.addFile(QString::fromUtf8(":/icons/icons/collapse-auto.png"), QSize(), QIcon::Normal, QIcon::Off);

	m_phylogenyAutoCollapseDlg->toggleViewAction()->setIcon(collapseNodeWizardIcon);
	m_phylogenyAutoCollapseDlg->toggleViewAction()->setStatusTip("Collapse node wizard");
	ui.tbPhylogenyCollapseWizard->setDefaultAction(m_phylogenyAutoCollapseDlg->toggleViewAction());

	// event handlers
	ui.spinPhylogenyLeafNodeSize->setValue(VisualNode::DEFAULT_LEAF_NODE_SIZE);
	ui.spinPhylogenyInternalNodeSize->setValue(VisualNode::DEFAULT_INTERNAL_NODE_SIZE);

	QObject::connect(ui.phylogenyViewport, SIGNAL(ViewportResized(int, int)), m_visualPhylogeny.data(), SLOT(SetViewportSize(int, int)));
	
	QObject::connect(ui.listPhylogenySearchResults, SIGNAL(currentTextChanged(const QString&)), m_visualPhylogeny.data(), SLOT(CenterOnNode(const QString&)));
	QObject::connect(ui.cboPhylogenySearchType, SIGNAL(currentIndexChanged(int)), this, SLOT(PhylogenySearch()));
	QObject::connect(ui.txtPhylogenySearchString, SIGNAL(textChanged(QString)), this, SLOT(PhylogenySearch()));

	QObject::connect(ui.tbPhylogenyToggleCollapse, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(CollapseSelectedNode()));
	QObject::connect(ui.tbPhylogenyCollapseComplement, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(CollapseComplementSelectedNode()));
	QObject::connect(ui.tbPhylogenyUncollapseAll, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(UncollapseAllNodes()));
	QObject::connect(ui.tbPhylogenyCollapseAll, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(CollapseAllNodes()));
	QObject::connect(ui.tbPhylogenyCollapseToScreen, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(CollapseToScreen()));
	QObject::connect(ui.cboPhylogenyParsimony, SIGNAL(currentIndexChanged(int)), this, SLOT(PhylogenyCalculateParsimonyScore()));
	QObject::connect(ui.tbPhylogenyReroot, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(Reroot()));
	QObject::connect(ui.tbPhylogenyRotateBranches, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(RotateSelectedBranches()));
	QObject::connect(ui.tbPhylogenyAlphabetical, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(SortAlphabetical()));
	QObject::connect(ui.tbPhylogenyLadderizeBottom, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(LadderizeBottom()));
	QObject::connect(ui.tbPhylogenyLadderizeTop, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(LadderizeTop()));
	QObject::connect(m_phylogenyAutoCollapseDlg, SIGNAL(Run()), this, SLOT(PhylogenyAutoCollapse()));
	
	QObject::connect(ui.cboPhylogenyBranchStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyBranchStyle()));
	QObject::connect(ui.chkPhylogenyAlignTipLabels, SIGNAL(stateChanged(int)), m_visualPhylogeny.data(), SLOT(SetAlignedTips(int)));
	QObject::connect(ui.cboPhylogenyLeafTreatment, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyLeafTreatment()));
	QObject::connect(ui.cboPhylogenyAbundanceStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyAbundanceStyle()));
	QObject::connect(ui.spinPhylogenyAbundanceMinSize, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyAbundanceStyle()));
	QObject::connect(ui.spinPhylogenyAbundanceMaxSize, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyAbundanceStyle()));
	QObject::connect(ui.spinPhylogenyRootLength, SIGNAL(valueChanged(double)), m_visualPhylogeny.data(), SLOT(SetRootLength(double)));
	QObject::connect(ui.spinPhylogenyLeafSpacing, SIGNAL(valueChanged(int)), m_visualPhylogeny.data(), SLOT(SetLeafSpacing(int)));
	QObject::connect(m_visualPhylogeny.data(), SIGNAL(RootLengthChanged(double)), ui.spinPhylogenyRootLength, SLOT(setValue(double)));
	QObject::connect(ui.btnPhylogenyRestoreActiveSamples, SIGNAL(clicked(bool)), this, SLOT(RestoreActiveSampleTree()));
	QObject::connect(ui.btnPhylogenyProjectSelectedSeqs, SIGNAL(clicked(bool)), this, SLOT(ProjectToSelectedLeaves()));
	
	QObject::connect(m_visualPhylogeny.data(), SIGNAL(BranchColorStyleChanged()), this, SLOT(SetPhylogenyBranchColorStyle()));
	QObject::connect(ui.cboPhylogenyBranchColorStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyBranchColorStyle()));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(SetPhylogenyBranchColorStyle()));
	QObject::connect(ui.btnPhylogenyBranchColor, SIGNAL(colorChanged(const QColor&)), m_visualPhylogeny.data(), SLOT(SetBranchColor(const QColor&)));
	QObject::connect(ui.spinPhylogenyBranchWidth, SIGNAL(valueChanged(int)), m_visualPhylogeny.data(), SLOT(SetBranchWidth(int)));
	QObject::connect(ui.chkPhylogenyDrawBranchOutline, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(SetDrawBranchOutline(bool)));
	QObject::connect(ui.cboPhylogenyBranchLabel, SIGNAL(currentIndexChanged(const QString&)), m_visualPhylogeny.data(), SLOT(SetBranchLabel(const QString&)));
	QObject::connect(ui.cboPhylogenyBranchFont, SIGNAL(currentFontChanged(const QFont&)), this, SLOT(SetPhylogenyBranchFont()));
	QObject::connect(ui.cboPhylogenyBranchFontSize, SIGNAL(editTextChanged(const QString &)), this, SLOT(SetPhylogenyBranchFont()));
	QObject::connect(ui.cboPhylogenyBranchFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(SetPhylogenyBranchFont()));
	QObject::connect(ui.tbPhylogenyBranchFontBold, SIGNAL(clicked()), this, SLOT(SetPhylogenyBranchFont()));
	QObject::connect(ui.tbPhylogenyBranchFontItalics, SIGNAL(clicked()), this, SLOT(SetPhylogenyBranchFont()));
	QObject::connect(ui.btnPhylogenyBranchLabelColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(SetPhylogenyBranchFont()));

	QObject::connect(m_visualPhylogeny.data(), SIGNAL(NodeColorStyleChanged()), this, SLOT(SetPhylogenyNodeColorStyle()));
	QObject::connect(ui.cboPhylogenyNodeColorStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyNodeColorStyle()));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(SetPhylogenyNodeColorStyle()));
	QObject::connect(ui.btnPhylogenyNodeColor, SIGNAL(colorChanged(const QColor&)), m_visualPhylogeny.data(), SLOT(SetNodeColor(const QColor&)));
	QObject::connect(m_visualPhylogeny.data(), SIGNAL(NodeShapeStyleChanged()), this, SLOT(SetPhylogenyNodeShapeStyle()));
	QObject::connect(ui.cboPhylogenyNodeShapeStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyNodeShapeStyle()));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(SetPhylogenyNodeShapeStyle()));
	QObject::connect(m_visualPhylogeny.data(), SIGNAL(NodeSizeStyleChanged()), this, SLOT(SetPhylogenyNodeSizeStyle()));
	QObject::connect(m_visualPhylogeny.data(), SIGNAL(AbundanceStyleChanged()), this, SLOT(SetPhylogenyAbundanceStyle()));
	QObject::connect(ui.cboPhylogenyNodeSizeStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyNodeSizeStyle()));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(SetPhylogenyNodeSizeStyle()));
	QObject::connect(ui.cboPhylogenyNodeShape, SIGNAL(currentIndexChanged(const QString&)), m_visualPhylogeny.data(), SLOT(SetNodeShape(const QString&)));
	QObject::connect(ui.spinPhylogenyLeafNodeSize, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyNodeSizeStyle()));
	QObject::connect(ui.spinPhylogenyInternalNodeSize, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyNodeSizeStyle()));
	QObject::connect(ui.cboPhylogenyNodeLabel, SIGNAL(currentIndexChanged(const QString&)), m_visualPhylogeny.data(), SLOT(SetNodeLabel(const QString&)));
	QObject::connect(ui.chkPhylogenyShowColorCategory, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(SetShowColorCategory(bool)));
	QObject::connect(ui.chkPhylogenyShowShapeCategory, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(SetShowShapeCategory(bool)));
	QObject::connect(ui.chkPhylogenyShowSizeCategory, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(SetShowSizeCategory(bool)));
	QObject::connect(ui.cboPhylogenyNodeFont, SIGNAL(currentFontChanged(const QFont&)), this, SLOT(SetPhylogenyNodeFont()));
	QObject::connect(ui.cboPhylogenyNodeFontSize, SIGNAL(editTextChanged(const QString &)), this, SLOT(SetPhylogenyNodeFont()));
	QObject::connect(ui.cboPhylogenyNodeFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(SetPhylogenyNodeFont()));
	QObject::connect(ui.tbPhylogenyNodeFontBold, SIGNAL(clicked()), this, SLOT(SetPhylogenyNodeFont()));
	QObject::connect(ui.tbPhylogenyNodeFontItalics, SIGNAL(clicked()), this, SLOT(SetPhylogenyNodeFont()));
	QObject::connect(ui.btnPhylogenyNodeLabelColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(SetPhylogenyNodeFont()));
	
	QObject::connect(ui.cboPhylogenyCollapsedNodeShape, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.chkPhylogenyCollapsedShowLabels, SIGNAL(clicked(bool)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.chkPhylogenyAbundanceInLabel, SIGNAL(clicked(bool)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyVariableTL, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyStatisticTL, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyFactorTL, SIGNAL(valueChanged(double)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyMinTL, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyMaxTL, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyVariableML, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyStatisticML, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyFactorML, SIGNAL(valueChanged(double)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyMinML, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyMaxML, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyVariableBL, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyStatisticBL, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyFactorBL, SIGNAL(valueChanged(double)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyMinBL, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyMaxBL, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyVariableHeight, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyStatisticHeight, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyFactorHeight, SIGNAL(valueChanged(double)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyMinHeight, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.spinPhylogenyMaxHeight, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyGradientStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.btnPhylogenyGradientSingleColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(ui.cboPhylogenyGradientFill, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	QObject::connect(m_visualPhylogeny.data(), SIGNAL(NewTreeSet()), this, SLOT(SetPhylogenyCollapsedNodeProperties()));
	
	QObject::connect(ui.chkPhylogenyShowScale, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(SetScaleVisibility(bool)));
	QObject::connect(ui.spinPhylogenyScale, SIGNAL(valueChanged(double)), m_visualPhylogeny.data(), SLOT(SetScaleLength(double)));
	QObject::connect(m_visualPhylogeny.data(), SIGNAL(AutomaticScaleChange(double)), ui.spinPhylogenyScale, SLOT(setValue(double)));
	QObject::connect(ui.spinPhylogenyScaleWidth, SIGNAL(valueChanged(int)), m_visualPhylogeny.data(), SLOT(SetScaleLineWidth(int)));
	QObject::connect(ui.chkPhylogenyScaleAutomatic, SIGNAL(clicked(bool)), m_visualPhylogeny.data(), SLOT(SetAutomaticScale(bool)));
	QObject::connect(ui.chkPhylogenyScaleAutomatic, SIGNAL(clicked(bool)), ui.spinPhylogenyScale, SLOT(setDisabled(bool)));
	QObject::connect(ui.spinPhylogenyScaleSignDigits, SIGNAL(valueChanged(int)), this, SLOT(SetPhylogenyScaleSignificantDigits(int)));
	QObject::connect(ui.cboPhylogenyScaleFont, SIGNAL(currentFontChanged(const QFont&)), this, SLOT(SetPhylogenyScaleFont()));
	QObject::connect(ui.cboPhylogenyScaleFontSize, SIGNAL(editTextChanged(const QString &)), this, SLOT(SetPhylogenyScaleFont()));
	QObject::connect(ui.cboPhylogenyScaleFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(SetPhylogenyScaleFont()));
	QObject::connect(ui.tbPhylogenyScaleFontBold, SIGNAL(clicked()), this, SLOT(SetPhylogenyScaleFont()));
	QObject::connect(ui.tbPhylogenyScaleFontItalics, SIGNAL(clicked()), this, SLOT(SetPhylogenyScaleFont()));
	QObject::connect(ui.btnPhylogenyScaleLabelColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(SetPhylogenyScaleFont()));

	QObject::connect(m_legends.data(), SIGNAL(CategoryChanged()), m_visualPhylogeny.data(), SLOT(LabelCategoriesChanged()));

	// sequence specific metadata
	QObject::connect(ui.chkPhylogenySeqMetadata, SIGNAL(clicked(bool)), this, SLOT(SetUsePhylogenySpecificMetadata()));
	QObject::connect(ui.tbPhylogenyBrowseSeqMetadataFile, SIGNAL(clicked()), this, SLOT(SetPhylogenyMetadataFile()));
	QObject::connect(ui.cboPhylogenySeqMetadataCategories, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyMetadataCategories()));
	QObject::connect(ui.cboPhylogenySeqMetadataColorMap, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetPhylogenyColorMap()));

	// setup sequence specific metadata legend dock widget
	m_phylogenySeqLegendDlg = new SeqLegendDlg(m_visualPhylogeny->GetSeqMetadata());
	m_phylogenySeqLegendDlg->setVisible(false);

	addDockWidget(Qt::BottomDockWidgetArea, m_phylogenySeqLegendDlg);
	m_phylogenySeqLegendDlg->setFloating(true);	

	QIcon seqLegendIcon;
	seqLegendIcon.addFile(QString::fromUtf8(":/icons/icons/legend.png"), QSize(), QIcon::Normal, QIcon::Off);

	m_phylogenySeqLegendDlg->toggleViewAction()->setIcon(seqLegendIcon);
	m_phylogenySeqLegendDlg->toggleViewAction()->setStatusTip("Toggle visibility of sequence legend");
	ui.tbPhylogenySeqMetadataLegend->setDefaultAction(m_phylogenySeqLegendDlg->toggleViewAction());

	QObject::connect(m_phylogenySeqLegendDlg, SIGNAL(OtherPercentageChanged()), this, SLOT(SetPhylogenyOtherPercentage()));
	
	// setup viewport
	ui.phylogenyViewport->setScene(m_visualPhylogeny->GetScene());
	m_visualPhylogeny->SetTreeInspector(ui.txtPhylogenyTreeInspector);
	ui.phylogenyViewport->show();
}

void GUI::InitClusterTree()
{
	// enable standard color box for all color pickers
	ui.btnClusterTreeBackgroundColor->setStandardColors();
	ui.btnClusterTreeBackgroundColor->setCurrentColor(Qt::white);
	ui.btnClusterTreeBranchColor->setStandardColors();
	ui.btnClusterTreeNodeColor->setStandardColors();
	ui.btnClusterTreeBranchLabelColor->setStandardColors();
	ui.btnClusterTreeNodeLabelColor->setStandardColors();
	ui.btnClusterTreeScaleLabelColor->setStandardColors();
	ui.btnClusterTreeGradientSingleColor->setStandardColors();
	ui.btnClusterTreeGradientSingleColor->setCurrentColor(Qt::lightGray);

	// setup collapse node wizard	
	m_clusterTreeAutoCollapseDlg = new AutoCollapseDlg();
	m_clusterTreeAutoCollapseDlg->setVisible(false);

	addDockWidget(Qt::BottomDockWidgetArea, m_clusterTreeAutoCollapseDlg);
	m_clusterTreeAutoCollapseDlg->setFloating(true);	

	QIcon collapseNodeWizardIcon;
	collapseNodeWizardIcon.addFile(QString::fromUtf8(":/icons/icons/collapse-auto.png"), QSize(), QIcon::Normal, QIcon::Off);

	m_clusterTreeAutoCollapseDlg->toggleViewAction()->setIcon(collapseNodeWizardIcon);
	m_clusterTreeAutoCollapseDlg->toggleViewAction()->setStatusTip("Collapse node wizard");
	ui.tbClusterTreeAutoCollapse->setDefaultAction(m_clusterTreeAutoCollapseDlg->toggleViewAction());

	// cluster tree analysis dialog
	m_clusterTreeAnalysisDlg = new ClusterTreeAnalysisDlg(m_splitSystem, m_uniSplit);
	m_clusterTreeAnalysisDlg->setVisible(false);
	m_clusterTreeAnalysisDlg->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, m_clusterTreeAnalysisDlg);
	m_clusterTreeAnalysisDlg->setFloating(true);	

	QIcon clusterTreeAnalysisIcon;
	clusterTreeAnalysisIcon.addFile(QString::fromUtf8(":/icons/icons/clusterTree-run.png"), QSize(), QIcon::Normal, QIcon::Off);

	m_clusterTreeAnalysisDlg->toggleViewAction()->setIcon(clusterTreeAnalysisIcon);
	m_clusterTreeAnalysisDlg->toggleViewAction()->setStatusTip("Run hierarchical clustering method");
	ui.tbClusterTreeRun->setDefaultAction(m_clusterTreeAnalysisDlg->toggleViewAction());

	// event handlers
	ui.spinClusterTreeLeafNodeSize->setValue(VisualNode::DEFAULT_LEAF_NODE_SIZE);
	ui.spinClusterTreeInternalNodeSize->setValue(VisualNode::DEFAULT_LEAF_NODE_SIZE);

	QObject::connect(ui.clusterTreeViewport, SIGNAL(ViewportResized(int, int)), m_visualClusterTree.data(), SLOT(SetViewportSize(int, int)));
	
	QObject::connect(ui.listClusterTreeSearchResults, SIGNAL(currentTextChanged(const QString&)), m_visualClusterTree.data(), SLOT(CenterOnNode(const QString&)));
	QObject::connect(ui.cboClusterTreeSearchType, SIGNAL(currentIndexChanged(int)), this, SLOT(ClusterTreeSearch()));
	QObject::connect(ui.txtClusterTreeSearchString, SIGNAL(textChanged(QString)), this, SLOT(ClusterTreeSearch()));

	QObject::connect(m_clusterTreeAnalysisDlg, SIGNAL(Run()), this, SLOT(ClusterTreeRun()));
	QObject::connect(ui.tbClusterTreeToggleCollapse, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(CollapseSelectedNode()));
	QObject::connect(ui.tbClusterTreeCollapseComplement, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(CollapseComplementSelectedNode()));
	QObject::connect(ui.tbClusterTreeUncollapseAll, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(UncollapseAllNodes()));
	QObject::connect(ui.tbClusterTreeCollapseAll, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(CollapseAllNodes()));
	QObject::connect(ui.tbClusterTreeCollapseToScreen, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(CollapseToScreen()));
	QObject::connect(ui.cboClusterTreeParsimony, SIGNAL(currentIndexChanged(int)), this, SLOT(ClusterTreeCalculateParsimonyScore()));
	QObject::connect(ui.tbClusterTreeReroot, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(Reroot()));
	QObject::connect(ui.tbClusterTreeRotateBranches, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(RotateSelectedBranches()));
	QObject::connect(ui.tbClusterTreeAlphabetical, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(SortAlphabetical()));
	QObject::connect(ui.tbClusterTreeLadderizeBottom, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(LadderizeBottom()));
	QObject::connect(ui.tbClusterTreeLadderizeTop, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(LadderizeTop()));
	QObject::connect(m_clusterTreeAutoCollapseDlg, SIGNAL(Run()), this, SLOT(ClusterTreeAutoCollapse()));
	
	QObject::connect(ui.cboClusterTreeBranchStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeBranchStyle()));
	QObject::connect(ui.chkClusterTreeAlignTipLabels, SIGNAL(stateChanged(int)), m_visualClusterTree.data(), SLOT(SetAlignedTips(int)));
	QObject::connect(ui.spinClusterTreeRootLength, SIGNAL(valueChanged(double)), m_visualClusterTree.data(), SLOT(SetRootLength(double)));
	QObject::connect(ui.spinClusterTreeLeafSpacing, SIGNAL(valueChanged(int)), m_visualClusterTree.data(), SLOT(SetLeafSpacing(int)));
	QObject::connect(m_visualClusterTree.data(), SIGNAL(RootLengthChanged(double)), ui.spinClusterTreeRootLength, SLOT(setValue(double)));
	
	QObject::connect(m_visualClusterTree.data(), SIGNAL(BranchColorStyleChanged()), this, SLOT(SetClusterTreeBranchColorStyle()));
	QObject::connect(ui.cboClusterTreeBranchColorStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeBranchColorStyle()));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(SetClusterTreeBranchColorStyle()));
	QObject::connect(ui.btnClusterTreeBranchColor, SIGNAL(colorChanged(const QColor&)), m_visualClusterTree.data(), SLOT(SetBranchColor(const QColor&)));
	QObject::connect(ui.spinClusterTreeBranchWidth, SIGNAL(valueChanged(int)), m_visualClusterTree.data(), SLOT(SetBranchWidth(int)));
	QObject::connect(ui.chkClusterTreeDrawBranchOutline, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(SetDrawBranchOutline(bool)));
	QObject::connect(ui.cboClusterTreeBranchLabel, SIGNAL(currentIndexChanged(const QString&)), m_visualClusterTree.data(), SLOT(SetBranchLabel(const QString&)));
	QObject::connect(ui.cboClusterTreeBranchFont, SIGNAL(currentFontChanged(const QFont&)), this, SLOT(SetClusterTreeBranchFont()));
	QObject::connect(ui.cboClusterTreeBranchFontSize, SIGNAL(editTextChanged(const QString &)), this, SLOT(SetClusterTreeBranchFont()));
	QObject::connect(ui.cboClusterTreeBranchFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(SetClusterTreeBranchFont()));
	QObject::connect(ui.tbClusterTreeBranchFontBold, SIGNAL(clicked()), this, SLOT(SetClusterTreeBranchFont()));
	QObject::connect(ui.tbClusterTreeBranchFontItalics, SIGNAL(clicked()), this, SLOT(SetClusterTreeBranchFont()));
	QObject::connect(ui.btnClusterTreeBranchLabelColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(SetClusterTreeBranchFont()));

	QObject::connect(m_visualClusterTree.data(), SIGNAL(NodeColorStyleChanged()), this, SLOT(SetClusterTreeNodeColorStyle()));
	QObject::connect(ui.cboClusterTreeNodeColorStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeNodeColorStyle()));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(SetClusterTreeNodeColorStyle()));
	QObject::connect(ui.btnClusterTreeNodeColor, SIGNAL(colorChanged(const QColor&)), m_visualClusterTree.data(), SLOT(SetNodeColor(const QColor&)));
	QObject::connect(m_visualClusterTree.data(), SIGNAL(NodeShapeStyleChanged()), this, SLOT(SetClusterTreeNodeShapeStyle()));
	QObject::connect(ui.cboClusterTreeNodeShapeStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeNodeShapeStyle()));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(SetClusterTreeNodeShapeStyle()));
	QObject::connect(m_visualClusterTree.data(), SIGNAL(NodeSizeStyleChanged()), this, SLOT(SetClusterTreeNodeSizeStyle()));
	QObject::connect(ui.cboClusterTreeNodeSizeStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeNodeSizeStyle()));
	QObject::connect(m_legends.data(), SIGNAL(VisualPropertiesChanged()), this, SLOT(SetClusterTreeNodeSizeStyle()));
	QObject::connect(ui.cboClusterTreeNodeShape, SIGNAL(currentIndexChanged(const QString&)), m_visualClusterTree.data(), SLOT(SetNodeShape(const QString&)));
	QObject::connect(ui.spinClusterTreeLeafNodeSize, SIGNAL(valueChanged(int)), m_visualClusterTree.data(), SLOT(SetLeafNodeSize(int)));
	QObject::connect(ui.spinClusterTreeInternalNodeSize, SIGNAL(valueChanged(int)), m_visualClusterTree.data(), SLOT(SetInternalNodeSize(int)));
	QObject::connect(ui.cboClusterTreeNodeLabel, SIGNAL(currentIndexChanged(const QString&)), m_visualClusterTree.data(), SLOT(SetNodeLabel(const QString&)));
	QObject::connect(ui.chkClusterTreeShowColorCategory, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(SetShowColorCategory(bool)));
	QObject::connect(ui.chkClusterTreeShowShapeCategory, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(SetShowShapeCategory(bool)));
	QObject::connect(ui.chkClusterTreeShowSizeCategory, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(SetShowSizeCategory(bool)));
	QObject::connect(ui.cboClusterTreeNodeFont, SIGNAL(currentFontChanged(const QFont&)), this, SLOT(SetClusterTreeNodeFont()));
	QObject::connect(ui.cboClusterTreeNodeFontSize, SIGNAL(editTextChanged(const QString &)), this, SLOT(SetClusterTreeNodeFont()));
	QObject::connect(ui.cboClusterTreeNodeFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(SetClusterTreeNodeFont()));
	QObject::connect(ui.tbClusterTreeNodeFontBold, SIGNAL(clicked()), this, SLOT(SetClusterTreeNodeFont()));
	QObject::connect(ui.tbClusterTreeNodeFontItalics, SIGNAL(clicked()), this, SLOT(SetClusterTreeNodeFont()));
	QObject::connect(ui.btnClusterTreeNodeLabelColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(SetClusterTreeNodeFont()));
	
	QObject::connect(ui.cboClusterTreeCollapsedNodeShape, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.chkClusterTreeCollapsedShowLabels, SIGNAL(clicked(bool)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.chkClusterTreeAbundanceInLabel, SIGNAL(clicked(bool)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeVariableTL, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeStatisticTL, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeFactorTL, SIGNAL(valueChanged(double)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeMinTL, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeMaxTL, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeVariableML, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeStatisticML, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeFactorML, SIGNAL(valueChanged(double)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeMinML, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeMaxML, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeVariableBL, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeStatisticBL, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeFactorBL, SIGNAL(valueChanged(double)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeMinBL, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeMaxBL, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeVariableHeight, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeStatisticHeight, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeFactorHeight, SIGNAL(valueChanged(double)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeMinHeight, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.spinClusterTreeMaxHeight, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeGradientStyle, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.btnClusterTreeGradientSingleColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(ui.cboClusterTreeGradientFill, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	QObject::connect(m_visualClusterTree.data(), SIGNAL(NewTreeSet()), this, SLOT(SetClusterTreeCollapsedNodeProperties()));
	
	QObject::connect(ui.chkClusterTreeShowScale, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(SetScaleVisibility(bool)));
	QObject::connect(ui.spinClusterTreeScale, SIGNAL(valueChanged(double)), m_visualClusterTree.data(), SLOT(SetScaleLength(double)));
	QObject::connect(m_visualClusterTree.data(), SIGNAL(AutomaticScaleChange(double)), ui.spinClusterTreeScale, SLOT(setValue(double)));
	QObject::connect(ui.spinClusterTreeScaleWidth, SIGNAL(valueChanged(int)), m_visualClusterTree.data(), SLOT(SetScaleLineWidth(int)));
	QObject::connect(ui.chkClusterTreeScaleAutomatic, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(SetAutomaticScale(bool)));
	QObject::connect(ui.chkClusterTreeScaleAutomatic, SIGNAL(clicked(bool)), ui.spinClusterTreeScale, SLOT(setDisabled(bool)));
	QObject::connect(ui.spinClusterTreeScaleSignDigits, SIGNAL(valueChanged(int)), this, SLOT(SetClusterTreeScaleSignificantDigits(int)));
	QObject::connect(ui.cboClusterTreeScaleFont, SIGNAL(currentFontChanged(const QFont&)), this, SLOT(SetClusterTreeScaleFont()));
	QObject::connect(ui.cboClusterTreeScaleFontSize, SIGNAL(editTextChanged(const QString &)), this, SLOT(SetClusterTreeScaleFont()));
	QObject::connect(ui.cboClusterTreeScaleFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(SetClusterTreeScaleFont()));
	QObject::connect(ui.tbClusterTreeScaleFontBold, SIGNAL(clicked()), this, SLOT(SetClusterTreeScaleFont()));
	QObject::connect(ui.tbClusterTreeScaleFontItalics, SIGNAL(clicked()), this, SLOT(SetClusterTreeScaleFont()));
	QObject::connect(ui.btnClusterTreeScaleLabelColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(SetClusterTreeScaleFont()));

	QObject::connect(m_legends.data(), SIGNAL(VisibileCategoriesChanged()), m_visualClusterTree.data(), SLOT(VisibleSamplesChanged()));
	QObject::connect(m_legends.data(), SIGNAL(CategoryChanged()), m_visualClusterTree.data(), SLOT(LabelCategoriesChanged()));

	QObject::connect(ui.chkGradientLabels, SIGNAL(clicked(bool)), m_visualClusterTree.data(), SLOT(SetAxisLabelVisibility(bool)));
	QObject::connect(ui.cboGradientField, SIGNAL(currentIndexChanged(const QString&)), m_visualClusterTree.data(), SLOT(SetAxisData(const QString&)));

	// setup viewport
	ui.clusterTreeViewport->setScene(m_visualClusterTree->GetScene());
	m_visualClusterTree->SetTreeInspector(ui.txtClusterTreeInspector);
	ui.clusterTreeViewport->show();
}

void GUI::OpenPhylogeny()
{
	OpenPhylogenyDlg dlg(this);
	if(dlg.exec())
	{
		QString phylogenyFile = dlg.GetPhylogenyFile();
		QString sampleFile = dlg.GetSampleFile();
		QString metadataFile = dlg.GetMetadataFile();
		bool bImplicitlyRooted = dlg.IsImplicitlyRooted();
		bool bShowPhylogeny = dlg.IsShowPhylogeny();
		LoadData(phylogenyFile, "", sampleFile, metadataFile, bImplicitlyRooted, bShowPhylogeny);
	}
}

void GUI::OpenDissimilarityMatrix()
{
	OpenDissimilarityMatrixDlg dlg(this);
	if(dlg.exec())
	{
		QString distMatrixFile = dlg.GetDissimilarityMatrixFile();
		QString metadataFile = dlg.GetMetadataFile();
		LoadData("", distMatrixFile, "", metadataFile, true, false);
	}
}

void GUI::LoadData(const QString& phylogenyFile, const QString& distMatrixFile, const QString& sampleFile, 
										const QString& metadataFile, bool bImplicitlyRooted, bool bShowPhylogeny)
{
	Log::Inst().Debug("Entering GUI::LoadData()");

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	if(!phylogenyFile.isEmpty() && !sampleFile.isEmpty())
	{
		bool bSuccess = m_splitSystem->LoadData(phylogenyFile, sampleFile, metadataFile, bImplicitlyRooted);
		if(bSuccess)
		{
			Log::Inst().Write("Data loaded successfully.");

			m_splitSystem->GetSamples()->GetMetadata()->PopulateTable(ui.tableMetadata);
			m_legends->SetSamples(m_splitSystem->GetSamples());
			m_legends->SetDefaultLegend();
			m_activeSystem = m_splitSystem;
		
			if(bShowPhylogeny)
			{
				Tree<VisualNode>* workingTree = m_splitSystem->GetTree()->Clone();
				m_splitSystem->CreateFromTree(workingTree->GetRootNode());
				m_visualPhylogeny->SetOriginalTree(m_splitSystem->GetTree());	
				m_visualPhylogeny->SetTree(workingTree);
			}
			
			QString message = "Samples = " + QString::number(m_splitSystem->GetSamples()->GetNumSamples())
											+ ", Splits = " + QString::number(m_splitSystem->GetNumSplits())
											+ ", Sequences = " + QString::number(m_splitSystem->GetSamples()->GetSequences()->GetNumActiveSequences(m_visualPhylogeny->GetLeafTreatment()));			
			m_statusBarTreeInfo.setText(message);
		}
		else
		{
			QApplication::restoreOverrideCursor();
			Log::Inst().Error("Failed to load phylogeny data.");
			return;
		}
	}
	else if(!distMatrixFile.isEmpty())
	{
		bool bSuccess = m_distMatrixSystem->LoadData(distMatrixFile, metadataFile);
		if(bSuccess)
		{
			Log::Inst().Write("Data loaded successfully.");

			m_distMatrixSystem->GetSamples()->GetMetadata()->PopulateTable(ui.tableMetadata);
			m_legends->SetSamples(m_distMatrixSystem->GetSamples());
			m_legends->SetDefaultLegend();
			m_activeSystem = m_distMatrixSystem;
		}
		else
		{
			QApplication::restoreOverrideCursor();
			Log::Inst().Error("Failed to load matrix data.");
			return;
		}
	}
	else
	{
		QApplication::restoreOverrideCursor();
		QMessageBox::information(this, "UniSplit", "A phylogeny must be specified along with a sample file.", QMessageBox::Ok);
		return;
	}

	m_ordinationAnalysisDlg->SetMetadata(m_activeSystem->GetSamples()->GetMetadata());
	m_isomap.SetMetadata(m_activeSystem->GetSamples()->GetMetadata());

	m_parallelCoordPlot->SetSamples(m_activeSystem->GetSamples());
	m_ordinationPlots->SetSamples(m_activeSystem->GetSamples());
	m_visualMatrix->SetSamples(m_activeSystem->GetSamples());
	m_visualClusterTree->SetActiveSystem(m_activeSystem);

	ui.cboPhylogenyParsimony->clear();
	ui.cboPhylogenyParsimony->addItems(m_activeSystem->GetSamples()->GetMetadata()->GetFields());
	ui.cboPhylogenyParsimony->updateGeometry();

	ui.cboClusterTreeParsimony->clear();
	ui.cboClusterTreeParsimony->addItems(m_activeSystem->GetSamples()->GetMetadata()->GetFields());
	ui.cboClusterTreeParsimony->updateGeometry();

	ui.cboGradientField->clear();
	ui.cboGradientField->addItem("<none>");
	ui.cboGradientField->addItems(m_activeSystem->GetSamples()->GetMetadata()->GetQuantitativeFields());
	ui.cboGradientField->updateGeometry();

	ui.cboMetadataField->clear();
	ui.cboMetadataField->addItems(m_activeSystem->GetSamples()->GetMetadata()->GetFields());
	ui.cboMetadataField->updateGeometry();

	m_diversityMeasureDlg->SplitSystemChanged();
	m_clusterTreeAnalysisDlg->AnalysisChanged();

	QObject::connect(m_activeSystem->GetSamples().data(), SIGNAL(ActiveSamplesChanged()), m_legends.data(), SLOT(ChangeActiveSamples()));

	QApplication::restoreOverrideCursor();

	Log::Inst().Debug("Leaving GUI::LoadData()");
}

void GUI::ShowAboutDlg()
{
	QString about = "Chameleon: many visualizations of biodiversity.\n";
	about += "v1.0\n\n";
	about += "Donovan Parks and Robert Beiko\n\n";
	about += "June 24, 2011";		

	QMessageBox::about(this, "About...", about);
}

void GUI::ShowSampleNames()
{
	m_ordinationPlots->SetShowSampleNames(ui.chkShowSampleNames->isChecked());
}

void GUI::SetOrdinationSelectionTransparency()
{
	m_ordinationPlots->SetSelectionTransparency(ui.chkOrdinationSelectionTransparency->isChecked());
}

void GUI::SetParrallelCoordSelectionTransparency()
{
	m_parallelCoordPlot->SetSelectionTransparency(ui.chkParallelCoordSelectionTransparency->isChecked());
}

void GUI::SetDissMatrixSelectionTransparency()
{
	m_visualMatrix->SetSelectionTransparency(ui.chkDissMatrixSelectionTransparency->isChecked());
}

void GUI::SetFittedCurves() 
{ 
	m_parallelCoordPlot->SetFittedCurves(ui.chkFitCurve->isChecked()); 
}

void GUI::SetParallelCoordCurves() 
{ 
	m_parallelCoordPlot->SetShowCurves(ui.chkShowCurve->isChecked()); 
}

void GUI::ShowVarianceLabels() 
{ 
	m_parallelCoordPlot->ShowVarianceLabels(ui.chkShowVarianceLabels->isChecked()); 
}

void GUI::SetNumDimensions() 
{ 
	m_parallelCoordPlot->SetNumDimensions(ui.spinParallelCoordDim->value()); 
}

void GUI::RunResemblanceScatterplot()
{
	// run analysis for x-axis
	QString measureX = ui.cboResemblenceXaxis->currentText();	
	if(measureX.contains("unweighted"))
		m_uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	else
		m_uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);

	if(measureX.contains("Common split set"))
		m_uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	else if(measureX.contains("Complete lineage"))
		m_uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	else if(measureX.contains("All splits"))
		m_uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	else if(measureX.contains("UniFrac semimetric"))
		m_uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);

	Matrix matrixX = m_uniSplit->Run();

	// run analysis for y-axis
	QString measureY = ui.cboResemblenceYaxis->currentText();
	if(measureY.contains("unweighted"))
		m_uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	else
		m_uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);

	if(measureY.contains("Common split set"))
		m_uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	else if(measureY.contains("Complete lineage"))
		m_uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	else if(measureY.contains("All splits"))
		m_uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	else if(measureY.contains("UniFrac semimetric"))
		m_uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);

	Matrix matrixY = m_uniSplit->Run();

	// plot results
	QStringList labels = m_splitSystem->GetSamples()->GetActiveSampleNames();
	m_resemblanceScatterplot->Plot(matrixX, matrixY, labels, measureX, measureY, ui.spinScatterplotSize->value(), ui.chkShowBestFit->isChecked());
}

void GUI::SetLegendProperties()
{
	VisualPropertiesDlg dlg(m_activeSystem->GetSamples()->GetMetadata(), m_legends, m_colorMaps, this);
	if(dlg.exec())
	{		
		m_legends->SetProperties(dlg.GetColorField(), dlg.GetColorMap(),
															dlg.GetShapeField(), dlg.IsFixedShape(), dlg.GetFixedShape(),
															dlg.GetSizeField(), dlg.GetMinSize(), dlg.GetMaxSize(), dlg.IsLogScale());
	}
}

void GUI::InspectSequencesPerSample()
{
	if(m_splitSystem && m_splitSystem->GetNumSplits() != 0)
	{
		QHash<QString, uint> readsPerSample = m_activeSystem->GetSamples()->GetSequences()->GetSequenceCounts(true);
		QHash<QString, uint> uniqueSeqPerSample = m_activeSystem->GetSamples()->GetSequences()->GetSequenceCounts(false);

		// find longest key
		int longestKey = 0;
		QStringList sampleLabels = readsPerSample.keys();
		foreach(QString label, sampleLabels)
		{
			if(label.size() > longestKey)
				longestKey = label.size();
		}
		
		Log::Inst().Write("");
		Log::Inst().Write("Sequence count (Unique sequences, Total sequences)");
		
		foreach(QString label, sampleLabels)
		{
			QString key = QString("%1").arg(label, longestKey);
			QString uniqueSeqs = QString("%1").arg(uniqueSeqPerSample.value(label), 8);
			QString reads = QString("%1").arg(readsPerSample.value(label), 8);			
			Log::Inst().Write(key + ": " + uniqueSeqs + " " + reads);
		}
	}
	else
	{
		Log::Inst().Warning("Split system contains no sequences.");
	}	

	// switch to log tab
	ui.tabWidget->setCurrentWidget(ui.tabLog);
}

void GUI::InspectSplitSystem()
{
	if(m_splitSystem->GetNumSplits() != 0)
	{	
		Log::Inst().Write("");
		Log::Inst().Write("Split system");
		Log::Inst().Write("--------------");
		m_splitSystem->Print();

	}
	else
	{
		Log::Inst().Warning("Split system contains zero splits.");
	}	

	// switch to log tab
	ui.tabWidget->setCurrentWidget(ui.tabLog);
}

void GUI::ClearLogWindow()
{
	Log::Inst().Clear();
}

void GUI::SaveLog()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save log...", "", "Text file (*.txt)");

	QFile file(filename);
	if(file.open(QFile::WriteOnly))
	{
		QTextStream stream(&file);
		stream << ui.txtLog->toPlainText();
		file.close();
	}
}

void GUI::RunDistanceMatrix()
{
	/*
	if(m_distMatrixSystem->GetMatrix().size() == 0)
	{
		QMessageBox::information(this, "UniSplit", "Dissimilarity matrix must be loaded before performing analysis.", QMessageBox::Ok);
		return;
	}

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	Matrix distMatrix = m_distMatrixSystem->GetMatrix();
	m_mds->Project(distMatrix);

	QStringList distLabels = m_distMatrixSystem->GetActiveSampleNames();
	Matrix sortedDistMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, distLabels);
	PopulateTable(ui.tableDissimilarityMatrix, sortedDistMatrix, distLabels, distLabels);

	Log::Inst().Write("");
	Log::Inst().Write("Projected distance matrix:");
	Log::Inst().Write(m_mds->GetProjectedData());
	Log::Inst().Write("");
	Log::Inst().Write("Eigenvalues:");
	for(int i = 0; i < m_mds->GetEigenvalues().size(); ++i)
		Log::Inst().Write(QString("%1").arg(m_mds->GetEigenvalues().at(i), 12, 'g', 4));

	Matrix projMatrix = m_mds->GetProjectedData();
	QStringList mdsLabels = m_distMatrixSystem->GetActiveSampleNames();
	Matrix sortedMdsMatrix = StatsUtils::AlphabeticallyOrderMatrix(projMatrix, mdsLabels, StatsUtils::RowSort);
	PopulateTable(ui.tableEmbeddedDimensions, sortedMdsMatrix, mdsLabels, QStringList());

	m_mdsPlot->SetMDS(m_mds);
	m_mdsPlot->Plot();

	m_parallelCoordPlot->SetMDS(m_mds);
	m_parallelCoordPlot->Plot();

	QApplication::restoreOverrideCursor();
	*/
}

void GUI::RunDiversityMeasure()
{
	Log::Inst().Debug("Entering GUI::RunDiversityMeasure()");

	if(m_splitSystem->GetNumSplits() == 0)
	{		
		QMessageBox::information(this, "UniSplit", "Community data must be loaded before performing analysis.", QMessageBox::Ok);
		return;
	}

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	// set the active split system
	Log::Inst().Debug("GUI::RunDiversityMeasure() - setting active split system");
	if(m_visualPhylogeny->GetTree())
		m_splitSystem->CreateFromTree(m_visualPhylogeny->GetActiveSubtreeRoot());
	else
		m_splitSystem->CreateFromTree(m_splitSystem->GetTree()->GetRootNode());

	// perform desired beta-diversity analysis
	m_uniSplit->SetMeasureType(m_diversityMeasureDlg->GetMeasureType());
	m_uniSplit->SetSplitsToConsider(m_diversityMeasureDlg->GetSplitsToConsider());

	Log::Inst().Debug("GUI::RunAnalyses() - UniSplit analysis");
	m_uniSplit->Run();

	m_statusBarDiversityMeasureInfo.setText(m_uniSplit->GetMethodMessage());

	RunDissimilarityMatrixAnalyses();

	QApplication::restoreOverrideCursor();

	Log::Inst().Debug("Leaving GUI::RunDiversityMeasure()");
}

void GUI::RunDissimilarityMatrixAnalyses()
{
	Log::Inst().Debug("Entering GUI::RunAnalyses()");

	// store any information relevant to the currently selected tab
	SetNewTab();

	Matrix dissimilarityMatrix;
	if(m_activeSystem == m_splitSystem)
		dissimilarityMatrix = m_uniSplit->GetDissimilarityMatrix();
	else
		dissimilarityMatrix = m_distMatrixSystem->GetMatrix();

	if(dissimilarityMatrix.size() == 0)
	{
		QMessageBox::information(this, "UniSplit", "Dissimilarity matrix is unspecified. Run a diversity measure.", QMessageBox::Ok);
		return;
	}

	// set dissimilarity table
	Log::Inst().Debug("GUI::RunAnalyses() - Set dissimilarity table");
	QStringList dissLabels = m_activeSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(dissimilarityMatrix, dissLabels);
	PopulateTable(ui.tableDissimilarityMatrix, sortedMatrix, dissLabels, dissLabels);

	// set dissimilarity matrix view
	Log::Inst().Debug("GUI::RunAnalyses() - Set dissimilarity matrix view");
	m_visualMatrix->SetData(sortedMatrix, dissLabels);
	m_visualMatrix->SetColorMap(ui.cboDissimilarityMatrixColorMap->currentText());
	
	// set ordination plot and associated tables
	Log::Inst().Debug("GUI::RunAnalyses() - MDS");
	Matrix embedding;
	QVector<double> variance;
	QVector<double> sumVariance;
	Matrix neighbourhoodGraph;
	float correlation;
	m_ordinationPlots->SetMethodMessage(m_ordinationAnalysisDlg->GetEmbeddingMethod());
	if(m_ordinationAnalysisDlg->GetEmbeddingMethod() == "Principal coordinate analysis")
	{
		m_pcoa.Project(dissimilarityMatrix);
		embedding = m_pcoa.GetProjectedData();
		variance = m_pcoa.GetVariance();
		sumVariance = m_pcoa.GetSumVariance();
	}
	else if(m_ordinationAnalysisDlg->GetEmbeddingMethod() == "Isomap")
	{
		m_isomap.Project(dissimilarityMatrix, 
											m_ordinationAnalysisDlg->GetNeighbourhoodMethod(),
											m_ordinationAnalysisDlg->GetNeighbourhoodField(),
											m_ordinationAnalysisDlg->GetNeighbourhoodValue());
		embedding = m_isomap.GetProjectedData();
		variance = m_isomap.GetVariance();
		sumVariance = m_isomap.GetSumVariance();
		neighbourhoodGraph = m_isomap.GetNeighbourhoodGraph();
	}
	else if(m_ordinationAnalysisDlg->GetEmbeddingMethod() == "Contiguous isomap")
	{
		m_isomap.ProjectSingleManifold(dissimilarityMatrix, 
																		m_ordinationAnalysisDlg->GetNeighbourhoodMethod(),
																		m_ordinationAnalysisDlg->GetNeighbourhoodField(),
																		m_ordinationAnalysisDlg->GetNeighbourhoodValue());
		embedding = m_isomap.GetProjectedData();
		variance = m_isomap.GetVariance();
		sumVariance = m_isomap.GetSumVariance();
		neighbourhoodGraph = m_isomap.GetNeighbourhoodGraph();
	}
	else if(m_ordinationAnalysisDlg->GetEmbeddingMethod() == "Nonmetric MDS")
	{
		m_nmds.Project(dissimilarityMatrix,	m_ordinationAnalysisDlg->GetNumberOfIter());
		embedding = m_nmds.GetProjectedData();
		correlation = m_nmds.GetCorrelation();
	}

	QStringList projLabels = m_activeSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedOrdinationMatrix = StatsUtils::AlphabeticallyOrderMatrix(embedding, projLabels, StatsUtils::RowSort);
	m_projectedCoordDlg->PopulateTable(sortedOrdinationMatrix, projLabels);

	m_ordinationPlots->SetData(embedding, variance, sumVariance, neighbourhoodGraph);
	m_ordinationPlots->Plot();

	// set parallel coordinate plot
	Log::Inst().Debug("GUI::RunAnalyses() - ||-coords");
	m_parallelCoordPlot->SetData(embedding, variance);
	m_parallelCoordPlot->Plot();

	// set cluster tree
	Log::Inst().Debug("GUI::RunAnalyses() - cluster tree");
	ClusterTreeRun();

	// set box plot
	Log::Inst().Debug("GUI::RunAnalyses() - box plot");
	PopulateBoxPlot();

	// update information associated with active tab
	Log::Inst().Debug("GUI::RunAnalyses() - set new tab");
	SetNewTab();

	Log::Inst().Debug("Leaving GUI::RunAnalyses()");
}

void GUI::PopulateTable(QTableWidget* table, const Matrix& matrix, const QStringList& rowHeaders, const QStringList& colHeaders)
{
	if(matrix.size() == 0)
	{
		table->clear();
		return;
	}

	table->setRowCount(matrix.size());
	table->setColumnCount(matrix.at(0).size());
	
	// set row headers
	if(rowHeaders.size() == matrix.size())
	{
		table->setVerticalHeaderLabels(rowHeaders);
	}
	else
	{
		QStringList numbers;
		for(int i = 0; i < matrix.at(0).size(); ++i)
			numbers << QString("%1").arg(i);
		table->setVerticalHeaderLabels(numbers);
	}

	// set column headers
	if(colHeaders.size() == matrix.at(0).size())
	{
		table->setHorizontalHeaderLabels(colHeaders);
	}
	else
	{
		QStringList numbers;
		for(int i = 0; i < matrix.size(); ++i)
			numbers << QString("%1").arg(i);
		table->setHorizontalHeaderLabels(numbers);
	}

	// set value of each cell
	for(int i = 0; i < matrix.size(); ++i)
	{	
		for(int j = 0; j < matrix.at(i).size(); ++j)
		{
			QTableWidgetItem* item = new QTableWidgetItem(tr("%1").arg(matrix.at(i).at(j)));
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			table->setItem(i, j, item);
		}
	}	

	table->resizeColumnsToContents();
}

void GUI::ExportTreeInNewick()
{
	QString types("Newick (*.tre *.nwk)");
	NewickIO newickIO;

	QString currentTab = ui.tabWidget->tabText(ui.tabWidget->currentIndex());
	if(currentTab == "Phylogeny" && m_visualPhylogeny->GetTree())
	{
		QString filename = QFileDialog::getSaveFileName(this, "Export phylogeny...", "", types);
		if(!filename.isEmpty()) 	
			newickIO.Write(*m_visualPhylogeny->GetTree(), filename);
	}
	else if(currentTab == "Cluster tree" && m_visualClusterTree)
	{
		QString filename = QFileDialog::getSaveFileName(this, "Export cluster tree...", "", types);
		if(!filename.isEmpty()) 
			newickIO.Write(*m_visualClusterTree->GetTree(), filename);
	}
	else
		QMessageBox::information(this, "UniSplit", "No tree contained in the current tab.", QMessageBox::Ok);
}

void GUI::SaveColorLegend()
{
	SaveRasterImageWidget(ui.legendColor);
}

void GUI::SaveShapeLegend()
{
	SaveRasterImageWidget(ui.legendShape);
}

void GUI::SaveSizeLegend()
{
	SaveRasterImageWidget(ui.legendSize);
}

void GUI::SaveRasterImage()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	// save image
	QString currentTab = ui.tabWidget->tabText(ui.tabWidget->currentIndex());
	if(currentTab == "Phylogeny")
		SaveRasterImageScene(m_visualPhylogeny->GetScene());
	else if(currentTab == "Ordination plots")
		SaveRasterImageWidget(ui.ordinationPlotFrame);
	else if(currentTab == "Cluster tree")
		SaveRasterImageScene(m_visualClusterTree->GetScene());
	else if(currentTab == "Parallel coordinate plot")
		SaveRasterImageWidget(ui.parallelCoordinatePlotFrame);
	else if(currentTab == "Dissimilarity matrix plot")
		SaveRasterImageScene(m_visualMatrix->GetScene());
	else if(currentTab == "Resemblance scatterplot")
		SaveRasterImageWidget(ui.resemblanceScatterplotFrame);
	else
		QMessageBox::information(this, "UniSplit", "No plot contained in the currently open tab.", QMessageBox::Ok);

	QApplication::restoreOverrideCursor();
}

void GUI::SaveRasterImageScene(QGraphicsScene* scene)
{
	QString types("Portable network graphics (*.png);;JPEG file (*.jpg *.jpeg);;Tagged image file format (*.tif *.tiff);;Bitmap file (*.bmp)");
	QString filename = QFileDialog::getSaveFileName(this, "Save raster image...", "", types);
	if(!filename.isEmpty())
	{
		// create image with desired properties
		QRectF sceneRect = scene->sceneRect();
		QImage image(sceneRect.width(), sceneRect.height(), QImage::Format_ARGB32_Premultiplied);

		// paint scene onto image
		QPainter painter(&image);
		painter.setRenderHint(QPainter::Antialiasing, true);
		scene->render(&painter);

		// save image to file
		if(!image.save(filename))
			QMessageBox::warning(this, "Failed to save image", "The image could not be written to file");
	}
}

void GUI::SaveRasterImageWidget(QWidget* widget)
{
	QString types("Portable network graphics (*.png);;JPEG file (*.jpg *.jpeg);;Tagged image file format (*.tif *.tiff);;Bitmap file (*.bmp)");
	QString filename = QFileDialog::getSaveFileName(this, "Save raster image...", "", types);
	if(!filename.isEmpty())
	{
		// create image with desired properties
		QRect rect = widget->rect();
		QImage image(rect.width(), rect.height(), QImage::Format_ARGB32_Premultiplied);
		
		// paint frame onto image
		QPainter painter(&image);
		painter.setRenderHint(QPainter::Antialiasing, true);
		widget->render(&painter);

		// save image to file
		if(!image.save(filename))
			QMessageBox::warning(this, "Failed to save image", "The image could not be written to file");
	}
}

void GUI::SavePhylogenyVector()
{
	SaveVectorScene(m_visualPhylogeny->GetScene());
}

void GUI::SavePC1vsPC2Vector()
{
	SaveVectorPlot(ui.ordinationPlot1);
}

void GUI::SavePC3vsPC2Vector()
{
	SaveVectorPlot(ui.ordinationPlot2);
}

void GUI::SavePC1vsPC3Vector()
{
	SaveVectorPlot(ui.ordinationPlot3);
}

void GUI::SaveScreePlotVector()
{
	SaveVectorPlot(ui.screePlot);
}

void GUI::SaveParallelCoordPlotVector()
{
	SaveVectorPlot(ui.qwtPlotParallelCoord);
}

void GUI::SaveClusterTreeVector()
{
	SaveVectorScene(m_visualClusterTree->GetScene());
}

void GUI::SaveDissMatrixPlotVector()
{
	SaveVectorScene(m_visualMatrix->GetScene());
}

void GUI::SaveResemblanceScatterplotVector()
{
	SaveVectorPlot(ui.qwtResemblanceScatterplot);
}

void GUI::SaveVectorPlot(QwtPlot* plot)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QString types("Scalable vector graphics (*.svg);;Portable document format (*.pdf);;PostScript (*.ps)");
	QString filename = QFileDialog::getSaveFileName(this, "Save vector image", "", types);
	if(!filename.isEmpty()) 
	{
		if(filename.contains(".pdf", Qt::CaseInsensitive) || filename.contains(".ps", Qt::CaseInsensitive))
		{
			QPrinter printer;
			printer.setOutputFileName(filename);
			printer.setDocName("");
			printer.setCreator("");
			printer.setFontEmbeddingEnabled(true);

			if(filename.contains(".pdf", Qt::CaseInsensitive))
				printer.setOutputFormat(QPrinter::PdfFormat);
			else
				printer.setOutputFormat(QPrinter::PostScriptFormat);

			QPainter painter;
			painter.begin(&printer);
			plot->render(&painter);
			painter.end();
		}
		else 
		{
			QSvgGenerator svg;
			svg.setFileName(filename);
			svg.setSize(QSize(plot->rect().width(), plot->rect().height()));
			svg.setViewBox(QRect(0, 0, plot->rect().width(), plot->rect().height()));
			svg.setTitle("");
			svg.setDescription(filename);

			QPainter painter;
			painter.begin(&svg);
			plot->render(&painter);
			painter.end();
		}
	}

	QApplication::restoreOverrideCursor();
}

void GUI::SaveVectorScene(QGraphicsScene* scene)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QString types("Scalable vector graphics (*.svg);;Portable document format (*.pdf);;PostScript (*.ps)");
	QString filename = QFileDialog::getSaveFileName(this, "Save vector image", "", types);
	if(!filename.isEmpty()) 
	{
		if(filename.contains(".pdf", Qt::CaseInsensitive) || filename.contains(".ps", Qt::CaseInsensitive))
		{
			QPrinter printer;
			printer.setOutputFileName(filename);
			printer.setDocName("");
			printer.setCreator("");
			printer.setFontEmbeddingEnabled(true);

			if(filename.contains(".pdf", Qt::CaseInsensitive))
				printer.setOutputFormat(QPrinter::PdfFormat);
			else
				printer.setOutputFormat(QPrinter::PostScriptFormat);

			QPainter painter;
			painter.begin(&printer);
			scene->render(&painter);
			painter.end();
		}
		else if(filename.contains(".svg", Qt::CaseInsensitive))
		{
			QSvgGenerator svg;
			svg.setFileName(filename);
			svg.setSize(QSize(scene->sceneRect().width(), scene->sceneRect().height()));
			svg.setViewBox(QRect(0, 0, scene->sceneRect().width(), scene->sceneRect().height()));
			svg.setTitle("");
			svg.setDescription(filename);
			
			QPainter painter;
			painter.begin(&svg);
			scene->render(&painter);
			painter.end();
		}
		else
		{
			QMessageBox::information(this, "Unknown vector format", "Vector files must be saved with a svg, pdf, or ps extension");
		}
	}

	QApplication::restoreOverrideCursor();
}

void GUI::SaveTable()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save table", "", "Tab seperated values file (*.tsv);;Comma seperated values file (*.csv)");

	// determine seperator type
	QString extension = filename.mid(filename.lastIndexOf(".")+1);
	extension = extension.toLower();
	QChar seperator = '\t';
	if(extension == "csv")
		seperator = ',';

	// write data to file
	QFile file(filename);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to create file: " + filename);
		return;
	}

	QTextStream textStream(&file);
	textStream.setRealNumberPrecision(6);

	QTableWidget* table;
	QString currentTab = ui.tabWidget->tabText(ui.tabWidget->currentIndex());
	if(currentTab == "Dissimilarity matrix")
		table = ui.tableDissimilarityMatrix;
	else if(currentTab == "Sample metadata")
		table = ui.tableMetadata;
	else
	{
		QMessageBox::information(this, "UniSplit", "No table contained in the currently open tab.", QMessageBox::Ok);
		return;
	}

	// write out row labels
	textStream << seperator;
	for(int i = 0; i < table->rowCount(); ++i)
			textStream << table->verticalHeaderItem(i)->text() << seperator;
	textStream << endl;

	for(int i = 0; i < table->rowCount(); ++i)
	{	
		textStream << table->horizontalHeaderItem(i)->text() << seperator;
		for(int j = 0; j < table->columnCount(); ++j)
		{
			QTableWidgetItem* item = table->item(i, j);
			textStream << item->text() << seperator;
		}

		textStream << endl;
	}	

	file.close();
}

void GUI::PopulateBoxPlot()
{
	if(!m_activeSystem)
		return;

	if(m_activeSystem->GetSamples()->IsActiveSetChanged())
	{
		// active set is being modified so hold off on recalculating
		// the box plots
		ui.tableBoxPlot->clear();
		return;
	}

	// determine group each sample is assigned to
	MetadataPtr metadata = m_activeSystem->GetSamples()->GetMetadata();

	QVector<QString> colorField;
	if(m_legends->GetNumColorLegendItems() == 0)
		colorField = QVector<QString>(m_activeSystem->GetSamples()->GetNumSamples(), "");
	else
		colorField = metadata->GetValues(m_legends->GetColorField());

	QVector<QString> shapeField;
	if(m_legends->GetNumShapeLegendItems() == 0)
		shapeField = QVector<QString>(m_activeSystem->GetSamples()->GetNumSamples(), "");
	else
		shapeField = metadata->GetValues(m_legends->GetShapeField());

	QVector<QString> sizeField;
	if(m_legends->GetNumSizeLegendItems() == 0)
		sizeField = QVector<QString>(m_activeSystem->GetSamples()->GetNumSamples(), "");
	else
		sizeField = metadata->GetValues(m_legends->GetSizeField());

	QList<QString> colors;
	QList<QString> shapes;
	QList<QString> sizes;
	for(uint i = 0; i < m_activeSystem->GetSamples()->GetNumSamples(); ++i)
	{		
		if(colors.indexOf(colorField.at(i)) == -1)
			colors.append(colorField.at(i));
		
		if(shapes.indexOf(shapeField.at(i)) == -1)
			shapes.append(shapeField.at(i));

		if(sizes.indexOf(sizeField.at(i)) == -1)
			sizes.append(sizeField.at(i));
	}

	QMap<uint, QList<QString> > groups;
	QMap<uint, QString> groupNames;
	QSet<uint> activeSampleIds = m_activeSystem->GetSamples()->GetActiveSampleIds();
	foreach(uint activeId, activeSampleIds)
	{	
		uint groupCode = (colors.indexOf(colorField.at(activeId)) << 24) 
												+ (shapes.indexOf(shapeField.at(activeId)) << 12) 
												+ sizes.indexOf(sizeField.at(activeId));

		QList<QString> members;
		QMap<uint, QList<QString> >::iterator it = groups.find(groupCode);
		if(it != groups.end())
		{
			members = it.value();

			QString groupName;
			if(colorField.at(activeId) != "")
				groupName += colorField.at(activeId);

			if(shapeField.at(activeId) != "")
			{
				if(groupName != "")
					groupName += ", " + shapeField.at(activeId);
				else
					groupName = shapeField.at(activeId);
			}

			if(sizeField.at(activeId) != "")
			{
				if(groupName != "")
					groupName += ", " + sizeField.at(activeId);
				else
					groupName = sizeField.at(activeId);
			}

			groupNames.insert(groupCode, groupName);
		}

		QString name = m_activeSystem->GetSamples()->GetSample(activeId).GetName();
		members.append(name);
		groups.insert(groupCode, members);
	}

	uint numGroups = groups.size();

	// get distance between samples
	QList<QString> columnNames;
	Matrix distances;

	for(int c = 0; c <	ui.tableDissimilarityMatrix->columnCount(); ++c)
	{
		QTableWidgetItem* columnHeader = ui.tableDissimilarityMatrix->horizontalHeaderItem(c);
		if(!columnHeader)	// make sure we have valid data
			return;

		columnNames.append(columnHeader->text());

		QVector<double> row;
		for(int r = 0; r < ui.tableDissimilarityMatrix->rowCount(); ++r)
			row.append(ui.tableDissimilarityMatrix->item(r, c)->text().toDouble());

		distances.append(row);
	}

	// determine and report average distances between groups
	ui.tableBoxPlot->setRowCount(numGroups);
	ui.tableBoxPlot->setColumnCount(numGroups);
	ui.tableBoxPlot->setVerticalHeaderLabels(groupNames.values());
	ui.tableBoxPlot->setHorizontalHeaderLabels(groupNames.values());

	for(uint i = 0; i < numGroups; ++i)
	{	
		for(uint j = i; j < numGroups; ++j)
		{
			// calculate average distance between groups
			QList<QString> group1 = groups.value(groups.keys()[i]);
			QList<QString> group2 = groups.value(groups.keys()[j]);

			double dist = 0;
			uint numComparisons = 0;
			foreach(const QString& sample1, group1)
			{
				uint index1 = columnNames.indexOf(sample1);
				foreach(const QString& sample2, group2)
				{
					uint index2 = columnNames.indexOf(sample2);
					if(index1 != index2)
					{
						dist += distances[index1][index2];
						numComparisons++;
					}
				}
			}

			dist /= numComparisons;

			QTableWidgetItem* item1 = new QTableWidgetItem(tr("%1").arg(dist));
			item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableBoxPlot->setItem(i, j, item1);

			QTableWidgetItem* item2 = new QTableWidgetItem(tr("%1").arg(dist));
			item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableBoxPlot->setItem(j, i, item2);
		}
	}	
	
	ui.tableBoxPlot->resizeColumnsToContents();
}


VisualNode::CollapsedLineProp GUI::GetCollapsedLineProp(QComboBox* cboVariable, 
																												QComboBox* cboStatistic, 
																													QDoubleSpinBox* spinFactor, 
																													QSpinBox* spinMin, 
																													QSpinBox* spinMax)
{
	VisualNode::CollapsedLineProp prop;

	if(cboVariable->currentText() == "Abundance")
		prop.variable = VisualNode::COLLAPSED_ABUNDANCE;
	else if(cboVariable->currentText() == "Branch length")
		prop.variable = VisualNode::COLLAPSED_BRANCH_LENGTH;
	else if(cboVariable->currentText() == "Fixed")
		prop.variable = VisualNode::COLLAPSED_FIXED;
	else if(cboVariable->currentText() == "Leaf node span")
		prop.variable = VisualNode::COLLAPSED_LEAF_NODE_SPAN;
	else if(cboVariable->currentText() == "Size variable")
		prop.variable = VisualNode::COLLAPSED_SIZE_VAR;
	else if(cboVariable->currentText() == "None")
		prop.variable = VisualNode::COLLAPSED_NONE;

	if(cboStatistic->currentText() == "Maximum")
		prop.statistic = VisualNode::COLLAPSED_MAX;
	else if(cboStatistic->currentText() == "Minimum")
		prop.statistic = VisualNode::COLLAPSED_MIN;
	else if(cboStatistic->currentText() == "Mean")
		prop.statistic = VisualNode::COLLAPSED_MEAN;
	else if(cboStatistic->currentText() == "Median")
		prop.statistic = VisualNode::COLLAPSED_MEDIAN;
	else if(cboStatistic->currentText() == "Total")
		prop.statistic = VisualNode::COLLAPSED_TOTAL;
	
	prop.factor = spinFactor->value();
	if(cboVariable->currentText() == "Branch length" || cboVariable->currentText() == "Leaf node span")
		prop.factor /= 100.0;

	prop.minSize = spinMin->value();
	prop.maxSize = spinMax->value();

	return prop;
}

void GUI::SetCollapsedLineGUI(QComboBox* cboVariable, QComboBox* cboStatistic, 
																QLabel* lblFactor, QDoubleSpinBox* spinFactor,
																QSpinBox* minSize, QSpinBox* maxSize)
{
	cboVariable->blockSignals(true);
	cboStatistic->blockSignals(true);
	lblFactor->blockSignals(true);
	spinFactor->blockSignals(true);

	if(cboVariable->currentText() == "Abundance")
	{
		spinFactor->setEnabled(false);
		cboStatistic->setEnabled(false);
		minSize->setEnabled(true);
		maxSize->setEnabled(true);
	}
	else if(cboVariable->currentText() == "Branch length")
	{
		lblFactor->setText("Percentage:");
		spinFactor->setRange(0.0, 100.0);
		spinFactor->setDecimals(1);
		spinFactor->setEnabled(true);

		uint currentIndex = cboStatistic->currentIndex();
		QStringList statistics;
		statistics << "Maximum" << "Minimum" << "Mean" << "Median" << "Total";
		cboStatistic->clear();
		cboStatistic->addItems(statistics);
		cboStatistic->setEnabled(true);
		cboStatistic->setCurrentIndex(qMin<int>(currentIndex, cboStatistic->count()-1));

		minSize->setEnabled(true);
		maxSize->setEnabled(true);
	}
	else if(cboVariable->currentText() == "Fixed")
	{
		lblFactor->setText("Width (in pixels):");
		spinFactor->setRange(0.0, 2000.0);
		spinFactor->setDecimals(0);
		spinFactor->setEnabled(true);

		cboStatistic->setEnabled(false);
		minSize->setEnabled(false);
		maxSize->setEnabled(false);
	}
	else if(cboVariable->currentText() == "Leaf node span")
	{
		lblFactor->setText("Percentage:");
		spinFactor->setRange(0.0, 100.0);
		spinFactor->setDecimals(1);
		spinFactor->setEnabled(true);

		QStringList statistics;
		statistics << "Total";
		cboStatistic->clear();
		cboStatistic->addItems(statistics);
		cboStatistic->setEnabled(true);
		cboStatistic->setCurrentIndex(0);

		minSize->setEnabled(true);
		maxSize->setEnabled(true);
	}
	else if(cboVariable->currentText() == "Size variable")
	{
		lblFactor->setText("Scaling factor:");
		spinFactor->setRange(0.0, 2000.0);
		spinFactor->setDecimals(3);
		spinFactor->setEnabled(true);

		uint currentIndex = cboStatistic->currentIndex();
		QStringList statistics;
		statistics << "Maximum" << "Minimum" << "Mean" << "Median" << "Total";
		cboStatistic->clear();
		cboStatistic->addItems(statistics);
		cboStatistic->setEnabled(true);
		cboStatistic->setCurrentIndex(qMin<int>(currentIndex, cboStatistic->count()-1));

		minSize->setEnabled(true);
		maxSize->setEnabled(true);
	}

	cboVariable->blockSignals(false);
	cboStatistic->blockSignals(false);
	lblFactor->blockSignals(false);
	spinFactor->blockSignals(false);
}

void GUI::SetPhylogenyNodeFont()
{
	QFont nodeFont = ui.cboPhylogenyNodeFont->currentFont();

	bool bOK;
	int fontSize = ui.cboPhylogenyNodeFontSize->currentText().toInt(&bOK);
	if(bOK)
		nodeFont.setPointSize(fontSize);
	nodeFont.setBold(ui.tbPhylogenyNodeFontBold->isChecked());
	nodeFont.setItalic(ui.tbPhylogenyNodeFontItalics->isChecked());

	m_visualPhylogeny->SetNodeFont(nodeFont, ui.btnPhylogenyNodeLabelColor->currentColor());
}

void GUI::SetPhylogenyBranchFont()
{
	QFont branchFont = ui.cboPhylogenyBranchFont->currentFont();

	bool bOK;
	int fontSize = ui.cboPhylogenyBranchFontSize->currentText().toInt(&bOK);
	if(bOK)
		branchFont.setPointSize(fontSize);
	branchFont.setBold(ui.tbPhylogenyBranchFontBold->isChecked());
	branchFont.setItalic(ui.tbPhylogenyBranchFontItalics->isChecked());

	m_visualPhylogeny->SetBranchFont(branchFont, ui.btnPhylogenyBranchLabelColor->currentColor());
}

void GUI::SetPhylogenyScaleFont()
{
	QFont scaleFont = ui.cboPhylogenyScaleFont->currentFont();

	bool bOK;
	int fontSize = ui.cboPhylogenyScaleFontSize->currentText().toInt(&bOK);
	if(bOK)
		scaleFont.setPointSize(fontSize);
	scaleFont.setBold(ui.tbPhylogenyScaleFontBold->isChecked());
	scaleFont.setItalic(ui.tbPhylogenyScaleFontItalics->isChecked());

	m_visualPhylogeny->SetScaleFont(scaleFont, ui.btnPhylogenyScaleLabelColor->currentColor());
}

void GUI::SetPhylogenyScaleSignificantDigits(int signDigits)
{
	ui.spinPhylogenyScale->setDecimals(signDigits);
	ui.spinPhylogenyScale->setSingleStep(pow(10.0,-signDigits));  
	m_visualPhylogeny->SetScaleLength(ui.spinPhylogenyScale->value());
}

void GUI::SetPhylogenyCollapsedNodeProperties()
{
	// set GUI elements to appropriate states
	bool bRectangular = ui.cboPhylogenyCollapsedNodeShape->currentText() == "Rectangular";
	ui.cboPhylogenyVariableHeight->setEnabled(bRectangular);
	ui.cboPhylogenyStatisticHeight->setEnabled(bRectangular);
	ui.spinPhylogenyFactorHeight->setEnabled(bRectangular);
	ui.spinPhylogenyMinHeight->setEnabled(bRectangular);
	ui.spinPhylogenyMaxHeight->setEnabled(bRectangular);

	SetCollapsedLineGUI(ui.cboPhylogenyVariableTL, ui.cboPhylogenyStatisticTL, 
													ui.lblPhylogenyFactorLabelTL, ui.spinPhylogenyFactorTL,
													ui.spinPhylogenyMinTL, ui.spinPhylogenyMaxTL);

	SetCollapsedLineGUI(ui.cboPhylogenyVariableML, ui.cboPhylogenyStatisticML, 
													ui.lblPhylogenyFactorLabelML, ui.spinPhylogenyFactorML,
													ui.spinPhylogenyMinML, ui.spinPhylogenyMaxML);

	SetCollapsedLineGUI(ui.cboPhylogenyVariableBL, ui.cboPhylogenyStatisticBL, 
													ui.lblPhylogenyFactorLabelBL, ui.spinPhylogenyFactorBL,
													ui.spinPhylogenyMinBL, ui.spinPhylogenyMaxBL);

	SetCollapsedLineGUI(ui.cboPhylogenyVariableHeight, ui.cboPhylogenyStatisticHeight, 
													ui.lblPhylogenyFactorLabelHeight, ui.spinPhylogenyFactorHeight,
													ui.spinPhylogenyMinHeight, ui.spinPhylogenyMaxHeight);
					

	// get collapsed node properties
	VisualNode::CollapsedProp collapsedProp;
	if(ui.cboPhylogenyCollapsedNodeShape->currentText() == "Rectangular")
		collapsedProp.shape = VisualNode::COLLAPSED_RECTANGULAR;
	else
		collapsedProp.shape = VisualNode::COLLAPSED_TRIANGULAR;

	collapsedProp.bShowLabels = ui.chkPhylogenyCollapsedShowLabels->isChecked();
	collapsedProp.bAbundanceInLabel = ui.chkPhylogenyAbundanceInLabel->isChecked();

	if(ui.cboPhylogenyGradientStyle->currentText() == "Continuous")
		collapsedProp.gradientStyle = VisualNode::COLLAPSED_GRADIENT_CONTINUOUS;
	else if(ui.cboPhylogenyGradientStyle->currentText() == "Discrete")
		collapsedProp.gradientStyle = VisualNode::COLLAPSED_GRADIENT_DISCRETE;
	else
		collapsedProp.gradientStyle = VisualNode::COLLAPSED_GRADIENT_SINGLE_COLOR;

	collapsedProp.gradientColor = ui.btnPhylogenyGradientSingleColor->currentColor();
	
	if(ui.cboPhylogenyGradientFill->currentText() == "Top half")
		collapsedProp.gradientFill = VisualNode::COLLAPSED_TOP_HALF;
	else
		collapsedProp.gradientFill = VisualNode::COLLAPSED_FULL;
	
	collapsedProp.topLine = GetCollapsedLineProp(ui.cboPhylogenyVariableTL, 
																								ui.cboPhylogenyStatisticTL,
																								ui.spinPhylogenyFactorTL,
																								ui.spinPhylogenyMinTL,
																								ui.spinPhylogenyMaxTL);

	collapsedProp.middleLine = GetCollapsedLineProp(ui.cboPhylogenyVariableML, 
																								ui.cboPhylogenyStatisticML,
																								ui.spinPhylogenyFactorML,
																								ui.spinPhylogenyMinML,
																								ui.spinPhylogenyMaxML);

	collapsedProp.bottomLine = GetCollapsedLineProp(ui.cboPhylogenyVariableBL, 
																								ui.cboPhylogenyStatisticBL,
																								ui.spinPhylogenyFactorBL,
																								ui.spinPhylogenyMinBL,
																								ui.spinPhylogenyMaxBL);

	collapsedProp.heightLine = GetCollapsedLineProp(ui.cboPhylogenyVariableHeight, 
																								ui.cboPhylogenyStatisticHeight,
																								ui.spinPhylogenyFactorHeight,
																								ui.spinPhylogenyMinHeight,
																								ui.spinPhylogenyMaxHeight);

	m_visualPhylogeny->SetCollapsedNodeProperties(collapsedProp);
}

void GUI::SetPhylogenyBranchColorStyle()
{
	if(ui.cboPhylogenyBranchColorStyle->currentText() == "Single colour")
		ui.btnPhylogenyBranchColor->setEnabled(true);
	else
		ui.btnPhylogenyBranchColor->setEnabled(false);

	m_visualPhylogeny->SetBranchColorStyle(ui.cboPhylogenyBranchColorStyle->currentText(), ui.btnPhylogenyBranchColor->currentColor());
}

void GUI::SetPhylogenyNodeColorStyle()
{
	if(ui.cboPhylogenyNodeColorStyle->currentText() == "Single colour")
		ui.btnPhylogenyNodeColor->setEnabled(true);
	else
		ui.btnPhylogenyNodeColor->setEnabled(false);

	m_visualPhylogeny->SetNodeColorStyle(ui.cboPhylogenyNodeColorStyle->currentText(), ui.btnPhylogenyNodeColor->currentColor());
}

void GUI::SetPhylogenyNodeShapeStyle()
{
	if(ui.cboPhylogenyNodeShapeStyle->currentText() == "Single shape")
		ui.cboPhylogenyNodeShape->setEnabled(true);
	else
		ui.cboPhylogenyNodeShape->setEnabled(false);

	m_visualPhylogeny->SetNodeShapeStyle(ui.cboPhylogenyNodeShapeStyle->currentText(), ui.cboPhylogenyNodeShape->currentText());
}

void GUI::SetPhylogenyNodeSizeStyle()
{
	if(ui.cboPhylogenyNodeSizeStyle->currentText() == "Single size")
	{
		ui.spinPhylogenyLeafNodeSize->setEnabled(true);
		ui.spinPhylogenyInternalNodeSize->setEnabled(true);
	}
	else
	{
		ui.spinPhylogenyLeafNodeSize->setEnabled(false);
		ui.spinPhylogenyInternalNodeSize->setEnabled(false);
	}

	m_visualPhylogeny->SetNodeSizeStyle(ui.cboPhylogenyNodeSizeStyle->currentText(),
																			ui.spinPhylogenyLeafNodeSize->value(), 
																				ui.spinPhylogenyInternalNodeSize->value());	
}

void GUI::PhylogenySearch()
{
	QString searchStr = ui.txtPhylogenySearchString->text();
	QString searchType = ui.cboPhylogenySearchType->currentText();

	QStringList results = m_visualPhylogeny->FindNodeLabels(searchStr, searchType);

	ui.listPhylogenySearchResults->clear();
	ui.listPhylogenySearchResults->addItems(results);
}

void GUI::PhylogenyCalculateParsimonyScore()
{
	m_visualPhylogeny->CalculateParsimonyScore(ui.cboPhylogenyParsimony->currentText());	
}

void GUI::PhylogenyAutoCollapse()
{
	m_visualPhylogeny->CollapseNodes(m_phylogenyAutoCollapseDlg->GetCollapseVariable(), m_phylogenyAutoCollapseDlg->GetCollapseConstraint());
}

void GUI::SetClusterTreeNodeFont()
{
	QFont nodeFont = ui.cboClusterTreeNodeFont->currentFont();

	bool bOK;
	int fontSize = ui.cboClusterTreeNodeFontSize->currentText().toInt(&bOK);
	if(bOK)
		nodeFont.setPointSize(fontSize);
	nodeFont.setBold(ui.tbClusterTreeNodeFontBold->isChecked());
	nodeFont.setItalic(ui.tbClusterTreeNodeFontItalics->isChecked());

	m_visualClusterTree->SetNodeFont(nodeFont, ui.btnClusterTreeNodeLabelColor->currentColor());
}

void GUI::SetClusterTreeBranchFont()
{
	QFont branchFont = ui.cboClusterTreeBranchFont->currentFont();

	bool bOK;
	int fontSize = ui.cboClusterTreeBranchFontSize->currentText().toInt(&bOK);
	if(bOK)
		branchFont.setPointSize(fontSize);
	branchFont.setBold(ui.tbClusterTreeBranchFontBold->isChecked());
	branchFont.setItalic(ui.tbClusterTreeBranchFontItalics->isChecked());

	m_visualClusterTree->SetBranchFont(branchFont, ui.btnClusterTreeBranchLabelColor->currentColor());
}

void GUI::SetClusterTreeScaleFont()
{
	QFont scaleFont = ui.cboClusterTreeScaleFont->currentFont();

	bool bOK;
	int fontSize = ui.cboClusterTreeScaleFontSize->currentText().toInt(&bOK);
	if(bOK)
		scaleFont.setPointSize(fontSize);
	scaleFont.setBold(ui.tbClusterTreeScaleFontBold->isChecked());
	scaleFont.setItalic(ui.tbClusterTreeScaleFontItalics->isChecked());

	m_visualClusterTree->SetScaleFont(scaleFont, ui.btnClusterTreeScaleLabelColor->currentColor());
}

void GUI::SetClusterTreeScaleSignificantDigits(int signDigits)
{
	ui.spinClusterTreeScale->setDecimals(signDigits);
	ui.spinClusterTreeScale->setSingleStep(pow(10.0,-signDigits));  
	m_visualClusterTree->SetScaleLength(ui.spinClusterTreeScale->value());
}

void GUI::SetClusterTreeCollapsedNodeProperties()
{
	// set GUI elements to appropriate states
	bool bRectangular = ui.cboClusterTreeCollapsedNodeShape->currentText() == "Rectangular";
	ui.cboClusterTreeVariableHeight->setEnabled(bRectangular);
	ui.cboClusterTreeStatisticHeight->setEnabled(bRectangular);
	ui.spinClusterTreeFactorHeight->setEnabled(bRectangular);
	ui.spinClusterTreeMinHeight->setEnabled(bRectangular);
	ui.spinClusterTreeMaxHeight->setEnabled(bRectangular);

	SetCollapsedLineGUI(ui.cboClusterTreeVariableTL, ui.cboClusterTreeStatisticTL, 
													ui.lblClusterTreeFactorLabelTL, ui.spinClusterTreeFactorTL,
													ui.spinClusterTreeMinTL, ui.spinClusterTreeMaxTL);

	SetCollapsedLineGUI(ui.cboClusterTreeVariableML, ui.cboClusterTreeStatisticML, 
													ui.lblClusterTreeFactorLabelML, ui.spinClusterTreeFactorML,
													ui.spinClusterTreeMinML, ui.spinClusterTreeMaxML);

	SetCollapsedLineGUI(ui.cboClusterTreeVariableBL, ui.cboClusterTreeStatisticBL, 
													ui.lblClusterTreeFactorLabelBL, ui.spinClusterTreeFactorBL,
													ui.spinClusterTreeMinBL, ui.spinClusterTreeMaxBL);

	SetCollapsedLineGUI(ui.cboClusterTreeVariableHeight, ui.cboClusterTreeStatisticHeight, 
													ui.lblClusterTreeFactorLabelHeight, ui.spinClusterTreeFactorHeight,
													ui.spinClusterTreeMinHeight, ui.spinClusterTreeMaxHeight);
					

	// get collapsed node properties
	VisualNode::CollapsedProp collapsedProp;
	if(ui.cboClusterTreeCollapsedNodeShape->currentText() == "Rectangular")
		collapsedProp.shape = VisualNode::COLLAPSED_RECTANGULAR;
	else
		collapsedProp.shape = VisualNode::COLLAPSED_TRIANGULAR;

	collapsedProp.bShowLabels = ui.chkClusterTreeCollapsedShowLabels->isChecked();
	collapsedProp.bAbundanceInLabel = ui.chkClusterTreeAbundanceInLabel->isChecked();

	if(ui.cboClusterTreeGradientStyle->currentText() == "Continuous")
		collapsedProp.gradientStyle = VisualNode::COLLAPSED_GRADIENT_CONTINUOUS;
	else if(ui.cboClusterTreeGradientStyle->currentText() == "Discrete")
		collapsedProp.gradientStyle = VisualNode::COLLAPSED_GRADIENT_DISCRETE;
	else
		collapsedProp.gradientStyle = VisualNode::COLLAPSED_GRADIENT_SINGLE_COLOR;

	collapsedProp.gradientColor = ui.btnClusterTreeGradientSingleColor->currentColor();
	
	if(ui.cboClusterTreeGradientFill->currentText() == "Top half")
		collapsedProp.gradientFill = VisualNode::COLLAPSED_TOP_HALF;
	else
		collapsedProp.gradientFill = VisualNode::COLLAPSED_FULL;
	
	collapsedProp.topLine = GetCollapsedLineProp(ui.cboClusterTreeVariableTL, 
																								ui.cboClusterTreeStatisticTL,
																								ui.spinClusterTreeFactorTL,
																								ui.spinClusterTreeMinTL,
																								ui.spinClusterTreeMaxTL);

	collapsedProp.middleLine = GetCollapsedLineProp(ui.cboClusterTreeVariableML, 
																								ui.cboClusterTreeStatisticML,
																								ui.spinClusterTreeFactorML,
																								ui.spinClusterTreeMinML,
																								ui.spinClusterTreeMaxML);

	collapsedProp.bottomLine = GetCollapsedLineProp(ui.cboClusterTreeVariableBL, 
																								ui.cboClusterTreeStatisticBL,
																								ui.spinClusterTreeFactorBL,
																								ui.spinClusterTreeMinBL,
																								ui.spinClusterTreeMaxBL);

	collapsedProp.heightLine = GetCollapsedLineProp(ui.cboClusterTreeVariableHeight, 
																								ui.cboClusterTreeStatisticHeight,
																								ui.spinClusterTreeFactorHeight,
																								ui.spinClusterTreeMinHeight,
																								ui.spinClusterTreeMaxHeight);

	m_visualClusterTree->SetCollapsedNodeProperties(collapsedProp);
}

void GUI::SetClusterTreeBranchColorStyle()
{
	if(ui.cboClusterTreeBranchColorStyle->currentText() == "Single colour")
		ui.btnClusterTreeBranchColor->setEnabled(true);
	else
		ui.btnClusterTreeBranchColor->setEnabled(false);

	m_visualClusterTree->SetBranchColorStyle(ui.cboClusterTreeBranchColorStyle->currentText(), ui.btnClusterTreeBranchColor->currentColor());
}

void GUI::SetClusterTreeNodeColorStyle()
{
	if(ui.cboClusterTreeNodeColorStyle->currentText() == "Single colour")
		ui.btnClusterTreeNodeColor->setEnabled(true);
	else
		ui.btnClusterTreeNodeColor->setEnabled(false);

	m_visualClusterTree->SetNodeColorStyle(ui.cboClusterTreeNodeColorStyle->currentText(), ui.btnClusterTreeNodeColor->currentColor());
}

void GUI::SetClusterTreeNodeShapeStyle()
{
	if(ui.cboClusterTreeNodeShapeStyle->currentText() == "Single shape")
		ui.cboClusterTreeNodeShape->setEnabled(true);
	else
		ui.cboClusterTreeNodeShape->setEnabled(false);

	m_visualClusterTree->SetNodeShapeStyle(ui.cboClusterTreeNodeShapeStyle->currentText(), ui.cboClusterTreeNodeShape->currentText());
}

void GUI::SetClusterTreeNodeSizeStyle()
{
	if(ui.cboClusterTreeNodeSizeStyle->currentText() == "Single size")
	{
		ui.spinClusterTreeLeafNodeSize->setEnabled(true);
		ui.spinClusterTreeInternalNodeSize->setEnabled(true);
	}
	else
	{
		ui.spinClusterTreeLeafNodeSize->setEnabled(false);
		ui.spinClusterTreeInternalNodeSize->setEnabled(false);
	}

	m_visualClusterTree->SetNodeSizeStyle(ui.cboClusterTreeNodeSizeStyle->currentText(), 
																			ui.spinClusterTreeLeafNodeSize->value(), 
																				ui.spinClusterTreeInternalNodeSize->value());	
}

void GUI::ClusterTreeSearch()
{
	QString searchStr = ui.txtClusterTreeSearchString->text();
	QString searchType = ui.cboClusterTreeSearchType->currentText();

	QStringList results = m_visualClusterTree->FindNodeLabels(searchStr, searchType);

	ui.listClusterTreeSearchResults->clear();
	ui.listClusterTreeSearchResults->addItems(results);
}

void GUI::ClusterTreeCalculateParsimonyScore()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	m_visualClusterTree->CalculateParsimonyScore(ui.cboClusterTreeParsimony->currentText());	

	QApplication::restoreOverrideCursor();
}

void GUI::ClusterTreeAutoCollapse()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	m_visualClusterTree->CollapseNodes(m_phylogenyAutoCollapseDlg->GetCollapseVariable(), m_phylogenyAutoCollapseDlg->GetCollapseConstraint());

	QApplication::restoreOverrideCursor();
}

void GUI::ClusterTreeRun()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	if(m_activeSystem == m_splitSystem)
	{
		m_uniSplit->Jackknife(m_clusterTreeAnalysisDlg->GetClusteringMethod(),
																	m_clusterTreeAnalysisDlg->GetNumberIterations(), 
																	m_clusterTreeAnalysisDlg->GetSeqToRetain());

		m_visualClusterTree->SetOriginalTree(m_uniSplit->GetClusterTree());
		m_visualClusterTree->SetTree(m_uniSplit->GetClusterTree()->Clone());
	}
	else
	{
		// get name of each sample
		QStringList orderedLabels = m_activeSystem->GetSamples()->GetActiveSampleNames();

		// perform clustering of original data
		Tree<VisualNode>* clusterTree = m_uniSplit->GetClusterTree();
		Cluster::Clustering(m_clusterTreeAnalysisDlg->GetClusteringMethod(), 
														m_distMatrixSystem->GetMatrix(), 
														orderedLabels, *clusterTree);

		// At this point, the leaf nodes will be labelled 0 to <number of samples-1>.
		// However, they will not correspond correctly to the actual sample id of
		// each leaf node so here we reset the sample ids.
		QList<VisualNode*> leaves = clusterTree->GetLeaves();
		foreach(VisualNode* leaf, leaves)
		{
			Sample sample;
			uint sampleId;
			if(m_activeSystem->GetSamples()->GetSample(leaf->GetName(), sample))
				sampleId = sample.GetId();
			else
				Log::Inst().Error("Invalid sample specified when performing jackknifing: " + leaf->GetName());

			leaf->SetId(sampleId);
		}

		// calculate the cophenetic correlation between the distance matrix and resulting cophenetic matrix
		double corr = Cluster::CopheneticCorrelation(m_distMatrixSystem->GetMatrix(), *clusterTree);
		Log::Inst().Write("Cophenetic correlation = " + QString::number(corr));

		m_visualClusterTree->SetOriginalTree(clusterTree);
		m_visualClusterTree->SetTree(clusterTree->Clone());
	}

	ClusterTreeCalculateParsimonyScore();

	if(ui.tabWidget->tabText(ui.tabWidget->currentIndex()) == "Cluster tree")
		m_visualClusterTree->SetSelectedLeafNodes();

	QApplication::restoreOverrideCursor();
}

void GUI::SetMetadataValues()
{
	QString field = ui.cboMetadataField->currentText();
	QVector<QString> values = m_activeSystem->GetSamples()->GetMetadata()->GetValues(field);

	QSet<QString> uniqueValues;
	foreach(const QString& value, values)
		uniqueValues.insert(value);

	QStringList unqieValueList = uniqueValues.toList();

	if(m_activeSystem->GetSamples()->GetMetadata()->GetDatatype(field) == Metadata::NUMERICAL_DATA)
		qSort(unqieValueList.begin(), unqieValueList.end(), numericStrLessThan);
	else
		qSort(unqieValueList.begin(), unqieValueList.end(), caseInsensitiveLessThan);

	ui.cboMetadataValue->clear();
	ui.cboMetadataValue->addItems(unqieValueList);
}

void GUI::SetMetadataAll()
{
	m_activeSystem->GetSamples()->SetAllSamplesToActive();
}

void GUI::SetMetadataRemoveAll()
{
	m_activeSystem->GetSamples()->SetAllSamplesToInactive();
}

void GUI::SetMetadataSelectedSamples()
{
	m_activeSystem->GetSamples()->SetSelectedSamplesToActive();
}

void GUI::SetMetadataFiltered()
{	
	m_activeSystem->GetSamples()->FilterActiveSamples(ui.cboMetadataAddRemove->currentText(),
																										ui.cboMetadataField->currentText(),
																										ui.cboMetadataRelationship->currentText(),
																										ui.cboMetadataValue->currentText());
}

void GUI::SetNewTab()
{	
	QString currentTab = ui.tabWidget->tabText(ui.tabWidget->currentIndex());
	if(currentTab == "Log")
		return;

	// *** Run updates required due to leaving a tab	
	if(m_previousTab == "Sample metadata")
	{
		if(m_activeSystem && m_activeSystem->GetSamples()->IsActiveSetChanged())
			RestoreActiveSampleTree();
	}
	else if(m_previousTab == "Phylogeny")
		m_visualPhylogeny->UpdateSelectedNodes();
	else if(m_previousTab == "Cluster tree")
		m_visualClusterTree->UpdateSelectedNodes();

	// Check if we need to update calculations since the active sample set has changed.
	if(m_activeSystem && m_activeSystem->GetSamples()->IsActiveSetChanged())
	{
		m_activeSystem->GetSamples()->SaveActiveSet();
		m_uniSplit->Run();
		RunDissimilarityMatrixAnalyses();
	}	
		
	// *** Run updates required due to entering a tab
	m_statusBarTabInfo.setText("");
	if(currentTab == "Sample metadata")
	{
		if(m_activeSystem)
		{
			m_activeSystem->GetSamples()->SaveActiveSet();	
			m_activeSystem->GetSamples()->GetMetadata()->SetSelectedRows();
		}
	}
	else if(currentTab == "Phylogeny")
	{
		m_statusBarTabInfo.setText(m_visualPhylogeny->GetMethodMessage());
		m_visualPhylogeny->SetSelectedLeafNodes();
	}
	else if(currentTab == "Ordination plots")
	{
		m_statusBarTabInfo.setText(m_ordinationPlots->GetMethodMessage());
		m_ordinationPlots->UpdateMarkers();
	}
	else if(currentTab == "Parallel coordinate plot")
	{
		m_statusBarTabInfo.setText(m_ordinationPlots->GetMethodMessage());
		m_parallelCoordPlot->UpdateMarkers();	
	}
	else if(currentTab == "Cluster tree")
	{
		m_statusBarTabInfo.setText(m_visualClusterTree->GetMethodMessage());
		m_visualClusterTree->SetSelectedLeafNodes();
	}
	else if(currentTab == "Dissimilarity matrix plot")
	{
		m_statusBarTabInfo.setText(m_visualMatrix->GetSortingMethod());
		m_visualMatrix->update();	// need to update drawing to reflect selected samples
	}

	m_previousTab = currentTab;
}

void GUI::UpdateSelectionSet()
{
	QString currentTab = ui.tabWidget->tabText(ui.tabWidget->currentIndex());
	if(currentTab == "Sample metadata")
	{
		if(m_activeSystem)
			m_activeSystem->GetSamples()->GetMetadata()->SetSelectedRows();
	}
	else if(currentTab == "Phylogeny")
		m_visualPhylogeny->SetSelectedLeafNodes();
	else if(currentTab == "Ordination plots")
		m_ordinationPlots->UpdateMarkers();
	else if(currentTab == "Parallel coordinate plot")
		m_parallelCoordPlot->UpdateMarkers();	
	else if(currentTab == "Cluster tree")
		m_visualClusterTree->SetSelectedLeafNodes();
	else if(currentTab == "Dissimilarity matrix plot")
		m_visualMatrix->update();	
}

void GUI::SetPhylogenyLeafTreatment()
{
	QString leafTreatmentStr = ui.cboPhylogenyLeafTreatment->currentText();

	VisualTree::LEAF_TREATMENT leafTreatment;
	if(leafTreatmentStr == "Relative proportion")
		leafTreatment = VisualTree::RELATIVE_PROPORITON_TREATMENT;
	else if(leafTreatmentStr == "Unweighted")
		leafTreatment = VisualTree::UNWEIGHTED_TREATMENT;
	else  if(leafTreatmentStr == "Weighted")
		leafTreatment = VisualTree::WEIGHTED_TREATMENT;

	m_visualPhylogeny->SetLeafTreatment(leafTreatment);

	if(ui.tabWidget->tabText(ui.tabWidget->currentIndex()) == "Phylogeny")
		m_statusBarTabInfo.setText(m_visualPhylogeny->GetMethodMessage());

	QString message;
	if(m_activeSystem == m_splitSystem)
	{
		message = "Samples = " 
								+ QString::number(m_activeSystem->GetSamples()->GetActiveSampleIds().size())
								+ ", Splits = " 
								+ QString::number(m_splitSystem->GetNumSplits())
								+ ", Sequences = " 
								+ QString::number(m_activeSystem->GetSamples()->GetSequences()->GetNumActiveSequences(m_visualPhylogeny->GetLeafTreatment() != VisualTree::UNWEIGHTED_TREATMENT));			
	}
	else
	{
		message = "Samples = " 
								+ QString::number(m_activeSystem->GetSamples()->GetActiveSampleIds().size())
								+ ", Sequences = " 
								+ QString::number(m_activeSystem->GetSamples()->GetSequences()->GetNumActiveSequences(m_visualPhylogeny->GetLeafTreatment() != VisualTree::UNWEIGHTED_TREATMENT));	
	}
	m_statusBarTreeInfo.setText(message);
}

void GUI::SetPhylogenyAbundanceStyle()
{
	QString abundanceStyleStr = ui.cboPhylogenyAbundanceStyle->currentText();

	VisualTree::ABUNDANCE_STYLE abundanceStyle;
	if(abundanceStyleStr == "<none>" || abundanceStyleStr == "Stacked bar charts")
		abundanceStyle = VisualTree::ABUNDANCE_NONE;
	else if(abundanceStyleStr == "Pie charts")
		abundanceStyle = VisualTree::ABUNDANCE_PIE_CHART;
	else if(abundanceStyleStr == "Pie charts (leaves only)")
		abundanceStyle = VisualTree::ABUNDANCE_PIE_CHART_LEAVES_ONLY;
	else if(abundanceStyleStr == "Collapsed leaf nodes")
		abundanceStyle = VisualTree::ABUNDANCE_COLLAPSED_LEAVES;
	else if(abundanceStyleStr == "Label only")
		abundanceStyle = VisualTree::ABUNDANCE_LABELS_ONLY;
	
	m_visualPhylogeny->SetAbundanceStyle(abundanceStyle, 
																				ui.spinPhylogenyAbundanceMinSize->value(),
																				ui.spinPhylogenyAbundanceMaxSize->value());
}

void GUI::SetPhylogenyBranchStyle()
{
	QString branchStlyeText = ui.cboPhylogenyBranchStyle->currentText();

	VisualTree::BRANCH_STYLE branchStyle;
	if(branchStlyeText == "Phylogram")
		branchStyle = VisualTree::PHYLOGRAM_BRANCHES;
	else if(branchStlyeText == "Cladogram")
		branchStyle = VisualTree::CLADOGRAM_BRANCHES;
	else if(branchStlyeText == "Equal")
		branchStyle = VisualTree::EQUAL_BRANCHES;

	m_visualPhylogeny->SetBranchStyle(branchStyle);

	if(ui.tabWidget->tabText(ui.tabWidget->currentIndex()) == "Phylogeny")
		m_statusBarTabInfo.setText(m_visualPhylogeny->GetMethodMessage());
}

void GUI::SetClusterTreeBranchStyle()
{
	QString branchStlyeText = ui.cboClusterTreeBranchStyle->currentText();

	VisualTree::BRANCH_STYLE branchStyle;
	if(branchStlyeText == "Phylogram")
		branchStyle = VisualTree::PHYLOGRAM_BRANCHES;
	else if(branchStlyeText == "Cladogram")
		branchStyle = VisualTree::CLADOGRAM_BRANCHES;
	else if(branchStlyeText == "Equal")
		branchStyle = VisualTree::EQUAL_BRANCHES;

	m_visualClusterTree->SetBranchStyle(branchStyle);

	if(ui.tabWidget->tabText(ui.tabWidget->currentIndex()) == "Cluster tree")
		m_statusBarTabInfo.setText(m_visualClusterTree->GetMethodMessage());
}

void GUI::SetDissimilarityMatrixRange()
{
	m_visualMatrix->SetColorMapRange(ui.chkDissimilarityMatrixFullRange->isChecked());
}

void GUI::SetDissimilarityMatrixThresholded()
{
	m_visualMatrix->SetColorMapThreshold(ui.chkDissimilarityMatrixThreshold->isChecked());
}

void GUI::RunDissimilarityMatrixSort()
{
	if(ui.cboDissimilarityMatrixSortMethod->currentText() == "Side-to-side")
		m_visualMatrix->Sort(VisualMatrix::SIDE_TO_SIDE);
	else if(ui.cboDissimilarityMatrixSortMethod->currentText() == "Neighbourhood")
		m_visualMatrix->Sort(VisualMatrix::NEIGHBOURHOOD);
	else if(ui.cboDissimilarityMatrixSortMethod->currentText() == "Simulated annealing")
		m_visualMatrix->Sort(VisualMatrix::SIMULATED_ANNEALING);
	else if(ui.cboDissimilarityMatrixSortMethod->currentText() == "Randomize")
		m_visualMatrix->Sort(VisualMatrix::RANDOMIZE);

	if(ui.tabWidget->tabText(ui.tabWidget->currentIndex()) == "Dissimilarity matrix plot")
		m_statusBarTabInfo.setText(m_visualMatrix->GetSortingMethod());
}

void GUI::SetDissimilarityColorMap(const QString& colorMapName)
{
	m_visualMatrix->SetColorMap(colorMapName);
}

void GUI::SetDissimilarityMatrixMinCellSize(int size)
{
	m_visualMatrix->SetMinCellSize(size);
}

void GUI::UpdateDissimilarityMatrix()
{
	m_visualMatrix->update();
}

void GUI::RestoreActiveSampleTree()
{
	m_visualPhylogeny->RestoreActiveSampleTree();

	QString message;
	if(m_activeSystem == m_splitSystem)
	{
		message = "Samples = " 
									+ QString::number(m_activeSystem->GetSamples()->GetActiveSampleIds().size())
									+ ", Splits = " 
									+ QString::number(m_splitSystem->GetNumSplits())
									+ ", Sequences = " 
									+ QString::number(m_activeSystem->GetSamples()->GetSequences()->GetNumActiveSequences(m_visualPhylogeny->GetLeafTreatment() != VisualTree::UNWEIGHTED_TREATMENT));
	}
	else
	{
		message = "Samples = " 
									+ QString::number(m_activeSystem->GetSamples()->GetActiveSampleIds().size())
									+ ", Sequences = " 
									+ QString::number(m_activeSystem->GetSamples()->GetSequences()->GetNumActiveSequences(m_visualPhylogeny->GetLeafTreatment() != VisualTree::UNWEIGHTED_TREATMENT));
	}
	m_statusBarTreeInfo.setText(message);
}

void GUI::ProjectToSelectedLeaves()
{
	m_visualPhylogeny->ProjectToSelectedLeaves();

	QString message;
	if(m_activeSystem == m_splitSystem)
	{
		message = "Samples = " 
									+ QString::number(m_activeSystem->GetSamples()->GetActiveSampleIds().size())
									+ ", Splits = " 
									+ QString::number(m_splitSystem->GetNumSplits())
									+ ", Sequences = " 
									+ QString::number(m_activeSystem->GetSamples()->GetSequences()->GetNumActiveSequences(m_visualPhylogeny->GetLeafTreatment() != VisualTree::UNWEIGHTED_TREATMENT));
	}
	else
	{
		message = "Samples = " 
									+ QString::number(m_activeSystem->GetSamples()->GetActiveSampleIds().size())
									+ ", Sequences = " 
									+ QString::number(m_activeSystem->GetSamples()->GetSequences()->GetNumActiveSequences(m_visualPhylogeny->GetLeafTreatment() != VisualTree::UNWEIGHTED_TREATMENT));
	}			
	m_statusBarTreeInfo.setText(message);
}

void GUI::SetUsePhylogenySpecificMetadata()
{
	ui.txtPhylogenySeqMetadataFile->setEnabled(ui.chkPhylogenySeqMetadata->isChecked());
	ui.tbPhylogenyBrowseSeqMetadataFile->setEnabled(ui.chkPhylogenySeqMetadata->isChecked());
	ui.cboPhylogenySeqMetadataCategories->setEnabled(ui.chkPhylogenySeqMetadata->isChecked());
	ui.cboPhylogenySeqMetadataColorMap->setEnabled(ui.chkPhylogenySeqMetadata->isChecked());

	m_visualPhylogeny->SetUseSequenceMetadata(ui.chkPhylogenySeqMetadata->isChecked());
}

void GUI::SetPhylogenyMetadataFile()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open sequence metadata...", "", 
																										"Metadata files (*.txt *.tsv);;All files (*.*)");

	if(!filename.isEmpty())
	{
		QString file = filename.mid(filename.lastIndexOf('/')+1);
		ui.txtPhylogenySeqMetadataFile->setText(file);

		SeqMetadataPtr metadata = m_visualPhylogeny->GetSeqMetadata();	

		QObject::disconnect(metadata.data(), SIGNAL(ColorMapChanged(const QMap<QString, QColor>&, const QMap<QString, float>&, bool)), 
																		m_phylogenySeqLegendDlg, SLOT(SetLegend(const QMap<QString, QColor>&, const QMap<QString, float>&, bool)));
		QObject::connect(metadata.data(), SIGNAL(ColorMapChanged(const QMap<QString, QColor>&, const QMap<QString, float>&, bool)), 
																		m_phylogenySeqLegendDlg, SLOT(SetLegend(const QMap<QString, QColor>&, const QMap<QString, float>&, bool)));

		QObject::disconnect(m_phylogenySeqLegendDlg, SIGNAL(Changed()), 
																		this, SLOT(CustomPhylogenyColorMap()));
		QObject::connect(m_phylogenySeqLegendDlg, SIGNAL(Changed()), 
																		this, SLOT(CustomPhylogenyColorMap()));
		
		bool bLoaded = metadata->Load(filename);
		if(bLoaded)
			ui.cboPhylogenySeqMetadataCategories->addItems(metadata->GetFields());
	}
}

void GUI::SetPhylogenyColorMap()
{
	if(ui.cboPhylogenySeqMetadataColorMap->currentText() != "<custom>")
		ui.cboPhylogenySeqMetadataColorMap->removeItem(ui.cboPhylogenySeqMetadataColorMap->findText("<custom>"));

	m_visualPhylogeny->SetPhylogenyMetadataColorMap(ui.cboPhylogenySeqMetadataColorMap->currentText());
}


void GUI::CustomPhylogenyColorMap()
{
	if(ui.cboPhylogenySeqMetadataColorMap->currentText() == "<custom>")
		SetPhylogenyColorMap();	// there is a new custom map
	else
	{
		ui.cboPhylogenySeqMetadataColorMap->addItem("<custom>");
		ui.cboPhylogenySeqMetadataColorMap->setCurrentIndex(ui.cboPhylogenySeqMetadataColorMap->findText("<custom>"));
		// this will call SetPhylogenyColorMap() since the index of the combobox changes
	}
}

void GUI::SetPhylogenyMetadataCategories()
{
	QString colorMapName = ui.cboPhylogenySeqMetadataColorMap->currentText();
	if(colorMapName == "<custom>")
	{
		// custom map will not be valid for new field, so set to default map
		colorMapName = "Ware (categorical - 9)";
		ui.cboPhylogenySeqMetadataColorMap->setCurrentIndex(ui.cboPhylogenySeqMetadataColorMap->findText(colorMapName));
	}

	m_visualPhylogeny->SetPhylogenyMetadataCategories(ui.cboPhylogenySeqMetadataCategories->currentText());
}

void GUI::SetPhylogenyOtherPercentage()
{
	m_visualPhylogeny->SetPhylogenyOtherPercentage(m_phylogenySeqLegendDlg->GetOtherPercentage());
}

void GUI::SetPlotBackgroundColor(const QColor& color)
{
	// ordination plots
	ui.ordinationPlotFrame->setAutoFillBackground(true);
	ui.ordinationPlotFrame->setPalette(color);
	ui.ordinationPlotFrame->repaint();

	m_ordinationPlots->SetBackgroundColor(color);

	// parallel coordination plots
	ui.parallelCoordinatePlotFrame->setAutoFillBackground(true);
	ui.parallelCoordinatePlotFrame->setPalette(color);
	ui.parallelCoordinatePlotFrame->repaint();

	m_parallelCoordPlot->SetBackgroundColor(color);

	// dissimilarity matrix plot
	m_visualMatrix->SetBackgroundColor(color);

	// resemlance scatterplot
	ui.resemblanceScatterplotFrame->setAutoFillBackground(true);
	ui.resemblanceScatterplotFrame->setPalette(color);
	ui.resemblanceScatterplotFrame->repaint();

	m_resemblanceScatterplot->SetBackgroundColor(color);

	// cluster tree viewport
	ui.clusterTreeViewport->SetBackgroundColor(color);

	// phylogeny viewport
	ui.phylogenyViewport->SetBackgroundColor(color);
}
