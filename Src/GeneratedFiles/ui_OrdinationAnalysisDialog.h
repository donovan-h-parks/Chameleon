/********************************************************************************
** Form generated from reading UI file 'OrdinationAnalysisDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDINATIONANALYSISDIALOG_H
#define UI_ORDINATIONANALYSISDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
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

class Ui_OrdinationAnalysisDlg
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *lblEmbeddingMethod;
    QComboBox *cboClusteringMethod;
    QLabel *lblNeighborhoodValue;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *spinNeighborhoodValue;
    QSpacerItem *horizontalSpacer;
    QLabel *lblIterations;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinMaxIter;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblNeighbourhoodMethod;
    QComboBox *cboNeighbourhoodMethod;
    QLabel *lblNeighbourhoodField;
    QComboBox *cboNeighbourhoodField;
    QPushButton *btnRun;

    void setupUi(QDockWidget *OrdinationAnalysisDlg)
    {
        if (OrdinationAnalysisDlg->objectName().isEmpty())
            OrdinationAnalysisDlg->setObjectName(QString::fromUtf8("OrdinationAnalysisDlg"));
        OrdinationAnalysisDlg->resize(302, 199);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OrdinationAnalysisDlg->sizePolicy().hasHeightForWidth());
        OrdinationAnalysisDlg->setSizePolicy(sizePolicy);
        OrdinationAnalysisDlg->setFloating(false);
        OrdinationAnalysisDlg->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lblEmbeddingMethod = new QLabel(dockWidgetContents);
        lblEmbeddingMethod->setObjectName(QString::fromUtf8("lblEmbeddingMethod"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblEmbeddingMethod);

        cboClusteringMethod = new QComboBox(dockWidgetContents);
        cboClusteringMethod->setObjectName(QString::fromUtf8("cboClusteringMethod"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboClusteringMethod);

        lblNeighborhoodValue = new QLabel(dockWidgetContents);
        lblNeighborhoodValue->setObjectName(QString::fromUtf8("lblNeighborhoodValue"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblNeighborhoodValue);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        spinNeighborhoodValue = new QDoubleSpinBox(dockWidgetContents);
        spinNeighborhoodValue->setObjectName(QString::fromUtf8("spinNeighborhoodValue"));
        spinNeighborhoodValue->setMinimum(1);
        spinNeighborhoodValue->setMaximum(10000);
        spinNeighborhoodValue->setValue(7);

        horizontalLayout_2->addWidget(spinNeighborhoodValue);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_2);

        lblIterations = new QLabel(dockWidgetContents);
        lblIterations->setObjectName(QString::fromUtf8("lblIterations"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lblIterations);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spinMaxIter = new QSpinBox(dockWidgetContents);
        spinMaxIter->setObjectName(QString::fromUtf8("spinMaxIter"));
        spinMaxIter->setEnabled(false);
        spinMaxIter->setMinimum(1);
        spinMaxIter->setMaximum(10000);
        spinMaxIter->setSingleStep(10);
        spinMaxIter->setValue(100);

        horizontalLayout->addWidget(spinMaxIter);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        formLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout);

        lblNeighbourhoodMethod = new QLabel(dockWidgetContents);
        lblNeighbourhoodMethod->setObjectName(QString::fromUtf8("lblNeighbourhoodMethod"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblNeighbourhoodMethod);

        cboNeighbourhoodMethod = new QComboBox(dockWidgetContents);
        cboNeighbourhoodMethod->setObjectName(QString::fromUtf8("cboNeighbourhoodMethod"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cboNeighbourhoodMethod);

        lblNeighbourhoodField = new QLabel(dockWidgetContents);
        lblNeighbourhoodField->setObjectName(QString::fromUtf8("lblNeighbourhoodField"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblNeighbourhoodField);

        cboNeighbourhoodField = new QComboBox(dockWidgetContents);
        cboNeighbourhoodField->setObjectName(QString::fromUtf8("cboNeighbourhoodField"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cboNeighbourhoodField);


        verticalLayout->addLayout(formLayout);

        btnRun = new QPushButton(dockWidgetContents);
        btnRun->setObjectName(QString::fromUtf8("btnRun"));

        verticalLayout->addWidget(btnRun);

        OrdinationAnalysisDlg->setWidget(dockWidgetContents);

        retranslateUi(OrdinationAnalysisDlg);

        cboClusteringMethod->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(OrdinationAnalysisDlg);
    } // setupUi

    void retranslateUi(QDockWidget *OrdinationAnalysisDlg)
    {
        OrdinationAnalysisDlg->setWindowTitle(QApplication::translate("OrdinationAnalysisDlg", "Ordination analysis", 0, QApplication::UnicodeUTF8));
        lblEmbeddingMethod->setText(QApplication::translate("OrdinationAnalysisDlg", "Embedding method:", 0, QApplication::UnicodeUTF8));
        cboClusteringMethod->clear();
        cboClusteringMethod->insertItems(0, QStringList()
         << QApplication::translate("OrdinationAnalysisDlg", "Contiguous isomap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OrdinationAnalysisDlg", "Nonmetric MDS", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OrdinationAnalysisDlg", "Isomap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OrdinationAnalysisDlg", "Principal coordinate analysis", 0, QApplication::UnicodeUTF8)
        );
        lblNeighborhoodValue->setText(QApplication::translate("OrdinationAnalysisDlg", "# neighbours (k):", 0, QApplication::UnicodeUTF8));
        lblIterations->setText(QApplication::translate("OrdinationAnalysisDlg", "Max. iterations:", 0, QApplication::UnicodeUTF8));
        lblNeighbourhoodMethod->setText(QApplication::translate("OrdinationAnalysisDlg", "Neighbourhood method:", 0, QApplication::UnicodeUTF8));
        cboNeighbourhoodMethod->clear();
        cboNeighbourhoodMethod->insertItems(0, QStringList()
         << QApplication::translate("OrdinationAnalysisDlg", "Fixed number of neighbours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OrdinationAnalysisDlg", "Sample dissimilarity", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OrdinationAnalysisDlg", "Quantitative factor", 0, QApplication::UnicodeUTF8)
        );
        lblNeighbourhoodField->setText(QApplication::translate("OrdinationAnalysisDlg", "Field:", 0, QApplication::UnicodeUTF8));
        btnRun->setText(QApplication::translate("OrdinationAnalysisDlg", "Run", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OrdinationAnalysisDlg: public Ui_OrdinationAnalysisDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDINATIONANALYSISDIALOG_H
