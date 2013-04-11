/********************************************************************************
** Form generated from reading UI file 'DiversityMeasureDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIVERSITYMEASUREDIALOG_H
#define UI_DIVERSITYMEASUREDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiversityMeasureDlg
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *lblDistTypeOfMeasure;
    QComboBox *cboMeasureType;
    QLabel *lblDistSplits;
    QComboBox *cboMeasure;
    QPushButton *btnRun;

    void setupUi(QDockWidget *DiversityMeasureDlg)
    {
        if (DiversityMeasureDlg->objectName().isEmpty())
            DiversityMeasureDlg->setObjectName(QString::fromUtf8("DiversityMeasureDlg"));
        DiversityMeasureDlg->resize(252, 117);
        DiversityMeasureDlg->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lblDistTypeOfMeasure = new QLabel(dockWidgetContents);
        lblDistTypeOfMeasure->setObjectName(QString::fromUtf8("lblDistTypeOfMeasure"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblDistTypeOfMeasure);

        cboMeasureType = new QComboBox(dockWidgetContents);
        cboMeasureType->setObjectName(QString::fromUtf8("cboMeasureType"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboMeasureType);

        lblDistSplits = new QLabel(dockWidgetContents);
        lblDistSplits->setObjectName(QString::fromUtf8("lblDistSplits"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblDistSplits);

        cboMeasure = new QComboBox(dockWidgetContents);
        cboMeasure->setObjectName(QString::fromUtf8("cboMeasure"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cboMeasure);


        verticalLayout->addLayout(formLayout);

        btnRun = new QPushButton(dockWidgetContents);
        btnRun->setObjectName(QString::fromUtf8("btnRun"));

        verticalLayout->addWidget(btnRun);

        DiversityMeasureDlg->setWidget(dockWidgetContents);

        retranslateUi(DiversityMeasureDlg);

        QMetaObject::connectSlotsByName(DiversityMeasureDlg);
    } // setupUi

    void retranslateUi(QDockWidget *DiversityMeasureDlg)
    {
        DiversityMeasureDlg->setWindowTitle(QApplication::translate("DiversityMeasureDlg", "Diversity measure", 0, QApplication::UnicodeUTF8));
        lblDistTypeOfMeasure->setText(QApplication::translate("DiversityMeasureDlg", "Type of measure:", 0, QApplication::UnicodeUTF8));
        cboMeasureType->clear();
        cboMeasureType->insertItems(0, QStringList()
         << QApplication::translate("DiversityMeasureDlg", "Unweighted", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DiversityMeasureDlg", "Weighted, unnormalized", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DiversityMeasureDlg", "Weighted, normalized", 0, QApplication::UnicodeUTF8)
        );
        lblDistSplits->setText(QApplication::translate("DiversityMeasureDlg", "Measure:", 0, QApplication::UnicodeUTF8));
        btnRun->setText(QApplication::translate("DiversityMeasureDlg", "Run", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DiversityMeasureDlg: public Ui_DiversityMeasureDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIVERSITYMEASUREDIALOG_H
