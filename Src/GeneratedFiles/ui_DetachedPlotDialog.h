/********************************************************************************
** Form generated from reading UI file 'DetachedPlotDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETACHEDPLOTDIALOG_H
#define UI_DETACHEDPLOTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_DetachedPlotDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *plotFrame;
    QVBoxLayout *verticalLayout;
    QwtPlot *qwtPlot;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSaveRaster;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;

    void setupUi(QDialog *DetachedPlotDlg)
    {
        if (DetachedPlotDlg->objectName().isEmpty())
            DetachedPlotDlg->setObjectName(QString::fromUtf8("DetachedPlotDlg"));
        DetachedPlotDlg->resize(800, 600);
        verticalLayout_2 = new QVBoxLayout(DetachedPlotDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        plotFrame = new QFrame(DetachedPlotDlg);
        plotFrame->setObjectName(QString::fromUtf8("plotFrame"));
        plotFrame->setFrameShape(QFrame::StyledPanel);
        plotFrame->setFrameShadow(QFrame::Plain);
        verticalLayout = new QVBoxLayout(plotFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        qwtPlot = new QwtPlot(plotFrame);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));

        verticalLayout->addWidget(qwtPlot);


        verticalLayout_2->addWidget(plotFrame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnSaveRaster = new QPushButton(DetachedPlotDlg);
        btnSaveRaster->setObjectName(QString::fromUtf8("btnSaveRaster"));
        btnSaveRaster->setAutoDefault(false);

        horizontalLayout->addWidget(btnSaveRaster);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnClose = new QPushButton(DetachedPlotDlg);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setDefault(true);

        horizontalLayout->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(DetachedPlotDlg);

        QMetaObject::connectSlotsByName(DetachedPlotDlg);
    } // setupUi

    void retranslateUi(QDialog *DetachedPlotDlg)
    {
        DetachedPlotDlg->setWindowTitle(QApplication::translate("DetachedPlotDlg", "Plot dialog", 0, QApplication::UnicodeUTF8));
        btnSaveRaster->setText(QApplication::translate("DetachedPlotDlg", "Save as raster image...", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("DetachedPlotDlg", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DetachedPlotDlg: public Ui_DetachedPlotDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETACHEDPLOTDIALOG_H
