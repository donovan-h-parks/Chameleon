/********************************************************************************
** Form generated from reading UI file 'VisualPropertiesDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALPROPERTIESDIALOG_H
#define UI_VISUALPROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VisualPropertiesDlg
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cboColorField;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cboColorMap;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *cboShapeField;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *chkFixedShape;
    QComboBox *cboShape;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *cboSizeField;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QSpinBox *spinSizeMin;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;
    QSpinBox *spinSizeMax;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *chkLogScale;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *VisualPropertiesDlg)
    {
        if (VisualPropertiesDlg->objectName().isEmpty())
            VisualPropertiesDlg->setObjectName(QString::fromUtf8("VisualPropertiesDlg"));
        VisualPropertiesDlg->resize(250, 336);
        verticalLayout_3 = new QVBoxLayout(VisualPropertiesDlg);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(VisualPropertiesDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        cboColorField = new QComboBox(groupBox);
        cboColorField->setObjectName(QString::fromUtf8("cboColorField"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cboColorField->sizePolicy().hasHeightForWidth());
        cboColorField->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(cboColorField);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        cboColorMap = new QComboBox(groupBox);
        cboColorMap->setObjectName(QString::fromUtf8("cboColorMap"));
        sizePolicy.setHeightForWidth(cboColorMap->sizePolicy().hasHeightForWidth());
        cboColorMap->setSizePolicy(sizePolicy);
        cboColorMap->setInsertPolicy(QComboBox::InsertAlphabetically);

        horizontalLayout_2->addWidget(cboColorMap);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(VisualPropertiesDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        cboShapeField = new QComboBox(groupBox_2);
        cboShapeField->setObjectName(QString::fromUtf8("cboShapeField"));
        sizePolicy.setHeightForWidth(cboShapeField->sizePolicy().hasHeightForWidth());
        cboShapeField->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(cboShapeField);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        chkFixedShape = new QCheckBox(groupBox_2);
        chkFixedShape->setObjectName(QString::fromUtf8("chkFixedShape"));

        horizontalLayout_9->addWidget(chkFixedShape);

        cboShape = new QComboBox(groupBox_2);
        cboShape->setObjectName(QString::fromUtf8("cboShape"));

        horizontalLayout_9->addWidget(cboShape);


        verticalLayout_2->addLayout(horizontalLayout_9);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(VisualPropertiesDlg);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        cboSizeField = new QComboBox(groupBox_3);
        cboSizeField->setObjectName(QString::fromUtf8("cboSizeField"));
        sizePolicy.setHeightForWidth(cboSizeField->sizePolicy().hasHeightForWidth());
        cboSizeField->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(cboSizeField);


        verticalLayout_4->addLayout(horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        spinSizeMin = new QSpinBox(groupBox_3);
        spinSizeMin->setObjectName(QString::fromUtf8("spinSizeMin"));
        spinSizeMin->setMinimum(0);
        spinSizeMin->setMaximum(100);
        spinSizeMin->setValue(6);

        gridLayout->addWidget(spinSizeMin, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 2);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        spinSizeMax = new QSpinBox(groupBox_3);
        spinSizeMax->setObjectName(QString::fromUtf8("spinSizeMax"));
        spinSizeMax->setMinimum(0);
        spinSizeMax->setMaximum(100);
        spinSizeMax->setValue(20);

        gridLayout->addWidget(spinSizeMax, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        chkLogScale = new QCheckBox(groupBox_3);
        chkLogScale->setObjectName(QString::fromUtf8("chkLogScale"));

        gridLayout->addWidget(chkLogScale, 1, 3, 1, 1);


        verticalLayout_4->addLayout(gridLayout);


        verticalLayout_3->addWidget(groupBox_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        btnOK = new QPushButton(VisualPropertiesDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setDefault(true);

        horizontalLayout_8->addWidget(btnOK);

        btnCancel = new QPushButton(VisualPropertiesDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout_8->addWidget(btnCancel);


        verticalLayout_3->addLayout(horizontalLayout_8);


        retranslateUi(VisualPropertiesDlg);

        QMetaObject::connectSlotsByName(VisualPropertiesDlg);
    } // setupUi

    void retranslateUi(QDialog *VisualPropertiesDlg)
    {
        VisualPropertiesDlg->setWindowTitle(QApplication::translate("VisualPropertiesDlg", "Legend properties", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("VisualPropertiesDlg", "Map color", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("VisualPropertiesDlg", "Field:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("VisualPropertiesDlg", "Colour map:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("VisualPropertiesDlg", "Map shape", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("VisualPropertiesDlg", "Field:", 0, QApplication::UnicodeUTF8));
        chkFixedShape->setText(QApplication::translate("VisualPropertiesDlg", "Use fixed shape:", 0, QApplication::UnicodeUTF8));
        cboShape->clear();
        cboShape->insertItems(0, QStringList()
         << QApplication::translate("VisualPropertiesDlg", "Circle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Square", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Triangle (up)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Star (style 1)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Star (style 2)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Diamond", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Hexagon", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Cross", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Triangle (down)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Triangle (left)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Triangle (right)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Horizontal line", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Vertical line", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VisualPropertiesDlg", "Diagonal cross", 0, QApplication::UnicodeUTF8)
        );
        groupBox_3->setTitle(QApplication::translate("VisualPropertiesDlg", "Map size", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("VisualPropertiesDlg", "Field:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("VisualPropertiesDlg", "Minimum:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("VisualPropertiesDlg", "Maximum:", 0, QApplication::UnicodeUTF8));
        chkLogScale->setText(QApplication::translate("VisualPropertiesDlg", "Use log scale", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("VisualPropertiesDlg", "OK", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("VisualPropertiesDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VisualPropertiesDlg: public Ui_VisualPropertiesDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALPROPERTIESDIALOG_H
