/********************************************************************************
** Form generated from reading UI file 'ProjectedCoordDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTEDCOORDDIALOG_H
#define UI_PROJECTEDCOORDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectedCoordDlg
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableEmbeddedDimensions;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSave;

    void setupUi(QDockWidget *ProjectedCoordDlg)
    {
        if (ProjectedCoordDlg->objectName().isEmpty())
            ProjectedCoordDlg->setObjectName(QString::fromUtf8("ProjectedCoordDlg"));
        ProjectedCoordDlg->resize(600, 456);
        ProjectedCoordDlg->setMinimumSize(QSize(400, 300));
        ProjectedCoordDlg->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableEmbeddedDimensions = new QTableWidget(dockWidgetContents);
        tableEmbeddedDimensions->setObjectName(QString::fromUtf8("tableEmbeddedDimensions"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(tableEmbeddedDimensions->sizePolicy().hasHeightForWidth());
        tableEmbeddedDimensions->setSizePolicy(sizePolicy);
        tableEmbeddedDimensions->setDragEnabled(true);
        tableEmbeddedDimensions->setAlternatingRowColors(true);
        tableEmbeddedDimensions->setCornerButtonEnabled(true);
        tableEmbeddedDimensions->setRowCount(0);
        tableEmbeddedDimensions->setColumnCount(0);
        tableEmbeddedDimensions->horizontalHeader()->setVisible(false);
        tableEmbeddedDimensions->horizontalHeader()->setCascadingSectionResizes(false);
        tableEmbeddedDimensions->horizontalHeader()->setDefaultSectionSize(100);
        tableEmbeddedDimensions->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableEmbeddedDimensions->horizontalHeader()->setStretchLastSection(false);
        tableEmbeddedDimensions->verticalHeader()->setVisible(false);
        tableEmbeddedDimensions->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout->addWidget(tableEmbeddedDimensions);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnSave = new QPushButton(dockWidgetContents);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout->addWidget(btnSave);


        verticalLayout->addLayout(horizontalLayout);

        ProjectedCoordDlg->setWidget(dockWidgetContents);

        retranslateUi(ProjectedCoordDlg);

        QMetaObject::connectSlotsByName(ProjectedCoordDlg);
    } // setupUi

    void retranslateUi(QDockWidget *ProjectedCoordDlg)
    {
        ProjectedCoordDlg->setWindowTitle(QApplication::translate("ProjectedCoordDlg", "Projected coordinates", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("ProjectedCoordDlg", "&Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProjectedCoordDlg: public Ui_ProjectedCoordDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTEDCOORDDIALOG_H
