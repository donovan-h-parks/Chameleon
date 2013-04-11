/********************************************************************************
** Form generated from reading UI file 'PropertiesDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIESDIALOG_H
#define UI_PROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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
#include "QtColorPicker.hpp"

QT_BEGIN_NAMESPACE

class Ui_PropertiesDlg
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinSelectionTransparency;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QtColorPicker *btnBackgroundColor;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnDefaultValues;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnOK;

    void setupUi(QDockWidget *PropertiesDlg)
    {
        if (PropertiesDlg->objectName().isEmpty())
            PropertiesDlg->setObjectName(QString::fromUtf8("PropertiesDlg"));
        PropertiesDlg->resize(230, 124);
        PropertiesDlg->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spinSelectionTransparency = new QSpinBox(dockWidgetContents);
        spinSelectionTransparency->setObjectName(QString::fromUtf8("spinSelectionTransparency"));
        spinSelectionTransparency->setMaximum(100);
        spinSelectionTransparency->setValue(70);

        horizontalLayout->addWidget(spinSelectionTransparency);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        btnBackgroundColor = new QtColorPicker(dockWidgetContents);
        btnBackgroundColor->setObjectName(QString::fromUtf8("btnBackgroundColor"));

        formLayout->setWidget(1, QFormLayout::FieldRole, btnBackgroundColor);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnDefaultValues = new QPushButton(dockWidgetContents);
        btnDefaultValues->setObjectName(QString::fromUtf8("btnDefaultValues"));

        horizontalLayout_2->addWidget(btnDefaultValues);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnOK = new QPushButton(dockWidgetContents);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        horizontalLayout_2->addWidget(btnOK);


        verticalLayout->addLayout(horizontalLayout_2);

        PropertiesDlg->setWidget(dockWidgetContents);

        retranslateUi(PropertiesDlg);

        QMetaObject::connectSlotsByName(PropertiesDlg);
    } // setupUi

    void retranslateUi(QDockWidget *PropertiesDlg)
    {
        PropertiesDlg->setWindowTitle(QApplication::translate("PropertiesDlg", "Properties", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PropertiesDlg", "Selection transparency:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PropertiesDlg", "Background colour:", 0, QApplication::UnicodeUTF8));
        btnBackgroundColor->setText(QApplication::translate("PropertiesDlg", "Background color", 0, QApplication::UnicodeUTF8));
        btnDefaultValues->setText(QApplication::translate("PropertiesDlg", "Restore Default Values", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("PropertiesDlg", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PropertiesDlg: public Ui_PropertiesDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIESDIALOG_H
