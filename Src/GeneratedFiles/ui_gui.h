/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFontComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBox>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "OrdinationPlot.hpp"
#include "QtColorPicker.hpp"
#include "TreeViewport.hpp"
#include "qwt_legend.h"
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_GUIClass
{
public:
    QAction *mnuFileOpenPhylogeny;
    QAction *mnuFileExit;
    QAction *mnuHelpAbout;
    QAction *mnuAnalysisFst;
    QAction *mnuFileSaveTable;
    QAction *mnuInspectSequencesPerSample;
    QAction *mnuInspectSplitSystem;
    QAction *mnuAnalysisDiversity;
    QAction *mnuInspectClearLog;
    QAction *mnuFileSaveRasterImage;
    QAction *mnuFileSaveColorLegend;
    QAction *mnuFileSaveShapeLegend;
    QAction *mnuFileSaveSizeLegend;
    QAction *mnuViewLogWindow;
    QAction *mnuViewLegendWindows;
    QAction *mnuFileExportPC1vsPC2;
    QAction *mnuFileExportPC3vsPC2;
    QAction *mnuFileExportPC1vsPC3;
    QAction *mnuFileExportScreePlot;
    QAction *mnuFileExportParallelCoordPlot;
    QAction *mnuAnalysisDistanceMatrix;
    QAction *mnuFileOpenDissimilarityMatrix;
    QAction *actionBlah;
    QAction *mnuFileExportDissimilarityMatrixPlot;
    QAction *mnuFileExportResemblanceScatterplot;
    QAction *mnuFileExportTree;
    QAction *mnuFileExportPhylogeny;
    QAction *mnuFileExportClusterTree;
    QAction *mnuFileExportDissMatrixPlot;
    QAction *mnuSettingsProperties;
    QAction *mnuFileOpenMatrix;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_9;
    QTabWidget *tabWidget;
    QWidget *tabPhylogeny;
    QHBoxLayout *horizontalLayout_21;
    QSplitter *splitterPhylogeny;
    QToolBox *toolboxPhylogeny;
    QWidget *pageLayout;
    QVBoxLayout *verticalLayout_34;
    QFormLayout *formLayout_27;
    QLabel *label_11;
    QComboBox *cboPhylogenyBranchStyle;
    QCheckBox *chkPhylogenyAlignTipLabels;
    QLabel *label_20;
    QHBoxLayout *horizontalLayout_17;
    QDoubleSpinBox *spinPhylogenyRootLength;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_18;
    QSpinBox *spinPhylogenyLeafSpacing;
    QSpacerItem *horizontalSpacer_15;
    QFrame *line_24;
    QFormLayout *formLayout_7;
    QLabel *label_111;
    QComboBox *cboPhylogenyLeafTreatment;
    QLabel *label_78;
    QComboBox *cboPhylogenyAbundanceStyle;
    QLabel *label_79;
    QLabel *label_80;
    QHBoxLayout *horizontalLayout_51;
    QSpinBox *spinPhylogenyAbundanceMinSize;
    QSpacerItem *horizontalSpacer_42;
    QHBoxLayout *horizontalLayout_52;
    QSpinBox *spinPhylogenyAbundanceMaxSize;
    QSpacerItem *horizontalSpacer_43;
    QFrame *line_9;
    QCheckBox *chkPhylogenySeqMetadata;
    QFormLayout *formLayout_28;
    QLabel *label_81;
    QHBoxLayout *horizontalLayout_59;
    QLineEdit *txtPhylogenySeqMetadataFile;
    QToolButton *tbPhylogenyBrowseSeqMetadataFile;
    QLabel *label_82;
    QComboBox *cboPhylogenySeqMetadataCategories;
    QLabel *label_83;
    QComboBox *cboPhylogenySeqMetadataColorMap;
    QHBoxLayout *horizontalLayout_60;
    QSpacerItem *horizontalSpacer_50;
    QToolButton *tbPhylogenySeqMetadataLegend;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_3;
    QtColorPicker *btnPhylogenyBackgroundColor;
    QSpacerItem *horizontalSpacer_17;
    QFrame *line_23;
    QPushButton *btnPhylogenyRestoreActiveSamples;
    QPushButton *btnPhylogenyProjectSelectedSeqs;
    QSpacerItem *verticalSpacer_4;
    QWidget *pageBranchProp;
    QVBoxLayout *verticalLayout_7;
    QFormLayout *formLayout_5;
    QLabel *label_2;
    QComboBox *cboPhylogenyBranchColorStyle;
    QtColorPicker *btnPhylogenyBranchColor;
    QFrame *line;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_4;
    QSpinBox *spinPhylogenyBranchWidth;
    QCheckBox *chkPhylogenyDrawBranchOutline;
    QSpacerItem *horizontalSpacer_9;
    QFrame *line_4;
    QFormLayout *formLayout_4;
    QLabel *label_8;
    QComboBox *cboPhylogenyBranchLabel;
    QLabel *label_13;
    QFontComboBox *cboPhylogenyBranchFont;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_14;
    QComboBox *cboPhylogenyBranchFontSize;
    QToolButton *tbPhylogenyBranchFontBold;
    QToolButton *tbPhylogenyBranchFontItalics;
    QSpacerItem *horizontalSpacer_4;
    QtColorPicker *btnPhylogenyBranchLabelColor;
    QSpacerItem *verticalSpacer_2;
    QWidget *pageNodeProp;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QComboBox *cboPhylogenyNodeColorStyle;
    QtColorPicker *btnPhylogenyNodeColor;
    QFrame *line_13;
    QFormLayout *formLayout_2;
    QLabel *label_9;
    QComboBox *cboPhylogenyNodeShapeStyle;
    QComboBox *cboPhylogenyNodeShape;
    QFrame *line_2;
    QFormLayout *formLayout_15;
    QLabel *label_5;
    QComboBox *cboPhylogenyNodeSizeStyle;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QSpinBox *spinPhylogenyLeafNodeSize;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_26;
    QSpinBox *spinPhylogenyInternalNodeSize;
    QSpacerItem *horizontalSpacer_16;
    QFrame *line_3;
    QFormLayout *formLayout_6;
    QLabel *label_12;
    QComboBox *cboPhylogenyNodeLabel;
    QHBoxLayout *horizontalLayout_55;
    QSpacerItem *horizontalSpacer_44;
    QCheckBox *chkPhylogenyShowColorCategory;
    QHBoxLayout *horizontalLayout_54;
    QSpacerItem *horizontalSpacer_45;
    QCheckBox *chkPhylogenyShowShapeCategory;
    QHBoxLayout *horizontalLayout_53;
    QSpacerItem *horizontalSpacer_46;
    QCheckBox *chkPhylogenyShowSizeCategory;
    QLabel *label_10;
    QFontComboBox *cboPhylogenyNodeFont;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_22;
    QComboBox *cboPhylogenyNodeFontSize;
    QToolButton *tbPhylogenyNodeFontBold;
    QToolButton *tbPhylogenyNodeFontItalics;
    QSpacerItem *horizontalSpacer_6;
    QtColorPicker *btnPhylogenyNodeLabelColor;
    QSpacerItem *verticalSpacer_3;
    QWidget *pageCollapsedNodeProp;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_22;
    QComboBox *cboPhylogenyCollapsedNodeShape;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_24;
    QCheckBox *chkPhylogenyCollapsedShowLabels;
    QCheckBox *chkPhylogenyAbundanceInLabel;
    QSpacerItem *horizontalSpacer_11;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_17;
    QFormLayout *formLayout;
    QLabel *label_23;
    QComboBox *cboPhylogenyVariableTL;
    QLabel *label_24;
    QComboBox *cboPhylogenyStatisticTL;
    QLabel *lblPhylogenyFactorLabelTL;
    QLabel *lblPhylogenyMinTL;
    QSpinBox *spinPhylogenyMinTL;
    QLabel *lblPhylogenyMaxTL;
    QSpinBox *spinPhylogenyMaxTL;
    QDoubleSpinBox *spinPhylogenyFactorTL;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_13;
    QFormLayout *formLayout_8;
    QLabel *label_27;
    QComboBox *cboPhylogenyVariableML;
    QLabel *label_28;
    QComboBox *cboPhylogenyStatisticML;
    QLabel *lblPhylogenyFactorLabelML;
    QLabel *lblPhylogenyMinTL_2;
    QSpinBox *spinPhylogenyMinML;
    QLabel *lblPhylogenyMaxTL_2;
    QSpinBox *spinPhylogenyMaxML;
    QDoubleSpinBox *spinPhylogenyFactorML;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_14;
    QFormLayout *formLayout_9;
    QLabel *label_29;
    QComboBox *cboPhylogenyVariableBL;
    QLabel *label_30;
    QComboBox *cboPhylogenyStatisticBL;
    QLabel *lblPhylogenyFactorLabelBL;
    QLabel *lblPhylogenyMinTL_3;
    QSpinBox *spinPhylogenyMinBL;
    QLabel *lblPhylogenyMaxTL_3;
    QSpinBox *spinPhylogenyMaxBL;
    QDoubleSpinBox *spinPhylogenyFactorBL;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_16;
    QFormLayout *formLayout_11;
    QLabel *label_33;
    QComboBox *cboPhylogenyVariableHeight;
    QLabel *label_34;
    QComboBox *cboPhylogenyStatisticHeight;
    QLabel *lblPhylogenyFactorLabelHeight;
    QLabel *lblPhylogenyMinTL_4;
    QSpinBox *spinPhylogenyMinHeight;
    QLabel *lblPhylogenyMaxTL_4;
    QSpinBox *spinPhylogenyMaxHeight;
    QDoubleSpinBox *spinPhylogenyFactorHeight;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_15;
    QFormLayout *formLayout_10;
    QLabel *label_31;
    QComboBox *cboPhylogenyGradientStyle;
    QLabel *label_32;
    QComboBox *cboPhylogenyGradientFill;
    QtColorPicker *btnPhylogenyGradientSingleColor;
    QSpacerItem *verticalSpacer_6;
    QWidget *pageScaleBarProp;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *chkPhylogenyShowScale;
    QFrame *line_8;
    QCheckBox *chkPhylogenyScaleAutomatic;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_17;
    QDoubleSpinBox *spinPhylogenyScale;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_18;
    QSpinBox *spinPhylogenyScaleSignDigits;
    QSpacerItem *horizontalSpacer_7;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_19;
    QSpinBox *spinPhylogenyScaleWidth;
    QSpacerItem *horizontalSpacer_13;
    QFrame *line_7;
    QFormLayout *formLayout_16;
    QLabel *label_16;
    QFontComboBox *cboPhylogenyScaleFont;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_25;
    QComboBox *cboPhylogenyScaleFontSize;
    QToolButton *tbPhylogenyScaleFontBold;
    QToolButton *tbPhylogenyScaleFontItalics;
    QSpacerItem *horizontalSpacer_14;
    QtColorPicker *btnPhylogenyScaleLabelColor;
    QSpacerItem *verticalSpacer_5;
    QWidget *pageTreeFinder;
    QVBoxLayout *verticalLayout_12;
    QListWidget *listPhylogenySearchResults;
    QComboBox *cboPhylogenySearchType;
    QLineEdit *txtPhylogenySearchString;
    QWidget *pageTreeInspector;
    QVBoxLayout *verticalLayout_10;
    QTextBrowser *txtPhylogenyTreeInspector;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    TreeViewport *phylogenyViewport;
    QHBoxLayout *horizontalLayout_10;
    QToolButton *tbPhylogenyToggleCollapse;
    QToolButton *tbPhylogenyCollapseComplement;
    QToolButton *tbPhylogenyCollapseAll;
    QToolButton *tbPhylogenyUncollapseAll;
    QToolButton *tbPhylogenyCollapseToScreen;
    QToolButton *tbPhylogenyCollapseWizard;
    QSpacerItem *horizontalSpacer_18;
    QLabel *label_35;
    QComboBox *cboPhylogenyParsimony;
    QSpacerItem *horizontalSpacer_30;
    QToolButton *tbPhylogenyReroot;
    QToolButton *tbPhylogenyRotateBranches;
    QToolButton *tbPhylogenyAlphabetical;
    QToolButton *tbPhylogenyLadderizeBottom;
    QToolButton *tbPhylogenyLadderizeTop;
    QWidget *tabMetadata;
    QVBoxLayout *verticalLayout_31;
    QHBoxLayout *horizontalLayout_12;
    QToolButton *tbMetadataAddAll;
    QToolButton *tbMetadataRemoveAll;
    QToolButton *tbMetadataSetSelected;
    QSpacerItem *horizontalSpacer_38;
    QLabel *label_70;
    QComboBox *cboMetadataAddRemove;
    QLabel *label_72;
    QComboBox *cboMetadataField;
    QComboBox *cboMetadataRelationship;
    QComboBox *cboMetadataValue;
    QToolButton *tbMetadataFilter;
    QSpacerItem *horizontalSpacer_39;
    QTableWidget *tableMetadata;
    QWidget *tabOrdinationPlots;
    QVBoxLayout *verticalLayout_3;
    QFrame *ordinationPlotFrame;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    OrdinationPlot *ordinationPlot1;
    OrdinationPlot *ordinationPlot2;
    OrdinationPlot *ordinationPlot3;
    OrdinationPlot *screePlot;
    QHBoxLayout *horizontalLayout_7;
    QToolButton *tbOrdinationMethodRun;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *chkShowSampleNames;
    QCheckBox *chkOrdinationSelectionTransparency;
    QToolButton *tbOrdinationPlotProjectedCoord;
    QWidget *tabParallelCoordPlot;
    QVBoxLayout *verticalLayout_2;
    QFrame *parallelCoordinatePlotFrame;
    QHBoxLayout *horizontalLayout_4;
    QwtPlot *qwtPlotParallelCoord;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QSpinBox *spinParallelCoordDim;
    QSpacerItem *horizontalSpacer;
    QCheckBox *chkShowCurve;
    QCheckBox *chkFitCurve;
    QCheckBox *chkShowVarianceLabels;
    QCheckBox *chkParallelCoordSelectionTransparency;
    QToolButton *tbParallelCoordProjectedCoord;
    QWidget *tabClusterTree;
    QHBoxLayout *horizontalLayout_43;
    QSplitter *splitter;
    QToolBox *toolBoxClusterTree;
    QWidget *pageLayout_2;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_36;
    QComboBox *cboClusterTreeBranchStyle;
    QSpacerItem *horizontalSpacer_19;
    QCheckBox *chkClusterTreeAlignTipLabels;
    QFrame *line_10;
    QFormLayout *formLayout_12;
    QLabel *label_37;
    QHBoxLayout *horizontalLayout_26;
    QDoubleSpinBox *spinClusterTreeRootLength;
    QSpacerItem *horizontalSpacer_20;
    QFrame *line_11;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_38;
    QSpinBox *spinClusterTreeLeafSpacing;
    QSpacerItem *horizontalSpacer_21;
    QFrame *line_15;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_39;
    QtColorPicker *btnClusterTreeBackgroundColor;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *verticalSpacer_7;
    QWidget *pageBranchProp_2;
    QVBoxLayout *verticalLayout_19;
    QFormLayout *formLayout_13;
    QLabel *label_40;
    QComboBox *cboClusterTreeBranchColorStyle;
    QtColorPicker *btnClusterTreeBranchColor;
    QFrame *line_12;
    QHBoxLayout *horizontalLayout_34;
    QLabel *label_41;
    QSpinBox *spinClusterTreeBranchWidth;
    QCheckBox *chkClusterTreeDrawBranchOutline;
    QSpacerItem *horizontalSpacer_23;
    QFrame *line_16;
    QFormLayout *formLayout_14;
    QLabel *label_42;
    QComboBox *cboClusterTreeBranchLabel;
    QLabel *label_43;
    QFontComboBox *cboClusterTreeBranchFont;
    QHBoxLayout *horizontalLayout_35;
    QLabel *label_44;
    QComboBox *cboClusterTreeBranchFontSize;
    QToolButton *tbClusterTreeBranchFontBold;
    QToolButton *tbClusterTreeBranchFontItalics;
    QSpacerItem *horizontalSpacer_24;
    QtColorPicker *btnClusterTreeBranchLabelColor;
    QSpacerItem *verticalSpacer_8;
    QWidget *pageNodeProp_2;
    QVBoxLayout *verticalLayout_20;
    QFormLayout *formLayout_17;
    QLabel *label_45;
    QComboBox *cboClusterTreeNodeColorStyle;
    QtColorPicker *btnClusterTreeNodeColor;
    QFrame *line_17;
    QFormLayout *formLayout_18;
    QLabel *label_46;
    QComboBox *cboClusterTreeNodeShapeStyle;
    QComboBox *cboClusterTreeNodeShape;
    QFrame *line_18;
    QFormLayout *formLayout_19;
    QLabel *label_47;
    QComboBox *cboClusterTreeNodeSizeStyle;
    QGridLayout *gridLayout_3;
    QLabel *label_48;
    QSpinBox *spinClusterTreeLeafNodeSize;
    QSpacerItem *horizontalSpacer_25;
    QLabel *label_49;
    QSpinBox *spinClusterTreeInternalNodeSize;
    QSpacerItem *horizontalSpacer_26;
    QFrame *line_19;
    QFormLayout *formLayout_20;
    QLabel *label_50;
    QComboBox *cboClusterTreeNodeLabel;
    QLabel *label_51;
    QFontComboBox *cboClusterTreeNodeFont;
    QHBoxLayout *horizontalLayout_56;
    QSpacerItem *horizontalSpacer_47;
    QCheckBox *chkClusterTreeShowColorCategory;
    QHBoxLayout *horizontalLayout_57;
    QSpacerItem *horizontalSpacer_48;
    QCheckBox *chkClusterTreeShowShapeCategory;
    QHBoxLayout *horizontalLayout_58;
    QSpacerItem *horizontalSpacer_49;
    QCheckBox *chkClusterTreeShowSizeCategory;
    QLabel *label_52;
    QHBoxLayout *horizontalLayout_36;
    QComboBox *cboClusterTreeNodeFontSize;
    QToolButton *tbClusterTreeNodeFontBold;
    QToolButton *tbClusterTreeNodeFontItalics;
    QSpacerItem *horizontalSpacer_27;
    QtColorPicker *btnClusterTreeNodeLabelColor;
    QSpacerItem *verticalSpacer_9;
    QWidget *pageCollapsedNodeProp_2;
    QVBoxLayout *verticalLayout_21;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_53;
    QComboBox *cboClusterTreeCollapsedNodeShape;
    QSpacerItem *horizontalSpacer_28;
    QHBoxLayout *horizontalLayout_38;
    QCheckBox *chkClusterTreeCollapsedShowLabels;
    QCheckBox *chkClusterTreeAbundanceInLabel;
    QSpacerItem *horizontalSpacer_29;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_22;
    QFormLayout *formLayout_21;
    QLabel *label_54;
    QComboBox *cboClusterTreeVariableTL;
    QLabel *label_55;
    QComboBox *cboClusterTreeStatisticTL;
    QLabel *lblClusterTreeFactorLabelTL;
    QLabel *lblPhylogenyMinTL_5;
    QSpinBox *spinClusterTreeMinTL;
    QLabel *lblPhylogenyMaxTL_5;
    QSpinBox *spinClusterTreeMaxTL;
    QDoubleSpinBox *spinClusterTreeFactorTL;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_23;
    QFormLayout *formLayout_22;
    QLabel *label_56;
    QComboBox *cboClusterTreeVariableML;
    QLabel *label_57;
    QComboBox *cboClusterTreeStatisticML;
    QLabel *lblClusterTreeFactorLabelML;
    QLabel *lblPhylogenyMinTL_6;
    QSpinBox *spinClusterTreeMinML;
    QLabel *lblPhylogenyMaxTL_6;
    QSpinBox *spinClusterTreeMaxML;
    QDoubleSpinBox *spinClusterTreeFactorML;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_24;
    QFormLayout *formLayout_23;
    QLabel *label_58;
    QComboBox *cboClusterTreeVariableBL;
    QLabel *label_59;
    QComboBox *cboClusterTreeStatisticBL;
    QLabel *lblClusterTreeFactorLabelBL;
    QLabel *lblPhylogenyMinTL_7;
    QSpinBox *spinClusterTreeMinBL;
    QLabel *lblPhylogenyMaxTL_7;
    QSpinBox *spinClusterTreeMaxBL;
    QDoubleSpinBox *spinClusterTreeFactorBL;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_25;
    QFormLayout *formLayout_24;
    QLabel *label_60;
    QComboBox *cboClusterTreeVariableHeight;
    QLabel *label_61;
    QComboBox *cboClusterTreeStatisticHeight;
    QLabel *lblClusterTreeFactorLabelHeight;
    QLabel *lblPhylogenyMinTL_8;
    QSpinBox *spinClusterTreeMinHeight;
    QLabel *lblPhylogenyMaxTL_8;
    QSpinBox *spinClusterTreeMaxHeight;
    QDoubleSpinBox *spinClusterTreeFactorHeight;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_26;
    QFormLayout *formLayout_25;
    QLabel *label_62;
    QComboBox *cboClusterTreeGradientStyle;
    QLabel *label_63;
    QComboBox *cboClusterTreeGradientFill;
    QtColorPicker *btnClusterTreeGradientSingleColor;
    QSpacerItem *verticalSpacer_10;
    QWidget *pageScaleBarProp_2;
    QVBoxLayout *verticalLayout_27;
    QCheckBox *chkClusterTreeShowScale;
    QFrame *line_20;
    QCheckBox *chkClusterTreeScaleAutomatic;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_64;
    QDoubleSpinBox *spinClusterTreeScale;
    QSpacerItem *horizontalSpacer_31;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_65;
    QSpinBox *spinClusterTreeScaleSignDigits;
    QSpacerItem *horizontalSpacer_32;
    QFrame *line_21;
    QHBoxLayout *horizontalLayout_41;
    QLabel *label_66;
    QSpinBox *spinClusterTreeScaleWidth;
    QSpacerItem *horizontalSpacer_33;
    QFrame *line_22;
    QFormLayout *formLayout_26;
    QLabel *label_67;
    QFontComboBox *cboClusterTreeScaleFont;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_68;
    QComboBox *cboClusterTreeScaleFontSize;
    QToolButton *tbClusterTreeScaleFontBold;
    QToolButton *tbClusterTreeScaleFontItalics;
    QSpacerItem *horizontalSpacer_34;
    QtColorPicker *btnClusterTreeScaleLabelColor;
    QSpacerItem *verticalSpacer_11;
    QWidget *pageTreeFinder_2;
    QVBoxLayout *verticalLayout_28;
    QListWidget *listClusterTreeSearchResults;
    QComboBox *cboClusterTreeSearchType;
    QLineEdit *txtClusterTreeSearchString;
    QWidget *pageTreeInspector_2;
    QVBoxLayout *verticalLayout_29;
    QTextBrowser *txtClusterTreeInspector;
    QWidget *anotherLayoutWidget;
    QVBoxLayout *verticalLayout_30;
    TreeViewport *clusterTreeViewport;
    QHBoxLayout *horizontalLayout_15;
    QToolButton *tbClusterTreeRun;
    QSpacerItem *horizontalSpacer_37;
    QToolButton *tbClusterTreeToggleCollapse;
    QToolButton *tbClusterTreeCollapseComplement;
    QToolButton *tbClusterTreeCollapseAll;
    QToolButton *tbClusterTreeUncollapseAll;
    QToolButton *tbClusterTreeCollapseToScreen;
    QToolButton *tbClusterTreeAutoCollapse;
    QSpacerItem *horizontalSpacer_35;
    QLabel *label_69;
    QComboBox *cboClusterTreeParsimony;
    QSpacerItem *horizontalSpacer_36;
    QToolButton *tbClusterTreeReroot;
    QToolButton *tbClusterTreeRotateBranches;
    QToolButton *tbClusterTreeAlphabetical;
    QToolButton *tbClusterTreeLadderizeBottom;
    QToolButton *tbClusterTreeLadderizeTop;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_53;
    QLabel *label_84;
    QComboBox *cboGradientField;
    QCheckBox *chkGradientLabels;
    QWidget *tabDissMatrixPlot;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblDissimilarityLabel;
    QGraphicsView *dissMatrixViewport;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_71;
    QComboBox *cboDissimilarityMatrixSortMethod;
    QToolButton *tbDissimilarityMatrixRunSort;
    QSpacerItem *horizontalSpacer_40;
    QLabel *label_77;
    QSpinBox *spinDissimilarityMatrixMinSize;
    QCheckBox *chkDissMatrixSelectionTransparency;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_73;
    QComboBox *cboDissimilarityMatrixColorMap;
    QCheckBox *chkDissimilarityMatrixFullRange;
    QCheckBox *chkDissimilarityMatrixThreshold;
    QSpacerItem *horizontalSpacer_3;
    QWidget *tabBoxPlot;
    QHBoxLayout *horizontalLayout_14;
    QTableWidget *tableBoxPlot;
    QWidget *tabDissimilarityMatrix;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tableDissimilarityMatrix;
    QWidget *tabResemblanceMeasureScatterplot;
    QVBoxLayout *verticalLayout_33;
    QFrame *resemblanceScatterplotFrame;
    QHBoxLayout *horizontalLayout_46;
    QwtPlot *qwtResemblanceScatterplot;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_74;
    QComboBox *cboResemblenceXaxis;
    QLabel *label_75;
    QComboBox *cboResemblenceYaxis;
    QPushButton *btnScatterplotRun;
    QSpacerItem *horizontalSpacer_41;
    QCheckBox *chkShowBestFit;
    QLabel *label_76;
    QSpinBox *spinScatterplotSize;
    QWidget *tabLog;
    QVBoxLayout *verticalLayout;
    QTextEdit *txtLog;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_51;
    QPushButton *btnSaveLog;
    QPushButton *btnClearLog;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuSave_legend;
    QMenu *mnuFileExportSVG;
    QMenu *menuHelp;
    QMenu *menuAnalysis;
    QMenu *menuInspect;
    QMenu *menuView;
    QMenu *menuSettings;
    QStatusBar *statusBar;
    QDockWidget *dockLegend;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupColorLegend;
    QHBoxLayout *horizontalLayout_2;
    QwtLegend *legendColor;
    QGroupBox *groupShapeLegend;
    QHBoxLayout *horizontalLayout_5;
    QwtLegend *legendShape;
    QGroupBox *groupSizeLegend;
    QHBoxLayout *horizontalLayout_8;
    QwtLegend *legendSize;
    QSpacerItem *verticalSpacer;
    QPushButton *btnSetVisualProperties;

    void setupUi(QMainWindow *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName(QString::fromUtf8("GUIClass"));
        GUIClass->resize(1093, 662);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GUIClass->sizePolicy().hasHeightForWidth());
        GUIClass->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/chameleon.png"), QSize(), QIcon::Normal, QIcon::Off);
        GUIClass->setWindowIcon(icon);
        GUIClass->setTabShape(QTabWidget::Rounded);
        GUIClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        mnuFileOpenPhylogeny = new QAction(GUIClass);
        mnuFileOpenPhylogeny->setObjectName(QString::fromUtf8("mnuFileOpenPhylogeny"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/folder_tree.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuFileOpenPhylogeny->setIcon(icon1);
        mnuFileExit = new QAction(GUIClass);
        mnuFileExit->setObjectName(QString::fromUtf8("mnuFileExit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/door_out.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuFileExit->setIcon(icon2);
        mnuHelpAbout = new QAction(GUIClass);
        mnuHelpAbout->setObjectName(QString::fromUtf8("mnuHelpAbout"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/information.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuHelpAbout->setIcon(icon3);
        mnuAnalysisFst = new QAction(GUIClass);
        mnuAnalysisFst->setObjectName(QString::fromUtf8("mnuAnalysisFst"));
        mnuFileSaveTable = new QAction(GUIClass);
        mnuFileSaveTable->setObjectName(QString::fromUtf8("mnuFileSaveTable"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/table_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuFileSaveTable->setIcon(icon4);
        mnuInspectSequencesPerSample = new QAction(GUIClass);
        mnuInspectSequencesPerSample->setObjectName(QString::fromUtf8("mnuInspectSequencesPerSample"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/report.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuInspectSequencesPerSample->setIcon(icon5);
        mnuInspectSplitSystem = new QAction(GUIClass);
        mnuInspectSplitSystem->setObjectName(QString::fromUtf8("mnuInspectSplitSystem"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/report_tree.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuInspectSplitSystem->setIcon(icon6);
        mnuAnalysisDiversity = new QAction(GUIClass);
        mnuAnalysisDiversity->setObjectName(QString::fromUtf8("mnuAnalysisDiversity"));
        mnuInspectClearLog = new QAction(GUIClass);
        mnuInspectClearLog->setObjectName(QString::fromUtf8("mnuInspectClearLog"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/draw_eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuInspectClearLog->setIcon(icon7);
        mnuFileSaveRasterImage = new QAction(GUIClass);
        mnuFileSaveRasterImage->setObjectName(QString::fromUtf8("mnuFileSaveRasterImage"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/chart_mds_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuFileSaveRasterImage->setIcon(icon8);
        mnuFileSaveColorLegend = new QAction(GUIClass);
        mnuFileSaveColorLegend->setObjectName(QString::fromUtf8("mnuFileSaveColorLegend"));
        mnuFileSaveShapeLegend = new QAction(GUIClass);
        mnuFileSaveShapeLegend->setObjectName(QString::fromUtf8("mnuFileSaveShapeLegend"));
        mnuFileSaveSizeLegend = new QAction(GUIClass);
        mnuFileSaveSizeLegend->setObjectName(QString::fromUtf8("mnuFileSaveSizeLegend"));
        mnuViewLogWindow = new QAction(GUIClass);
        mnuViewLogWindow->setObjectName(QString::fromUtf8("mnuViewLogWindow"));
        mnuViewLogWindow->setCheckable(true);
        mnuViewLogWindow->setChecked(true);
        mnuViewLegendWindows = new QAction(GUIClass);
        mnuViewLegendWindows->setObjectName(QString::fromUtf8("mnuViewLegendWindows"));
        mnuViewLegendWindows->setCheckable(true);
        mnuViewLegendWindows->setChecked(true);
        mnuFileExportPC1vsPC2 = new QAction(GUIClass);
        mnuFileExportPC1vsPC2->setObjectName(QString::fromUtf8("mnuFileExportPC1vsPC2"));
        mnuFileExportPC3vsPC2 = new QAction(GUIClass);
        mnuFileExportPC3vsPC2->setObjectName(QString::fromUtf8("mnuFileExportPC3vsPC2"));
        mnuFileExportPC1vsPC3 = new QAction(GUIClass);
        mnuFileExportPC1vsPC3->setObjectName(QString::fromUtf8("mnuFileExportPC1vsPC3"));
        mnuFileExportScreePlot = new QAction(GUIClass);
        mnuFileExportScreePlot->setObjectName(QString::fromUtf8("mnuFileExportScreePlot"));
        mnuFileExportParallelCoordPlot = new QAction(GUIClass);
        mnuFileExportParallelCoordPlot->setObjectName(QString::fromUtf8("mnuFileExportParallelCoordPlot"));
        mnuAnalysisDistanceMatrix = new QAction(GUIClass);
        mnuAnalysisDistanceMatrix->setObjectName(QString::fromUtf8("mnuAnalysisDistanceMatrix"));
        mnuFileOpenDissimilarityMatrix = new QAction(GUIClass);
        mnuFileOpenDissimilarityMatrix->setObjectName(QString::fromUtf8("mnuFileOpenDissimilarityMatrix"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icons/folder_table.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuFileOpenDissimilarityMatrix->setIcon(icon9);
        actionBlah = new QAction(GUIClass);
        actionBlah->setObjectName(QString::fromUtf8("actionBlah"));
        mnuFileExportDissimilarityMatrixPlot = new QAction(GUIClass);
        mnuFileExportDissimilarityMatrixPlot->setObjectName(QString::fromUtf8("mnuFileExportDissimilarityMatrixPlot"));
        mnuFileExportResemblanceScatterplot = new QAction(GUIClass);
        mnuFileExportResemblanceScatterplot->setObjectName(QString::fromUtf8("mnuFileExportResemblanceScatterplot"));
        mnuFileExportTree = new QAction(GUIClass);
        mnuFileExportTree->setObjectName(QString::fromUtf8("mnuFileExportTree"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/icons/export_tree.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuFileExportTree->setIcon(icon10);
        mnuFileExportPhylogeny = new QAction(GUIClass);
        mnuFileExportPhylogeny->setObjectName(QString::fromUtf8("mnuFileExportPhylogeny"));
        mnuFileExportClusterTree = new QAction(GUIClass);
        mnuFileExportClusterTree->setObjectName(QString::fromUtf8("mnuFileExportClusterTree"));
        mnuFileExportDissMatrixPlot = new QAction(GUIClass);
        mnuFileExportDissMatrixPlot->setObjectName(QString::fromUtf8("mnuFileExportDissMatrixPlot"));
        mnuSettingsProperties = new QAction(GUIClass);
        mnuSettingsProperties->setObjectName(QString::fromUtf8("mnuSettingsProperties"));
        mnuFileOpenMatrix = new QAction(GUIClass);
        mnuFileOpenMatrix->setObjectName(QString::fromUtf8("mnuFileOpenMatrix"));
        mnuFileOpenMatrix->setIcon(icon9);
        centralWidget = new QWidget(GUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(4);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayout_9 = new QHBoxLayout(centralWidget);
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 1, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        tabPhylogeny = new QWidget();
        tabPhylogeny->setObjectName(QString::fromUtf8("tabPhylogeny"));
        horizontalLayout_21 = new QHBoxLayout(tabPhylogeny);
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        splitterPhylogeny = new QSplitter(tabPhylogeny);
        splitterPhylogeny->setObjectName(QString::fromUtf8("splitterPhylogeny"));
        splitterPhylogeny->setOrientation(Qt::Horizontal);
        toolboxPhylogeny = new QToolBox(splitterPhylogeny);
        toolboxPhylogeny->setObjectName(QString::fromUtf8("toolboxPhylogeny"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(toolboxPhylogeny->sizePolicy().hasHeightForWidth());
        toolboxPhylogeny->setSizePolicy(sizePolicy2);
        toolboxPhylogeny->setMinimumSize(QSize(255, 0));
        toolboxPhylogeny->setMaximumSize(QSize(16777215, 16777215));
        toolboxPhylogeny->setBaseSize(QSize(0, 0));
        toolboxPhylogeny->setFrameShape(QFrame::StyledPanel);
        toolboxPhylogeny->setFrameShadow(QFrame::Sunken);
        toolboxPhylogeny->setLineWidth(1);
        pageLayout = new QWidget();
        pageLayout->setObjectName(QString::fromUtf8("pageLayout"));
        pageLayout->setGeometry(QRect(0, 0, 264, 499));
        verticalLayout_34 = new QVBoxLayout(pageLayout);
        verticalLayout_34->setSpacing(6);
        verticalLayout_34->setContentsMargins(11, 11, 11, 11);
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
        formLayout_27 = new QFormLayout();
        formLayout_27->setSpacing(6);
        formLayout_27->setObjectName(QString::fromUtf8("formLayout_27"));
        label_11 = new QLabel(pageLayout);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_27->setWidget(0, QFormLayout::LabelRole, label_11);

        cboPhylogenyBranchStyle = new QComboBox(pageLayout);
        cboPhylogenyBranchStyle->setObjectName(QString::fromUtf8("cboPhylogenyBranchStyle"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(cboPhylogenyBranchStyle->sizePolicy().hasHeightForWidth());
        cboPhylogenyBranchStyle->setSizePolicy(sizePolicy3);
        cboPhylogenyBranchStyle->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        formLayout_27->setWidget(0, QFormLayout::FieldRole, cboPhylogenyBranchStyle);

        chkPhylogenyAlignTipLabels = new QCheckBox(pageLayout);
        chkPhylogenyAlignTipLabels->setObjectName(QString::fromUtf8("chkPhylogenyAlignTipLabels"));
        chkPhylogenyAlignTipLabels->setChecked(true);

        formLayout_27->setWidget(1, QFormLayout::FieldRole, chkPhylogenyAlignTipLabels);

        label_20 = new QLabel(pageLayout);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        formLayout_27->setWidget(2, QFormLayout::LabelRole, label_20);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        spinPhylogenyRootLength = new QDoubleSpinBox(pageLayout);
        spinPhylogenyRootLength->setObjectName(QString::fromUtf8("spinPhylogenyRootLength"));
        spinPhylogenyRootLength->setDecimals(3);
        spinPhylogenyRootLength->setMaximum(1000);
        spinPhylogenyRootLength->setSingleStep(0.01);
        spinPhylogenyRootLength->setValue(0.5);

        horizontalLayout_17->addWidget(spinPhylogenyRootLength);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_8);


        formLayout_27->setLayout(2, QFormLayout::FieldRole, horizontalLayout_17);

        label_21 = new QLabel(pageLayout);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setTextFormat(Qt::AutoText);

        formLayout_27->setWidget(3, QFormLayout::LabelRole, label_21);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        spinPhylogenyLeafSpacing = new QSpinBox(pageLayout);
        spinPhylogenyLeafSpacing->setObjectName(QString::fromUtf8("spinPhylogenyLeafSpacing"));
        spinPhylogenyLeafSpacing->setMaximum(100);

        horizontalLayout_18->addWidget(spinPhylogenyLeafSpacing);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_15);


        formLayout_27->setLayout(3, QFormLayout::FieldRole, horizontalLayout_18);


        verticalLayout_34->addLayout(formLayout_27);

        line_24 = new QFrame(pageLayout);
        line_24->setObjectName(QString::fromUtf8("line_24"));
        line_24->setFrameShape(QFrame::HLine);
        line_24->setFrameShadow(QFrame::Sunken);

        verticalLayout_34->addWidget(line_24);

        formLayout_7 = new QFormLayout();
        formLayout_7->setSpacing(6);
        formLayout_7->setObjectName(QString::fromUtf8("formLayout_7"));
        label_111 = new QLabel(pageLayout);
        label_111->setObjectName(QString::fromUtf8("label_111"));

        formLayout_7->setWidget(0, QFormLayout::LabelRole, label_111);

        cboPhylogenyLeafTreatment = new QComboBox(pageLayout);
        cboPhylogenyLeafTreatment->setObjectName(QString::fromUtf8("cboPhylogenyLeafTreatment"));

        formLayout_7->setWidget(0, QFormLayout::FieldRole, cboPhylogenyLeafTreatment);

        label_78 = new QLabel(pageLayout);
        label_78->setObjectName(QString::fromUtf8("label_78"));

        formLayout_7->setWidget(1, QFormLayout::LabelRole, label_78);

        cboPhylogenyAbundanceStyle = new QComboBox(pageLayout);
        cboPhylogenyAbundanceStyle->setObjectName(QString::fromUtf8("cboPhylogenyAbundanceStyle"));

        formLayout_7->setWidget(1, QFormLayout::FieldRole, cboPhylogenyAbundanceStyle);

        label_79 = new QLabel(pageLayout);
        label_79->setObjectName(QString::fromUtf8("label_79"));

        formLayout_7->setWidget(2, QFormLayout::LabelRole, label_79);

        label_80 = new QLabel(pageLayout);
        label_80->setObjectName(QString::fromUtf8("label_80"));

        formLayout_7->setWidget(3, QFormLayout::LabelRole, label_80);

        horizontalLayout_51 = new QHBoxLayout();
        horizontalLayout_51->setSpacing(6);
        horizontalLayout_51->setObjectName(QString::fromUtf8("horizontalLayout_51"));
        spinPhylogenyAbundanceMinSize = new QSpinBox(pageLayout);
        spinPhylogenyAbundanceMinSize->setObjectName(QString::fromUtf8("spinPhylogenyAbundanceMinSize"));
        spinPhylogenyAbundanceMinSize->setMinimum(1);
        spinPhylogenyAbundanceMinSize->setMaximum(1000);
        spinPhylogenyAbundanceMinSize->setValue(10);

        horizontalLayout_51->addWidget(spinPhylogenyAbundanceMinSize);

        horizontalSpacer_42 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_51->addItem(horizontalSpacer_42);


        formLayout_7->setLayout(2, QFormLayout::FieldRole, horizontalLayout_51);

        horizontalLayout_52 = new QHBoxLayout();
        horizontalLayout_52->setSpacing(6);
        horizontalLayout_52->setObjectName(QString::fromUtf8("horizontalLayout_52"));
        spinPhylogenyAbundanceMaxSize = new QSpinBox(pageLayout);
        spinPhylogenyAbundanceMaxSize->setObjectName(QString::fromUtf8("spinPhylogenyAbundanceMaxSize"));
        spinPhylogenyAbundanceMaxSize->setMinimum(1);
        spinPhylogenyAbundanceMaxSize->setMaximum(1000);
        spinPhylogenyAbundanceMaxSize->setValue(100);

        horizontalLayout_52->addWidget(spinPhylogenyAbundanceMaxSize);

        horizontalSpacer_43 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_52->addItem(horizontalSpacer_43);


        formLayout_7->setLayout(3, QFormLayout::FieldRole, horizontalLayout_52);


        verticalLayout_34->addLayout(formLayout_7);

        line_9 = new QFrame(pageLayout);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        verticalLayout_34->addWidget(line_9);

        chkPhylogenySeqMetadata = new QCheckBox(pageLayout);
        chkPhylogenySeqMetadata->setObjectName(QString::fromUtf8("chkPhylogenySeqMetadata"));

        verticalLayout_34->addWidget(chkPhylogenySeqMetadata);

        formLayout_28 = new QFormLayout();
        formLayout_28->setSpacing(6);
        formLayout_28->setObjectName(QString::fromUtf8("formLayout_28"));
        label_81 = new QLabel(pageLayout);
        label_81->setObjectName(QString::fromUtf8("label_81"));

        formLayout_28->setWidget(0, QFormLayout::LabelRole, label_81);

        horizontalLayout_59 = new QHBoxLayout();
        horizontalLayout_59->setSpacing(6);
        horizontalLayout_59->setObjectName(QString::fromUtf8("horizontalLayout_59"));
        txtPhylogenySeqMetadataFile = new QLineEdit(pageLayout);
        txtPhylogenySeqMetadataFile->setObjectName(QString::fromUtf8("txtPhylogenySeqMetadataFile"));
        txtPhylogenySeqMetadataFile->setEnabled(false);
        txtPhylogenySeqMetadataFile->setReadOnly(true);

        horizontalLayout_59->addWidget(txtPhylogenySeqMetadataFile);

        tbPhylogenyBrowseSeqMetadataFile = new QToolButton(pageLayout);
        tbPhylogenyBrowseSeqMetadataFile->setObjectName(QString::fromUtf8("tbPhylogenyBrowseSeqMetadataFile"));
        tbPhylogenyBrowseSeqMetadataFile->setEnabled(false);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/icons/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyBrowseSeqMetadataFile->setIcon(icon11);
        tbPhylogenyBrowseSeqMetadataFile->setIconSize(QSize(16, 16));

        horizontalLayout_59->addWidget(tbPhylogenyBrowseSeqMetadataFile);


        formLayout_28->setLayout(0, QFormLayout::FieldRole, horizontalLayout_59);

        label_82 = new QLabel(pageLayout);
        label_82->setObjectName(QString::fromUtf8("label_82"));

        formLayout_28->setWidget(1, QFormLayout::LabelRole, label_82);

        cboPhylogenySeqMetadataCategories = new QComboBox(pageLayout);
        cboPhylogenySeqMetadataCategories->setObjectName(QString::fromUtf8("cboPhylogenySeqMetadataCategories"));
        cboPhylogenySeqMetadataCategories->setEnabled(false);

        formLayout_28->setWidget(1, QFormLayout::FieldRole, cboPhylogenySeqMetadataCategories);

        label_83 = new QLabel(pageLayout);
        label_83->setObjectName(QString::fromUtf8("label_83"));

        formLayout_28->setWidget(2, QFormLayout::LabelRole, label_83);

        cboPhylogenySeqMetadataColorMap = new QComboBox(pageLayout);
        cboPhylogenySeqMetadataColorMap->setObjectName(QString::fromUtf8("cboPhylogenySeqMetadataColorMap"));
        cboPhylogenySeqMetadataColorMap->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(cboPhylogenySeqMetadataColorMap->sizePolicy().hasHeightForWidth());
        cboPhylogenySeqMetadataColorMap->setSizePolicy(sizePolicy4);

        formLayout_28->setWidget(2, QFormLayout::FieldRole, cboPhylogenySeqMetadataColorMap);


        verticalLayout_34->addLayout(formLayout_28);

        horizontalLayout_60 = new QHBoxLayout();
        horizontalLayout_60->setSpacing(6);
        horizontalLayout_60->setObjectName(QString::fromUtf8("horizontalLayout_60"));
        horizontalSpacer_50 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_60->addItem(horizontalSpacer_50);

        tbPhylogenySeqMetadataLegend = new QToolButton(pageLayout);
        tbPhylogenySeqMetadataLegend->setObjectName(QString::fromUtf8("tbPhylogenySeqMetadataLegend"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(tbPhylogenySeqMetadataLegend->sizePolicy().hasHeightForWidth());
        tbPhylogenySeqMetadataLegend->setSizePolicy(sizePolicy5);
        tbPhylogenySeqMetadataLegend->setLayoutDirection(Qt::LeftToRight);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/icons/legend.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenySeqMetadataLegend->setIcon(icon12);
        tbPhylogenySeqMetadataLegend->setIconSize(QSize(16, 16));
        tbPhylogenySeqMetadataLegend->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_60->addWidget(tbPhylogenySeqMetadataLegend);


        verticalLayout_34->addLayout(horizontalLayout_60);

        line_6 = new QFrame(pageLayout);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(line_6->sizePolicy().hasHeightForWidth());
        line_6->setSizePolicy(sizePolicy6);
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_34->addWidget(line_6);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_3 = new QLabel(pageLayout);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_30->addWidget(label_3);

        btnPhylogenyBackgroundColor = new QtColorPicker(pageLayout);
        btnPhylogenyBackgroundColor->setObjectName(QString::fromUtf8("btnPhylogenyBackgroundColor"));

        horizontalLayout_30->addWidget(btnPhylogenyBackgroundColor);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_30->addItem(horizontalSpacer_17);


        verticalLayout_34->addLayout(horizontalLayout_30);

        line_23 = new QFrame(pageLayout);
        line_23->setObjectName(QString::fromUtf8("line_23"));
        line_23->setFrameShape(QFrame::HLine);
        line_23->setFrameShadow(QFrame::Sunken);

        verticalLayout_34->addWidget(line_23);

        btnPhylogenyRestoreActiveSamples = new QPushButton(pageLayout);
        btnPhylogenyRestoreActiveSamples->setObjectName(QString::fromUtf8("btnPhylogenyRestoreActiveSamples"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icons/icons/tree.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPhylogenyRestoreActiveSamples->setIcon(icon13);

        verticalLayout_34->addWidget(btnPhylogenyRestoreActiveSamples);

        btnPhylogenyProjectSelectedSeqs = new QPushButton(pageLayout);
        btnPhylogenyProjectSelectedSeqs->setObjectName(QString::fromUtf8("btnPhylogenyProjectSelectedSeqs"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icons/icons/Plant.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPhylogenyProjectSelectedSeqs->setIcon(icon14);

        verticalLayout_34->addWidget(btnPhylogenyProjectSelectedSeqs);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_34->addItem(verticalSpacer_4);

        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icons/icons/phylogram.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolboxPhylogeny->addItem(pageLayout, icon15, QString::fromUtf8("Layout properties"));
        pageBranchProp = new QWidget();
        pageBranchProp->setObjectName(QString::fromUtf8("pageBranchProp"));
        pageBranchProp->setGeometry(QRect(0, 0, 218, 234));
        sizePolicy2.setHeightForWidth(pageBranchProp->sizePolicy().hasHeightForWidth());
        pageBranchProp->setSizePolicy(sizePolicy2);
        verticalLayout_7 = new QVBoxLayout(pageBranchProp);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        formLayout_5 = new QFormLayout();
        formLayout_5->setSpacing(6);
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        label_2 = new QLabel(pageBranchProp);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_2);

        cboPhylogenyBranchColorStyle = new QComboBox(pageBranchProp);
        cboPhylogenyBranchColorStyle->setObjectName(QString::fromUtf8("cboPhylogenyBranchColorStyle"));
        sizePolicy3.setHeightForWidth(cboPhylogenyBranchColorStyle->sizePolicy().hasHeightForWidth());
        cboPhylogenyBranchColorStyle->setSizePolicy(sizePolicy3);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, cboPhylogenyBranchColorStyle);

        btnPhylogenyBranchColor = new QtColorPicker(pageBranchProp);
        btnPhylogenyBranchColor->setObjectName(QString::fromUtf8("btnPhylogenyBranchColor"));

        formLayout_5->setWidget(1, QFormLayout::FieldRole, btnPhylogenyBranchColor);


        verticalLayout_7->addLayout(formLayout_5);

        line = new QFrame(pageBranchProp);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_4 = new QLabel(pageBranchProp);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_19->addWidget(label_4);

        spinPhylogenyBranchWidth = new QSpinBox(pageBranchProp);
        spinPhylogenyBranchWidth->setObjectName(QString::fromUtf8("spinPhylogenyBranchWidth"));
        spinPhylogenyBranchWidth->setMinimum(1);
        spinPhylogenyBranchWidth->setMaximum(50);
        spinPhylogenyBranchWidth->setSingleStep(2);
        spinPhylogenyBranchWidth->setValue(1);

        horizontalLayout_19->addWidget(spinPhylogenyBranchWidth);

        chkPhylogenyDrawBranchOutline = new QCheckBox(pageBranchProp);
        chkPhylogenyDrawBranchOutline->setObjectName(QString::fromUtf8("chkPhylogenyDrawBranchOutline"));
        chkPhylogenyDrawBranchOutline->setChecked(true);

        horizontalLayout_19->addWidget(chkPhylogenyDrawBranchOutline);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_9);


        verticalLayout_7->addLayout(horizontalLayout_19);

        line_4 = new QFrame(pageBranchProp);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_4);

        formLayout_4 = new QFormLayout();
        formLayout_4->setSpacing(6);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        label_8 = new QLabel(pageBranchProp);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_8);

        cboPhylogenyBranchLabel = new QComboBox(pageBranchProp);
        cboPhylogenyBranchLabel->setObjectName(QString::fromUtf8("cboPhylogenyBranchLabel"));
        sizePolicy3.setHeightForWidth(cboPhylogenyBranchLabel->sizePolicy().hasHeightForWidth());
        cboPhylogenyBranchLabel->setSizePolicy(sizePolicy3);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, cboPhylogenyBranchLabel);

        label_13 = new QLabel(pageBranchProp);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_13);

        cboPhylogenyBranchFont = new QFontComboBox(pageBranchProp);
        cboPhylogenyBranchFont->setObjectName(QString::fromUtf8("cboPhylogenyBranchFont"));
        sizePolicy6.setHeightForWidth(cboPhylogenyBranchFont->sizePolicy().hasHeightForWidth());
        cboPhylogenyBranchFont->setSizePolicy(sizePolicy6);
        cboPhylogenyBranchFont->setMinimumSize(QSize(40, 0));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, cboPhylogenyBranchFont);


        verticalLayout_7->addLayout(formLayout_4);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_14 = new QLabel(pageBranchProp);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_20->addWidget(label_14);

        cboPhylogenyBranchFontSize = new QComboBox(pageBranchProp);
        cboPhylogenyBranchFontSize->setObjectName(QString::fromUtf8("cboPhylogenyBranchFontSize"));
        cboPhylogenyBranchFontSize->setMinimumSize(QSize(40, 0));
        cboPhylogenyBranchFontSize->setEditable(true);
        cboPhylogenyBranchFontSize->setMinimumContentsLength(0);

        horizontalLayout_20->addWidget(cboPhylogenyBranchFontSize);

        tbPhylogenyBranchFontBold = new QToolButton(pageBranchProp);
        tbPhylogenyBranchFontBold->setObjectName(QString::fromUtf8("tbPhylogenyBranchFontBold"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icons/icons/text_bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyBranchFontBold->setIcon(icon16);
        tbPhylogenyBranchFontBold->setIconSize(QSize(16, 16));
        tbPhylogenyBranchFontBold->setCheckable(true);

        horizontalLayout_20->addWidget(tbPhylogenyBranchFontBold);

        tbPhylogenyBranchFontItalics = new QToolButton(pageBranchProp);
        tbPhylogenyBranchFontItalics->setObjectName(QString::fromUtf8("tbPhylogenyBranchFontItalics"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/icons/icons/text_italic.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyBranchFontItalics->setIcon(icon17);
        tbPhylogenyBranchFontItalics->setCheckable(true);

        horizontalLayout_20->addWidget(tbPhylogenyBranchFontItalics);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_4);


        verticalLayout_7->addLayout(horizontalLayout_20);

        btnPhylogenyBranchLabelColor = new QtColorPicker(pageBranchProp);
        btnPhylogenyBranchLabelColor->setObjectName(QString::fromUtf8("btnPhylogenyBranchLabelColor"));

        verticalLayout_7->addWidget(btnPhylogenyBranchLabelColor);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_2);

        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/icons/icons/link.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolboxPhylogeny->addItem(pageBranchProp, icon18, QString::fromUtf8("Branch properties"));
        pageNodeProp = new QWidget();
        pageNodeProp->setObjectName(QString::fromUtf8("pageNodeProp"));
        pageNodeProp->setGeometry(QRect(0, 0, 238, 435));
        verticalLayout_6 = new QVBoxLayout(pageNodeProp);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_7 = new QLabel(pageNodeProp);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_7);

        cboPhylogenyNodeColorStyle = new QComboBox(pageNodeProp);
        cboPhylogenyNodeColorStyle->setObjectName(QString::fromUtf8("cboPhylogenyNodeColorStyle"));
        sizePolicy3.setHeightForWidth(cboPhylogenyNodeColorStyle->sizePolicy().hasHeightForWidth());
        cboPhylogenyNodeColorStyle->setSizePolicy(sizePolicy3);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, cboPhylogenyNodeColorStyle);

        btnPhylogenyNodeColor = new QtColorPicker(pageNodeProp);
        btnPhylogenyNodeColor->setObjectName(QString::fromUtf8("btnPhylogenyNodeColor"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, btnPhylogenyNodeColor);


        verticalLayout_6->addLayout(formLayout_3);

        line_13 = new QFrame(pageNodeProp);
        line_13->setObjectName(QString::fromUtf8("line_13"));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_13);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_9 = new QLabel(pageNodeProp);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_9);

        cboPhylogenyNodeShapeStyle = new QComboBox(pageNodeProp);
        cboPhylogenyNodeShapeStyle->setObjectName(QString::fromUtf8("cboPhylogenyNodeShapeStyle"));
        sizePolicy3.setHeightForWidth(cboPhylogenyNodeShapeStyle->sizePolicy().hasHeightForWidth());
        cboPhylogenyNodeShapeStyle->setSizePolicy(sizePolicy3);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cboPhylogenyNodeShapeStyle);

        cboPhylogenyNodeShape = new QComboBox(pageNodeProp);
        cboPhylogenyNodeShape->setObjectName(QString::fromUtf8("cboPhylogenyNodeShape"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cboPhylogenyNodeShape);


        verticalLayout_6->addLayout(formLayout_2);

        line_2 = new QFrame(pageNodeProp);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_2);

        formLayout_15 = new QFormLayout();
        formLayout_15->setSpacing(6);
        formLayout_15->setObjectName(QString::fromUtf8("formLayout_15"));
        label_5 = new QLabel(pageNodeProp);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_15->setWidget(0, QFormLayout::LabelRole, label_5);

        cboPhylogenyNodeSizeStyle = new QComboBox(pageNodeProp);
        cboPhylogenyNodeSizeStyle->setObjectName(QString::fromUtf8("cboPhylogenyNodeSizeStyle"));

        formLayout_15->setWidget(0, QFormLayout::FieldRole, cboPhylogenyNodeSizeStyle);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(pageNodeProp);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        spinPhylogenyLeafNodeSize = new QSpinBox(pageNodeProp);
        spinPhylogenyLeafNodeSize->setObjectName(QString::fromUtf8("spinPhylogenyLeafNodeSize"));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(spinPhylogenyLeafNodeSize->sizePolicy().hasHeightForWidth());
        spinPhylogenyLeafNodeSize->setSizePolicy(sizePolicy7);
        spinPhylogenyLeafNodeSize->setMinimum(0);
        spinPhylogenyLeafNodeSize->setMaximum(100);
        spinPhylogenyLeafNodeSize->setSingleStep(1);
        spinPhylogenyLeafNodeSize->setValue(10);

        gridLayout_2->addWidget(spinPhylogenyLeafNodeSize, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        label_26 = new QLabel(pageNodeProp);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_2->addWidget(label_26, 1, 0, 1, 1);

        spinPhylogenyInternalNodeSize = new QSpinBox(pageNodeProp);
        spinPhylogenyInternalNodeSize->setObjectName(QString::fromUtf8("spinPhylogenyInternalNodeSize"));
        sizePolicy7.setHeightForWidth(spinPhylogenyInternalNodeSize->sizePolicy().hasHeightForWidth());
        spinPhylogenyInternalNodeSize->setSizePolicy(sizePolicy7);
        spinPhylogenyInternalNodeSize->setMinimum(0);
        spinPhylogenyInternalNodeSize->setMaximum(100);
        spinPhylogenyInternalNodeSize->setSingleStep(1);
        spinPhylogenyInternalNodeSize->setValue(10);

        gridLayout_2->addWidget(spinPhylogenyInternalNodeSize, 1, 1, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_16, 1, 2, 1, 1);


        formLayout_15->setLayout(1, QFormLayout::FieldRole, gridLayout_2);


        verticalLayout_6->addLayout(formLayout_15);

        line_3 = new QFrame(pageNodeProp);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_3);

        formLayout_6 = new QFormLayout();
        formLayout_6->setSpacing(6);
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        label_12 = new QLabel(pageNodeProp);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_12);

        cboPhylogenyNodeLabel = new QComboBox(pageNodeProp);
        cboPhylogenyNodeLabel->setObjectName(QString::fromUtf8("cboPhylogenyNodeLabel"));
        sizePolicy3.setHeightForWidth(cboPhylogenyNodeLabel->sizePolicy().hasHeightForWidth());
        cboPhylogenyNodeLabel->setSizePolicy(sizePolicy3);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, cboPhylogenyNodeLabel);

        horizontalLayout_55 = new QHBoxLayout();
        horizontalLayout_55->setSpacing(6);
        horizontalLayout_55->setObjectName(QString::fromUtf8("horizontalLayout_55"));
        horizontalSpacer_44 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_55->addItem(horizontalSpacer_44);

        chkPhylogenyShowColorCategory = new QCheckBox(pageNodeProp);
        chkPhylogenyShowColorCategory->setObjectName(QString::fromUtf8("chkPhylogenyShowColorCategory"));

        horizontalLayout_55->addWidget(chkPhylogenyShowColorCategory);


        formLayout_6->setLayout(1, QFormLayout::FieldRole, horizontalLayout_55);

        horizontalLayout_54 = new QHBoxLayout();
        horizontalLayout_54->setSpacing(6);
        horizontalLayout_54->setObjectName(QString::fromUtf8("horizontalLayout_54"));
        horizontalSpacer_45 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_54->addItem(horizontalSpacer_45);

        chkPhylogenyShowShapeCategory = new QCheckBox(pageNodeProp);
        chkPhylogenyShowShapeCategory->setObjectName(QString::fromUtf8("chkPhylogenyShowShapeCategory"));

        horizontalLayout_54->addWidget(chkPhylogenyShowShapeCategory);


        formLayout_6->setLayout(2, QFormLayout::FieldRole, horizontalLayout_54);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setSpacing(6);
        horizontalLayout_53->setObjectName(QString::fromUtf8("horizontalLayout_53"));
        horizontalSpacer_46 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_53->addItem(horizontalSpacer_46);

        chkPhylogenyShowSizeCategory = new QCheckBox(pageNodeProp);
        chkPhylogenyShowSizeCategory->setObjectName(QString::fromUtf8("chkPhylogenyShowSizeCategory"));

        horizontalLayout_53->addWidget(chkPhylogenyShowSizeCategory);


        formLayout_6->setLayout(3, QFormLayout::FieldRole, horizontalLayout_53);

        label_10 = new QLabel(pageNodeProp);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_6->setWidget(4, QFormLayout::LabelRole, label_10);

        cboPhylogenyNodeFont = new QFontComboBox(pageNodeProp);
        cboPhylogenyNodeFont->setObjectName(QString::fromUtf8("cboPhylogenyNodeFont"));
        sizePolicy6.setHeightForWidth(cboPhylogenyNodeFont->sizePolicy().hasHeightForWidth());
        cboPhylogenyNodeFont->setSizePolicy(sizePolicy6);
        cboPhylogenyNodeFont->setMinimumSize(QSize(40, 0));

        formLayout_6->setWidget(4, QFormLayout::FieldRole, cboPhylogenyNodeFont);

        label_15 = new QLabel(pageNodeProp);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout_6->setWidget(5, QFormLayout::LabelRole, label_15);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        cboPhylogenyNodeFontSize = new QComboBox(pageNodeProp);
        cboPhylogenyNodeFontSize->setObjectName(QString::fromUtf8("cboPhylogenyNodeFontSize"));
        cboPhylogenyNodeFontSize->setMinimumSize(QSize(40, 0));
        cboPhylogenyNodeFontSize->setEditable(true);
        cboPhylogenyNodeFontSize->setMinimumContentsLength(0);

        horizontalLayout_22->addWidget(cboPhylogenyNodeFontSize);

        tbPhylogenyNodeFontBold = new QToolButton(pageNodeProp);
        tbPhylogenyNodeFontBold->setObjectName(QString::fromUtf8("tbPhylogenyNodeFontBold"));
        tbPhylogenyNodeFontBold->setIcon(icon16);
        tbPhylogenyNodeFontBold->setCheckable(true);

        horizontalLayout_22->addWidget(tbPhylogenyNodeFontBold);

        tbPhylogenyNodeFontItalics = new QToolButton(pageNodeProp);
        tbPhylogenyNodeFontItalics->setObjectName(QString::fromUtf8("tbPhylogenyNodeFontItalics"));
        tbPhylogenyNodeFontItalics->setIcon(icon17);
        tbPhylogenyNodeFontItalics->setCheckable(true);

        horizontalLayout_22->addWidget(tbPhylogenyNodeFontItalics);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_6);


        formLayout_6->setLayout(5, QFormLayout::FieldRole, horizontalLayout_22);


        verticalLayout_6->addLayout(formLayout_6);

        btnPhylogenyNodeLabelColor = new QtColorPicker(pageNodeProp);
        btnPhylogenyNodeLabelColor->setObjectName(QString::fromUtf8("btnPhylogenyNodeLabelColor"));

        verticalLayout_6->addWidget(btnPhylogenyNodeLabelColor);

        verticalSpacer_3 = new QSpacerItem(20, 165, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/icons/icons/bullet_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolboxPhylogeny->addItem(pageNodeProp, icon19, QString::fromUtf8("Node properties"));
        pageCollapsedNodeProp = new QWidget();
        pageCollapsedNodeProp->setObjectName(QString::fromUtf8("pageCollapsedNodeProp"));
        pageCollapsedNodeProp->setGeometry(QRect(0, 0, 236, 743));
        verticalLayout_8 = new QVBoxLayout(pageCollapsedNodeProp);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(-1, -1, -1, 0);
        label_22 = new QLabel(pageCollapsedNodeProp);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_23->addWidget(label_22);

        cboPhylogenyCollapsedNodeShape = new QComboBox(pageCollapsedNodeProp);
        cboPhylogenyCollapsedNodeShape->setObjectName(QString::fromUtf8("cboPhylogenyCollapsedNodeShape"));
        sizePolicy3.setHeightForWidth(cboPhylogenyCollapsedNodeShape->sizePolicy().hasHeightForWidth());
        cboPhylogenyCollapsedNodeShape->setSizePolicy(sizePolicy3);

        horizontalLayout_23->addWidget(cboPhylogenyCollapsedNodeShape);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_12);


        verticalLayout_8->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(-1, -1, -1, 4);
        chkPhylogenyCollapsedShowLabels = new QCheckBox(pageCollapsedNodeProp);
        chkPhylogenyCollapsedShowLabels->setObjectName(QString::fromUtf8("chkPhylogenyCollapsedShowLabels"));
        chkPhylogenyCollapsedShowLabels->setChecked(true);

        horizontalLayout_24->addWidget(chkPhylogenyCollapsedShowLabels);

        chkPhylogenyAbundanceInLabel = new QCheckBox(pageCollapsedNodeProp);
        chkPhylogenyAbundanceInLabel->setObjectName(QString::fromUtf8("chkPhylogenyAbundanceInLabel"));
        chkPhylogenyAbundanceInLabel->setChecked(true);

        horizontalLayout_24->addWidget(chkPhylogenyAbundanceInLabel);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_11);


        verticalLayout_8->addLayout(horizontalLayout_24);

        groupBox = new QGroupBox(pageCollapsedNodeProp);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(true);
        verticalLayout_17 = new QVBoxLayout(groupBox);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setVerticalSpacing(1);
        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_23);

        cboPhylogenyVariableTL = new QComboBox(groupBox);
        cboPhylogenyVariableTL->setObjectName(QString::fromUtf8("cboPhylogenyVariableTL"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboPhylogenyVariableTL);

        label_24 = new QLabel(groupBox);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_24);

        cboPhylogenyStatisticTL = new QComboBox(groupBox);
        cboPhylogenyStatisticTL->setObjectName(QString::fromUtf8("cboPhylogenyStatisticTL"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cboPhylogenyStatisticTL);

        lblPhylogenyFactorLabelTL = new QLabel(groupBox);
        lblPhylogenyFactorLabelTL->setObjectName(QString::fromUtf8("lblPhylogenyFactorLabelTL"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblPhylogenyFactorLabelTL);

        lblPhylogenyMinTL = new QLabel(groupBox);
        lblPhylogenyMinTL->setObjectName(QString::fromUtf8("lblPhylogenyMinTL"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblPhylogenyMinTL);

        spinPhylogenyMinTL = new QSpinBox(groupBox);
        spinPhylogenyMinTL->setObjectName(QString::fromUtf8("spinPhylogenyMinTL"));
        spinPhylogenyMinTL->setAccelerated(false);
        spinPhylogenyMinTL->setMinimum(0);
        spinPhylogenyMinTL->setMaximum(1000);
        spinPhylogenyMinTL->setValue(20);

        formLayout->setWidget(3, QFormLayout::FieldRole, spinPhylogenyMinTL);

        lblPhylogenyMaxTL = new QLabel(groupBox);
        lblPhylogenyMaxTL->setObjectName(QString::fromUtf8("lblPhylogenyMaxTL"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lblPhylogenyMaxTL);

        spinPhylogenyMaxTL = new QSpinBox(groupBox);
        spinPhylogenyMaxTL->setObjectName(QString::fromUtf8("spinPhylogenyMaxTL"));
        spinPhylogenyMaxTL->setAccelerated(false);
        spinPhylogenyMaxTL->setMinimum(0);
        spinPhylogenyMaxTL->setMaximum(10000);
        spinPhylogenyMaxTL->setValue(200);

        formLayout->setWidget(4, QFormLayout::FieldRole, spinPhylogenyMaxTL);

        spinPhylogenyFactorTL = new QDoubleSpinBox(groupBox);
        spinPhylogenyFactorTL->setObjectName(QString::fromUtf8("spinPhylogenyFactorTL"));
        spinPhylogenyFactorTL->setAccelerated(false);
        spinPhylogenyFactorTL->setMaximum(100);
        spinPhylogenyFactorTL->setValue(100);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinPhylogenyFactorTL);


        verticalLayout_17->addLayout(formLayout);


        verticalLayout_8->addWidget(groupBox);

        groupBox_2 = new QGroupBox(pageCollapsedNodeProp);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFlat(true);
        groupBox_2->setCheckable(false);
        verticalLayout_13 = new QVBoxLayout(groupBox_2);
        verticalLayout_13->setSpacing(4);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(-1, 4, -1, -1);
        formLayout_8 = new QFormLayout();
        formLayout_8->setSpacing(6);
        formLayout_8->setObjectName(QString::fromUtf8("formLayout_8"));
        formLayout_8->setVerticalSpacing(1);
        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        formLayout_8->setWidget(0, QFormLayout::LabelRole, label_27);

        cboPhylogenyVariableML = new QComboBox(groupBox_2);
        cboPhylogenyVariableML->setObjectName(QString::fromUtf8("cboPhylogenyVariableML"));

        formLayout_8->setWidget(0, QFormLayout::FieldRole, cboPhylogenyVariableML);

        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        formLayout_8->setWidget(1, QFormLayout::LabelRole, label_28);

        cboPhylogenyStatisticML = new QComboBox(groupBox_2);
        cboPhylogenyStatisticML->setObjectName(QString::fromUtf8("cboPhylogenyStatisticML"));

        formLayout_8->setWidget(1, QFormLayout::FieldRole, cboPhylogenyStatisticML);

        lblPhylogenyFactorLabelML = new QLabel(groupBox_2);
        lblPhylogenyFactorLabelML->setObjectName(QString::fromUtf8("lblPhylogenyFactorLabelML"));

        formLayout_8->setWidget(2, QFormLayout::LabelRole, lblPhylogenyFactorLabelML);

        lblPhylogenyMinTL_2 = new QLabel(groupBox_2);
        lblPhylogenyMinTL_2->setObjectName(QString::fromUtf8("lblPhylogenyMinTL_2"));

        formLayout_8->setWidget(3, QFormLayout::LabelRole, lblPhylogenyMinTL_2);

        spinPhylogenyMinML = new QSpinBox(groupBox_2);
        spinPhylogenyMinML->setObjectName(QString::fromUtf8("spinPhylogenyMinML"));
        spinPhylogenyMinML->setMinimum(0);
        spinPhylogenyMinML->setMaximum(1000);
        spinPhylogenyMinML->setValue(20);

        formLayout_8->setWidget(3, QFormLayout::FieldRole, spinPhylogenyMinML);

        lblPhylogenyMaxTL_2 = new QLabel(groupBox_2);
        lblPhylogenyMaxTL_2->setObjectName(QString::fromUtf8("lblPhylogenyMaxTL_2"));

        formLayout_8->setWidget(4, QFormLayout::LabelRole, lblPhylogenyMaxTL_2);

        spinPhylogenyMaxML = new QSpinBox(groupBox_2);
        spinPhylogenyMaxML->setObjectName(QString::fromUtf8("spinPhylogenyMaxML"));
        spinPhylogenyMaxML->setMinimum(0);
        spinPhylogenyMaxML->setMaximum(10000);
        spinPhylogenyMaxML->setValue(200);

        formLayout_8->setWidget(4, QFormLayout::FieldRole, spinPhylogenyMaxML);

        spinPhylogenyFactorML = new QDoubleSpinBox(groupBox_2);
        spinPhylogenyFactorML->setObjectName(QString::fromUtf8("spinPhylogenyFactorML"));
        spinPhylogenyFactorML->setMaximum(100);
        spinPhylogenyFactorML->setValue(100);

        formLayout_8->setWidget(2, QFormLayout::FieldRole, spinPhylogenyFactorML);


        verticalLayout_13->addLayout(formLayout_8);


        verticalLayout_8->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(pageCollapsedNodeProp);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFlat(true);
        groupBox_3->setCheckable(false);
        verticalLayout_14 = new QVBoxLayout(groupBox_3);
        verticalLayout_14->setSpacing(4);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(-1, 4, -1, -1);
        formLayout_9 = new QFormLayout();
        formLayout_9->setSpacing(6);
        formLayout_9->setObjectName(QString::fromUtf8("formLayout_9"));
        formLayout_9->setVerticalSpacing(1);
        label_29 = new QLabel(groupBox_3);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        formLayout_9->setWidget(0, QFormLayout::LabelRole, label_29);

        cboPhylogenyVariableBL = new QComboBox(groupBox_3);
        cboPhylogenyVariableBL->setObjectName(QString::fromUtf8("cboPhylogenyVariableBL"));

        formLayout_9->setWidget(0, QFormLayout::FieldRole, cboPhylogenyVariableBL);

        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        formLayout_9->setWidget(1, QFormLayout::LabelRole, label_30);

        cboPhylogenyStatisticBL = new QComboBox(groupBox_3);
        cboPhylogenyStatisticBL->setObjectName(QString::fromUtf8("cboPhylogenyStatisticBL"));

        formLayout_9->setWidget(1, QFormLayout::FieldRole, cboPhylogenyStatisticBL);

        lblPhylogenyFactorLabelBL = new QLabel(groupBox_3);
        lblPhylogenyFactorLabelBL->setObjectName(QString::fromUtf8("lblPhylogenyFactorLabelBL"));

        formLayout_9->setWidget(2, QFormLayout::LabelRole, lblPhylogenyFactorLabelBL);

        lblPhylogenyMinTL_3 = new QLabel(groupBox_3);
        lblPhylogenyMinTL_3->setObjectName(QString::fromUtf8("lblPhylogenyMinTL_3"));

        formLayout_9->setWidget(3, QFormLayout::LabelRole, lblPhylogenyMinTL_3);

        spinPhylogenyMinBL = new QSpinBox(groupBox_3);
        spinPhylogenyMinBL->setObjectName(QString::fromUtf8("spinPhylogenyMinBL"));
        spinPhylogenyMinBL->setMinimum(0);
        spinPhylogenyMinBL->setMaximum(1000);
        spinPhylogenyMinBL->setValue(20);

        formLayout_9->setWidget(3, QFormLayout::FieldRole, spinPhylogenyMinBL);

        lblPhylogenyMaxTL_3 = new QLabel(groupBox_3);
        lblPhylogenyMaxTL_3->setObjectName(QString::fromUtf8("lblPhylogenyMaxTL_3"));

        formLayout_9->setWidget(4, QFormLayout::LabelRole, lblPhylogenyMaxTL_3);

        spinPhylogenyMaxBL = new QSpinBox(groupBox_3);
        spinPhylogenyMaxBL->setObjectName(QString::fromUtf8("spinPhylogenyMaxBL"));
        spinPhylogenyMaxBL->setMinimum(0);
        spinPhylogenyMaxBL->setMaximum(10000);
        spinPhylogenyMaxBL->setValue(200);

        formLayout_9->setWidget(4, QFormLayout::FieldRole, spinPhylogenyMaxBL);

        spinPhylogenyFactorBL = new QDoubleSpinBox(groupBox_3);
        spinPhylogenyFactorBL->setObjectName(QString::fromUtf8("spinPhylogenyFactorBL"));
        spinPhylogenyFactorBL->setMaximum(100);
        spinPhylogenyFactorBL->setValue(100);

        formLayout_9->setWidget(2, QFormLayout::FieldRole, spinPhylogenyFactorBL);


        verticalLayout_14->addLayout(formLayout_9);


        verticalLayout_8->addWidget(groupBox_3);

        groupBox_5 = new QGroupBox(pageCollapsedNodeProp);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFlat(true);
        groupBox_5->setCheckable(false);
        verticalLayout_16 = new QVBoxLayout(groupBox_5);
        verticalLayout_16->setSpacing(4);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(-1, 4, -1, -1);
        formLayout_11 = new QFormLayout();
        formLayout_11->setSpacing(6);
        formLayout_11->setObjectName(QString::fromUtf8("formLayout_11"));
        formLayout_11->setVerticalSpacing(1);
        label_33 = new QLabel(groupBox_5);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        formLayout_11->setWidget(0, QFormLayout::LabelRole, label_33);

        cboPhylogenyVariableHeight = new QComboBox(groupBox_5);
        cboPhylogenyVariableHeight->setObjectName(QString::fromUtf8("cboPhylogenyVariableHeight"));

        formLayout_11->setWidget(0, QFormLayout::FieldRole, cboPhylogenyVariableHeight);

        label_34 = new QLabel(groupBox_5);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        formLayout_11->setWidget(1, QFormLayout::LabelRole, label_34);

        cboPhylogenyStatisticHeight = new QComboBox(groupBox_5);
        cboPhylogenyStatisticHeight->setObjectName(QString::fromUtf8("cboPhylogenyStatisticHeight"));

        formLayout_11->setWidget(1, QFormLayout::FieldRole, cboPhylogenyStatisticHeight);

        lblPhylogenyFactorLabelHeight = new QLabel(groupBox_5);
        lblPhylogenyFactorLabelHeight->setObjectName(QString::fromUtf8("lblPhylogenyFactorLabelHeight"));

        formLayout_11->setWidget(2, QFormLayout::LabelRole, lblPhylogenyFactorLabelHeight);

        lblPhylogenyMinTL_4 = new QLabel(groupBox_5);
        lblPhylogenyMinTL_4->setObjectName(QString::fromUtf8("lblPhylogenyMinTL_4"));

        formLayout_11->setWidget(3, QFormLayout::LabelRole, lblPhylogenyMinTL_4);

        spinPhylogenyMinHeight = new QSpinBox(groupBox_5);
        spinPhylogenyMinHeight->setObjectName(QString::fromUtf8("spinPhylogenyMinHeight"));
        spinPhylogenyMinHeight->setMinimum(0);
        spinPhylogenyMinHeight->setMaximum(100);
        spinPhylogenyMinHeight->setValue(20);

        formLayout_11->setWidget(3, QFormLayout::FieldRole, spinPhylogenyMinHeight);

        lblPhylogenyMaxTL_4 = new QLabel(groupBox_5);
        lblPhylogenyMaxTL_4->setObjectName(QString::fromUtf8("lblPhylogenyMaxTL_4"));

        formLayout_11->setWidget(4, QFormLayout::LabelRole, lblPhylogenyMaxTL_4);

        spinPhylogenyMaxHeight = new QSpinBox(groupBox_5);
        spinPhylogenyMaxHeight->setObjectName(QString::fromUtf8("spinPhylogenyMaxHeight"));
        spinPhylogenyMaxHeight->setMinimum(0);
        spinPhylogenyMaxHeight->setMaximum(10000);
        spinPhylogenyMaxHeight->setValue(100);

        formLayout_11->setWidget(4, QFormLayout::FieldRole, spinPhylogenyMaxHeight);

        spinPhylogenyFactorHeight = new QDoubleSpinBox(groupBox_5);
        spinPhylogenyFactorHeight->setObjectName(QString::fromUtf8("spinPhylogenyFactorHeight"));
        spinPhylogenyFactorHeight->setMaximum(100);
        spinPhylogenyFactorHeight->setValue(10);

        formLayout_11->setWidget(2, QFormLayout::FieldRole, spinPhylogenyFactorHeight);


        verticalLayout_16->addLayout(formLayout_11);


        verticalLayout_8->addWidget(groupBox_5);

        groupBox_4 = new QGroupBox(pageCollapsedNodeProp);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFlat(true);
        groupBox_4->setCheckable(false);
        verticalLayout_15 = new QVBoxLayout(groupBox_4);
        verticalLayout_15->setSpacing(4);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(-1, 4, -1, -1);
        formLayout_10 = new QFormLayout();
        formLayout_10->setSpacing(6);
        formLayout_10->setObjectName(QString::fromUtf8("formLayout_10"));
        formLayout_10->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_10->setVerticalSpacing(1);
        label_31 = new QLabel(groupBox_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        formLayout_10->setWidget(0, QFormLayout::LabelRole, label_31);

        cboPhylogenyGradientStyle = new QComboBox(groupBox_4);
        cboPhylogenyGradientStyle->setObjectName(QString::fromUtf8("cboPhylogenyGradientStyle"));

        formLayout_10->setWidget(0, QFormLayout::FieldRole, cboPhylogenyGradientStyle);

        label_32 = new QLabel(groupBox_4);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        formLayout_10->setWidget(2, QFormLayout::LabelRole, label_32);

        cboPhylogenyGradientFill = new QComboBox(groupBox_4);
        cboPhylogenyGradientFill->setObjectName(QString::fromUtf8("cboPhylogenyGradientFill"));

        formLayout_10->setWidget(2, QFormLayout::FieldRole, cboPhylogenyGradientFill);

        btnPhylogenyGradientSingleColor = new QtColorPicker(groupBox_4);
        btnPhylogenyGradientSingleColor->setObjectName(QString::fromUtf8("btnPhylogenyGradientSingleColor"));

        formLayout_10->setWidget(1, QFormLayout::FieldRole, btnPhylogenyGradientSingleColor);


        verticalLayout_15->addLayout(formLayout_10);


        verticalLayout_8->addWidget(groupBox_4);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_6);

        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/icons/icons/collapse.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolboxPhylogeny->addItem(pageCollapsedNodeProp, icon20, QString::fromUtf8("Collapsed node properties"));
        pageScaleBarProp = new QWidget();
        pageScaleBarProp->setObjectName(QString::fromUtf8("pageScaleBarProp"));
        pageScaleBarProp->setGeometry(QRect(0, 0, 177, 262));
        verticalLayout_9 = new QVBoxLayout(pageScaleBarProp);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        chkPhylogenyShowScale = new QCheckBox(pageScaleBarProp);
        chkPhylogenyShowScale->setObjectName(QString::fromUtf8("chkPhylogenyShowScale"));
        chkPhylogenyShowScale->setChecked(false);

        verticalLayout_9->addWidget(chkPhylogenyShowScale);

        line_8 = new QFrame(pageScaleBarProp);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line_8);

        chkPhylogenyScaleAutomatic = new QCheckBox(pageScaleBarProp);
        chkPhylogenyScaleAutomatic->setObjectName(QString::fromUtf8("chkPhylogenyScaleAutomatic"));
        chkPhylogenyScaleAutomatic->setChecked(true);

        verticalLayout_9->addWidget(chkPhylogenyScaleAutomatic);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_17 = new QLabel(pageScaleBarProp);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_27->addWidget(label_17);

        spinPhylogenyScale = new QDoubleSpinBox(pageScaleBarProp);
        spinPhylogenyScale->setObjectName(QString::fromUtf8("spinPhylogenyScale"));
        spinPhylogenyScale->setEnabled(false);
        spinPhylogenyScale->setDecimals(3);
        spinPhylogenyScale->setMaximum(1000);
        spinPhylogenyScale->setSingleStep(0.01);
        spinPhylogenyScale->setValue(1);

        horizontalLayout_27->addWidget(spinPhylogenyScale);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_10);


        verticalLayout_9->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_18 = new QLabel(pageScaleBarProp);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_28->addWidget(label_18);

        spinPhylogenyScaleSignDigits = new QSpinBox(pageScaleBarProp);
        spinPhylogenyScaleSignDigits->setObjectName(QString::fromUtf8("spinPhylogenyScaleSignDigits"));
        spinPhylogenyScaleSignDigits->setMinimum(1);
        spinPhylogenyScaleSignDigits->setMaximum(16);
        spinPhylogenyScaleSignDigits->setValue(2);

        horizontalLayout_28->addWidget(spinPhylogenyScaleSignDigits);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_7);


        verticalLayout_9->addLayout(horizontalLayout_28);

        line_5 = new QFrame(pageScaleBarProp);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line_5);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_19 = new QLabel(pageScaleBarProp);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_29->addWidget(label_19);

        spinPhylogenyScaleWidth = new QSpinBox(pageScaleBarProp);
        spinPhylogenyScaleWidth->setObjectName(QString::fromUtf8("spinPhylogenyScaleWidth"));
        spinPhylogenyScaleWidth->setMinimum(1);
        spinPhylogenyScaleWidth->setMaximum(100);
        spinPhylogenyScaleWidth->setValue(1);

        horizontalLayout_29->addWidget(spinPhylogenyScaleWidth);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_13);


        verticalLayout_9->addLayout(horizontalLayout_29);

        line_7 = new QFrame(pageScaleBarProp);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line_7);

        formLayout_16 = new QFormLayout();
        formLayout_16->setSpacing(6);
        formLayout_16->setObjectName(QString::fromUtf8("formLayout_16"));
        label_16 = new QLabel(pageScaleBarProp);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_16->setWidget(0, QFormLayout::LabelRole, label_16);

        cboPhylogenyScaleFont = new QFontComboBox(pageScaleBarProp);
        cboPhylogenyScaleFont->setObjectName(QString::fromUtf8("cboPhylogenyScaleFont"));
        sizePolicy3.setHeightForWidth(cboPhylogenyScaleFont->sizePolicy().hasHeightForWidth());
        cboPhylogenyScaleFont->setSizePolicy(sizePolicy3);
        cboPhylogenyScaleFont->setMinimumSize(QSize(40, 0));

        formLayout_16->setWidget(0, QFormLayout::FieldRole, cboPhylogenyScaleFont);


        verticalLayout_9->addLayout(formLayout_16);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_25 = new QLabel(pageScaleBarProp);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_31->addWidget(label_25);

        cboPhylogenyScaleFontSize = new QComboBox(pageScaleBarProp);
        cboPhylogenyScaleFontSize->setObjectName(QString::fromUtf8("cboPhylogenyScaleFontSize"));
        cboPhylogenyScaleFontSize->setMinimumSize(QSize(40, 0));
        cboPhylogenyScaleFontSize->setEditable(true);
        cboPhylogenyScaleFontSize->setMinimumContentsLength(0);

        horizontalLayout_31->addWidget(cboPhylogenyScaleFontSize);

        tbPhylogenyScaleFontBold = new QToolButton(pageScaleBarProp);
        tbPhylogenyScaleFontBold->setObjectName(QString::fromUtf8("tbPhylogenyScaleFontBold"));
        tbPhylogenyScaleFontBold->setIcon(icon16);
        tbPhylogenyScaleFontBold->setCheckable(true);

        horizontalLayout_31->addWidget(tbPhylogenyScaleFontBold);

        tbPhylogenyScaleFontItalics = new QToolButton(pageScaleBarProp);
        tbPhylogenyScaleFontItalics->setObjectName(QString::fromUtf8("tbPhylogenyScaleFontItalics"));
        tbPhylogenyScaleFontItalics->setIcon(icon17);
        tbPhylogenyScaleFontItalics->setCheckable(true);

        horizontalLayout_31->addWidget(tbPhylogenyScaleFontItalics);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_14);


        verticalLayout_9->addLayout(horizontalLayout_31);

        btnPhylogenyScaleLabelColor = new QtColorPicker(pageScaleBarProp);
        btnPhylogenyScaleLabelColor->setObjectName(QString::fromUtf8("btnPhylogenyScaleLabelColor"));

        verticalLayout_9->addWidget(btnPhylogenyScaleLabelColor);

        verticalSpacer_5 = new QSpacerItem(20, 72, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_5);

        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/icons/icons/hrule.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolboxPhylogeny->addItem(pageScaleBarProp, icon21, QString::fromUtf8("Scale bar properties"));
        pageTreeFinder = new QWidget();
        pageTreeFinder->setObjectName(QString::fromUtf8("pageTreeFinder"));
        pageTreeFinder->setGeometry(QRect(0, 0, 98, 143));
        verticalLayout_12 = new QVBoxLayout(pageTreeFinder);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        listPhylogenySearchResults = new QListWidget(pageTreeFinder);
        listPhylogenySearchResults->setObjectName(QString::fromUtf8("listPhylogenySearchResults"));
        listPhylogenySearchResults->setSortingEnabled(true);

        verticalLayout_12->addWidget(listPhylogenySearchResults);

        cboPhylogenySearchType = new QComboBox(pageTreeFinder);
        cboPhylogenySearchType->setObjectName(QString::fromUtf8("cboPhylogenySearchType"));

        verticalLayout_12->addWidget(cboPhylogenySearchType);

        txtPhylogenySearchString = new QLineEdit(pageTreeFinder);
        txtPhylogenySearchString->setObjectName(QString::fromUtf8("txtPhylogenySearchString"));

        verticalLayout_12->addWidget(txtPhylogenySearchString);

        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/icons/icons/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolboxPhylogeny->addItem(pageTreeFinder, icon22, QString::fromUtf8("Search tree"));
        pageTreeInspector = new QWidget();
        pageTreeInspector->setObjectName(QString::fromUtf8("pageTreeInspector"));
        pageTreeInspector->setGeometry(QRect(0, 0, 98, 89));
        verticalLayout_10 = new QVBoxLayout(pageTreeInspector);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        txtPhylogenyTreeInspector = new QTextBrowser(pageTreeInspector);
        txtPhylogenyTreeInspector->setObjectName(QString::fromUtf8("txtPhylogenyTreeInspector"));

        verticalLayout_10->addWidget(txtPhylogenyTreeInspector);

        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/icons/icons/administrator.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolboxPhylogeny->addItem(pageTreeInspector, icon23, QString::fromUtf8("Tree inspector"));
        splitterPhylogeny->addWidget(toolboxPhylogeny);
        layoutWidget = new QWidget(splitterPhylogeny);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        phylogenyViewport = new TreeViewport(layoutWidget);
        phylogenyViewport->setObjectName(QString::fromUtf8("phylogenyViewport"));
        sizePolicy.setHeightForWidth(phylogenyViewport->sizePolicy().hasHeightForWidth());
        phylogenyViewport->setSizePolicy(sizePolicy);
        phylogenyViewport->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        phylogenyViewport->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_4->addWidget(phylogenyViewport);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        tbPhylogenyToggleCollapse = new QToolButton(layoutWidget);
        tbPhylogenyToggleCollapse->setObjectName(QString::fromUtf8("tbPhylogenyToggleCollapse"));
        tbPhylogenyToggleCollapse->setIcon(icon20);
        tbPhylogenyToggleCollapse->setIconSize(QSize(24, 24));
        tbPhylogenyToggleCollapse->setAutoRaise(false);
        tbPhylogenyToggleCollapse->setArrowType(Qt::NoArrow);

        horizontalLayout_10->addWidget(tbPhylogenyToggleCollapse);

        tbPhylogenyCollapseComplement = new QToolButton(layoutWidget);
        tbPhylogenyCollapseComplement->setObjectName(QString::fromUtf8("tbPhylogenyCollapseComplement"));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/icons/icons/collapse-complement.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyCollapseComplement->setIcon(icon24);
        tbPhylogenyCollapseComplement->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyCollapseComplement);

        tbPhylogenyCollapseAll = new QToolButton(layoutWidget);
        tbPhylogenyCollapseAll->setObjectName(QString::fromUtf8("tbPhylogenyCollapseAll"));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/icons/icons/collapse-all.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyCollapseAll->setIcon(icon25);
        tbPhylogenyCollapseAll->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyCollapseAll);

        tbPhylogenyUncollapseAll = new QToolButton(layoutWidget);
        tbPhylogenyUncollapseAll->setObjectName(QString::fromUtf8("tbPhylogenyUncollapseAll"));
        tbPhylogenyUncollapseAll->setIcon(icon15);
        tbPhylogenyUncollapseAll->setIconSize(QSize(24, 24));
        tbPhylogenyUncollapseAll->setAutoRaise(false);
        tbPhylogenyUncollapseAll->setArrowType(Qt::NoArrow);

        horizontalLayout_10->addWidget(tbPhylogenyUncollapseAll);

        tbPhylogenyCollapseToScreen = new QToolButton(layoutWidget);
        tbPhylogenyCollapseToScreen->setObjectName(QString::fromUtf8("tbPhylogenyCollapseToScreen"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/icons/icons/collapse-fit-on-screen.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyCollapseToScreen->setIcon(icon26);
        tbPhylogenyCollapseToScreen->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyCollapseToScreen);

        tbPhylogenyCollapseWizard = new QToolButton(layoutWidget);
        tbPhylogenyCollapseWizard->setObjectName(QString::fromUtf8("tbPhylogenyCollapseWizard"));
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/icons/icons/collapse-auto.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyCollapseWizard->setIcon(icon27);
        tbPhylogenyCollapseWizard->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyCollapseWizard);

        horizontalSpacer_18 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_18);

        label_35 = new QLabel(layoutWidget);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        horizontalLayout_10->addWidget(label_35);

        cboPhylogenyParsimony = new QComboBox(layoutWidget);
        cboPhylogenyParsimony->setObjectName(QString::fromUtf8("cboPhylogenyParsimony"));
        sizePolicy7.setHeightForWidth(cboPhylogenyParsimony->sizePolicy().hasHeightForWidth());
        cboPhylogenyParsimony->setSizePolicy(sizePolicy7);
        cboPhylogenyParsimony->setInsertPolicy(QComboBox::InsertAlphabetically);
        cboPhylogenyParsimony->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_10->addWidget(cboPhylogenyParsimony);

        horizontalSpacer_30 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_30);

        tbPhylogenyReroot = new QToolButton(layoutWidget);
        tbPhylogenyReroot->setObjectName(QString::fromUtf8("tbPhylogenyReroot"));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/icons/icons/reroot.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyReroot->setIcon(icon28);
        tbPhylogenyReroot->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyReroot);

        tbPhylogenyRotateBranches = new QToolButton(layoutWidget);
        tbPhylogenyRotateBranches->setObjectName(QString::fromUtf8("tbPhylogenyRotateBranches"));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/icons/icons/arrow_switch.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyRotateBranches->setIcon(icon29);
        tbPhylogenyRotateBranches->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyRotateBranches);

        tbPhylogenyAlphabetical = new QToolButton(layoutWidget);
        tbPhylogenyAlphabetical->setObjectName(QString::fromUtf8("tbPhylogenyAlphabetical"));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/icons/icons/sort_columns.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyAlphabetical->setIcon(icon30);
        tbPhylogenyAlphabetical->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyAlphabetical);

        tbPhylogenyLadderizeBottom = new QToolButton(layoutWidget);
        tbPhylogenyLadderizeBottom->setObjectName(QString::fromUtf8("tbPhylogenyLadderizeBottom"));
        QIcon icon31;
        icon31.addFile(QString::fromUtf8(":/icons/icons/sort_ascending.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyLadderizeBottom->setIcon(icon31);
        tbPhylogenyLadderizeBottom->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyLadderizeBottom);

        tbPhylogenyLadderizeTop = new QToolButton(layoutWidget);
        tbPhylogenyLadderizeTop->setObjectName(QString::fromUtf8("tbPhylogenyLadderizeTop"));
        QIcon icon32;
        icon32.addFile(QString::fromUtf8(":/icons/icons/sort_descending.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPhylogenyLadderizeTop->setIcon(icon32);
        tbPhylogenyLadderizeTop->setIconSize(QSize(24, 24));

        horizontalLayout_10->addWidget(tbPhylogenyLadderizeTop);


        verticalLayout_4->addLayout(horizontalLayout_10);

        splitterPhylogeny->addWidget(layoutWidget);

        horizontalLayout_21->addWidget(splitterPhylogeny);

        tabWidget->addTab(tabPhylogeny, icon13, QString());
        tabMetadata = new QWidget();
        tabMetadata->setObjectName(QString::fromUtf8("tabMetadata"));
        verticalLayout_31 = new QVBoxLayout(tabMetadata);
        verticalLayout_31->setSpacing(6);
        verticalLayout_31->setContentsMargins(11, 11, 11, 11);
        verticalLayout_31->setObjectName(QString::fromUtf8("verticalLayout_31"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        tbMetadataAddAll = new QToolButton(tabMetadata);
        tbMetadataAddAll->setObjectName(QString::fromUtf8("tbMetadataAddAll"));
        QIcon icon33;
        icon33.addFile(QString::fromUtf8(":/icons/icons/filter_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMetadataAddAll->setIcon(icon33);
        tbMetadataAddAll->setIconSize(QSize(24, 24));

        horizontalLayout_12->addWidget(tbMetadataAddAll);

        tbMetadataRemoveAll = new QToolButton(tabMetadata);
        tbMetadataRemoveAll->setObjectName(QString::fromUtf8("tbMetadataRemoveAll"));
        QIcon icon34;
        icon34.addFile(QString::fromUtf8(":/icons/icons/filter_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMetadataRemoveAll->setIcon(icon34);
        tbMetadataRemoveAll->setIconSize(QSize(24, 24));

        horizontalLayout_12->addWidget(tbMetadataRemoveAll);

        tbMetadataSetSelected = new QToolButton(tabMetadata);
        tbMetadataSetSelected->setObjectName(QString::fromUtf8("tbMetadataSetSelected"));
        QIcon icon35;
        icon35.addFile(QString::fromUtf8(":/icons/icons/filter_selected.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMetadataSetSelected->setIcon(icon35);
        tbMetadataSetSelected->setIconSize(QSize(24, 24));

        horizontalLayout_12->addWidget(tbMetadataSetSelected);

        horizontalSpacer_38 = new QSpacerItem(12, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_38);

        label_70 = new QLabel(tabMetadata);
        label_70->setObjectName(QString::fromUtf8("label_70"));

        horizontalLayout_12->addWidget(label_70);

        cboMetadataAddRemove = new QComboBox(tabMetadata);
        cboMetadataAddRemove->setObjectName(QString::fromUtf8("cboMetadataAddRemove"));

        horizontalLayout_12->addWidget(cboMetadataAddRemove);

        label_72 = new QLabel(tabMetadata);
        label_72->setObjectName(QString::fromUtf8("label_72"));

        horizontalLayout_12->addWidget(label_72);

        cboMetadataField = new QComboBox(tabMetadata);
        cboMetadataField->setObjectName(QString::fromUtf8("cboMetadataField"));
        cboMetadataField->setMaximumSize(QSize(300, 16777215));
        cboMetadataField->setInsertPolicy(QComboBox::InsertAlphabetically);
        cboMetadataField->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_12->addWidget(cboMetadataField);

        cboMetadataRelationship = new QComboBox(tabMetadata);
        cboMetadataRelationship->setObjectName(QString::fromUtf8("cboMetadataRelationship"));

        horizontalLayout_12->addWidget(cboMetadataRelationship);

        cboMetadataValue = new QComboBox(tabMetadata);
        cboMetadataValue->setObjectName(QString::fromUtf8("cboMetadataValue"));
        cboMetadataValue->setMaximumSize(QSize(300, 16777215));
        cboMetadataValue->setInsertPolicy(QComboBox::InsertAtBottom);
        cboMetadataValue->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_12->addWidget(cboMetadataValue);

        tbMetadataFilter = new QToolButton(tabMetadata);
        tbMetadataFilter->setObjectName(QString::fromUtf8("tbMetadataFilter"));
        QIcon icon36;
        icon36.addFile(QString::fromUtf8(":/icons/icons/filter.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMetadataFilter->setIcon(icon36);
        tbMetadataFilter->setIconSize(QSize(24, 24));

        horizontalLayout_12->addWidget(tbMetadataFilter);

        horizontalSpacer_39 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_39);


        verticalLayout_31->addLayout(horizontalLayout_12);

        tableMetadata = new QTableWidget(tabMetadata);
        if (tableMetadata->columnCount() < 5)
            tableMetadata->setColumnCount(5);
        if (tableMetadata->rowCount() < 5)
            tableMetadata->setRowCount(5);
        tableMetadata->setObjectName(QString::fromUtf8("tableMetadata"));
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(10);
        sizePolicy8.setHeightForWidth(tableMetadata->sizePolicy().hasHeightForWidth());
        tableMetadata->setSizePolicy(sizePolicy8);
        tableMetadata->setAlternatingRowColors(true);
        tableMetadata->setSelectionMode(QAbstractItemView::MultiSelection);
        tableMetadata->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableMetadata->setSortingEnabled(true);
        tableMetadata->setCornerButtonEnabled(true);
        tableMetadata->setRowCount(5);
        tableMetadata->setColumnCount(5);
        tableMetadata->horizontalHeader()->setVisible(false);
        tableMetadata->horizontalHeader()->setCascadingSectionResizes(false);
        tableMetadata->horizontalHeader()->setDefaultSectionSize(100);
        tableMetadata->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableMetadata->horizontalHeader()->setStretchLastSection(false);
        tableMetadata->verticalHeader()->setVisible(false);
        tableMetadata->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout_31->addWidget(tableMetadata);

        QIcon icon37;
        icon37.addFile(QString::fromUtf8(":/icons/icons/table.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabMetadata, icon37, QString());
        tabOrdinationPlots = new QWidget();
        tabOrdinationPlots->setObjectName(QString::fromUtf8("tabOrdinationPlots"));
        sizePolicy.setHeightForWidth(tabOrdinationPlots->sizePolicy().hasHeightForWidth());
        tabOrdinationPlots->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(tabOrdinationPlots);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        ordinationPlotFrame = new QFrame(tabOrdinationPlots);
        ordinationPlotFrame->setObjectName(QString::fromUtf8("ordinationPlotFrame"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(4);
        sizePolicy9.setVerticalStretch(4);
        sizePolicy9.setHeightForWidth(ordinationPlotFrame->sizePolicy().hasHeightForWidth());
        ordinationPlotFrame->setSizePolicy(sizePolicy9);
        ordinationPlotFrame->setStyleSheet(QString::fromUtf8(""));
        ordinationPlotFrame->setFrameShape(QFrame::StyledPanel);
        ordinationPlotFrame->setFrameShadow(QFrame::Plain);
        horizontalLayout = new QHBoxLayout(ordinationPlotFrame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(20);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ordinationPlot1 = new OrdinationPlot(ordinationPlotFrame);
        ordinationPlot1->setObjectName(QString::fromUtf8("ordinationPlot1"));
        QSizePolicy sizePolicy10(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(ordinationPlot1->sizePolicy().hasHeightForWidth());
        ordinationPlot1->setSizePolicy(sizePolicy10);
        ordinationPlot1->setFocusPolicy(Qt::StrongFocus);
        ordinationPlot1->setAutoFillBackground(false);

        gridLayout->addWidget(ordinationPlot1, 0, 0, 1, 1);

        ordinationPlot2 = new OrdinationPlot(ordinationPlotFrame);
        ordinationPlot2->setObjectName(QString::fromUtf8("ordinationPlot2"));
        sizePolicy10.setHeightForWidth(ordinationPlot2->sizePolicy().hasHeightForWidth());
        ordinationPlot2->setSizePolicy(sizePolicy10);

        gridLayout->addWidget(ordinationPlot2, 0, 1, 1, 1);

        ordinationPlot3 = new OrdinationPlot(ordinationPlotFrame);
        ordinationPlot3->setObjectName(QString::fromUtf8("ordinationPlot3"));
        sizePolicy10.setHeightForWidth(ordinationPlot3->sizePolicy().hasHeightForWidth());
        ordinationPlot3->setSizePolicy(sizePolicy10);

        gridLayout->addWidget(ordinationPlot3, 1, 0, 1, 1);

        screePlot = new OrdinationPlot(ordinationPlotFrame);
        screePlot->setObjectName(QString::fromUtf8("screePlot"));
        sizePolicy10.setHeightForWidth(screePlot->sizePolicy().hasHeightForWidth());
        screePlot->setSizePolicy(sizePolicy10);

        gridLayout->addWidget(screePlot, 1, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_3->addWidget(ordinationPlotFrame);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        tbOrdinationMethodRun = new QToolButton(tabOrdinationPlots);
        tbOrdinationMethodRun->setObjectName(QString::fromUtf8("tbOrdinationMethodRun"));
        QIcon icon38;
        icon38.addFile(QString::fromUtf8(":/icons/icons/ordination-run.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbOrdinationMethodRun->setIcon(icon38);
        tbOrdinationMethodRun->setIconSize(QSize(24, 24));

        horizontalLayout_7->addWidget(tbOrdinationMethodRun);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        chkShowSampleNames = new QCheckBox(tabOrdinationPlots);
        chkShowSampleNames->setObjectName(QString::fromUtf8("chkShowSampleNames"));
        chkShowSampleNames->setChecked(false);

        horizontalLayout_7->addWidget(chkShowSampleNames);

        chkOrdinationSelectionTransparency = new QCheckBox(tabOrdinationPlots);
        chkOrdinationSelectionTransparency->setObjectName(QString::fromUtf8("chkOrdinationSelectionTransparency"));
        chkOrdinationSelectionTransparency->setChecked(false);

        horizontalLayout_7->addWidget(chkOrdinationSelectionTransparency);

        tbOrdinationPlotProjectedCoord = new QToolButton(tabOrdinationPlots);
        tbOrdinationPlotProjectedCoord->setObjectName(QString::fromUtf8("tbOrdinationPlotProjectedCoord"));
        QIcon icon39;
        icon39.addFile(QString::fromUtf8(":/icons/icons/table_mds.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbOrdinationPlotProjectedCoord->setIcon(icon39);
        tbOrdinationPlotProjectedCoord->setIconSize(QSize(24, 24));

        horizontalLayout_7->addWidget(tbOrdinationPlotProjectedCoord);


        verticalLayout_3->addLayout(horizontalLayout_7);

        QIcon icon40;
        icon40.addFile(QString::fromUtf8(":/icons/icons/chart_bullseye.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabOrdinationPlots, icon40, QString());
        tabParallelCoordPlot = new QWidget();
        tabParallelCoordPlot->setObjectName(QString::fromUtf8("tabParallelCoordPlot"));
        sizePolicy.setHeightForWidth(tabParallelCoordPlot->sizePolicy().hasHeightForWidth());
        tabParallelCoordPlot->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(tabParallelCoordPlot);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        parallelCoordinatePlotFrame = new QFrame(tabParallelCoordPlot);
        parallelCoordinatePlotFrame->setObjectName(QString::fromUtf8("parallelCoordinatePlotFrame"));
        QSizePolicy sizePolicy11(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy11.setHorizontalStretch(4);
        sizePolicy11.setVerticalStretch(4);
        sizePolicy11.setHeightForWidth(parallelCoordinatePlotFrame->sizePolicy().hasHeightForWidth());
        parallelCoordinatePlotFrame->setSizePolicy(sizePolicy11);
        parallelCoordinatePlotFrame->setFrameShape(QFrame::StyledPanel);
        parallelCoordinatePlotFrame->setFrameShadow(QFrame::Plain);
        horizontalLayout_4 = new QHBoxLayout(parallelCoordinatePlotFrame);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        qwtPlotParallelCoord = new QwtPlot(parallelCoordinatePlotFrame);
        qwtPlotParallelCoord->setObjectName(QString::fromUtf8("qwtPlotParallelCoord"));
        sizePolicy9.setHeightForWidth(qwtPlotParallelCoord->sizePolicy().hasHeightForWidth());
        qwtPlotParallelCoord->setSizePolicy(sizePolicy9);

        horizontalLayout_4->addWidget(qwtPlotParallelCoord);


        verticalLayout_2->addWidget(parallelCoordinatePlotFrame);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label = new QLabel(tabParallelCoordPlot);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);

        spinParallelCoordDim = new QSpinBox(tabParallelCoordPlot);
        spinParallelCoordDim->setObjectName(QString::fromUtf8("spinParallelCoordDim"));
        spinParallelCoordDim->setMinimum(2);
        spinParallelCoordDim->setMaximum(1000);
        spinParallelCoordDim->setValue(8);

        horizontalLayout_6->addWidget(spinParallelCoordDim);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        chkShowCurve = new QCheckBox(tabParallelCoordPlot);
        chkShowCurve->setObjectName(QString::fromUtf8("chkShowCurve"));
        chkShowCurve->setChecked(true);

        horizontalLayout_6->addWidget(chkShowCurve);

        chkFitCurve = new QCheckBox(tabParallelCoordPlot);
        chkFitCurve->setObjectName(QString::fromUtf8("chkFitCurve"));
        chkFitCurve->setChecked(true);

        horizontalLayout_6->addWidget(chkFitCurve);

        chkShowVarianceLabels = new QCheckBox(tabParallelCoordPlot);
        chkShowVarianceLabels->setObjectName(QString::fromUtf8("chkShowVarianceLabels"));
        chkShowVarianceLabels->setChecked(true);

        horizontalLayout_6->addWidget(chkShowVarianceLabels);

        chkParallelCoordSelectionTransparency = new QCheckBox(tabParallelCoordPlot);
        chkParallelCoordSelectionTransparency->setObjectName(QString::fromUtf8("chkParallelCoordSelectionTransparency"));
        chkParallelCoordSelectionTransparency->setChecked(true);

        horizontalLayout_6->addWidget(chkParallelCoordSelectionTransparency);

        tbParallelCoordProjectedCoord = new QToolButton(tabParallelCoordPlot);
        tbParallelCoordProjectedCoord->setObjectName(QString::fromUtf8("tbParallelCoordProjectedCoord"));
        tbParallelCoordProjectedCoord->setIcon(icon39);
        tbParallelCoordProjectedCoord->setIconSize(QSize(24, 24));

        horizontalLayout_6->addWidget(tbParallelCoordProjectedCoord);


        verticalLayout_2->addLayout(horizontalLayout_6);

        QIcon icon41;
        icon41.addFile(QString::fromUtf8(":/icons/icons/chart_parallel.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabParallelCoordPlot, icon41, QString());
        tabClusterTree = new QWidget();
        tabClusterTree->setObjectName(QString::fromUtf8("tabClusterTree"));
        horizontalLayout_43 = new QHBoxLayout(tabClusterTree);
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        splitter = new QSplitter(tabClusterTree);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        toolBoxClusterTree = new QToolBox(splitter);
        toolBoxClusterTree->setObjectName(QString::fromUtf8("toolBoxClusterTree"));
        sizePolicy2.setHeightForWidth(toolBoxClusterTree->sizePolicy().hasHeightForWidth());
        toolBoxClusterTree->setSizePolicy(sizePolicy2);
        toolBoxClusterTree->setMinimumSize(QSize(255, 0));
        toolBoxClusterTree->setMaximumSize(QSize(16777215, 16777215));
        toolBoxClusterTree->setBaseSize(QSize(0, 0));
        toolBoxClusterTree->setFrameShape(QFrame::StyledPanel);
        toolBoxClusterTree->setFrameShadow(QFrame::Sunken);
        toolBoxClusterTree->setLineWidth(1);
        pageLayout_2 = new QWidget();
        pageLayout_2->setObjectName(QString::fromUtf8("pageLayout_2"));
        pageLayout_2->setGeometry(QRect(0, 0, 253, 403));
        verticalLayout_18 = new QVBoxLayout(pageLayout_2);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_36 = new QLabel(pageLayout_2);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        horizontalLayout_25->addWidget(label_36);

        cboClusterTreeBranchStyle = new QComboBox(pageLayout_2);
        cboClusterTreeBranchStyle->setObjectName(QString::fromUtf8("cboClusterTreeBranchStyle"));
        sizePolicy3.setHeightForWidth(cboClusterTreeBranchStyle->sizePolicy().hasHeightForWidth());
        cboClusterTreeBranchStyle->setSizePolicy(sizePolicy3);
        cboClusterTreeBranchStyle->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        horizontalLayout_25->addWidget(cboClusterTreeBranchStyle);

        horizontalSpacer_19 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_19);


        verticalLayout_18->addLayout(horizontalLayout_25);

        chkClusterTreeAlignTipLabels = new QCheckBox(pageLayout_2);
        chkClusterTreeAlignTipLabels->setObjectName(QString::fromUtf8("chkClusterTreeAlignTipLabels"));
        chkClusterTreeAlignTipLabels->setChecked(true);

        verticalLayout_18->addWidget(chkClusterTreeAlignTipLabels);

        line_10 = new QFrame(pageLayout_2);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        verticalLayout_18->addWidget(line_10);

        formLayout_12 = new QFormLayout();
        formLayout_12->setSpacing(6);
        formLayout_12->setObjectName(QString::fromUtf8("formLayout_12"));
        formLayout_12->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_37 = new QLabel(pageLayout_2);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        formLayout_12->setWidget(0, QFormLayout::LabelRole, label_37);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        spinClusterTreeRootLength = new QDoubleSpinBox(pageLayout_2);
        spinClusterTreeRootLength->setObjectName(QString::fromUtf8("spinClusterTreeRootLength"));
        spinClusterTreeRootLength->setDecimals(3);
        spinClusterTreeRootLength->setMaximum(1000);
        spinClusterTreeRootLength->setSingleStep(0.01);
        spinClusterTreeRootLength->setValue(0.5);

        horizontalLayout_26->addWidget(spinClusterTreeRootLength);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_20);


        formLayout_12->setLayout(0, QFormLayout::FieldRole, horizontalLayout_26);


        verticalLayout_18->addLayout(formLayout_12);

        line_11 = new QFrame(pageLayout_2);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        sizePolicy6.setHeightForWidth(line_11->sizePolicy().hasHeightForWidth());
        line_11->setSizePolicy(sizePolicy6);
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);

        verticalLayout_18->addWidget(line_11);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        label_38 = new QLabel(pageLayout_2);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setTextFormat(Qt::AutoText);

        horizontalLayout_32->addWidget(label_38);

        spinClusterTreeLeafSpacing = new QSpinBox(pageLayout_2);
        spinClusterTreeLeafSpacing->setObjectName(QString::fromUtf8("spinClusterTreeLeafSpacing"));
        spinClusterTreeLeafSpacing->setMaximum(100);

        horizontalLayout_32->addWidget(spinClusterTreeLeafSpacing);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_21);


        verticalLayout_18->addLayout(horizontalLayout_32);

        line_15 = new QFrame(pageLayout_2);
        line_15->setObjectName(QString::fromUtf8("line_15"));
        sizePolicy6.setHeightForWidth(line_15->sizePolicy().hasHeightForWidth());
        line_15->setSizePolicy(sizePolicy6);
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);

        verticalLayout_18->addWidget(line_15);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        label_39 = new QLabel(pageLayout_2);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        horizontalLayout_33->addWidget(label_39);

        btnClusterTreeBackgroundColor = new QtColorPicker(pageLayout_2);
        btnClusterTreeBackgroundColor->setObjectName(QString::fromUtf8("btnClusterTreeBackgroundColor"));

        horizontalLayout_33->addWidget(btnClusterTreeBackgroundColor);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_22);


        verticalLayout_18->addLayout(horizontalLayout_33);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_7);

        toolBoxClusterTree->addItem(pageLayout_2, icon15, QString::fromUtf8("Layout properties"));
        pageBranchProp_2 = new QWidget();
        pageBranchProp_2->setObjectName(QString::fromUtf8("pageBranchProp_2"));
        pageBranchProp_2->setGeometry(QRect(0, 0, 218, 234));
        sizePolicy2.setHeightForWidth(pageBranchProp_2->sizePolicy().hasHeightForWidth());
        pageBranchProp_2->setSizePolicy(sizePolicy2);
        verticalLayout_19 = new QVBoxLayout(pageBranchProp_2);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        formLayout_13 = new QFormLayout();
        formLayout_13->setSpacing(6);
        formLayout_13->setObjectName(QString::fromUtf8("formLayout_13"));
        label_40 = new QLabel(pageBranchProp_2);
        label_40->setObjectName(QString::fromUtf8("label_40"));

        formLayout_13->setWidget(0, QFormLayout::LabelRole, label_40);

        cboClusterTreeBranchColorStyle = new QComboBox(pageBranchProp_2);
        cboClusterTreeBranchColorStyle->setObjectName(QString::fromUtf8("cboClusterTreeBranchColorStyle"));
        sizePolicy3.setHeightForWidth(cboClusterTreeBranchColorStyle->sizePolicy().hasHeightForWidth());
        cboClusterTreeBranchColorStyle->setSizePolicy(sizePolicy3);

        formLayout_13->setWidget(0, QFormLayout::FieldRole, cboClusterTreeBranchColorStyle);

        btnClusterTreeBranchColor = new QtColorPicker(pageBranchProp_2);
        btnClusterTreeBranchColor->setObjectName(QString::fromUtf8("btnClusterTreeBranchColor"));

        formLayout_13->setWidget(1, QFormLayout::FieldRole, btnClusterTreeBranchColor);


        verticalLayout_19->addLayout(formLayout_13);

        line_12 = new QFrame(pageBranchProp_2);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);

        verticalLayout_19->addWidget(line_12);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        label_41 = new QLabel(pageBranchProp_2);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        horizontalLayout_34->addWidget(label_41);

        spinClusterTreeBranchWidth = new QSpinBox(pageBranchProp_2);
        spinClusterTreeBranchWidth->setObjectName(QString::fromUtf8("spinClusterTreeBranchWidth"));
        spinClusterTreeBranchWidth->setMinimum(1);
        spinClusterTreeBranchWidth->setMaximum(50);
        spinClusterTreeBranchWidth->setSingleStep(2);
        spinClusterTreeBranchWidth->setValue(1);

        horizontalLayout_34->addWidget(spinClusterTreeBranchWidth);

        chkClusterTreeDrawBranchOutline = new QCheckBox(pageBranchProp_2);
        chkClusterTreeDrawBranchOutline->setObjectName(QString::fromUtf8("chkClusterTreeDrawBranchOutline"));
        chkClusterTreeDrawBranchOutline->setChecked(true);

        horizontalLayout_34->addWidget(chkClusterTreeDrawBranchOutline);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_23);


        verticalLayout_19->addLayout(horizontalLayout_34);

        line_16 = new QFrame(pageBranchProp_2);
        line_16->setObjectName(QString::fromUtf8("line_16"));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);

        verticalLayout_19->addWidget(line_16);

        formLayout_14 = new QFormLayout();
        formLayout_14->setSpacing(6);
        formLayout_14->setObjectName(QString::fromUtf8("formLayout_14"));
        label_42 = new QLabel(pageBranchProp_2);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        formLayout_14->setWidget(0, QFormLayout::LabelRole, label_42);

        cboClusterTreeBranchLabel = new QComboBox(pageBranchProp_2);
        cboClusterTreeBranchLabel->setObjectName(QString::fromUtf8("cboClusterTreeBranchLabel"));
        sizePolicy3.setHeightForWidth(cboClusterTreeBranchLabel->sizePolicy().hasHeightForWidth());
        cboClusterTreeBranchLabel->setSizePolicy(sizePolicy3);

        formLayout_14->setWidget(0, QFormLayout::FieldRole, cboClusterTreeBranchLabel);

        label_43 = new QLabel(pageBranchProp_2);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        formLayout_14->setWidget(1, QFormLayout::LabelRole, label_43);

        cboClusterTreeBranchFont = new QFontComboBox(pageBranchProp_2);
        cboClusterTreeBranchFont->setObjectName(QString::fromUtf8("cboClusterTreeBranchFont"));
        sizePolicy6.setHeightForWidth(cboClusterTreeBranchFont->sizePolicy().hasHeightForWidth());
        cboClusterTreeBranchFont->setSizePolicy(sizePolicy6);
        cboClusterTreeBranchFont->setMinimumSize(QSize(40, 0));

        formLayout_14->setWidget(1, QFormLayout::FieldRole, cboClusterTreeBranchFont);


        verticalLayout_19->addLayout(formLayout_14);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        label_44 = new QLabel(pageBranchProp_2);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        horizontalLayout_35->addWidget(label_44);

        cboClusterTreeBranchFontSize = new QComboBox(pageBranchProp_2);
        cboClusterTreeBranchFontSize->setObjectName(QString::fromUtf8("cboClusterTreeBranchFontSize"));
        cboClusterTreeBranchFontSize->setMinimumSize(QSize(40, 0));
        cboClusterTreeBranchFontSize->setEditable(true);
        cboClusterTreeBranchFontSize->setMinimumContentsLength(0);

        horizontalLayout_35->addWidget(cboClusterTreeBranchFontSize);

        tbClusterTreeBranchFontBold = new QToolButton(pageBranchProp_2);
        tbClusterTreeBranchFontBold->setObjectName(QString::fromUtf8("tbClusterTreeBranchFontBold"));
        tbClusterTreeBranchFontBold->setIcon(icon16);
        tbClusterTreeBranchFontBold->setIconSize(QSize(16, 16));
        tbClusterTreeBranchFontBold->setCheckable(true);

        horizontalLayout_35->addWidget(tbClusterTreeBranchFontBold);

        tbClusterTreeBranchFontItalics = new QToolButton(pageBranchProp_2);
        tbClusterTreeBranchFontItalics->setObjectName(QString::fromUtf8("tbClusterTreeBranchFontItalics"));
        tbClusterTreeBranchFontItalics->setIcon(icon17);
        tbClusterTreeBranchFontItalics->setCheckable(true);

        horizontalLayout_35->addWidget(tbClusterTreeBranchFontItalics);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_35->addItem(horizontalSpacer_24);


        verticalLayout_19->addLayout(horizontalLayout_35);

        btnClusterTreeBranchLabelColor = new QtColorPicker(pageBranchProp_2);
        btnClusterTreeBranchLabelColor->setObjectName(QString::fromUtf8("btnClusterTreeBranchLabelColor"));

        verticalLayout_19->addWidget(btnClusterTreeBranchLabelColor);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_19->addItem(verticalSpacer_8);

        toolBoxClusterTree->addItem(pageBranchProp_2, icon18, QString::fromUtf8("Branch properties"));
        pageNodeProp_2 = new QWidget();
        pageNodeProp_2->setObjectName(QString::fromUtf8("pageNodeProp_2"));
        pageNodeProp_2->setGeometry(QRect(0, 0, 238, 435));
        verticalLayout_20 = new QVBoxLayout(pageNodeProp_2);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        formLayout_17 = new QFormLayout();
        formLayout_17->setSpacing(6);
        formLayout_17->setObjectName(QString::fromUtf8("formLayout_17"));
        formLayout_17->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_45 = new QLabel(pageNodeProp_2);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        formLayout_17->setWidget(0, QFormLayout::LabelRole, label_45);

        cboClusterTreeNodeColorStyle = new QComboBox(pageNodeProp_2);
        cboClusterTreeNodeColorStyle->setObjectName(QString::fromUtf8("cboClusterTreeNodeColorStyle"));
        sizePolicy3.setHeightForWidth(cboClusterTreeNodeColorStyle->sizePolicy().hasHeightForWidth());
        cboClusterTreeNodeColorStyle->setSizePolicy(sizePolicy3);

        formLayout_17->setWidget(0, QFormLayout::FieldRole, cboClusterTreeNodeColorStyle);

        btnClusterTreeNodeColor = new QtColorPicker(pageNodeProp_2);
        btnClusterTreeNodeColor->setObjectName(QString::fromUtf8("btnClusterTreeNodeColor"));

        formLayout_17->setWidget(1, QFormLayout::FieldRole, btnClusterTreeNodeColor);


        verticalLayout_20->addLayout(formLayout_17);

        line_17 = new QFrame(pageNodeProp_2);
        line_17->setObjectName(QString::fromUtf8("line_17"));
        line_17->setFrameShape(QFrame::HLine);
        line_17->setFrameShadow(QFrame::Sunken);

        verticalLayout_20->addWidget(line_17);

        formLayout_18 = new QFormLayout();
        formLayout_18->setSpacing(6);
        formLayout_18->setObjectName(QString::fromUtf8("formLayout_18"));
        label_46 = new QLabel(pageNodeProp_2);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        formLayout_18->setWidget(0, QFormLayout::LabelRole, label_46);

        cboClusterTreeNodeShapeStyle = new QComboBox(pageNodeProp_2);
        cboClusterTreeNodeShapeStyle->setObjectName(QString::fromUtf8("cboClusterTreeNodeShapeStyle"));
        sizePolicy3.setHeightForWidth(cboClusterTreeNodeShapeStyle->sizePolicy().hasHeightForWidth());
        cboClusterTreeNodeShapeStyle->setSizePolicy(sizePolicy3);

        formLayout_18->setWidget(0, QFormLayout::FieldRole, cboClusterTreeNodeShapeStyle);

        cboClusterTreeNodeShape = new QComboBox(pageNodeProp_2);
        cboClusterTreeNodeShape->setObjectName(QString::fromUtf8("cboClusterTreeNodeShape"));

        formLayout_18->setWidget(1, QFormLayout::FieldRole, cboClusterTreeNodeShape);


        verticalLayout_20->addLayout(formLayout_18);

        line_18 = new QFrame(pageNodeProp_2);
        line_18->setObjectName(QString::fromUtf8("line_18"));
        line_18->setFrameShape(QFrame::HLine);
        line_18->setFrameShadow(QFrame::Sunken);

        verticalLayout_20->addWidget(line_18);

        formLayout_19 = new QFormLayout();
        formLayout_19->setSpacing(6);
        formLayout_19->setObjectName(QString::fromUtf8("formLayout_19"));
        label_47 = new QLabel(pageNodeProp_2);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        formLayout_19->setWidget(0, QFormLayout::LabelRole, label_47);

        cboClusterTreeNodeSizeStyle = new QComboBox(pageNodeProp_2);
        cboClusterTreeNodeSizeStyle->setObjectName(QString::fromUtf8("cboClusterTreeNodeSizeStyle"));

        formLayout_19->setWidget(0, QFormLayout::FieldRole, cboClusterTreeNodeSizeStyle);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_48 = new QLabel(pageNodeProp_2);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_3->addWidget(label_48, 0, 0, 1, 1);

        spinClusterTreeLeafNodeSize = new QSpinBox(pageNodeProp_2);
        spinClusterTreeLeafNodeSize->setObjectName(QString::fromUtf8("spinClusterTreeLeafNodeSize"));
        sizePolicy7.setHeightForWidth(spinClusterTreeLeafNodeSize->sizePolicy().hasHeightForWidth());
        spinClusterTreeLeafNodeSize->setSizePolicy(sizePolicy7);
        spinClusterTreeLeafNodeSize->setMinimum(0);
        spinClusterTreeLeafNodeSize->setMaximum(100);
        spinClusterTreeLeafNodeSize->setSingleStep(1);
        spinClusterTreeLeafNodeSize->setValue(10);

        gridLayout_3->addWidget(spinClusterTreeLeafNodeSize, 0, 1, 1, 1);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_25, 0, 2, 1, 1);

        label_49 = new QLabel(pageNodeProp_2);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        gridLayout_3->addWidget(label_49, 1, 0, 1, 1);

        spinClusterTreeInternalNodeSize = new QSpinBox(pageNodeProp_2);
        spinClusterTreeInternalNodeSize->setObjectName(QString::fromUtf8("spinClusterTreeInternalNodeSize"));
        sizePolicy7.setHeightForWidth(spinClusterTreeInternalNodeSize->sizePolicy().hasHeightForWidth());
        spinClusterTreeInternalNodeSize->setSizePolicy(sizePolicy7);
        spinClusterTreeInternalNodeSize->setMinimum(0);
        spinClusterTreeInternalNodeSize->setMaximum(100);
        spinClusterTreeInternalNodeSize->setSingleStep(1);
        spinClusterTreeInternalNodeSize->setValue(10);

        gridLayout_3->addWidget(spinClusterTreeInternalNodeSize, 1, 1, 1, 1);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_26, 1, 2, 1, 1);


        formLayout_19->setLayout(1, QFormLayout::FieldRole, gridLayout_3);


        verticalLayout_20->addLayout(formLayout_19);

        line_19 = new QFrame(pageNodeProp_2);
        line_19->setObjectName(QString::fromUtf8("line_19"));
        line_19->setFrameShape(QFrame::HLine);
        line_19->setFrameShadow(QFrame::Sunken);

        verticalLayout_20->addWidget(line_19);

        formLayout_20 = new QFormLayout();
        formLayout_20->setSpacing(6);
        formLayout_20->setObjectName(QString::fromUtf8("formLayout_20"));
        label_50 = new QLabel(pageNodeProp_2);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        formLayout_20->setWidget(0, QFormLayout::LabelRole, label_50);

        cboClusterTreeNodeLabel = new QComboBox(pageNodeProp_2);
        cboClusterTreeNodeLabel->setObjectName(QString::fromUtf8("cboClusterTreeNodeLabel"));
        sizePolicy3.setHeightForWidth(cboClusterTreeNodeLabel->sizePolicy().hasHeightForWidth());
        cboClusterTreeNodeLabel->setSizePolicy(sizePolicy3);

        formLayout_20->setWidget(0, QFormLayout::FieldRole, cboClusterTreeNodeLabel);

        label_51 = new QLabel(pageNodeProp_2);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        formLayout_20->setWidget(1, QFormLayout::LabelRole, label_51);

        cboClusterTreeNodeFont = new QFontComboBox(pageNodeProp_2);
        cboClusterTreeNodeFont->setObjectName(QString::fromUtf8("cboClusterTreeNodeFont"));
        sizePolicy6.setHeightForWidth(cboClusterTreeNodeFont->sizePolicy().hasHeightForWidth());
        cboClusterTreeNodeFont->setSizePolicy(sizePolicy6);
        cboClusterTreeNodeFont->setMinimumSize(QSize(40, 0));

        formLayout_20->setWidget(1, QFormLayout::FieldRole, cboClusterTreeNodeFont);

        horizontalLayout_56 = new QHBoxLayout();
        horizontalLayout_56->setSpacing(6);
        horizontalLayout_56->setObjectName(QString::fromUtf8("horizontalLayout_56"));
        horizontalSpacer_47 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_56->addItem(horizontalSpacer_47);

        chkClusterTreeShowColorCategory = new QCheckBox(pageNodeProp_2);
        chkClusterTreeShowColorCategory->setObjectName(QString::fromUtf8("chkClusterTreeShowColorCategory"));

        horizontalLayout_56->addWidget(chkClusterTreeShowColorCategory);


        formLayout_20->setLayout(2, QFormLayout::FieldRole, horizontalLayout_56);

        horizontalLayout_57 = new QHBoxLayout();
        horizontalLayout_57->setSpacing(6);
        horizontalLayout_57->setObjectName(QString::fromUtf8("horizontalLayout_57"));
        horizontalSpacer_48 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_57->addItem(horizontalSpacer_48);

        chkClusterTreeShowShapeCategory = new QCheckBox(pageNodeProp_2);
        chkClusterTreeShowShapeCategory->setObjectName(QString::fromUtf8("chkClusterTreeShowShapeCategory"));

        horizontalLayout_57->addWidget(chkClusterTreeShowShapeCategory);


        formLayout_20->setLayout(3, QFormLayout::FieldRole, horizontalLayout_57);

        horizontalLayout_58 = new QHBoxLayout();
        horizontalLayout_58->setSpacing(6);
        horizontalLayout_58->setObjectName(QString::fromUtf8("horizontalLayout_58"));
        horizontalSpacer_49 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_58->addItem(horizontalSpacer_49);

        chkClusterTreeShowSizeCategory = new QCheckBox(pageNodeProp_2);
        chkClusterTreeShowSizeCategory->setObjectName(QString::fromUtf8("chkClusterTreeShowSizeCategory"));

        horizontalLayout_58->addWidget(chkClusterTreeShowSizeCategory);


        formLayout_20->setLayout(4, QFormLayout::FieldRole, horizontalLayout_58);

        label_52 = new QLabel(pageNodeProp_2);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        formLayout_20->setWidget(5, QFormLayout::LabelRole, label_52);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        cboClusterTreeNodeFontSize = new QComboBox(pageNodeProp_2);
        cboClusterTreeNodeFontSize->setObjectName(QString::fromUtf8("cboClusterTreeNodeFontSize"));
        cboClusterTreeNodeFontSize->setMinimumSize(QSize(40, 0));
        cboClusterTreeNodeFontSize->setEditable(true);
        cboClusterTreeNodeFontSize->setMinimumContentsLength(0);

        horizontalLayout_36->addWidget(cboClusterTreeNodeFontSize);

        tbClusterTreeNodeFontBold = new QToolButton(pageNodeProp_2);
        tbClusterTreeNodeFontBold->setObjectName(QString::fromUtf8("tbClusterTreeNodeFontBold"));
        tbClusterTreeNodeFontBold->setIcon(icon16);
        tbClusterTreeNodeFontBold->setCheckable(true);

        horizontalLayout_36->addWidget(tbClusterTreeNodeFontBold);

        tbClusterTreeNodeFontItalics = new QToolButton(pageNodeProp_2);
        tbClusterTreeNodeFontItalics->setObjectName(QString::fromUtf8("tbClusterTreeNodeFontItalics"));
        tbClusterTreeNodeFontItalics->setIcon(icon17);
        tbClusterTreeNodeFontItalics->setCheckable(true);

        horizontalLayout_36->addWidget(tbClusterTreeNodeFontItalics);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_36->addItem(horizontalSpacer_27);


        formLayout_20->setLayout(5, QFormLayout::FieldRole, horizontalLayout_36);


        verticalLayout_20->addLayout(formLayout_20);

        btnClusterTreeNodeLabelColor = new QtColorPicker(pageNodeProp_2);
        btnClusterTreeNodeLabelColor->setObjectName(QString::fromUtf8("btnClusterTreeNodeLabelColor"));

        verticalLayout_20->addWidget(btnClusterTreeNodeLabelColor);

        verticalSpacer_9 = new QSpacerItem(20, 165, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_9);

        toolBoxClusterTree->addItem(pageNodeProp_2, icon19, QString::fromUtf8("Node properties"));
        pageCollapsedNodeProp_2 = new QWidget();
        pageCollapsedNodeProp_2->setObjectName(QString::fromUtf8("pageCollapsedNodeProp_2"));
        pageCollapsedNodeProp_2->setGeometry(QRect(0, 0, 236, 743));
        verticalLayout_21 = new QVBoxLayout(pageCollapsedNodeProp_2);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        horizontalLayout_37->setContentsMargins(-1, -1, -1, 0);
        label_53 = new QLabel(pageCollapsedNodeProp_2);
        label_53->setObjectName(QString::fromUtf8("label_53"));

        horizontalLayout_37->addWidget(label_53);

        cboClusterTreeCollapsedNodeShape = new QComboBox(pageCollapsedNodeProp_2);
        cboClusterTreeCollapsedNodeShape->setObjectName(QString::fromUtf8("cboClusterTreeCollapsedNodeShape"));
        sizePolicy3.setHeightForWidth(cboClusterTreeCollapsedNodeShape->sizePolicy().hasHeightForWidth());
        cboClusterTreeCollapsedNodeShape->setSizePolicy(sizePolicy3);

        horizontalLayout_37->addWidget(cboClusterTreeCollapsedNodeShape);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer_28);


        verticalLayout_21->addLayout(horizontalLayout_37);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        horizontalLayout_38->setContentsMargins(-1, -1, -1, 4);
        chkClusterTreeCollapsedShowLabels = new QCheckBox(pageCollapsedNodeProp_2);
        chkClusterTreeCollapsedShowLabels->setObjectName(QString::fromUtf8("chkClusterTreeCollapsedShowLabels"));
        chkClusterTreeCollapsedShowLabels->setChecked(true);

        horizontalLayout_38->addWidget(chkClusterTreeCollapsedShowLabels);

        chkClusterTreeAbundanceInLabel = new QCheckBox(pageCollapsedNodeProp_2);
        chkClusterTreeAbundanceInLabel->setObjectName(QString::fromUtf8("chkClusterTreeAbundanceInLabel"));
        chkClusterTreeAbundanceInLabel->setChecked(true);

        horizontalLayout_38->addWidget(chkClusterTreeAbundanceInLabel);

        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_29);


        verticalLayout_21->addLayout(horizontalLayout_38);

        groupBox_6 = new QGroupBox(pageCollapsedNodeProp_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setFlat(true);
        verticalLayout_22 = new QVBoxLayout(groupBox_6);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        formLayout_21 = new QFormLayout();
        formLayout_21->setSpacing(6);
        formLayout_21->setObjectName(QString::fromUtf8("formLayout_21"));
        formLayout_21->setVerticalSpacing(1);
        label_54 = new QLabel(groupBox_6);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        formLayout_21->setWidget(0, QFormLayout::LabelRole, label_54);

        cboClusterTreeVariableTL = new QComboBox(groupBox_6);
        cboClusterTreeVariableTL->setObjectName(QString::fromUtf8("cboClusterTreeVariableTL"));

        formLayout_21->setWidget(0, QFormLayout::FieldRole, cboClusterTreeVariableTL);

        label_55 = new QLabel(groupBox_6);
        label_55->setObjectName(QString::fromUtf8("label_55"));

        formLayout_21->setWidget(1, QFormLayout::LabelRole, label_55);

        cboClusterTreeStatisticTL = new QComboBox(groupBox_6);
        cboClusterTreeStatisticTL->setObjectName(QString::fromUtf8("cboClusterTreeStatisticTL"));

        formLayout_21->setWidget(1, QFormLayout::FieldRole, cboClusterTreeStatisticTL);

        lblClusterTreeFactorLabelTL = new QLabel(groupBox_6);
        lblClusterTreeFactorLabelTL->setObjectName(QString::fromUtf8("lblClusterTreeFactorLabelTL"));

        formLayout_21->setWidget(2, QFormLayout::LabelRole, lblClusterTreeFactorLabelTL);

        lblPhylogenyMinTL_5 = new QLabel(groupBox_6);
        lblPhylogenyMinTL_5->setObjectName(QString::fromUtf8("lblPhylogenyMinTL_5"));

        formLayout_21->setWidget(3, QFormLayout::LabelRole, lblPhylogenyMinTL_5);

        spinClusterTreeMinTL = new QSpinBox(groupBox_6);
        spinClusterTreeMinTL->setObjectName(QString::fromUtf8("spinClusterTreeMinTL"));
        spinClusterTreeMinTL->setAccelerated(false);
        spinClusterTreeMinTL->setMinimum(0);
        spinClusterTreeMinTL->setMaximum(1000);
        spinClusterTreeMinTL->setValue(20);

        formLayout_21->setWidget(3, QFormLayout::FieldRole, spinClusterTreeMinTL);

        lblPhylogenyMaxTL_5 = new QLabel(groupBox_6);
        lblPhylogenyMaxTL_5->setObjectName(QString::fromUtf8("lblPhylogenyMaxTL_5"));

        formLayout_21->setWidget(4, QFormLayout::LabelRole, lblPhylogenyMaxTL_5);

        spinClusterTreeMaxTL = new QSpinBox(groupBox_6);
        spinClusterTreeMaxTL->setObjectName(QString::fromUtf8("spinClusterTreeMaxTL"));
        spinClusterTreeMaxTL->setAccelerated(false);
        spinClusterTreeMaxTL->setMinimum(0);
        spinClusterTreeMaxTL->setMaximum(10000);
        spinClusterTreeMaxTL->setValue(200);

        formLayout_21->setWidget(4, QFormLayout::FieldRole, spinClusterTreeMaxTL);

        spinClusterTreeFactorTL = new QDoubleSpinBox(groupBox_6);
        spinClusterTreeFactorTL->setObjectName(QString::fromUtf8("spinClusterTreeFactorTL"));
        spinClusterTreeFactorTL->setAccelerated(false);
        spinClusterTreeFactorTL->setMaximum(100);
        spinClusterTreeFactorTL->setValue(100);

        formLayout_21->setWidget(2, QFormLayout::FieldRole, spinClusterTreeFactorTL);


        verticalLayout_22->addLayout(formLayout_21);


        verticalLayout_21->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(pageCollapsedNodeProp_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setFlat(true);
        groupBox_7->setCheckable(false);
        verticalLayout_23 = new QVBoxLayout(groupBox_7);
        verticalLayout_23->setSpacing(4);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        verticalLayout_23->setContentsMargins(-1, 4, -1, -1);
        formLayout_22 = new QFormLayout();
        formLayout_22->setSpacing(6);
        formLayout_22->setObjectName(QString::fromUtf8("formLayout_22"));
        formLayout_22->setVerticalSpacing(1);
        label_56 = new QLabel(groupBox_7);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        formLayout_22->setWidget(0, QFormLayout::LabelRole, label_56);

        cboClusterTreeVariableML = new QComboBox(groupBox_7);
        cboClusterTreeVariableML->setObjectName(QString::fromUtf8("cboClusterTreeVariableML"));

        formLayout_22->setWidget(0, QFormLayout::FieldRole, cboClusterTreeVariableML);

        label_57 = new QLabel(groupBox_7);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        formLayout_22->setWidget(1, QFormLayout::LabelRole, label_57);

        cboClusterTreeStatisticML = new QComboBox(groupBox_7);
        cboClusterTreeStatisticML->setObjectName(QString::fromUtf8("cboClusterTreeStatisticML"));

        formLayout_22->setWidget(1, QFormLayout::FieldRole, cboClusterTreeStatisticML);

        lblClusterTreeFactorLabelML = new QLabel(groupBox_7);
        lblClusterTreeFactorLabelML->setObjectName(QString::fromUtf8("lblClusterTreeFactorLabelML"));

        formLayout_22->setWidget(2, QFormLayout::LabelRole, lblClusterTreeFactorLabelML);

        lblPhylogenyMinTL_6 = new QLabel(groupBox_7);
        lblPhylogenyMinTL_6->setObjectName(QString::fromUtf8("lblPhylogenyMinTL_6"));

        formLayout_22->setWidget(3, QFormLayout::LabelRole, lblPhylogenyMinTL_6);

        spinClusterTreeMinML = new QSpinBox(groupBox_7);
        spinClusterTreeMinML->setObjectName(QString::fromUtf8("spinClusterTreeMinML"));
        spinClusterTreeMinML->setMinimum(0);
        spinClusterTreeMinML->setMaximum(1000);
        spinClusterTreeMinML->setValue(20);

        formLayout_22->setWidget(3, QFormLayout::FieldRole, spinClusterTreeMinML);

        lblPhylogenyMaxTL_6 = new QLabel(groupBox_7);
        lblPhylogenyMaxTL_6->setObjectName(QString::fromUtf8("lblPhylogenyMaxTL_6"));

        formLayout_22->setWidget(4, QFormLayout::LabelRole, lblPhylogenyMaxTL_6);

        spinClusterTreeMaxML = new QSpinBox(groupBox_7);
        spinClusterTreeMaxML->setObjectName(QString::fromUtf8("spinClusterTreeMaxML"));
        spinClusterTreeMaxML->setMinimum(0);
        spinClusterTreeMaxML->setMaximum(10000);
        spinClusterTreeMaxML->setValue(200);

        formLayout_22->setWidget(4, QFormLayout::FieldRole, spinClusterTreeMaxML);

        spinClusterTreeFactorML = new QDoubleSpinBox(groupBox_7);
        spinClusterTreeFactorML->setObjectName(QString::fromUtf8("spinClusterTreeFactorML"));
        spinClusterTreeFactorML->setMaximum(100);
        spinClusterTreeFactorML->setValue(100);

        formLayout_22->setWidget(2, QFormLayout::FieldRole, spinClusterTreeFactorML);


        verticalLayout_23->addLayout(formLayout_22);


        verticalLayout_21->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(pageCollapsedNodeProp_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setFlat(true);
        groupBox_8->setCheckable(false);
        verticalLayout_24 = new QVBoxLayout(groupBox_8);
        verticalLayout_24->setSpacing(4);
        verticalLayout_24->setContentsMargins(11, 11, 11, 11);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(-1, 4, -1, -1);
        formLayout_23 = new QFormLayout();
        formLayout_23->setSpacing(6);
        formLayout_23->setObjectName(QString::fromUtf8("formLayout_23"));
        formLayout_23->setVerticalSpacing(1);
        label_58 = new QLabel(groupBox_8);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        formLayout_23->setWidget(0, QFormLayout::LabelRole, label_58);

        cboClusterTreeVariableBL = new QComboBox(groupBox_8);
        cboClusterTreeVariableBL->setObjectName(QString::fromUtf8("cboClusterTreeVariableBL"));

        formLayout_23->setWidget(0, QFormLayout::FieldRole, cboClusterTreeVariableBL);

        label_59 = new QLabel(groupBox_8);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        formLayout_23->setWidget(1, QFormLayout::LabelRole, label_59);

        cboClusterTreeStatisticBL = new QComboBox(groupBox_8);
        cboClusterTreeStatisticBL->setObjectName(QString::fromUtf8("cboClusterTreeStatisticBL"));

        formLayout_23->setWidget(1, QFormLayout::FieldRole, cboClusterTreeStatisticBL);

        lblClusterTreeFactorLabelBL = new QLabel(groupBox_8);
        lblClusterTreeFactorLabelBL->setObjectName(QString::fromUtf8("lblClusterTreeFactorLabelBL"));

        formLayout_23->setWidget(2, QFormLayout::LabelRole, lblClusterTreeFactorLabelBL);

        lblPhylogenyMinTL_7 = new QLabel(groupBox_8);
        lblPhylogenyMinTL_7->setObjectName(QString::fromUtf8("lblPhylogenyMinTL_7"));

        formLayout_23->setWidget(3, QFormLayout::LabelRole, lblPhylogenyMinTL_7);

        spinClusterTreeMinBL = new QSpinBox(groupBox_8);
        spinClusterTreeMinBL->setObjectName(QString::fromUtf8("spinClusterTreeMinBL"));
        spinClusterTreeMinBL->setMinimum(0);
        spinClusterTreeMinBL->setMaximum(1000);
        spinClusterTreeMinBL->setValue(20);

        formLayout_23->setWidget(3, QFormLayout::FieldRole, spinClusterTreeMinBL);

        lblPhylogenyMaxTL_7 = new QLabel(groupBox_8);
        lblPhylogenyMaxTL_7->setObjectName(QString::fromUtf8("lblPhylogenyMaxTL_7"));

        formLayout_23->setWidget(4, QFormLayout::LabelRole, lblPhylogenyMaxTL_7);

        spinClusterTreeMaxBL = new QSpinBox(groupBox_8);
        spinClusterTreeMaxBL->setObjectName(QString::fromUtf8("spinClusterTreeMaxBL"));
        spinClusterTreeMaxBL->setMinimum(0);
        spinClusterTreeMaxBL->setMaximum(10000);
        spinClusterTreeMaxBL->setValue(200);

        formLayout_23->setWidget(4, QFormLayout::FieldRole, spinClusterTreeMaxBL);

        spinClusterTreeFactorBL = new QDoubleSpinBox(groupBox_8);
        spinClusterTreeFactorBL->setObjectName(QString::fromUtf8("spinClusterTreeFactorBL"));
        spinClusterTreeFactorBL->setMaximum(100);
        spinClusterTreeFactorBL->setValue(100);

        formLayout_23->setWidget(2, QFormLayout::FieldRole, spinClusterTreeFactorBL);


        verticalLayout_24->addLayout(formLayout_23);


        verticalLayout_21->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(pageCollapsedNodeProp_2);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setFlat(true);
        groupBox_9->setCheckable(false);
        verticalLayout_25 = new QVBoxLayout(groupBox_9);
        verticalLayout_25->setSpacing(4);
        verticalLayout_25->setContentsMargins(11, 11, 11, 11);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        verticalLayout_25->setContentsMargins(-1, 4, -1, -1);
        formLayout_24 = new QFormLayout();
        formLayout_24->setSpacing(6);
        formLayout_24->setObjectName(QString::fromUtf8("formLayout_24"));
        formLayout_24->setVerticalSpacing(1);
        label_60 = new QLabel(groupBox_9);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        formLayout_24->setWidget(0, QFormLayout::LabelRole, label_60);

        cboClusterTreeVariableHeight = new QComboBox(groupBox_9);
        cboClusterTreeVariableHeight->setObjectName(QString::fromUtf8("cboClusterTreeVariableHeight"));

        formLayout_24->setWidget(0, QFormLayout::FieldRole, cboClusterTreeVariableHeight);

        label_61 = new QLabel(groupBox_9);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        formLayout_24->setWidget(1, QFormLayout::LabelRole, label_61);

        cboClusterTreeStatisticHeight = new QComboBox(groupBox_9);
        cboClusterTreeStatisticHeight->setObjectName(QString::fromUtf8("cboClusterTreeStatisticHeight"));

        formLayout_24->setWidget(1, QFormLayout::FieldRole, cboClusterTreeStatisticHeight);

        lblClusterTreeFactorLabelHeight = new QLabel(groupBox_9);
        lblClusterTreeFactorLabelHeight->setObjectName(QString::fromUtf8("lblClusterTreeFactorLabelHeight"));

        formLayout_24->setWidget(2, QFormLayout::LabelRole, lblClusterTreeFactorLabelHeight);

        lblPhylogenyMinTL_8 = new QLabel(groupBox_9);
        lblPhylogenyMinTL_8->setObjectName(QString::fromUtf8("lblPhylogenyMinTL_8"));

        formLayout_24->setWidget(3, QFormLayout::LabelRole, lblPhylogenyMinTL_8);

        spinClusterTreeMinHeight = new QSpinBox(groupBox_9);
        spinClusterTreeMinHeight->setObjectName(QString::fromUtf8("spinClusterTreeMinHeight"));
        spinClusterTreeMinHeight->setMinimum(0);
        spinClusterTreeMinHeight->setMaximum(100);
        spinClusterTreeMinHeight->setValue(20);

        formLayout_24->setWidget(3, QFormLayout::FieldRole, spinClusterTreeMinHeight);

        lblPhylogenyMaxTL_8 = new QLabel(groupBox_9);
        lblPhylogenyMaxTL_8->setObjectName(QString::fromUtf8("lblPhylogenyMaxTL_8"));

        formLayout_24->setWidget(4, QFormLayout::LabelRole, lblPhylogenyMaxTL_8);

        spinClusterTreeMaxHeight = new QSpinBox(groupBox_9);
        spinClusterTreeMaxHeight->setObjectName(QString::fromUtf8("spinClusterTreeMaxHeight"));
        spinClusterTreeMaxHeight->setMinimum(0);
        spinClusterTreeMaxHeight->setMaximum(10000);
        spinClusterTreeMaxHeight->setValue(100);

        formLayout_24->setWidget(4, QFormLayout::FieldRole, spinClusterTreeMaxHeight);

        spinClusterTreeFactorHeight = new QDoubleSpinBox(groupBox_9);
        spinClusterTreeFactorHeight->setObjectName(QString::fromUtf8("spinClusterTreeFactorHeight"));
        spinClusterTreeFactorHeight->setMaximum(100);
        spinClusterTreeFactorHeight->setValue(10);

        formLayout_24->setWidget(2, QFormLayout::FieldRole, spinClusterTreeFactorHeight);


        verticalLayout_25->addLayout(formLayout_24);


        verticalLayout_21->addWidget(groupBox_9);

        groupBox_10 = new QGroupBox(pageCollapsedNodeProp_2);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setFlat(true);
        groupBox_10->setCheckable(false);
        verticalLayout_26 = new QVBoxLayout(groupBox_10);
        verticalLayout_26->setSpacing(4);
        verticalLayout_26->setContentsMargins(11, 11, 11, 11);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        verticalLayout_26->setContentsMargins(-1, 4, -1, -1);
        formLayout_25 = new QFormLayout();
        formLayout_25->setSpacing(6);
        formLayout_25->setObjectName(QString::fromUtf8("formLayout_25"));
        formLayout_25->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_25->setVerticalSpacing(1);
        label_62 = new QLabel(groupBox_10);
        label_62->setObjectName(QString::fromUtf8("label_62"));

        formLayout_25->setWidget(0, QFormLayout::LabelRole, label_62);

        cboClusterTreeGradientStyle = new QComboBox(groupBox_10);
        cboClusterTreeGradientStyle->setObjectName(QString::fromUtf8("cboClusterTreeGradientStyle"));

        formLayout_25->setWidget(0, QFormLayout::FieldRole, cboClusterTreeGradientStyle);

        label_63 = new QLabel(groupBox_10);
        label_63->setObjectName(QString::fromUtf8("label_63"));

        formLayout_25->setWidget(2, QFormLayout::LabelRole, label_63);

        cboClusterTreeGradientFill = new QComboBox(groupBox_10);
        cboClusterTreeGradientFill->setObjectName(QString::fromUtf8("cboClusterTreeGradientFill"));

        formLayout_25->setWidget(2, QFormLayout::FieldRole, cboClusterTreeGradientFill);

        btnClusterTreeGradientSingleColor = new QtColorPicker(groupBox_10);
        btnClusterTreeGradientSingleColor->setObjectName(QString::fromUtf8("btnClusterTreeGradientSingleColor"));

        formLayout_25->setWidget(1, QFormLayout::FieldRole, btnClusterTreeGradientSingleColor);


        verticalLayout_26->addLayout(formLayout_25);


        verticalLayout_21->addWidget(groupBox_10);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_21->addItem(verticalSpacer_10);

        toolBoxClusterTree->addItem(pageCollapsedNodeProp_2, icon20, QString::fromUtf8("Collapsed node properties"));
        pageScaleBarProp_2 = new QWidget();
        pageScaleBarProp_2->setObjectName(QString::fromUtf8("pageScaleBarProp_2"));
        pageScaleBarProp_2->setGeometry(QRect(0, 0, 177, 262));
        verticalLayout_27 = new QVBoxLayout(pageScaleBarProp_2);
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setContentsMargins(11, 11, 11, 11);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        chkClusterTreeShowScale = new QCheckBox(pageScaleBarProp_2);
        chkClusterTreeShowScale->setObjectName(QString::fromUtf8("chkClusterTreeShowScale"));
        chkClusterTreeShowScale->setChecked(false);

        verticalLayout_27->addWidget(chkClusterTreeShowScale);

        line_20 = new QFrame(pageScaleBarProp_2);
        line_20->setObjectName(QString::fromUtf8("line_20"));
        line_20->setFrameShape(QFrame::HLine);
        line_20->setFrameShadow(QFrame::Sunken);

        verticalLayout_27->addWidget(line_20);

        chkClusterTreeScaleAutomatic = new QCheckBox(pageScaleBarProp_2);
        chkClusterTreeScaleAutomatic->setObjectName(QString::fromUtf8("chkClusterTreeScaleAutomatic"));
        chkClusterTreeScaleAutomatic->setChecked(true);

        verticalLayout_27->addWidget(chkClusterTreeScaleAutomatic);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        label_64 = new QLabel(pageScaleBarProp_2);
        label_64->setObjectName(QString::fromUtf8("label_64"));

        horizontalLayout_39->addWidget(label_64);

        spinClusterTreeScale = new QDoubleSpinBox(pageScaleBarProp_2);
        spinClusterTreeScale->setObjectName(QString::fromUtf8("spinClusterTreeScale"));
        spinClusterTreeScale->setEnabled(false);
        spinClusterTreeScale->setDecimals(3);
        spinClusterTreeScale->setMaximum(1000);
        spinClusterTreeScale->setSingleStep(0.01);
        spinClusterTreeScale->setValue(1);

        horizontalLayout_39->addWidget(spinClusterTreeScale);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_31);


        verticalLayout_27->addLayout(horizontalLayout_39);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        label_65 = new QLabel(pageScaleBarProp_2);
        label_65->setObjectName(QString::fromUtf8("label_65"));

        horizontalLayout_40->addWidget(label_65);

        spinClusterTreeScaleSignDigits = new QSpinBox(pageScaleBarProp_2);
        spinClusterTreeScaleSignDigits->setObjectName(QString::fromUtf8("spinClusterTreeScaleSignDigits"));
        spinClusterTreeScaleSignDigits->setMinimum(1);
        spinClusterTreeScaleSignDigits->setMaximum(16);
        spinClusterTreeScaleSignDigits->setValue(2);

        horizontalLayout_40->addWidget(spinClusterTreeScaleSignDigits);

        horizontalSpacer_32 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_32);


        verticalLayout_27->addLayout(horizontalLayout_40);

        line_21 = new QFrame(pageScaleBarProp_2);
        line_21->setObjectName(QString::fromUtf8("line_21"));
        line_21->setFrameShape(QFrame::HLine);
        line_21->setFrameShadow(QFrame::Sunken);

        verticalLayout_27->addWidget(line_21);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        label_66 = new QLabel(pageScaleBarProp_2);
        label_66->setObjectName(QString::fromUtf8("label_66"));

        horizontalLayout_41->addWidget(label_66);

        spinClusterTreeScaleWidth = new QSpinBox(pageScaleBarProp_2);
        spinClusterTreeScaleWidth->setObjectName(QString::fromUtf8("spinClusterTreeScaleWidth"));
        spinClusterTreeScaleWidth->setMinimum(1);
        spinClusterTreeScaleWidth->setMaximum(100);
        spinClusterTreeScaleWidth->setValue(1);

        horizontalLayout_41->addWidget(spinClusterTreeScaleWidth);

        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_41->addItem(horizontalSpacer_33);


        verticalLayout_27->addLayout(horizontalLayout_41);

        line_22 = new QFrame(pageScaleBarProp_2);
        line_22->setObjectName(QString::fromUtf8("line_22"));
        line_22->setFrameShape(QFrame::HLine);
        line_22->setFrameShadow(QFrame::Sunken);

        verticalLayout_27->addWidget(line_22);

        formLayout_26 = new QFormLayout();
        formLayout_26->setSpacing(6);
        formLayout_26->setObjectName(QString::fromUtf8("formLayout_26"));
        label_67 = new QLabel(pageScaleBarProp_2);
        label_67->setObjectName(QString::fromUtf8("label_67"));

        formLayout_26->setWidget(0, QFormLayout::LabelRole, label_67);

        cboClusterTreeScaleFont = new QFontComboBox(pageScaleBarProp_2);
        cboClusterTreeScaleFont->setObjectName(QString::fromUtf8("cboClusterTreeScaleFont"));
        sizePolicy3.setHeightForWidth(cboClusterTreeScaleFont->sizePolicy().hasHeightForWidth());
        cboClusterTreeScaleFont->setSizePolicy(sizePolicy3);
        cboClusterTreeScaleFont->setMinimumSize(QSize(40, 0));

        formLayout_26->setWidget(0, QFormLayout::FieldRole, cboClusterTreeScaleFont);


        verticalLayout_27->addLayout(formLayout_26);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setSpacing(6);
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        label_68 = new QLabel(pageScaleBarProp_2);
        label_68->setObjectName(QString::fromUtf8("label_68"));

        horizontalLayout_42->addWidget(label_68);

        cboClusterTreeScaleFontSize = new QComboBox(pageScaleBarProp_2);
        cboClusterTreeScaleFontSize->setObjectName(QString::fromUtf8("cboClusterTreeScaleFontSize"));
        cboClusterTreeScaleFontSize->setMinimumSize(QSize(40, 0));
        cboClusterTreeScaleFontSize->setEditable(true);
        cboClusterTreeScaleFontSize->setMinimumContentsLength(0);

        horizontalLayout_42->addWidget(cboClusterTreeScaleFontSize);

        tbClusterTreeScaleFontBold = new QToolButton(pageScaleBarProp_2);
        tbClusterTreeScaleFontBold->setObjectName(QString::fromUtf8("tbClusterTreeScaleFontBold"));
        tbClusterTreeScaleFontBold->setIcon(icon16);
        tbClusterTreeScaleFontBold->setCheckable(true);

        horizontalLayout_42->addWidget(tbClusterTreeScaleFontBold);

        tbClusterTreeScaleFontItalics = new QToolButton(pageScaleBarProp_2);
        tbClusterTreeScaleFontItalics->setObjectName(QString::fromUtf8("tbClusterTreeScaleFontItalics"));
        tbClusterTreeScaleFontItalics->setIcon(icon17);
        tbClusterTreeScaleFontItalics->setCheckable(true);

        horizontalLayout_42->addWidget(tbClusterTreeScaleFontItalics);

        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_42->addItem(horizontalSpacer_34);


        verticalLayout_27->addLayout(horizontalLayout_42);

        btnClusterTreeScaleLabelColor = new QtColorPicker(pageScaleBarProp_2);
        btnClusterTreeScaleLabelColor->setObjectName(QString::fromUtf8("btnClusterTreeScaleLabelColor"));

        verticalLayout_27->addWidget(btnClusterTreeScaleLabelColor);

        verticalSpacer_11 = new QSpacerItem(20, 72, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_27->addItem(verticalSpacer_11);

        toolBoxClusterTree->addItem(pageScaleBarProp_2, icon21, QString::fromUtf8("Scale bar properties"));
        pageTreeFinder_2 = new QWidget();
        pageTreeFinder_2->setObjectName(QString::fromUtf8("pageTreeFinder_2"));
        pageTreeFinder_2->setGeometry(QRect(0, 0, 98, 143));
        verticalLayout_28 = new QVBoxLayout(pageTreeFinder_2);
        verticalLayout_28->setSpacing(6);
        verticalLayout_28->setContentsMargins(11, 11, 11, 11);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        listClusterTreeSearchResults = new QListWidget(pageTreeFinder_2);
        listClusterTreeSearchResults->setObjectName(QString::fromUtf8("listClusterTreeSearchResults"));
        listClusterTreeSearchResults->setSortingEnabled(true);

        verticalLayout_28->addWidget(listClusterTreeSearchResults);

        cboClusterTreeSearchType = new QComboBox(pageTreeFinder_2);
        cboClusterTreeSearchType->setObjectName(QString::fromUtf8("cboClusterTreeSearchType"));

        verticalLayout_28->addWidget(cboClusterTreeSearchType);

        txtClusterTreeSearchString = new QLineEdit(pageTreeFinder_2);
        txtClusterTreeSearchString->setObjectName(QString::fromUtf8("txtClusterTreeSearchString"));

        verticalLayout_28->addWidget(txtClusterTreeSearchString);

        toolBoxClusterTree->addItem(pageTreeFinder_2, icon22, QString::fromUtf8("Search tree"));
        pageTreeInspector_2 = new QWidget();
        pageTreeInspector_2->setObjectName(QString::fromUtf8("pageTreeInspector_2"));
        pageTreeInspector_2->setGeometry(QRect(0, 0, 98, 89));
        verticalLayout_29 = new QVBoxLayout(pageTreeInspector_2);
        verticalLayout_29->setSpacing(6);
        verticalLayout_29->setContentsMargins(11, 11, 11, 11);
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        txtClusterTreeInspector = new QTextBrowser(pageTreeInspector_2);
        txtClusterTreeInspector->setObjectName(QString::fromUtf8("txtClusterTreeInspector"));

        verticalLayout_29->addWidget(txtClusterTreeInspector);

        toolBoxClusterTree->addItem(pageTreeInspector_2, icon23, QString::fromUtf8("Tree inspector"));
        splitter->addWidget(toolBoxClusterTree);
        anotherLayoutWidget = new QWidget(splitter);
        anotherLayoutWidget->setObjectName(QString::fromUtf8("anotherLayoutWidget"));
        verticalLayout_30 = new QVBoxLayout(anotherLayoutWidget);
        verticalLayout_30->setSpacing(6);
        verticalLayout_30->setContentsMargins(11, 11, 11, 11);
        verticalLayout_30->setObjectName(QString::fromUtf8("verticalLayout_30"));
        verticalLayout_30->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_30->setContentsMargins(0, 0, 0, 0);
        clusterTreeViewport = new TreeViewport(anotherLayoutWidget);
        clusterTreeViewport->setObjectName(QString::fromUtf8("clusterTreeViewport"));
        clusterTreeViewport->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        clusterTreeViewport->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_30->addWidget(clusterTreeViewport);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        tbClusterTreeRun = new QToolButton(anotherLayoutWidget);
        tbClusterTreeRun->setObjectName(QString::fromUtf8("tbClusterTreeRun"));
        QIcon icon42;
        icon42.addFile(QString::fromUtf8(":/icons/icons/clusterTree-run.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbClusterTreeRun->setIcon(icon42);
        tbClusterTreeRun->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeRun);

        horizontalSpacer_37 = new QSpacerItem(12, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_37);

        tbClusterTreeToggleCollapse = new QToolButton(anotherLayoutWidget);
        tbClusterTreeToggleCollapse->setObjectName(QString::fromUtf8("tbClusterTreeToggleCollapse"));
        tbClusterTreeToggleCollapse->setIcon(icon20);
        tbClusterTreeToggleCollapse->setIconSize(QSize(24, 24));
        tbClusterTreeToggleCollapse->setAutoRaise(false);
        tbClusterTreeToggleCollapse->setArrowType(Qt::NoArrow);

        horizontalLayout_15->addWidget(tbClusterTreeToggleCollapse);

        tbClusterTreeCollapseComplement = new QToolButton(anotherLayoutWidget);
        tbClusterTreeCollapseComplement->setObjectName(QString::fromUtf8("tbClusterTreeCollapseComplement"));
        tbClusterTreeCollapseComplement->setIcon(icon24);
        tbClusterTreeCollapseComplement->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeCollapseComplement);

        tbClusterTreeCollapseAll = new QToolButton(anotherLayoutWidget);
        tbClusterTreeCollapseAll->setObjectName(QString::fromUtf8("tbClusterTreeCollapseAll"));
        tbClusterTreeCollapseAll->setIcon(icon25);
        tbClusterTreeCollapseAll->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeCollapseAll);

        tbClusterTreeUncollapseAll = new QToolButton(anotherLayoutWidget);
        tbClusterTreeUncollapseAll->setObjectName(QString::fromUtf8("tbClusterTreeUncollapseAll"));
        tbClusterTreeUncollapseAll->setIcon(icon15);
        tbClusterTreeUncollapseAll->setIconSize(QSize(24, 24));
        tbClusterTreeUncollapseAll->setAutoRaise(false);
        tbClusterTreeUncollapseAll->setArrowType(Qt::NoArrow);

        horizontalLayout_15->addWidget(tbClusterTreeUncollapseAll);

        tbClusterTreeCollapseToScreen = new QToolButton(anotherLayoutWidget);
        tbClusterTreeCollapseToScreen->setObjectName(QString::fromUtf8("tbClusterTreeCollapseToScreen"));
        tbClusterTreeCollapseToScreen->setIcon(icon26);
        tbClusterTreeCollapseToScreen->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeCollapseToScreen);

        tbClusterTreeAutoCollapse = new QToolButton(anotherLayoutWidget);
        tbClusterTreeAutoCollapse->setObjectName(QString::fromUtf8("tbClusterTreeAutoCollapse"));
        tbClusterTreeAutoCollapse->setIcon(icon27);
        tbClusterTreeAutoCollapse->setIconSize(QSize(26, 24));
        tbClusterTreeAutoCollapse->setCheckable(true);

        horizontalLayout_15->addWidget(tbClusterTreeAutoCollapse);

        horizontalSpacer_35 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_35);

        label_69 = new QLabel(anotherLayoutWidget);
        label_69->setObjectName(QString::fromUtf8("label_69"));

        horizontalLayout_15->addWidget(label_69);

        cboClusterTreeParsimony = new QComboBox(anotherLayoutWidget);
        cboClusterTreeParsimony->setObjectName(QString::fromUtf8("cboClusterTreeParsimony"));
        sizePolicy7.setHeightForWidth(cboClusterTreeParsimony->sizePolicy().hasHeightForWidth());
        cboClusterTreeParsimony->setSizePolicy(sizePolicy7);
        cboClusterTreeParsimony->setInsertPolicy(QComboBox::InsertAlphabetically);
        cboClusterTreeParsimony->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_15->addWidget(cboClusterTreeParsimony);

        horizontalSpacer_36 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_36);

        tbClusterTreeReroot = new QToolButton(anotherLayoutWidget);
        tbClusterTreeReroot->setObjectName(QString::fromUtf8("tbClusterTreeReroot"));
        tbClusterTreeReroot->setIcon(icon28);
        tbClusterTreeReroot->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeReroot);

        tbClusterTreeRotateBranches = new QToolButton(anotherLayoutWidget);
        tbClusterTreeRotateBranches->setObjectName(QString::fromUtf8("tbClusterTreeRotateBranches"));
        tbClusterTreeRotateBranches->setIcon(icon29);
        tbClusterTreeRotateBranches->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeRotateBranches);

        tbClusterTreeAlphabetical = new QToolButton(anotherLayoutWidget);
        tbClusterTreeAlphabetical->setObjectName(QString::fromUtf8("tbClusterTreeAlphabetical"));
        tbClusterTreeAlphabetical->setIcon(icon30);
        tbClusterTreeAlphabetical->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeAlphabetical);

        tbClusterTreeLadderizeBottom = new QToolButton(anotherLayoutWidget);
        tbClusterTreeLadderizeBottom->setObjectName(QString::fromUtf8("tbClusterTreeLadderizeBottom"));
        tbClusterTreeLadderizeBottom->setIcon(icon31);
        tbClusterTreeLadderizeBottom->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeLadderizeBottom);

        tbClusterTreeLadderizeTop = new QToolButton(anotherLayoutWidget);
        tbClusterTreeLadderizeTop->setObjectName(QString::fromUtf8("tbClusterTreeLadderizeTop"));
        tbClusterTreeLadderizeTop->setIcon(icon32);
        tbClusterTreeLadderizeTop->setIconSize(QSize(24, 24));

        horizontalLayout_15->addWidget(tbClusterTreeLadderizeTop);


        verticalLayout_30->addLayout(horizontalLayout_15);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_53 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_53);

        label_84 = new QLabel(anotherLayoutWidget);
        label_84->setObjectName(QString::fromUtf8("label_84"));

        horizontalLayout_13->addWidget(label_84);

        cboGradientField = new QComboBox(anotherLayoutWidget);
        cboGradientField->setObjectName(QString::fromUtf8("cboGradientField"));

        horizontalLayout_13->addWidget(cboGradientField);

        chkGradientLabels = new QCheckBox(anotherLayoutWidget);
        chkGradientLabels->setObjectName(QString::fromUtf8("chkGradientLabels"));
        chkGradientLabels->setChecked(true);

        horizontalLayout_13->addWidget(chkGradientLabels);


        verticalLayout_30->addLayout(horizontalLayout_13);

        splitter->addWidget(anotherLayoutWidget);

        horizontalLayout_43->addWidget(splitter);

        QIcon icon43;
        icon43.addFile(QString::fromUtf8(":/icons/icons/clusterTree.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabClusterTree, icon43, QString());
        tabDissMatrixPlot = new QWidget();
        tabDissMatrixPlot->setObjectName(QString::fromUtf8("tabDissMatrixPlot"));
        verticalLayout_5 = new QVBoxLayout(tabDissMatrixPlot);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lblDissimilarityLabel = new QLabel(tabDissMatrixPlot);
        lblDissimilarityLabel->setObjectName(QString::fromUtf8("lblDissimilarityLabel"));
        lblDissimilarityLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lblDissimilarityLabel);

        dissMatrixViewport = new QGraphicsView(tabDissMatrixPlot);
        dissMatrixViewport->setObjectName(QString::fromUtf8("dissMatrixViewport"));

        verticalLayout_5->addWidget(dissMatrixViewport);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        label_71 = new QLabel(tabDissMatrixPlot);
        label_71->setObjectName(QString::fromUtf8("label_71"));

        horizontalLayout_44->addWidget(label_71);

        cboDissimilarityMatrixSortMethod = new QComboBox(tabDissMatrixPlot);
        cboDissimilarityMatrixSortMethod->setObjectName(QString::fromUtf8("cboDissimilarityMatrixSortMethod"));

        horizontalLayout_44->addWidget(cboDissimilarityMatrixSortMethod);

        tbDissimilarityMatrixRunSort = new QToolButton(tabDissMatrixPlot);
        tbDissimilarityMatrixRunSort->setObjectName(QString::fromUtf8("tbDissimilarityMatrixRunSort"));
        QIcon icon44;
        icon44.addFile(QString::fromUtf8(":/icons/icons/DissimilarityMatrixViewRun.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbDissimilarityMatrixRunSort->setIcon(icon44);
        tbDissimilarityMatrixRunSort->setIconSize(QSize(24, 24));

        horizontalLayout_44->addWidget(tbDissimilarityMatrixRunSort);

        horizontalSpacer_40 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_40);

        label_77 = new QLabel(tabDissMatrixPlot);
        label_77->setObjectName(QString::fromUtf8("label_77"));

        horizontalLayout_44->addWidget(label_77);

        spinDissimilarityMatrixMinSize = new QSpinBox(tabDissMatrixPlot);
        spinDissimilarityMatrixMinSize->setObjectName(QString::fromUtf8("spinDissimilarityMatrixMinSize"));
        spinDissimilarityMatrixMinSize->setMinimum(1);
        spinDissimilarityMatrixMinSize->setMaximum(100);
        spinDissimilarityMatrixMinSize->setValue(1);

        horizontalLayout_44->addWidget(spinDissimilarityMatrixMinSize);

        chkDissMatrixSelectionTransparency = new QCheckBox(tabDissMatrixPlot);
        chkDissMatrixSelectionTransparency->setObjectName(QString::fromUtf8("chkDissMatrixSelectionTransparency"));
        chkDissMatrixSelectionTransparency->setChecked(true);

        horizontalLayout_44->addWidget(chkDissMatrixSelectionTransparency);


        verticalLayout_5->addLayout(horizontalLayout_44);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_73 = new QLabel(tabDissMatrixPlot);
        label_73->setObjectName(QString::fromUtf8("label_73"));

        horizontalLayout_16->addWidget(label_73);

        cboDissimilarityMatrixColorMap = new QComboBox(tabDissMatrixPlot);
        cboDissimilarityMatrixColorMap->setObjectName(QString::fromUtf8("cboDissimilarityMatrixColorMap"));
        cboDissimilarityMatrixColorMap->setInsertPolicy(QComboBox::InsertAlphabetically);
        cboDissimilarityMatrixColorMap->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_16->addWidget(cboDissimilarityMatrixColorMap);

        chkDissimilarityMatrixFullRange = new QCheckBox(tabDissMatrixPlot);
        chkDissimilarityMatrixFullRange->setObjectName(QString::fromUtf8("chkDissimilarityMatrixFullRange"));
        chkDissimilarityMatrixFullRange->setChecked(true);

        horizontalLayout_16->addWidget(chkDissimilarityMatrixFullRange);

        chkDissimilarityMatrixThreshold = new QCheckBox(tabDissMatrixPlot);
        chkDissimilarityMatrixThreshold->setObjectName(QString::fromUtf8("chkDissimilarityMatrixThreshold"));

        horizontalLayout_16->addWidget(chkDissimilarityMatrixThreshold);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout_16);

        QIcon icon45;
        icon45.addFile(QString::fromUtf8(":/icons/icons/DissimilarityMatrixView.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabDissMatrixPlot, icon45, QString());
        tabBoxPlot = new QWidget();
        tabBoxPlot->setObjectName(QString::fromUtf8("tabBoxPlot"));
        horizontalLayout_14 = new QHBoxLayout(tabBoxPlot);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        tableBoxPlot = new QTableWidget(tabBoxPlot);
        if (tableBoxPlot->columnCount() < 5)
            tableBoxPlot->setColumnCount(5);
        if (tableBoxPlot->rowCount() < 5)
            tableBoxPlot->setRowCount(5);
        tableBoxPlot->setObjectName(QString::fromUtf8("tableBoxPlot"));
        sizePolicy8.setHeightForWidth(tableBoxPlot->sizePolicy().hasHeightForWidth());
        tableBoxPlot->setSizePolicy(sizePolicy8);
        tableBoxPlot->setAlternatingRowColors(true);
        tableBoxPlot->setCornerButtonEnabled(true);
        tableBoxPlot->setRowCount(5);
        tableBoxPlot->setColumnCount(5);
        tableBoxPlot->horizontalHeader()->setVisible(false);
        tableBoxPlot->horizontalHeader()->setCascadingSectionResizes(true);
        tableBoxPlot->horizontalHeader()->setDefaultSectionSize(100);
        tableBoxPlot->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableBoxPlot->horizontalHeader()->setStretchLastSection(false);
        tableBoxPlot->verticalHeader()->setVisible(false);
        tableBoxPlot->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout_14->addWidget(tableBoxPlot);

        QIcon icon46;
        icon46.addFile(QString::fromUtf8(":/icons/icons/box_closed.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabBoxPlot, icon46, QString());
        tabDissimilarityMatrix = new QWidget();
        tabDissimilarityMatrix->setObjectName(QString::fromUtf8("tabDissimilarityMatrix"));
        sizePolicy.setHeightForWidth(tabDissimilarityMatrix->sizePolicy().hasHeightForWidth());
        tabDissimilarityMatrix->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(tabDissimilarityMatrix);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tableDissimilarityMatrix = new QTableWidget(tabDissimilarityMatrix);
        if (tableDissimilarityMatrix->columnCount() < 5)
            tableDissimilarityMatrix->setColumnCount(5);
        if (tableDissimilarityMatrix->rowCount() < 5)
            tableDissimilarityMatrix->setRowCount(5);
        tableDissimilarityMatrix->setObjectName(QString::fromUtf8("tableDissimilarityMatrix"));
        sizePolicy8.setHeightForWidth(tableDissimilarityMatrix->sizePolicy().hasHeightForWidth());
        tableDissimilarityMatrix->setSizePolicy(sizePolicy8);
        tableDissimilarityMatrix->setAlternatingRowColors(true);
        tableDissimilarityMatrix->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableDissimilarityMatrix->setCornerButtonEnabled(true);
        tableDissimilarityMatrix->setRowCount(5);
        tableDissimilarityMatrix->setColumnCount(5);
        tableDissimilarityMatrix->horizontalHeader()->setVisible(false);
        tableDissimilarityMatrix->horizontalHeader()->setCascadingSectionResizes(true);
        tableDissimilarityMatrix->horizontalHeader()->setDefaultSectionSize(100);
        tableDissimilarityMatrix->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableDissimilarityMatrix->horizontalHeader()->setStretchLastSection(false);
        tableDissimilarityMatrix->verticalHeader()->setVisible(false);
        tableDissimilarityMatrix->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout_3->addWidget(tableDissimilarityMatrix);

        QIcon icon47;
        icon47.addFile(QString::fromUtf8(":/icons/icons/layer.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabDissimilarityMatrix, icon47, QString());
        tabResemblanceMeasureScatterplot = new QWidget();
        tabResemblanceMeasureScatterplot->setObjectName(QString::fromUtf8("tabResemblanceMeasureScatterplot"));
        verticalLayout_33 = new QVBoxLayout(tabResemblanceMeasureScatterplot);
        verticalLayout_33->setSpacing(6);
        verticalLayout_33->setContentsMargins(11, 11, 11, 11);
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        resemblanceScatterplotFrame = new QFrame(tabResemblanceMeasureScatterplot);
        resemblanceScatterplotFrame->setObjectName(QString::fromUtf8("resemblanceScatterplotFrame"));
        sizePolicy11.setHeightForWidth(resemblanceScatterplotFrame->sizePolicy().hasHeightForWidth());
        resemblanceScatterplotFrame->setSizePolicy(sizePolicy11);
        resemblanceScatterplotFrame->setFrameShape(QFrame::StyledPanel);
        resemblanceScatterplotFrame->setFrameShadow(QFrame::Plain);
        horizontalLayout_46 = new QHBoxLayout(resemblanceScatterplotFrame);
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        qwtResemblanceScatterplot = new QwtPlot(resemblanceScatterplotFrame);
        qwtResemblanceScatterplot->setObjectName(QString::fromUtf8("qwtResemblanceScatterplot"));
        sizePolicy2.setHeightForWidth(qwtResemblanceScatterplot->sizePolicy().hasHeightForWidth());
        qwtResemblanceScatterplot->setSizePolicy(sizePolicy2);
        qwtResemblanceScatterplot->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_46->addWidget(qwtResemblanceScatterplot);


        verticalLayout_33->addWidget(resemblanceScatterplotFrame);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        label_74 = new QLabel(tabResemblanceMeasureScatterplot);
        label_74->setObjectName(QString::fromUtf8("label_74"));

        horizontalLayout_45->addWidget(label_74);

        cboResemblenceXaxis = new QComboBox(tabResemblanceMeasureScatterplot);
        cboResemblenceXaxis->setObjectName(QString::fromUtf8("cboResemblenceXaxis"));

        horizontalLayout_45->addWidget(cboResemblenceXaxis);

        label_75 = new QLabel(tabResemblanceMeasureScatterplot);
        label_75->setObjectName(QString::fromUtf8("label_75"));

        horizontalLayout_45->addWidget(label_75);

        cboResemblenceYaxis = new QComboBox(tabResemblanceMeasureScatterplot);
        cboResemblenceYaxis->setObjectName(QString::fromUtf8("cboResemblenceYaxis"));

        horizontalLayout_45->addWidget(cboResemblenceYaxis);

        btnScatterplotRun = new QPushButton(tabResemblanceMeasureScatterplot);
        btnScatterplotRun->setObjectName(QString::fromUtf8("btnScatterplotRun"));

        horizontalLayout_45->addWidget(btnScatterplotRun);

        horizontalSpacer_41 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_41);

        chkShowBestFit = new QCheckBox(tabResemblanceMeasureScatterplot);
        chkShowBestFit->setObjectName(QString::fromUtf8("chkShowBestFit"));
        chkShowBestFit->setChecked(true);

        horizontalLayout_45->addWidget(chkShowBestFit);

        label_76 = new QLabel(tabResemblanceMeasureScatterplot);
        label_76->setObjectName(QString::fromUtf8("label_76"));

        horizontalLayout_45->addWidget(label_76);

        spinScatterplotSize = new QSpinBox(tabResemblanceMeasureScatterplot);
        spinScatterplotSize->setObjectName(QString::fromUtf8("spinScatterplotSize"));
        spinScatterplotSize->setMinimum(1);
        spinScatterplotSize->setValue(8);

        horizontalLayout_45->addWidget(spinScatterplotSize);


        verticalLayout_33->addLayout(horizontalLayout_45);

        QIcon icon48;
        icon48.addFile(QString::fromUtf8(":/icons/icons/scatterplot.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabResemblanceMeasureScatterplot, icon48, QString());
        tabLog = new QWidget();
        tabLog->setObjectName(QString::fromUtf8("tabLog"));
        verticalLayout = new QVBoxLayout(tabLog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        txtLog = new QTextEdit(tabLog);
        txtLog->setObjectName(QString::fromUtf8("txtLog"));
        QSizePolicy sizePolicy12(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(1);
        sizePolicy12.setHeightForWidth(txtLog->sizePolicy().hasHeightForWidth());
        txtLog->setSizePolicy(sizePolicy12);
        txtLog->setFrameShape(QFrame::Box);
        txtLog->setFrameShadow(QFrame::Plain);
        txtLog->setMidLineWidth(0);
        txtLog->setReadOnly(true);
        txtLog->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(txtLog);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_51 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_51);

        btnSaveLog = new QPushButton(tabLog);
        btnSaveLog->setObjectName(QString::fromUtf8("btnSaveLog"));
        QIcon icon49;
        icon49.addFile(QString::fromUtf8(":/icons/icons/log_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSaveLog->setIcon(icon49);

        horizontalLayout_11->addWidget(btnSaveLog);

        btnClearLog = new QPushButton(tabLog);
        btnClearLog->setObjectName(QString::fromUtf8("btnClearLog"));
        btnClearLog->setIcon(icon7);

        horizontalLayout_11->addWidget(btnClearLog);


        verticalLayout->addLayout(horizontalLayout_11);

        QIcon icon50;
        icon50.addFile(QString::fromUtf8(":/icons/icons/pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabLog, icon50, QString());

        horizontalLayout_9->addWidget(tabWidget);

        GUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1093, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuSave_legend = new QMenu(menu_File);
        menuSave_legend->setObjectName(QString::fromUtf8("menuSave_legend"));
        mnuFileExportSVG = new QMenu(menu_File);
        mnuFileExportSVG->setObjectName(QString::fromUtf8("mnuFileExportSVG"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuAnalysis = new QMenu(menuBar);
        menuAnalysis->setObjectName(QString::fromUtf8("menuAnalysis"));
        menuInspect = new QMenu(menuBar);
        menuInspect->setObjectName(QString::fromUtf8("menuInspect"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        GUIClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(GUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setAutoFillBackground(false);
        statusBar->setSizeGripEnabled(true);
        GUIClass->setStatusBar(statusBar);
        dockLegend = new QDockWidget(GUIClass);
        dockLegend->setObjectName(QString::fromUtf8("dockLegend"));
        dockLegend->setMinimumSize(QSize(200, 351));
        dockLegend->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockLegend->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_11 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        groupColorLegend = new QGroupBox(dockWidgetContents_2);
        groupColorLegend->setObjectName(QString::fromUtf8("groupColorLegend"));
        QSizePolicy sizePolicy13(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy13.setHorizontalStretch(0);
        sizePolicy13.setVerticalStretch(1);
        sizePolicy13.setHeightForWidth(groupColorLegend->sizePolicy().hasHeightForWidth());
        groupColorLegend->setSizePolicy(sizePolicy13);
        groupColorLegend->setFlat(true);
        groupColorLegend->setCheckable(false);
        horizontalLayout_2 = new QHBoxLayout(groupColorLegend);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        legendColor = new QwtLegend(groupColorLegend);
        legendColor->setObjectName(QString::fromUtf8("legendColor"));
        legendColor->setFrameShape(QFrame::StyledPanel);
        legendColor->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(legendColor);


        verticalLayout_11->addWidget(groupColorLegend);

        groupShapeLegend = new QGroupBox(dockWidgetContents_2);
        groupShapeLegend->setObjectName(QString::fromUtf8("groupShapeLegend"));
        sizePolicy13.setHeightForWidth(groupShapeLegend->sizePolicy().hasHeightForWidth());
        groupShapeLegend->setSizePolicy(sizePolicy13);
        groupShapeLegend->setFlat(true);
        horizontalLayout_5 = new QHBoxLayout(groupShapeLegend);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        legendShape = new QwtLegend(groupShapeLegend);
        legendShape->setObjectName(QString::fromUtf8("legendShape"));
        legendShape->setFrameShape(QFrame::StyledPanel);
        legendShape->setFrameShadow(QFrame::Raised);

        horizontalLayout_5->addWidget(legendShape);


        verticalLayout_11->addWidget(groupShapeLegend);

        groupSizeLegend = new QGroupBox(dockWidgetContents_2);
        groupSizeLegend->setObjectName(QString::fromUtf8("groupSizeLegend"));
        sizePolicy13.setHeightForWidth(groupSizeLegend->sizePolicy().hasHeightForWidth());
        groupSizeLegend->setSizePolicy(sizePolicy13);
        groupSizeLegend->setFlat(true);
        horizontalLayout_8 = new QHBoxLayout(groupSizeLegend);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        legendSize = new QwtLegend(groupSizeLegend);
        legendSize->setObjectName(QString::fromUtf8("legendSize"));
        legendSize->setFrameShape(QFrame::StyledPanel);
        legendSize->setFrameShadow(QFrame::Raised);

        horizontalLayout_8->addWidget(legendSize);


        verticalLayout_11->addWidget(groupSizeLegend);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer);

        btnSetVisualProperties = new QPushButton(dockWidgetContents_2);
        btnSetVisualProperties->setObjectName(QString::fromUtf8("btnSetVisualProperties"));

        verticalLayout_11->addWidget(btnSetVisualProperties);

        dockLegend->setWidget(dockWidgetContents_2);
        GUIClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockLegend);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuInspect->menuAction());
        menuBar->addAction(menuAnalysis->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menu_File->addAction(mnuFileOpenPhylogeny);
        menu_File->addAction(mnuFileOpenMatrix);
        menu_File->addSeparator();
        menu_File->addAction(mnuFileSaveRasterImage);
        menu_File->addAction(menuSave_legend->menuAction());
        menu_File->addAction(mnuFileSaveTable);
        menu_File->addSeparator();
        menu_File->addAction(mnuFileExportSVG->menuAction());
        menu_File->addAction(mnuFileExportTree);
        menu_File->addSeparator();
        menu_File->addAction(mnuFileExit);
        menuSave_legend->addAction(mnuFileSaveColorLegend);
        menuSave_legend->addAction(mnuFileSaveShapeLegend);
        menuSave_legend->addAction(mnuFileSaveSizeLegend);
        mnuFileExportSVG->addAction(mnuFileExportPhylogeny);
        mnuFileExportSVG->addAction(mnuFileExportPC1vsPC2);
        mnuFileExportSVG->addAction(mnuFileExportPC3vsPC2);
        mnuFileExportSVG->addAction(mnuFileExportPC1vsPC3);
        mnuFileExportSVG->addAction(mnuFileExportScreePlot);
        mnuFileExportSVG->addAction(mnuFileExportParallelCoordPlot);
        mnuFileExportSVG->addAction(mnuFileExportClusterTree);
        mnuFileExportSVG->addAction(mnuFileExportDissMatrixPlot);
        mnuFileExportSVG->addAction(mnuFileExportResemblanceScatterplot);
        menuHelp->addAction(mnuHelpAbout);
        menuInspect->addAction(mnuInspectSequencesPerSample);
        menuInspect->addSeparator();
        menuInspect->addAction(mnuInspectClearLog);

        retranslateUi(GUIClass);

        tabWidget->setCurrentIndex(0);
        toolboxPhylogeny->setCurrentIndex(0);
        toolboxPhylogeny->layout()->setSpacing(0);
        cboPhylogenyLeafTreatment->setCurrentIndex(2);
        cboPhylogenyAbundanceStyle->setCurrentIndex(0);
        cboPhylogenyBranchColorStyle->setCurrentIndex(1);
        cboPhylogenyBranchFontSize->setCurrentIndex(2);
        cboPhylogenyNodeColorStyle->setCurrentIndex(2);
        cboPhylogenyNodeShapeStyle->setCurrentIndex(0);
        cboPhylogenyNodeSizeStyle->setCurrentIndex(0);
        cboPhylogenyNodeLabel->setCurrentIndex(2);
        cboPhylogenyNodeFontSize->setCurrentIndex(2);
        cboPhylogenyCollapsedNodeShape->setCurrentIndex(0);
        cboPhylogenyVariableTL->setCurrentIndex(1);
        cboPhylogenyVariableML->setCurrentIndex(1);
        cboPhylogenyStatisticML->setCurrentIndex(0);
        cboPhylogenyVariableBL->setCurrentIndex(1);
        cboPhylogenyStatisticBL->setCurrentIndex(1);
        cboPhylogenyVariableHeight->setCurrentIndex(3);
        cboPhylogenyStatisticHeight->setCurrentIndex(4);
        cboPhylogenyGradientStyle->setCurrentIndex(1);
        cboPhylogenyScaleFontSize->setCurrentIndex(2);
        cboPhylogenySearchType->setCurrentIndex(1);
        cboMetadataRelationship->setCurrentIndex(1);
        toolBoxClusterTree->setCurrentIndex(0);
        toolBoxClusterTree->layout()->setSpacing(0);
        cboClusterTreeBranchColorStyle->setCurrentIndex(1);
        cboClusterTreeBranchFontSize->setCurrentIndex(2);
        cboClusterTreeNodeColorStyle->setCurrentIndex(2);
        cboClusterTreeNodeShapeStyle->setCurrentIndex(0);
        cboClusterTreeNodeSizeStyle->setCurrentIndex(2);
        cboClusterTreeNodeLabel->setCurrentIndex(2);
        cboClusterTreeNodeFontSize->setCurrentIndex(2);
        cboClusterTreeCollapsedNodeShape->setCurrentIndex(0);
        cboClusterTreeVariableTL->setCurrentIndex(1);
        cboClusterTreeVariableML->setCurrentIndex(1);
        cboClusterTreeStatisticML->setCurrentIndex(0);
        cboClusterTreeVariableBL->setCurrentIndex(1);
        cboClusterTreeStatisticBL->setCurrentIndex(1);
        cboClusterTreeVariableHeight->setCurrentIndex(3);
        cboClusterTreeStatisticHeight->setCurrentIndex(4);
        cboClusterTreeGradientStyle->setCurrentIndex(1);
        cboClusterTreeGradientFill->setCurrentIndex(1);
        cboClusterTreeScaleFontSize->setCurrentIndex(2);
        cboClusterTreeSearchType->setCurrentIndex(1);
        cboDissimilarityMatrixSortMethod->setCurrentIndex(1);
        cboResemblenceXaxis->setCurrentIndex(0);
        cboResemblenceYaxis->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUIClass)
    {
        GUIClass->setWindowTitle(QApplication::translate("GUIClass", "Chameleon", 0, QApplication::UnicodeUTF8));
        mnuFileOpenPhylogeny->setText(QApplication::translate("GUIClass", "Open &phylogenetic data...", 0, QApplication::UnicodeUTF8));
        mnuFileOpenPhylogeny->setIconText(QApplication::translate("GUIClass", "Load phylogenetic data", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileOpenPhylogeny->setToolTip(QApplication::translate("GUIClass", "Load phylogenetic data", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileOpenPhylogeny->setStatusTip(QApplication::translate("GUIClass", "Load phylogenetic data", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileOpenPhylogeny->setShortcut(QApplication::translate("GUIClass", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        mnuFileExit->setText(QApplication::translate("GUIClass", "E&xit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExit->setToolTip(QApplication::translate("GUIClass", "Quit program", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExit->setStatusTip(QApplication::translate("GUIClass", "Quit program", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuHelpAbout->setText(QApplication::translate("GUIClass", "&About...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        mnuHelpAbout->setStatusTip(QApplication::translate("GUIClass", "UniSplit information", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuAnalysisFst->setText(QApplication::translate("GUIClass", "&Fst", 0, QApplication::UnicodeUTF8));
        mnuFileSaveTable->setText(QApplication::translate("GUIClass", "Save &table...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileSaveTable->setToolTip(QApplication::translate("GUIClass", "Save table to file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileSaveTable->setStatusTip(QApplication::translate("GUIClass", "Save table to file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuInspectSequencesPerSample->setText(QApplication::translate("GUIClass", "&Sequence per sample", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuInspectSequencesPerSample->setToolTip(QApplication::translate("GUIClass", "Report sequence per sample", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuInspectSequencesPerSample->setStatusTip(QApplication::translate("GUIClass", "Report sequence per sample", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuInspectSplitSystem->setText(QApplication::translate("GUIClass", "Split system", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        mnuInspectSplitSystem->setStatusTip(QApplication::translate("GUIClass", "Report details of split system", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuAnalysisDiversity->setText(QApplication::translate("GUIClass", "UniSplit", 0, QApplication::UnicodeUTF8));
        mnuInspectClearLog->setText(QApplication::translate("GUIClass", "&Clear log", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        mnuInspectClearLog->setStatusTip(QApplication::translate("GUIClass", "Clear entire log", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileSaveRasterImage->setText(QApplication::translate("GUIClass", "Save &raster image...", 0, QApplication::UnicodeUTF8));
        mnuFileSaveRasterImage->setIconText(QApplication::translate("GUIClass", "Save plot as a raster image", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileSaveRasterImage->setToolTip(QApplication::translate("GUIClass", "Save plot as a raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileSaveRasterImage->setStatusTip(QApplication::translate("GUIClass", "Save plot as a raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileSaveColorLegend->setText(QApplication::translate("GUIClass", "&Colour legend", 0, QApplication::UnicodeUTF8));
        mnuFileSaveColorLegend->setIconText(QApplication::translate("GUIClass", "Save color legend as raster image", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileSaveColorLegend->setToolTip(QApplication::translate("GUIClass", "Save color legend as raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileSaveColorLegend->setStatusTip(QApplication::translate("GUIClass", "Save color legend as raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileSaveShapeLegend->setText(QApplication::translate("GUIClass", "&Shape legend", 0, QApplication::UnicodeUTF8));
        mnuFileSaveShapeLegend->setIconText(QApplication::translate("GUIClass", "Save shape legend as raster image", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileSaveShapeLegend->setToolTip(QApplication::translate("GUIClass", "Save shape legend as raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileSaveShapeLegend->setStatusTip(QApplication::translate("GUIClass", "Save shape legend as raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileSaveSizeLegend->setText(QApplication::translate("GUIClass", "S&ize legend", 0, QApplication::UnicodeUTF8));
        mnuFileSaveSizeLegend->setIconText(QApplication::translate("GUIClass", "Save size legend as raster image", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileSaveSizeLegend->setToolTip(QApplication::translate("GUIClass", "Save size legend as raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileSaveSizeLegend->setStatusTip(QApplication::translate("GUIClass", "Save size legend as raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuViewLogWindow->setText(QApplication::translate("GUIClass", "Log window", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuViewLogWindow->setToolTip(QApplication::translate("GUIClass", "Hide/show log window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuViewLogWindow->setStatusTip(QApplication::translate("GUIClass", "Hide/show log window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuViewLegendWindows->setText(QApplication::translate("GUIClass", "Legend windows", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuViewLegendWindows->setToolTip(QApplication::translate("GUIClass", "Hide/show legend windows", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuViewLegendWindows->setStatusTip(QApplication::translate("GUIClass", "Hide/show legend windows", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportPC1vsPC2->setText(QApplication::translate("GUIClass", "MDS plot (PC1 vs. PC2)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportPC1vsPC2->setToolTip(QApplication::translate("GUIClass", "Save ordination plot (PC1 vs. PC2) as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportPC1vsPC2->setStatusTip(QApplication::translate("GUIClass", "Save ordination plot (PC1 vs. PC2) as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportPC3vsPC2->setText(QApplication::translate("GUIClass", "MDS plot (PC3 vs. PC2)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportPC3vsPC2->setToolTip(QApplication::translate("GUIClass", "Save ordination plot (PC3 vs. PC2) as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportPC3vsPC2->setStatusTip(QApplication::translate("GUIClass", "Save ordination plot (PC3 vs. PC2) as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportPC1vsPC3->setText(QApplication::translate("GUIClass", "MDS plot (PC1 vs. PC3)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportPC1vsPC3->setToolTip(QApplication::translate("GUIClass", "Save ordination plot (PC1 vs. PC3) as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportPC1vsPC3->setStatusTip(QApplication::translate("GUIClass", "Save ordination plot (PC1 vs. PC3) as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportScreePlot->setText(QApplication::translate("GUIClass", "Scree plot", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportScreePlot->setToolTip(QApplication::translate("GUIClass", "Save scree plot as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportScreePlot->setStatusTip(QApplication::translate("GUIClass", "Save scree plot as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportParallelCoordPlot->setText(QApplication::translate("GUIClass", "Parallel coordinate plot", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportParallelCoordPlot->setToolTip(QApplication::translate("GUIClass", "Save parallel coordinate plot as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportParallelCoordPlot->setStatusTip(QApplication::translate("GUIClass", "Save parallel coordinate plot as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuAnalysisDistanceMatrix->setText(QApplication::translate("GUIClass", "Distance matrix", 0, QApplication::UnicodeUTF8));
        mnuFileOpenDissimilarityMatrix->setText(QApplication::translate("GUIClass", "Open dissimilarity matrix...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        mnuFileOpenDissimilarityMatrix->setStatusTip(QApplication::translate("GUIClass", "Load dissimilarity matrix data", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionBlah->setText(QApplication::translate("GUIClass", "blah", 0, QApplication::UnicodeUTF8));
        mnuFileExportDissimilarityMatrixPlot->setText(QApplication::translate("GUIClass", "Dissimilarity matrix plot", 0, QApplication::UnicodeUTF8));
        mnuFileExportResemblanceScatterplot->setText(QApplication::translate("GUIClass", "Resemblance scatterplot", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportResemblanceScatterplot->setToolTip(QApplication::translate("GUIClass", "Save resemblance scatterplot as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportResemblanceScatterplot->setStatusTip(QApplication::translate("GUIClass", "Save resemblance scatterplot as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportTree->setText(QApplication::translate("GUIClass", "Export &tree...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportTree->setToolTip(QApplication::translate("GUIClass", "Export phylogeny as Newick string", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportTree->setStatusTip(QApplication::translate("GUIClass", "Export phylogeny as Newick string", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportPhylogeny->setText(QApplication::translate("GUIClass", "Phylogeny", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportPhylogeny->setToolTip(QApplication::translate("GUIClass", "Save phylogeny as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportPhylogeny->setStatusTip(QApplication::translate("GUIClass", "Save phylogeny as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportClusterTree->setText(QApplication::translate("GUIClass", "Cluster tree", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportClusterTree->setToolTip(QApplication::translate("GUIClass", "Save cluster tree as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportClusterTree->setStatusTip(QApplication::translate("GUIClass", "Save cluster tree as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportDissMatrixPlot->setText(QApplication::translate("GUIClass", "Dissimilarity matrix plot", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportDissMatrixPlot->setToolTip(QApplication::translate("GUIClass", "Save dissimilarity matrix as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportDissMatrixPlot->setStatusTip(QApplication::translate("GUIClass", "Save dissimilarity matrix as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuSettingsProperties->setText(QApplication::translate("GUIClass", "Properties", 0, QApplication::UnicodeUTF8));
        mnuFileOpenMatrix->setText(QApplication::translate("GUIClass", "Open &matrix data...", 0, QApplication::UnicodeUTF8));
        mnuFileOpenMatrix->setIconText(QApplication::translate("GUIClass", "Load matrix data", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileOpenMatrix->setToolTip(QApplication::translate("GUIClass", "Load matrix data", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileOpenMatrix->setStatusTip(QApplication::translate("GUIClass", "Load matrix data", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileOpenMatrix->setShortcut(QApplication::translate("GUIClass", "Ctrl+M", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tabWidget->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        label_11->setText(QApplication::translate("GUIClass", "Branch style:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyBranchStyle->clear();
        cboPhylogenyBranchStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Phylogram", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Cladogram", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Equal", 0, QApplication::UnicodeUTF8)
        );
        chkPhylogenyAlignTipLabels->setText(QApplication::translate("GUIClass", "Align tip labels", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("GUIClass", "Root length:", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("GUIClass", "Leaf spacing:", 0, QApplication::UnicodeUTF8));
        label_111->setText(QApplication::translate("GUIClass", "Treat as:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyLeafTreatment->clear();
        cboPhylogenyLeafTreatment->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Relative proportion", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Unweighted", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Weighted", 0, QApplication::UnicodeUTF8)
        );
        label_78->setText(QApplication::translate("GUIClass", "Show abundance as:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyAbundanceStyle->clear();
        cboPhylogenyAbundanceStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "<none>", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Collapsed leaf nodes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Label only", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Pie charts", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Pie charts (leaves only)", 0, QApplication::UnicodeUTF8)
        );
        label_79->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        label_80->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        chkPhylogenySeqMetadata->setText(QApplication::translate("GUIClass", "Colour using sequence specific metadata", 0, QApplication::UnicodeUTF8));
        label_81->setText(QApplication::translate("GUIClass", "Metadata:", 0, QApplication::UnicodeUTF8));
        tbPhylogenyBrowseSeqMetadataFile->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
        label_82->setText(QApplication::translate("GUIClass", "Category:", 0, QApplication::UnicodeUTF8));
        label_83->setText(QApplication::translate("GUIClass", "Colour map:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenySeqMetadataLegend->setToolTip(QApplication::translate("GUIClass", "Show/hide sequence legend", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenySeqMetadataLegend->setStatusTip(QApplication::translate("GUIClass", "Show/hide sequence legend", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenySeqMetadataLegend->setText(QApplication::translate("GUIClass", "Legend", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GUIClass", "Background color:", 0, QApplication::UnicodeUTF8));
        btnPhylogenyBackgroundColor->setText(QApplication::translate("GUIClass", "Background color", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnPhylogenyRestoreActiveSamples->setToolTip(QApplication::translate("GUIClass", "Set tree to all sequences in active samples", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btnPhylogenyRestoreActiveSamples->setStatusTip(QApplication::translate("GUIClass", "Set tree to all sequences in active samples", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        btnPhylogenyRestoreActiveSamples->setText(QApplication::translate("GUIClass", "Restore active sample tree", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnPhylogenyProjectSelectedSeqs->setToolTip(QApplication::translate("GUIClass", "Prune tree to selected leaves", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btnPhylogenyProjectSelectedSeqs->setStatusTip(QApplication::translate("GUIClass", "Prune tree to selected leaves", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        btnPhylogenyProjectSelectedSeqs->setText(QApplication::translate("GUIClass", "Prune to selected leaves", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemText(toolboxPhylogeny->indexOf(pageLayout), QApplication::translate("GUIClass", "Layout properties", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemToolTip(toolboxPhylogeny->indexOf(pageLayout), QApplication::translate("GUIClass", "Set phylogeny layout properties", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GUIClass", "Colour style:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyBranchColorStyle->clear();
        cboPhylogenyBranchColorStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Propogate continuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate weighted", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Single colour", 0, QApplication::UnicodeUTF8)
        );
        btnPhylogenyBranchColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GUIClass", "Width:", 0, QApplication::UnicodeUTF8));
        chkPhylogenyDrawBranchOutline->setText(QApplication::translate("GUIClass", "Draw outline", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("GUIClass", "Label:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyBranchLabel->clear();
        cboPhylogenyBranchLabel->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Assigned internal labels", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Depth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Height", 0, QApplication::UnicodeUTF8)
        );
        label_13->setText(QApplication::translate("GUIClass", "Font:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("GUIClass", "Font size:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyBranchFontSize->clear();
        cboPhylogenyBranchFontSize->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "22", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "24", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "26", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "28", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "48", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "72", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        tbPhylogenyBranchFontBold->setToolTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyBranchFontBold->setStatusTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyBranchFontBold->setText(QApplication::translate("GUIClass", "Bold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyBranchFontItalics->setToolTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyBranchFontItalics->setStatusTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyBranchFontItalics->setText(QApplication::translate("GUIClass", "italics", 0, QApplication::UnicodeUTF8));
        btnPhylogenyBranchLabelColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemText(toolboxPhylogeny->indexOf(pageBranchProp), QApplication::translate("GUIClass", "Branch properties", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemToolTip(toolboxPhylogeny->indexOf(pageBranchProp), QApplication::translate("GUIClass", "Set visual properties of branches", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("GUIClass", "Colour style:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyNodeColorStyle->clear();
        cboPhylogenyNodeColorStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Single colour", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate continuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate weighted", 0, QApplication::UnicodeUTF8)
        );
        btnPhylogenyNodeColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("GUIClass", "Shape by:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyNodeShapeStyle->clear();
        cboPhylogenyNodeShapeStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Propogate discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Single shape", 0, QApplication::UnicodeUTF8)
        );
        cboPhylogenyNodeShape->clear();
        cboPhylogenyNodeShape->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Circle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Square", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangle (up)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Star (style 1)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Star (style 2)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Diamond", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Hexagon", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Cross", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangle (down)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangle (left)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangle (right)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Horizontal line", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Vertical line", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Diagonal cross", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("GUIClass", "Size style:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyNodeSizeStyle->clear();
        cboPhylogenyNodeSizeStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Leaves only (average)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate continuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate weighted", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Single size", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("GUIClass", "Leaf nodes:", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("GUIClass", "Internal nodes:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("GUIClass", "Label:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyNodeLabel->clear();
        cboPhylogenyNodeLabel->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Assigned labels", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Assigned labels (leaves only)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Support values", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Consistency index", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Depth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Height", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Distance to root", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Distance to closest leaf", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Distance to furthest leaf", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Distance to leaves (average)", 0, QApplication::UnicodeUTF8)
        );
        chkPhylogenyShowColorCategory->setText(QApplication::translate("GUIClass", "Show colour category", 0, QApplication::UnicodeUTF8));
        chkPhylogenyShowShapeCategory->setText(QApplication::translate("GUIClass", "Show shape category", 0, QApplication::UnicodeUTF8));
        chkPhylogenyShowSizeCategory->setText(QApplication::translate("GUIClass", "Show size category", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("GUIClass", "Font:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("GUIClass", "Font size:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyNodeFontSize->clear();
        cboPhylogenyNodeFontSize->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "22", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "24", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "26", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "28", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "48", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "72", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        tbPhylogenyNodeFontBold->setToolTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyNodeFontBold->setStatusTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyNodeFontBold->setText(QApplication::translate("GUIClass", "Bold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyNodeFontItalics->setToolTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyNodeFontItalics->setStatusTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyNodeFontItalics->setText(QApplication::translate("GUIClass", " Italics", 0, QApplication::UnicodeUTF8));
        btnPhylogenyNodeLabelColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemText(toolboxPhylogeny->indexOf(pageNodeProp), QApplication::translate("GUIClass", "Node properties", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemToolTip(toolboxPhylogeny->indexOf(pageNodeProp), QApplication::translate("GUIClass", "Set visual properties of nodes", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("GUIClass", "Shape:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyCollapsedNodeShape->clear();
        cboPhylogenyCollapsedNodeShape->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Rectangular", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangular", 0, QApplication::UnicodeUTF8)
        );
        chkPhylogenyCollapsedShowLabels->setText(QApplication::translate("GUIClass", "Show labels", 0, QApplication::UnicodeUTF8));
        chkPhylogenyAbundanceInLabel->setText(QApplication::translate("GUIClass", "Show abundance", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("GUIClass", "Top line:", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("GUIClass", "Variable:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyVariableTL->clear();
        cboPhylogenyVariableTL->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Abundance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Branch length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Fixed", 0, QApplication::UnicodeUTF8)
        );
        label_24->setText(QApplication::translate("GUIClass", "Statistic:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyStatisticTL->clear();
        cboPhylogenyStatisticTL->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Maximum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Minimum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Mean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Total", 0, QApplication::UnicodeUTF8)
        );
        lblPhylogenyFactorLabelTL->setText(QApplication::translate("GUIClass", "Percentage:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMinTL->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMaxTL->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GUIClass", "Middle line:", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("GUIClass", "Variable:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyVariableML->clear();
        cboPhylogenyVariableML->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Abundance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Branch length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Fixed", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "None", 0, QApplication::UnicodeUTF8)
        );
        label_28->setText(QApplication::translate("GUIClass", "Statistic:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyStatisticML->clear();
        cboPhylogenyStatisticML->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Maximum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Minimum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Mean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Total", 0, QApplication::UnicodeUTF8)
        );
        lblPhylogenyFactorLabelML->setText(QApplication::translate("GUIClass", "Percentage:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMinTL_2->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMaxTL_2->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("GUIClass", "Bottom line:", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("GUIClass", "Variable:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyVariableBL->clear();
        cboPhylogenyVariableBL->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Abundance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Branch length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Fixed", 0, QApplication::UnicodeUTF8)
        );
        label_30->setText(QApplication::translate("GUIClass", "Statistic:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyStatisticBL->clear();
        cboPhylogenyStatisticBL->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Maximum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Minimum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Mean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Total", 0, QApplication::UnicodeUTF8)
        );
        lblPhylogenyFactorLabelBL->setText(QApplication::translate("GUIClass", "Percentage:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMinTL_3->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMaxTL_3->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("GUIClass", "Height:", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("GUIClass", "Variable:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyVariableHeight->clear();
        cboPhylogenyVariableHeight->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Abundance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Branch length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Fixed", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Leaf node span", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Size variable", 0, QApplication::UnicodeUTF8)
        );
        label_34->setText(QApplication::translate("GUIClass", "Statistic:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyStatisticHeight->clear();
        cboPhylogenyStatisticHeight->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Maximum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Minimum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Mean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Total", 0, QApplication::UnicodeUTF8)
        );
        lblPhylogenyFactorLabelHeight->setText(QApplication::translate("GUIClass", "Percentage:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMinTL_4->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMaxTL_4->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("GUIClass", "Colour gradient:", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("GUIClass", "Style:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyGradientStyle->clear();
        cboPhylogenyGradientStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Continuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Single colour", 0, QApplication::UnicodeUTF8)
        );
        label_32->setText(QApplication::translate("GUIClass", "Fill:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyGradientFill->clear();
        cboPhylogenyGradientFill->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Top half", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Full", 0, QApplication::UnicodeUTF8)
        );
        btnPhylogenyGradientSingleColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemText(toolboxPhylogeny->indexOf(pageCollapsedNodeProp), QApplication::translate("GUIClass", "Collapsed node properties", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemToolTip(toolboxPhylogeny->indexOf(pageCollapsedNodeProp), QApplication::translate("GUIClass", "Set visual properties of collapsed nodes", 0, QApplication::UnicodeUTF8));
        chkPhylogenyShowScale->setText(QApplication::translate("GUIClass", "Show scale", 0, QApplication::UnicodeUTF8));
        chkPhylogenyScaleAutomatic->setText(QApplication::translate("GUIClass", "Automatic scale", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("GUIClass", "Scale:", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("GUIClass", "Significant digits:", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("GUIClass", "Width:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("GUIClass", "Font:", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("GUIClass", "Font size:", 0, QApplication::UnicodeUTF8));
        cboPhylogenyScaleFontSize->clear();
        cboPhylogenyScaleFontSize->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "22", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "24", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "26", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "28", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "48", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "72", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        tbPhylogenyScaleFontBold->setToolTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyScaleFontBold->setStatusTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyScaleFontBold->setText(QApplication::translate("GUIClass", " Bold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        tbPhylogenyScaleFontItalics->setStatusTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        tbPhylogenyScaleFontItalics->setWhatsThis(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        tbPhylogenyScaleFontItalics->setText(QApplication::translate("GUIClass", " Italics", 0, QApplication::UnicodeUTF8));
        btnPhylogenyScaleLabelColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemText(toolboxPhylogeny->indexOf(pageScaleBarProp), QApplication::translate("GUIClass", "Scale bar properties", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemToolTip(toolboxPhylogeny->indexOf(pageScaleBarProp), QApplication::translate("GUIClass", "Set visual properties of scale bar", 0, QApplication::UnicodeUTF8));
        cboPhylogenySearchType->clear();
        cboPhylogenySearchType->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "contains", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "starts with", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "ends with", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "matches", 0, QApplication::UnicodeUTF8)
        );
        toolboxPhylogeny->setItemText(toolboxPhylogeny->indexOf(pageTreeFinder), QApplication::translate("GUIClass", "Search tree", 0, QApplication::UnicodeUTF8));
        toolboxPhylogeny->setItemText(toolboxPhylogeny->indexOf(pageTreeInspector), QApplication::translate("GUIClass", "Tree inspector", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyToggleCollapse->setToolTip(QApplication::translate("GUIClass", "Collapse/Uncollapse node(s)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyToggleCollapse->setStatusTip(QApplication::translate("GUIClass", "Toggle collapsed state of node(s)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyToggleCollapse->setText(QApplication::translate("GUIClass", "Collapse", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyCollapseComplement->setToolTip(QApplication::translate("GUIClass", "Collapse all unselected nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyCollapseComplement->setStatusTip(QApplication::translate("GUIClass", "Collapse all unselected nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyCollapseComplement->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyCollapseAll->setToolTip(QApplication::translate("GUIClass", "Collapse all nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyCollapseAll->setStatusTip(QApplication::translate("GUIClass", "Collapse all nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyCollapseAll->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyUncollapseAll->setToolTip(QApplication::translate("GUIClass", "Uncollapse all nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyUncollapseAll->setStatusTip(QApplication::translate("GUIClass", "Uncollapse all nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyUncollapseAll->setText(QApplication::translate("GUIClass", "Uncollapse all nodes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyCollapseToScreen->setToolTip(QApplication::translate("GUIClass", "Collapse tree to fit on screen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyCollapseToScreen->setStatusTip(QApplication::translate("GUIClass", "Collapse tree to fit on screen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyCollapseToScreen->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyCollapseWizard->setToolTip(QApplication::translate("GUIClass", "Collapse node wizard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyCollapseWizard->setStatusTip(QApplication::translate("GUIClass", "Collapse node wizard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyCollapseWizard->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("GUIClass", "Parsimony:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cboPhylogenyParsimony->setToolTip(QApplication::translate("GUIClass", "Parsimony field", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cboPhylogenyParsimony->setStatusTip(QApplication::translate("GUIClass", "Parsimony field", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        tbPhylogenyReroot->setToolTip(QApplication::translate("GUIClass", "Reroot tree", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyReroot->setStatusTip(QApplication::translate("GUIClass", "Reroot tree", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyReroot->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyRotateBranches->setToolTip(QApplication::translate("GUIClass", "Rotate branches", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyRotateBranches->setStatusTip(QApplication::translate("GUIClass", "Rotate branches", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyRotateBranches->setText(QApplication::translate("GUIClass", "Rotate branches", 0, QApplication::UnicodeUTF8));
        tbPhylogenyRotateBranches->setShortcut(QApplication::translate("GUIClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyAlphabetical->setToolTip(QApplication::translate("GUIClass", "Put leaf nodes in alphabetical order", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyAlphabetical->setStatusTip(QApplication::translate("GUIClass", "Put leaf nodes in alphabetical order", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyAlphabetical->setText(QApplication::translate("GUIClass", "Alphabetical", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyLadderizeBottom->setToolTip(QApplication::translate("GUIClass", "Ladderize tree from bottom", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyLadderizeBottom->setStatusTip(QApplication::translate("GUIClass", "Ladderize tree from bottom", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyLadderizeBottom->setText(QApplication::translate("GUIClass", "Ladderize bottom", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbPhylogenyLadderizeTop->setToolTip(QApplication::translate("GUIClass", "Ladderize tree from top", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbPhylogenyLadderizeTop->setStatusTip(QApplication::translate("GUIClass", "Ladderize tree from top", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbPhylogenyLadderizeTop->setText(QApplication::translate("GUIClass", "Ladderize top", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabPhylogeny), QApplication::translate("GUIClass", "Phylogeny", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabPhylogeny), QApplication::translate("GUIClass", "Phylogeny", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbMetadataAddAll->setToolTip(QApplication::translate("GUIClass", "Set all samples as active", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbMetadataAddAll->setStatusTip(QApplication::translate("GUIClass", "Set all samples as active", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbMetadataAddAll->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbMetadataRemoveAll->setToolTip(QApplication::translate("GUIClass", "Remove all samples from active set", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbMetadataRemoveAll->setStatusTip(QApplication::translate("GUIClass", "Remove all samples from active set", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbMetadataRemoveAll->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbMetadataSetSelected->setToolTip(QApplication::translate("GUIClass", "Set active set to selected samples", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbMetadataSetSelected->setStatusTip(QApplication::translate("GUIClass", "Set active set to selected samples", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbMetadataSetSelected->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
        label_70->setText(QApplication::translate("GUIClass", "Filter:", 0, QApplication::UnicodeUTF8));
        cboMetadataAddRemove->clear();
        cboMetadataAddRemove->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Add", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Remove", 0, QApplication::UnicodeUTF8)
        );
        label_72->setText(QApplication::translate("GUIClass", "all samples where", 0, QApplication::UnicodeUTF8));
        cboMetadataRelationship->clear();
        cboMetadataRelationship->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "<", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "=", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", ">", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        tbMetadataFilter->setToolTip(QApplication::translate("GUIClass", "Apply filtering criteria", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbMetadataFilter->setStatusTip(QApplication::translate("GUIClass", "Apply filtering criteria", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbMetadataFilter->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabMetadata), QApplication::translate("GUIClass", "Sample metadata", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabMetadata), QApplication::translate("GUIClass", "Metadata for each sample", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbOrdinationMethodRun->setToolTip(QApplication::translate("GUIClass", "Run dimensionality reduction method", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbOrdinationMethodRun->setStatusTip(QApplication::translate("GUIClass", "Run dimensionality reduction method", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbOrdinationMethodRun->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
        chkShowSampleNames->setText(QApplication::translate("GUIClass", "Show sample names", 0, QApplication::UnicodeUTF8));
        chkOrdinationSelectionTransparency->setText(QApplication::translate("GUIClass", "Apply selection transparency", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbOrdinationPlotProjectedCoord->setToolTip(QApplication::translate("GUIClass", "View projected coordinates table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbOrdinationPlotProjectedCoord->setStatusTip(QApplication::translate("GUIClass", "View projected coordinates table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbOrdinationPlotProjectedCoord->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabOrdinationPlots), QApplication::translate("GUIClass", "Ordination plots", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabOrdinationPlots), QApplication::translate("GUIClass", "Ordination plots", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GUIClass", "Dimensions to view:", 0, QApplication::UnicodeUTF8));
        chkShowCurve->setText(QApplication::translate("GUIClass", "Show curves", 0, QApplication::UnicodeUTF8));
        chkFitCurve->setText(QApplication::translate("GUIClass", "Smooth curves", 0, QApplication::UnicodeUTF8));
        chkShowVarianceLabels->setText(QApplication::translate("GUIClass", "Show variance labels", 0, QApplication::UnicodeUTF8));
        chkParallelCoordSelectionTransparency->setText(QApplication::translate("GUIClass", "Apply selection transparency", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbParallelCoordProjectedCoord->setToolTip(QApplication::translate("GUIClass", "View projected coordinates table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbParallelCoordProjectedCoord->setStatusTip(QApplication::translate("GUIClass", "View projected coordinates table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbParallelCoordProjectedCoord->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabParallelCoordPlot), QApplication::translate("GUIClass", "Parallel coordinate plot", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabParallelCoordPlot), QApplication::translate("GUIClass", "Parallel coordinate plot", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("GUIClass", "Branch style:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeBranchStyle->clear();
        cboClusterTreeBranchStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Phylogram", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Cladogram", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Equal", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        cboClusterTreeBranchStyle->setToolTip(QApplication::translate("GUIClass", "Tree layout style", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cboClusterTreeBranchStyle->setStatusTip(QApplication::translate("GUIClass", "Tree layout style", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        chkClusterTreeAlignTipLabels->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        chkClusterTreeAlignTipLabels->setText(QApplication::translate("GUIClass", "Align tip labels", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("GUIClass", "Root length:", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("GUIClass", "Leaf spacing:", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("GUIClass", "Background color:", 0, QApplication::UnicodeUTF8));
        btnClusterTreeBackgroundColor->setText(QApplication::translate("GUIClass", "Background color", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemText(toolBoxClusterTree->indexOf(pageLayout_2), QApplication::translate("GUIClass", "Layout properties", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemToolTip(toolBoxClusterTree->indexOf(pageLayout_2), QApplication::translate("GUIClass", "Set cluster tree layout properties", 0, QApplication::UnicodeUTF8));
        label_40->setText(QApplication::translate("GUIClass", "Colour style:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeBranchColorStyle->clear();
        cboClusterTreeBranchColorStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Propogate continuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate weighted", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Single colour", 0, QApplication::UnicodeUTF8)
        );
        btnClusterTreeBranchColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        label_41->setText(QApplication::translate("GUIClass", "Width:", 0, QApplication::UnicodeUTF8));
        chkClusterTreeDrawBranchOutline->setText(QApplication::translate("GUIClass", "Draw outline", 0, QApplication::UnicodeUTF8));
        label_42->setText(QApplication::translate("GUIClass", "Label:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeBranchLabel->clear();
        cboClusterTreeBranchLabel->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Assigned internal labels", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Depth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Height", 0, QApplication::UnicodeUTF8)
        );
        label_43->setText(QApplication::translate("GUIClass", "Font:", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("GUIClass", "Font size:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeBranchFontSize->clear();
        cboClusterTreeBranchFontSize->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "22", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "24", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "26", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "28", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "48", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "72", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        tbClusterTreeBranchFontBold->setToolTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeBranchFontBold->setStatusTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeBranchFontBold->setText(QApplication::translate("GUIClass", "Bold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeBranchFontItalics->setToolTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeBranchFontItalics->setStatusTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeBranchFontItalics->setText(QApplication::translate("GUIClass", "italics", 0, QApplication::UnicodeUTF8));
        btnClusterTreeBranchLabelColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemText(toolBoxClusterTree->indexOf(pageBranchProp_2), QApplication::translate("GUIClass", "Branch properties", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemToolTip(toolBoxClusterTree->indexOf(pageBranchProp_2), QApplication::translate("GUIClass", "Set visual properties of branches", 0, QApplication::UnicodeUTF8));
        label_45->setText(QApplication::translate("GUIClass", "Colour style:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeNodeColorStyle->clear();
        cboClusterTreeNodeColorStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Single colour", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate continuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate weighted", 0, QApplication::UnicodeUTF8)
        );
        btnClusterTreeNodeColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("GUIClass", "Shape by:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeNodeShapeStyle->clear();
        cboClusterTreeNodeShapeStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Propogate discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Single shape", 0, QApplication::UnicodeUTF8)
        );
        cboClusterTreeNodeShape->clear();
        cboClusterTreeNodeShape->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Circle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Square", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangle (up)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Star (style 1)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Star (style 2)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Diamond", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Hexagon", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Cross", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangle (down)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangle (left)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangle (right)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Horizontal line", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Vertical line", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Diagonal cross", 0, QApplication::UnicodeUTF8)
        );
        label_47->setText(QApplication::translate("GUIClass", "Size style:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeNodeSizeStyle->clear();
        cboClusterTreeNodeSizeStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Leaves only", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate continuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Propogate weighted", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Single size", 0, QApplication::UnicodeUTF8)
        );
        label_48->setText(QApplication::translate("GUIClass", "Leaf nodes:", 0, QApplication::UnicodeUTF8));
        label_49->setText(QApplication::translate("GUIClass", "Internal nodes:", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("GUIClass", "Label:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeNodeLabel->clear();
        cboClusterTreeNodeLabel->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Assigned labels", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Assigned labels (leaves only)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Support values", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Consistency index", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Depth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Height", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Distance to root", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Distance to closest leaf", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Distance to furthest leaf", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Distance to leaves (average)", 0, QApplication::UnicodeUTF8)
        );
        label_51->setText(QApplication::translate("GUIClass", "Font:", 0, QApplication::UnicodeUTF8));
        chkClusterTreeShowColorCategory->setText(QApplication::translate("GUIClass", "Show colour category", 0, QApplication::UnicodeUTF8));
        chkClusterTreeShowShapeCategory->setText(QApplication::translate("GUIClass", "Show shape category", 0, QApplication::UnicodeUTF8));
        chkClusterTreeShowSizeCategory->setText(QApplication::translate("GUIClass", "Show size category", 0, QApplication::UnicodeUTF8));
        label_52->setText(QApplication::translate("GUIClass", "Font size:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeNodeFontSize->clear();
        cboClusterTreeNodeFontSize->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "22", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "24", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "26", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "28", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "48", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "72", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        tbClusterTreeNodeFontBold->setToolTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeNodeFontBold->setStatusTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeNodeFontBold->setText(QApplication::translate("GUIClass", "Bold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeNodeFontItalics->setToolTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeNodeFontItalics->setStatusTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeNodeFontItalics->setText(QApplication::translate("GUIClass", " Italics", 0, QApplication::UnicodeUTF8));
        btnClusterTreeNodeLabelColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemText(toolBoxClusterTree->indexOf(pageNodeProp_2), QApplication::translate("GUIClass", "Node properties", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemToolTip(toolBoxClusterTree->indexOf(pageNodeProp_2), QApplication::translate("GUIClass", "Set visual properties of nodes", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("GUIClass", "Shape:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeCollapsedNodeShape->clear();
        cboClusterTreeCollapsedNodeShape->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Rectangular", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Triangular", 0, QApplication::UnicodeUTF8)
        );
        chkClusterTreeCollapsedShowLabels->setText(QApplication::translate("GUIClass", "Show labels", 0, QApplication::UnicodeUTF8));
        chkClusterTreeAbundanceInLabel->setText(QApplication::translate("GUIClass", "Show abundance", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("GUIClass", "Top line:", 0, QApplication::UnicodeUTF8));
        label_54->setText(QApplication::translate("GUIClass", "Variable:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeVariableTL->clear();
        cboClusterTreeVariableTL->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Abundance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Branch length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Fixed", 0, QApplication::UnicodeUTF8)
        );
        label_55->setText(QApplication::translate("GUIClass", "Statistic:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeStatisticTL->clear();
        cboClusterTreeStatisticTL->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Maximum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Minimum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Mean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Total", 0, QApplication::UnicodeUTF8)
        );
        lblClusterTreeFactorLabelTL->setText(QApplication::translate("GUIClass", "Percentage:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMinTL_5->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMaxTL_5->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("GUIClass", "Middle line:", 0, QApplication::UnicodeUTF8));
        label_56->setText(QApplication::translate("GUIClass", "Variable:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeVariableML->clear();
        cboClusterTreeVariableML->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Abundance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Branch length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Fixed", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "None", 0, QApplication::UnicodeUTF8)
        );
        label_57->setText(QApplication::translate("GUIClass", "Statistic:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeStatisticML->clear();
        cboClusterTreeStatisticML->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Maximum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Minimum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Mean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Total", 0, QApplication::UnicodeUTF8)
        );
        lblClusterTreeFactorLabelML->setText(QApplication::translate("GUIClass", "Percentage:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMinTL_6->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMaxTL_6->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("GUIClass", "Bottom line:", 0, QApplication::UnicodeUTF8));
        label_58->setText(QApplication::translate("GUIClass", "Variable:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeVariableBL->clear();
        cboClusterTreeVariableBL->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Abundance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Branch length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Fixed", 0, QApplication::UnicodeUTF8)
        );
        label_59->setText(QApplication::translate("GUIClass", "Statistic:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeStatisticBL->clear();
        cboClusterTreeStatisticBL->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Maximum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Minimum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Mean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Total", 0, QApplication::UnicodeUTF8)
        );
        lblClusterTreeFactorLabelBL->setText(QApplication::translate("GUIClass", "Percentage:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMinTL_7->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMaxTL_7->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("GUIClass", "Height:", 0, QApplication::UnicodeUTF8));
        label_60->setText(QApplication::translate("GUIClass", "Variable:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeVariableHeight->clear();
        cboClusterTreeVariableHeight->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Abundance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Branch length", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Fixed", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Leaf node span", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Size variable", 0, QApplication::UnicodeUTF8)
        );
        label_61->setText(QApplication::translate("GUIClass", "Statistic:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeStatisticHeight->clear();
        cboClusterTreeStatisticHeight->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Maximum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Minimum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Mean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Median", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Total", 0, QApplication::UnicodeUTF8)
        );
        lblClusterTreeFactorLabelHeight->setText(QApplication::translate("GUIClass", "Percentage:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMinTL_8->setText(QApplication::translate("GUIClass", "Min. size in pixels:", 0, QApplication::UnicodeUTF8));
        lblPhylogenyMaxTL_8->setText(QApplication::translate("GUIClass", "Max. size in pixels:", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("GUIClass", "Colour gradient:", 0, QApplication::UnicodeUTF8));
        label_62->setText(QApplication::translate("GUIClass", "Style:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeGradientStyle->clear();
        cboClusterTreeGradientStyle->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Continuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Discrete", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Single colour", 0, QApplication::UnicodeUTF8)
        );
        label_63->setText(QApplication::translate("GUIClass", "Fill:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeGradientFill->clear();
        cboClusterTreeGradientFill->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Top half", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Full", 0, QApplication::UnicodeUTF8)
        );
        btnClusterTreeGradientSingleColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemText(toolBoxClusterTree->indexOf(pageCollapsedNodeProp_2), QApplication::translate("GUIClass", "Collapsed node properties", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemToolTip(toolBoxClusterTree->indexOf(pageCollapsedNodeProp_2), QApplication::translate("GUIClass", "Set visual properties of collapsed nodes", 0, QApplication::UnicodeUTF8));
        chkClusterTreeShowScale->setText(QApplication::translate("GUIClass", "Show scale", 0, QApplication::UnicodeUTF8));
        chkClusterTreeScaleAutomatic->setText(QApplication::translate("GUIClass", "Automatic scale", 0, QApplication::UnicodeUTF8));
        label_64->setText(QApplication::translate("GUIClass", "Scale:", 0, QApplication::UnicodeUTF8));
        label_65->setText(QApplication::translate("GUIClass", "Significant digits:", 0, QApplication::UnicodeUTF8));
        label_66->setText(QApplication::translate("GUIClass", "Width:", 0, QApplication::UnicodeUTF8));
        label_67->setText(QApplication::translate("GUIClass", "Font:", 0, QApplication::UnicodeUTF8));
        label_68->setText(QApplication::translate("GUIClass", "Font size:", 0, QApplication::UnicodeUTF8));
        cboClusterTreeScaleFontSize->clear();
        cboClusterTreeScaleFontSize->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "22", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "24", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "26", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "28", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "48", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "72", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        tbClusterTreeScaleFontBold->setToolTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeScaleFontBold->setStatusTip(QApplication::translate("GUIClass", "Make text bold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeScaleFontBold->setText(QApplication::translate("GUIClass", " Bold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        tbClusterTreeScaleFontItalics->setStatusTip(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        tbClusterTreeScaleFontItalics->setWhatsThis(QApplication::translate("GUIClass", "Make text talicised", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        tbClusterTreeScaleFontItalics->setText(QApplication::translate("GUIClass", " Italics", 0, QApplication::UnicodeUTF8));
        btnClusterTreeScaleLabelColor->setText(QApplication::translate("GUIClass", "Color", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemText(toolBoxClusterTree->indexOf(pageScaleBarProp_2), QApplication::translate("GUIClass", "Scale bar properties", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemToolTip(toolBoxClusterTree->indexOf(pageScaleBarProp_2), QApplication::translate("GUIClass", "Set visual properties of scale bar", 0, QApplication::UnicodeUTF8));
        cboClusterTreeSearchType->clear();
        cboClusterTreeSearchType->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "contains", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "starts with", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "ends with", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "matches", 0, QApplication::UnicodeUTF8)
        );
        toolBoxClusterTree->setItemText(toolBoxClusterTree->indexOf(pageTreeFinder_2), QApplication::translate("GUIClass", "Search tree", 0, QApplication::UnicodeUTF8));
        toolBoxClusterTree->setItemText(toolBoxClusterTree->indexOf(pageTreeInspector_2), QApplication::translate("GUIClass", "Tree inspector", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeRun->setToolTip(QApplication::translate("GUIClass", "Run cluster tree analysis", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeRun->setStatusTip(QApplication::translate("GUIClass", "Run cluster tree analysis", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeRun->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeToggleCollapse->setToolTip(QApplication::translate("GUIClass", "Collapse/Uncollapse node", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeToggleCollapse->setStatusTip(QApplication::translate("GUIClass", "Toggle collapsed state of node", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeToggleCollapse->setText(QApplication::translate("GUIClass", "Collapse", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeCollapseComplement->setToolTip(QApplication::translate("GUIClass", "Collapse all unselected nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeCollapseComplement->setStatusTip(QApplication::translate("GUIClass", "Collapse all unselected nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeCollapseComplement->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeCollapseAll->setToolTip(QApplication::translate("GUIClass", "Collapse all nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeCollapseAll->setStatusTip(QApplication::translate("GUIClass", "Collapse all nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeCollapseAll->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeUncollapseAll->setToolTip(QApplication::translate("GUIClass", "Uncollapse all nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeUncollapseAll->setStatusTip(QApplication::translate("GUIClass", "Uncollapse all nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeUncollapseAll->setText(QApplication::translate("GUIClass", "Uncollapse all nodes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeCollapseToScreen->setToolTip(QApplication::translate("GUIClass", "Collapse tree to fit on screen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeCollapseToScreen->setStatusTip(QApplication::translate("GUIClass", "Collapse tree to fit on screen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeCollapseToScreen->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeAutoCollapse->setToolTip(QApplication::translate("GUIClass", "Collapse node wizard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeAutoCollapse->setStatusTip(QApplication::translate("GUIClass", "Collapse node wizard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeAutoCollapse->setText(QApplication::translate("GUIClass", "Auto collapse", 0, QApplication::UnicodeUTF8));
        label_69->setText(QApplication::translate("GUIClass", "Parsimony:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeReroot->setToolTip(QApplication::translate("GUIClass", "Reroot tree", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeReroot->setStatusTip(QApplication::translate("GUIClass", "Reroot tree", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeReroot->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeRotateBranches->setToolTip(QApplication::translate("GUIClass", "Rotate branches", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeRotateBranches->setStatusTip(QApplication::translate("GUIClass", "Rotate branches", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeRotateBranches->setText(QApplication::translate("GUIClass", "Rotate branches", 0, QApplication::UnicodeUTF8));
        tbClusterTreeRotateBranches->setShortcut(QApplication::translate("GUIClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeAlphabetical->setToolTip(QApplication::translate("GUIClass", "Put leaf nodes in alphabetical order", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeAlphabetical->setStatusTip(QApplication::translate("GUIClass", "Put leaf nodes in alphabetical order", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeAlphabetical->setText(QApplication::translate("GUIClass", "Alphabetical", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeLadderizeBottom->setToolTip(QApplication::translate("GUIClass", "Ladderize tree from bottom", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeLadderizeBottom->setStatusTip(QApplication::translate("GUIClass", "Ladderize tree from bottom", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeLadderizeBottom->setText(QApplication::translate("GUIClass", "Ladderize bottom", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tbClusterTreeLadderizeTop->setToolTip(QApplication::translate("GUIClass", "Ladderize tree from top", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbClusterTreeLadderizeTop->setStatusTip(QApplication::translate("GUIClass", "Ladderize tree from top", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbClusterTreeLadderizeTop->setText(QApplication::translate("GUIClass", "Ladderize top", 0, QApplication::UnicodeUTF8));
        label_84->setText(QApplication::translate("GUIClass", "Optimize layout to gradient:", 0, QApplication::UnicodeUTF8));
        chkGradientLabels->setText(QApplication::translate("GUIClass", "Show labels", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabClusterTree), QApplication::translate("GUIClass", "Cluster tree", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabClusterTree), QApplication::translate("GUIClass", "Cluster tree", 0, QApplication::UnicodeUTF8));
        lblDissimilarityLabel->setText(QApplication::translate("GUIClass", "<dissimilarity label>", 0, QApplication::UnicodeUTF8));
        label_71->setText(QApplication::translate("GUIClass", "Sorting method:", 0, QApplication::UnicodeUTF8));
        cboDissimilarityMatrixSortMethod->clear();
        cboDissimilarityMatrixSortMethod->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Randomize", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Side-to-side", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Simulated annealing", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        cboDissimilarityMatrixSortMethod->setToolTip(QApplication::translate("GUIClass", "Sort matrix with specified method", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cboDissimilarityMatrixSortMethod->setStatusTip(QApplication::translate("GUIClass", "Sort matrix with specified method", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        tbDissimilarityMatrixRunSort->setToolTip(QApplication::translate("GUIClass", "Run sorting method", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tbDissimilarityMatrixRunSort->setStatusTip(QApplication::translate("GUIClass", "Run sorting method", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        tbDissimilarityMatrixRunSort->setText(QApplication::translate("GUIClass", "...", 0, QApplication::UnicodeUTF8));
        label_77->setText(QApplication::translate("GUIClass", "Minimum cell size:", 0, QApplication::UnicodeUTF8));
        chkDissMatrixSelectionTransparency->setText(QApplication::translate("GUIClass", "Apply selection transparency", 0, QApplication::UnicodeUTF8));
        label_73->setText(QApplication::translate("GUIClass", "Colour map:", 0, QApplication::UnicodeUTF8));
        chkDissimilarityMatrixFullRange->setText(QApplication::translate("GUIClass", "Full range", 0, QApplication::UnicodeUTF8));
        chkDissimilarityMatrixThreshold->setText(QApplication::translate("GUIClass", "Threshold colour map", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabDissMatrixPlot), QApplication::translate("GUIClass", "Dissimilarity matrix plot", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabDissMatrixPlot), QApplication::translate("GUIClass", "Visual representation of dissimilarity matrix", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabBoxPlot), QApplication::translate("GUIClass", "Box plot", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabBoxPlot), QApplication::translate("GUIClass", "Box plot", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabDissimilarityMatrix), QApplication::translate("GUIClass", "Dissimilarity matrix", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabDissimilarityMatrix), QApplication::translate("GUIClass", "Biotic-dissimilarity matrix", 0, QApplication::UnicodeUTF8));
        label_74->setText(QApplication::translate("GUIClass", "X-axis:", 0, QApplication::UnicodeUTF8));
        cboResemblenceXaxis->clear();
        cboResemblenceXaxis->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Common split set (unweighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Complete lineage (unweighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "All splits (unweighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Common split set (normalized)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Complete lineage (normalized)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "All splits (normalized)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "UniFrac semimetric (normalized)", 0, QApplication::UnicodeUTF8)
        );
        label_75->setText(QApplication::translate("GUIClass", "Y-axis:", 0, QApplication::UnicodeUTF8));
        cboResemblenceYaxis->clear();
        cboResemblenceYaxis->insertItems(0, QStringList()
         << QApplication::translate("GUIClass", "Common split set (unweighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Complete lineage (unweighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "All splits (unweighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Common split set (weighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "Complete lineage (weighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "All splits (weighted)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GUIClass", "UniFrac semimetric (weighted)", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_STATUSTIP
        btnScatterplotRun->setStatusTip(QApplication::translate("GUIClass", "Plot resemblance scatterplot", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btnScatterplotRun->setWhatsThis(QApplication::translate("GUIClass", "Plot resemblance scatterplot", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btnScatterplotRun->setText(QApplication::translate("GUIClass", "Run", 0, QApplication::UnicodeUTF8));
        chkShowBestFit->setText(QApplication::translate("GUIClass", "Show best fit line", 0, QApplication::UnicodeUTF8));
        label_76->setText(QApplication::translate("GUIClass", "Marker size:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabResemblanceMeasureScatterplot), QApplication::translate("GUIClass", "Resemblance scatterplot", 0, QApplication::UnicodeUTF8));
        btnSaveLog->setText(QApplication::translate("GUIClass", "Save log", 0, QApplication::UnicodeUTF8));
        btnClearLog->setText(QApplication::translate("GUIClass", "Clear log", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabLog), QApplication::translate("GUIClass", "Log", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tabLog), QApplication::translate("GUIClass", "Program log", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("GUIClass", "&File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        menuSave_legend->setToolTip(QApplication::translate("GUIClass", "Save legend as raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        menuSave_legend->setStatusTip(QApplication::translate("GUIClass", "Save legend as raster image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        menuSave_legend->setTitle(QApplication::translate("GUIClass", "Save &legend...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mnuFileExportSVG->setToolTip(QApplication::translate("GUIClass", "Save  plots as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mnuFileExportSVG->setStatusTip(QApplication::translate("GUIClass", "Save  plots as scalable vector graphic", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        mnuFileExportSVG->setTitle(QApplication::translate("GUIClass", "&Export plot as SVG...", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("GUIClass", "&Help", 0, QApplication::UnicodeUTF8));
        menuAnalysis->setTitle(QApplication::translate("GUIClass", "&Analysis", 0, QApplication::UnicodeUTF8));
        menuInspect->setTitle(QApplication::translate("GUIClass", "&Inspect", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("GUIClass", "&View", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("GUIClass", "&Settings", 0, QApplication::UnicodeUTF8));
        dockLegend->setWindowTitle(QApplication::translate("GUIClass", "Legend", 0, QApplication::UnicodeUTF8));
        groupColorLegend->setTitle(QApplication::translate("GUIClass", "Colour", 0, QApplication::UnicodeUTF8));
        groupShapeLegend->setTitle(QApplication::translate("GUIClass", "Shape", 0, QApplication::UnicodeUTF8));
        groupSizeLegend->setTitle(QApplication::translate("GUIClass", "Size", 0, QApplication::UnicodeUTF8));
        btnSetVisualProperties->setText(QApplication::translate("GUIClass", "Legend Properties", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
