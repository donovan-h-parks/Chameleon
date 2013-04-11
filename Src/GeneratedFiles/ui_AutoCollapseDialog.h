/********************************************************************************
** Form generated from reading UI file 'AutoCollapseDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOCOLLAPSEDIALOG_H
#define UI_AUTOCOLLAPSEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoCollapseDlg
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cboFilterVariable;
    QDoubleSpinBox *spinFilterValue;
    QPushButton *btnRun;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDockWidget *AutoCollapseDlg)
    {
        if (AutoCollapseDlg->objectName().isEmpty())
            AutoCollapseDlg->setObjectName(QString::fromUtf8("AutoCollapseDlg"));
        AutoCollapseDlg->resize(527, 47);
        AutoCollapseDlg->setFloating(true);
        AutoCollapseDlg->setAllowedAreas(Qt::NoDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(4, 0, 4, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        cboFilterVariable = new QComboBox(dockWidgetContents);
        cboFilterVariable->setObjectName(QString::fromUtf8("cboFilterVariable"));

        horizontalLayout_2->addWidget(cboFilterVariable);

        spinFilterValue = new QDoubleSpinBox(dockWidgetContents);
        spinFilterValue->setObjectName(QString::fromUtf8("spinFilterValue"));
        spinFilterValue->setDecimals(3);
        spinFilterValue->setMaximum(10000);
        spinFilterValue->setSingleStep(0.1);
        spinFilterValue->setValue(0.8);

        horizontalLayout_2->addWidget(spinFilterValue);

        btnRun = new QPushButton(dockWidgetContents);
        btnRun->setObjectName(QString::fromUtf8("btnRun"));

        horizontalLayout_2->addWidget(btnRun);

        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        AutoCollapseDlg->setWidget(dockWidgetContents);

        retranslateUi(AutoCollapseDlg);

        cboFilterVariable->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(AutoCollapseDlg);
    } // setupUi

    void retranslateUi(QDockWidget *AutoCollapseDlg)
    {
        AutoCollapseDlg->setWindowTitle(QApplication::translate("AutoCollapseDlg", "Collapse nodes", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AutoCollapseDlg", "Collapse nodes where the", 0, QApplication::UnicodeUTF8));
        cboFilterVariable->clear();
        cboFilterVariable->insertItems(0, QStringList()
         << QApplication::translate("AutoCollapseDlg", "distance to the furthest leaf node is below", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AutoCollapseDlg", "distance to the root is above", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AutoCollapseDlg", "total branch length is below", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AutoCollapseDlg", "consistency index is above", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AutoCollapseDlg", "support value is below", 0, QApplication::UnicodeUTF8)
        );
        btnRun->setText(QApplication::translate("AutoCollapseDlg", "&Run", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AutoCollapseDlg: public Ui_AutoCollapseDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOCOLLAPSEDIALOG_H
