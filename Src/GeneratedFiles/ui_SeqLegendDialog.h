/********************************************************************************
** Form generated from reading UI file 'SeqLegendDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEQLEGENDDIALOG_H
#define UI_SEQLEGENDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SeqLegendDlg
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QDoubleSpinBox *spinOtherPercentage;
    QPushButton *btnOtherPercentage;

    void setupUi(QDockWidget *SeqLegendDlg)
    {
        if (SeqLegendDlg->objectName().isEmpty())
            SeqLegendDlg->setObjectName(QString::fromUtf8("SeqLegendDlg"));
        SeqLegendDlg->resize(255, 486);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SeqLegendDlg->sizePolicy().hasHeightForWidth());
        SeqLegendDlg->setSizePolicy(sizePolicy);
        SeqLegendDlg->setFloating(false);
        SeqLegendDlg->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(4);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setContentsMargins(4, 4, 4, 4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(frame);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 245, 423));
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 2, -1, 2);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinOtherPercentage = new QDoubleSpinBox(frame);
        spinOtherPercentage->setObjectName(QString::fromUtf8("spinOtherPercentage"));
        spinOtherPercentage->setDecimals(1);
        spinOtherPercentage->setMaximum(100);
        spinOtherPercentage->setSingleStep(1);
        spinOtherPercentage->setValue(5);

        horizontalLayout->addWidget(spinOtherPercentage);

        btnOtherPercentage = new QPushButton(frame);
        btnOtherPercentage->setObjectName(QString::fromUtf8("btnOtherPercentage"));
        btnOtherPercentage->setDefault(true);

        horizontalLayout->addWidget(btnOtherPercentage);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(frame);

        SeqLegendDlg->setWidget(dockWidgetContents);

        retranslateUi(SeqLegendDlg);

        QMetaObject::connectSlotsByName(SeqLegendDlg);
    } // setupUi

    void retranslateUi(QDockWidget *SeqLegendDlg)
    {
        SeqLegendDlg->setWindowTitle(QApplication::translate("SeqLegendDlg", "Sequence legend", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SeqLegendDlg", "Other percentage (<):", 0, QApplication::UnicodeUTF8));
        btnOtherPercentage->setText(QApplication::translate("SeqLegendDlg", "Update", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SeqLegendDlg: public Ui_SeqLegendDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEQLEGENDDIALOG_H
