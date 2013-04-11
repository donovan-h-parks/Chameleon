/********************************************************************************
** Form generated from reading UI file 'ClusterTreeAnalysisDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLUSTERTREEANALYSISDIALOG_H
#define UI_CLUSTERTREEANALYSISDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClusterTreeAnalysisDlg
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *lblClusterSplits_2;
    QComboBox *cboClusteringMethod;
    QLabel *lblClusterIterations;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinJackknifeIterations;
    QSpacerItem *horizontalSpacer;
    QLabel *lblClusterSeqToRetain;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinSeqToRetain;
    QPushButton *btnMinSeq;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnRun;

    void setupUi(QDockWidget *ClusterTreeAnalysisDlg)
    {
        if (ClusterTreeAnalysisDlg->objectName().isEmpty())
            ClusterTreeAnalysisDlg->setObjectName(QString::fromUtf8("ClusterTreeAnalysisDlg"));
        ClusterTreeAnalysisDlg->resize(303, 152);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ClusterTreeAnalysisDlg->sizePolicy().hasHeightForWidth());
        ClusterTreeAnalysisDlg->setSizePolicy(sizePolicy);
        ClusterTreeAnalysisDlg->setFloating(false);
        ClusterTreeAnalysisDlg->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        lblClusterSplits_2 = new QLabel(dockWidgetContents);
        lblClusterSplits_2->setObjectName(QString::fromUtf8("lblClusterSplits_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblClusterSplits_2);

        cboClusteringMethod = new QComboBox(dockWidgetContents);
        cboClusteringMethod->setObjectName(QString::fromUtf8("cboClusteringMethod"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboClusteringMethod);

        lblClusterIterations = new QLabel(dockWidgetContents);
        lblClusterIterations->setObjectName(QString::fromUtf8("lblClusterIterations"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblClusterIterations);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        spinJackknifeIterations = new QSpinBox(dockWidgetContents);
        spinJackknifeIterations->setObjectName(QString::fromUtf8("spinJackknifeIterations"));
        spinJackknifeIterations->setMaximum(1000);
        spinJackknifeIterations->setSingleStep(1);
        spinJackknifeIterations->setValue(0);

        horizontalLayout_2->addWidget(spinJackknifeIterations);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_2);

        lblClusterSeqToRetain = new QLabel(dockWidgetContents);
        lblClusterSeqToRetain->setObjectName(QString::fromUtf8("lblClusterSeqToRetain"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblClusterSeqToRetain);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spinSeqToRetain = new QSpinBox(dockWidgetContents);
        spinSeqToRetain->setObjectName(QString::fromUtf8("spinSeqToRetain"));
        spinSeqToRetain->setMinimum(1);
        spinSeqToRetain->setMaximum(10000);
        spinSeqToRetain->setValue(50);

        horizontalLayout->addWidget(spinSeqToRetain);

        btnMinSeq = new QPushButton(dockWidgetContents);
        btnMinSeq->setObjectName(QString::fromUtf8("btnMinSeq"));

        horizontalLayout->addWidget(btnMinSeq);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout);


        verticalLayout->addLayout(formLayout);

        btnRun = new QPushButton(dockWidgetContents);
        btnRun->setObjectName(QString::fromUtf8("btnRun"));

        verticalLayout->addWidget(btnRun);


        verticalLayout_2->addLayout(verticalLayout);

        ClusterTreeAnalysisDlg->setWidget(dockWidgetContents);

        retranslateUi(ClusterTreeAnalysisDlg);

        cboClusteringMethod->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(ClusterTreeAnalysisDlg);
    } // setupUi

    void retranslateUi(QDockWidget *ClusterTreeAnalysisDlg)
    {
        ClusterTreeAnalysisDlg->setWindowTitle(QApplication::translate("ClusterTreeAnalysisDlg", "Cluster tree analysis", 0, QApplication::UnicodeUTF8));
        lblClusterSplits_2->setText(QApplication::translate("ClusterTreeAnalysisDlg", "Clustering method:", 0, QApplication::UnicodeUTF8));
        cboClusteringMethod->clear();
        cboClusteringMethod->insertItems(0, QStringList()
         << QApplication::translate("ClusterTreeAnalysisDlg", "Complete linkage", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ClusterTreeAnalysisDlg", "Neighbour joining", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ClusterTreeAnalysisDlg", "Single linkage", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ClusterTreeAnalysisDlg", "UPGMA", 0, QApplication::UnicodeUTF8)
        );
        lblClusterIterations->setText(QApplication::translate("ClusterTreeAnalysisDlg", "Number of jackknife trees:", 0, QApplication::UnicodeUTF8));
        lblClusterSeqToRetain->setText(QApplication::translate("ClusterTreeAnalysisDlg", "Sequences to retain:", 0, QApplication::UnicodeUTF8));
        btnMinSeq->setText(QApplication::translate("ClusterTreeAnalysisDlg", "Min. Sequences", 0, QApplication::UnicodeUTF8));
        btnRun->setText(QApplication::translate("ClusterTreeAnalysisDlg", "Run", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClusterTreeAnalysisDlg: public Ui_ClusterTreeAnalysisDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLUSTERTREEANALYSISDIALOG_H
