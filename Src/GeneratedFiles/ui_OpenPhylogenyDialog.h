/********************************************************************************
** Form generated from reading UI file 'OpenPhylogenyDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENPHYLOGENYDIALOG_H
#define UI_OPENPHYLOGENYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OpenPhylogenyDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *txtPhylogenyFile;
    QPushButton *btnOpenPhylogeny;
    QVBoxLayout *verticalLayout;
    QCheckBox *chkRooted;
    QCheckBox *chkShowPhylogeny;
    QLabel *lblSampleFile;
    QLineEdit *txtSampleFile;
    QPushButton *btnOpenSampleFile;
    QLabel *label_2;
    QLineEdit *txtMetadataFile;
    QPushButton *btnOpenMetadataFile;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *btnLoadData;
    QPushButton *btnCancel;

    void setupUi(QDialog *OpenPhylogenyDlg)
    {
        if (OpenPhylogenyDlg->objectName().isEmpty())
            OpenPhylogenyDlg->setObjectName(QString::fromUtf8("OpenPhylogenyDlg"));
        OpenPhylogenyDlg->resize(387, 188);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/Resources/UniSplit.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenPhylogenyDlg->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(OpenPhylogenyDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(OpenPhylogenyDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        txtPhylogenyFile = new QLineEdit(OpenPhylogenyDlg);
        txtPhylogenyFile->setObjectName(QString::fromUtf8("txtPhylogenyFile"));

        gridLayout->addWidget(txtPhylogenyFile, 0, 1, 1, 1);

        btnOpenPhylogeny = new QPushButton(OpenPhylogenyDlg);
        btnOpenPhylogeny->setObjectName(QString::fromUtf8("btnOpenPhylogeny"));

        gridLayout->addWidget(btnOpenPhylogeny, 0, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        chkRooted = new QCheckBox(OpenPhylogenyDlg);
        chkRooted->setObjectName(QString::fromUtf8("chkRooted"));
        chkRooted->setLayoutDirection(Qt::RightToLeft);
        chkRooted->setChecked(true);

        verticalLayout->addWidget(chkRooted);

        chkShowPhylogeny = new QCheckBox(OpenPhylogenyDlg);
        chkShowPhylogeny->setObjectName(QString::fromUtf8("chkShowPhylogeny"));
        chkShowPhylogeny->setLayoutDirection(Qt::RightToLeft);
        chkShowPhylogeny->setChecked(true);

        verticalLayout->addWidget(chkShowPhylogeny);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        lblSampleFile = new QLabel(OpenPhylogenyDlg);
        lblSampleFile->setObjectName(QString::fromUtf8("lblSampleFile"));
        lblSampleFile->setLayoutDirection(Qt::LeftToRight);
        lblSampleFile->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lblSampleFile, 2, 0, 1, 1);

        txtSampleFile = new QLineEdit(OpenPhylogenyDlg);
        txtSampleFile->setObjectName(QString::fromUtf8("txtSampleFile"));

        gridLayout->addWidget(txtSampleFile, 2, 1, 1, 1);

        btnOpenSampleFile = new QPushButton(OpenPhylogenyDlg);
        btnOpenSampleFile->setObjectName(QString::fromUtf8("btnOpenSampleFile"));

        gridLayout->addWidget(btnOpenSampleFile, 2, 2, 1, 1);

        label_2 = new QLabel(OpenPhylogenyDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        txtMetadataFile = new QLineEdit(OpenPhylogenyDlg);
        txtMetadataFile->setObjectName(QString::fromUtf8("txtMetadataFile"));

        gridLayout->addWidget(txtMetadataFile, 3, 1, 1, 1);

        btnOpenMetadataFile = new QPushButton(OpenPhylogenyDlg);
        btnOpenMetadataFile->setObjectName(QString::fromUtf8("btnOpenMetadataFile"));

        gridLayout->addWidget(btnOpenMetadataFile, 3, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        btnLoadData = new QPushButton(OpenPhylogenyDlg);
        btnLoadData->setObjectName(QString::fromUtf8("btnLoadData"));

        hboxLayout->addWidget(btnLoadData);

        btnCancel = new QPushButton(OpenPhylogenyDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        hboxLayout->addWidget(btnCancel);


        verticalLayout_2->addLayout(hboxLayout);


        retranslateUi(OpenPhylogenyDlg);
        QObject::connect(btnLoadData, SIGNAL(clicked()), OpenPhylogenyDlg, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), OpenPhylogenyDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(OpenPhylogenyDlg);
    } // setupUi

    void retranslateUi(QDialog *OpenPhylogenyDlg)
    {
        OpenPhylogenyDlg->setWindowTitle(QApplication::translate("OpenPhylogenyDlg", "Open phylogeny", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OpenPhylogenyDlg", "Phylogeny file:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtPhylogenyFile->setToolTip(QApplication::translate("OpenPhylogenyDlg", "Phylogenetic tree or network with named leaf nodes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnOpenPhylogeny->setText(QApplication::translate("OpenPhylogenyDlg", "Open", 0, QApplication::UnicodeUTF8));
        chkRooted->setText(QApplication::translate("OpenPhylogenyDlg", "Treat tree as implicitly rooted", 0, QApplication::UnicodeUTF8));
        chkShowPhylogeny->setText(QApplication::translate("OpenPhylogenyDlg", "Show phylogeny", 0, QApplication::UnicodeUTF8));
        lblSampleFile->setText(QApplication::translate("OpenPhylogenyDlg", "Sample file:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtSampleFile->setToolTip(QApplication::translate("OpenPhylogenyDlg", "Maps sequences to their source sample", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnOpenSampleFile->setText(QApplication::translate("OpenPhylogenyDlg", "Open", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OpenPhylogenyDlg", "Metadata file (optional):", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtMetadataFile->setToolTip(QApplication::translate("OpenPhylogenyDlg", "Indicates metadata for each sample site", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnOpenMetadataFile->setText(QApplication::translate("OpenPhylogenyDlg", "Open", 0, QApplication::UnicodeUTF8));
        btnLoadData->setText(QApplication::translate("OpenPhylogenyDlg", "Load", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("OpenPhylogenyDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OpenPhylogenyDlg: public Ui_OpenPhylogenyDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENPHYLOGENYDIALOG_H
