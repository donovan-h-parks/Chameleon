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

#ifndef GUI_H
#define GUI_H

#include "ui_gui.h"

#include "stdafx.h"

#include "VisualNode.hpp"

#include "DiversityMeasureDlg.hpp"
#include "AutoCollapseDlg.hpp"
#include "ClusterTreeAnalysisDlg.hpp"
#include "OrdinationAnalysisDlg.hpp"
#include "ProjectedCoordDlg.hpp"
#include "PropertiesDlg.hpp"
#include "SeqLegendDlg.hpp"
#include "PCoA.hpp"
#include "ISOMAP.hpp"
#include "NMDS.hpp"

class QwtPlot;
class OrdinationPlot;

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(QWidget *parent = 0, Qt::WFlags flags = 0);
	~GUI();

	void LoadData(const QString& phylogenyFile, const QString& distMatrixFile, const QString& sampleFile, 
										const QString& metadataFile, bool bImplicitlyRooted, bool bShowPhylogeny);

public slots:
	void SetLegendProperties();

	void InspectSequencesPerSample();
	void InspectSplitSystem();

	void SaveLog();
	void ClearLogWindow();

	void RunDiversityMeasure();
	void RunDistanceMatrix();

private slots:
	void OpenPhylogeny();
	void OpenDissimilarityMatrix();
	void SaveTable();
	void SaveRasterImage();
	void SaveColorLegend();
	void SaveShapeLegend();
	void SaveSizeLegend();
	void SavePhylogenyVector();
	void SavePC1vsPC2Vector();
	void SavePC3vsPC2Vector();
	void SavePC1vsPC3Vector();
	void SaveScreePlotVector();
	void SaveParallelCoordPlotVector();
	void SaveClusterTreeVector();
	void SaveDissMatrixPlotVector();
	void SaveResemblanceScatterplotVector();

	void UpdateSelectionSet();

	void ExportTreeInNewick();

	void RunResemblanceScatterplot();

	void RunDissimilarityMatrixSort();
	void SetDissimilarityMatrixRange();
	void SetDissimilarityMatrixThresholded();
	void SetDissimilarityColorMap(const QString& colorMapName);
	void SetDissimilarityMatrixMinCellSize(int size);
	void UpdateDissimilarityMatrix();

	void ShowSampleNames();
	void SetOrdinationSelectionTransparency();
	void SetParrallelCoordSelectionTransparency();
	void SetDissMatrixSelectionTransparency();
	void SetParallelCoordCurves();
	void SetFittedCurves();
	void ShowVarianceLabels();
	void SetNumDimensions();
	
	void ShowAboutDlg();

	void SetMetadataAll();
	void SetMetadataRemoveAll();
	void SetMetadataSelectedSamples();
	void SetMetadataFiltered();
	void SetMetadataValues();

	void SetNewTab();

	void RestoreActiveSampleTree();
	void ProjectToSelectedLeaves();

	// *** Phylogeny tree
	void SetPhylogenyLeafTreatment();
	void SetPhylogenyAbundanceStyle();
	void SetPhylogenyBranchStyle();
	void SetPhylogenyNodeFont();
	void SetPhylogenyBranchFont();
	void SetPhylogenyScaleFont();
	void SetPhylogenyCollapsedNodeProperties();
	void SetPhylogenyScaleSignificantDigits(int signDigits);
	void SetPhylogenyNodeColorStyle();
	void SetPhylogenyNodeShapeStyle();
	void SetPhylogenyNodeSizeStyle();
	void SetPhylogenyBranchColorStyle();
	
	void PhylogenyCalculateParsimonyScore();
	void PhylogenyAutoCollapse();

	// *** Cluster tree
	void SetClusterTreeBranchStyle();
	void SetClusterTreeNodeFont();
	void SetClusterTreeBranchFont();
	void SetClusterTreeScaleFont();
	void SetClusterTreeCollapsedNodeProperties();
	void SetClusterTreeScaleSignificantDigits(int signDigits);
	void SetClusterTreeNodeColorStyle();
	void SetClusterTreeNodeShapeStyle();
	void SetClusterTreeNodeSizeStyle();
	void SetClusterTreeBranchColorStyle();
	
	void ClusterTreeCalculateParsimonyScore();
	void ClusterTreeAutoCollapse();

	void SetUsePhylogenySpecificMetadata();
	void SetPhylogenyMetadataFile();

	void SetPlotBackgroundColor(const QColor& color);
		
private slots:
	void PopulateBoxPlot();

	void PhylogenySearch();
	void ClusterTreeSearch();
	void ClusterTreeRun();

	void RunDissimilarityMatrixAnalyses();

	void CustomPhylogenyColorMap();
	void SetPhylogenyColorMap();
	void SetPhylogenyMetadataCategories();
	void SetPhylogenyOtherPercentage();

private:
	enum TABLE_HEADERS { RowHeaders, ColumnHeaders, ColumnAndRowHeaders, NoHeaders };

	void PopulateTable(QTableWidget* table, const Matrix& matrix, const QStringList& rowHeaders, const QStringList& colHeaders);
	
	void SaveRasterImageWidget(QWidget* widget);
	void SaveRasterImageScene(QGraphicsScene* scene);

	void SaveVectorScene(QGraphicsScene* scene);
	void SaveVectorPlot(QwtPlot* plot);

	VisualNode::CollapsedLineProp  GetCollapsedLineProp(QComboBox* cboVariable, QComboBox* cboStatistic, 
																															QDoubleSpinBox* spinFactor, QSpinBox* spinMin, 
																															QSpinBox* spinMax);

	void SetCollapsedLineGUI(QComboBox* cboVariable, QComboBox* cboStatistic, QLabel* lblFactor, 
																	QDoubleSpinBox* spinFactor, QSpinBox* minSize, QSpinBox* maxSize);

	void InitPhylogeny();
	void InitClusterTree();

	void closeEvent(QCloseEvent *event);

	void WriteProperties();
	void ReadProperties();

private:
	Ui::GUIClass ui;

	QLabel m_statusBarTreeInfo;
	QLabel m_statusBarTabInfo;
	QLabel m_statusBarDiversityMeasureInfo;

	SplitSystemPtr m_splitSystem;
	MatrixSystemPtr m_distMatrixSystem;
	SystemPtr m_activeSystem;
	ColorMapsPtr m_colorMaps;
	UniSplitPtr m_uniSplit;
	LegendsPtr m_legends;

	PCoA m_pcoa;
	Isomap m_isomap;
	NMDS m_nmds;

	ParallelCoordPlotPtr m_parallelCoordPlot;
	OrdinationPlotsPtr m_ordinationPlots;
	ResemblanceScatterplotPtr m_resemblanceScatterplot;

	VisualPhylogenyPtr m_visualPhylogeny;
	VisualClusterTreePtr m_visualClusterTree;
	VisualMatrixPtr m_visualMatrix;

	DiversityMeasureDlg* m_diversityMeasureDlg;
	AutoCollapseDlg* m_phylogenyAutoCollapseDlg;
	AutoCollapseDlg* m_clusterTreeAutoCollapseDlg;
	ClusterTreeAnalysisDlg* m_clusterTreeAnalysisDlg;
	OrdinationAnalysisDlg* m_ordinationAnalysisDlg;
	ProjectedCoordDlg* m_projectedCoordDlg;
	PropertiesDlg* m_propertiesDlg;
	SeqLegendDlg* m_phylogenySeqLegendDlg;

	QString m_previousTab;
};

#endif // GUI_H
