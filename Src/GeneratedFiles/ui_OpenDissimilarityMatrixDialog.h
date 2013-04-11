/********************************************************************************
** Form generated from reading UI file 'OpenDissimilarityMatrixDialog.ui'
**
** Created: Fri Apr 5 15:59:36 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENDISSIMILARITYMATRIXDIALOG_H
#define UI_OPENDISSIMILARITYMATRIXDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_OpenDissimilarityMatrixDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *txtDissimilarityMatrix;
    QPushButton *btnOpenDissimilarityMatrix;
    QLabel *label_2;
    QLineEdit *txtMetadataFile;
    QPushButton *btnOpenMetadataFile;
    QHBoxLayout *_2;
    QSpacerItem *spacerItem;
    QPushButton *btnLoadData;
    QPushButton *btnCancel;

    void setupUi(QDialog *OpenDissimilarityMatrixDlg)
    {
        if (OpenDissimilarityMatrixDlg->objectName().isEmpty())
            OpenDissimilarityMatrixDlg->setObjectName(QString::fromUtf8("OpenDissimilarityMatrixDlg"));
        OpenDissimilarityMatrixDlg->resize(418, 111);
        verticalLayout = new QVBoxLayout(OpenDissimilarityMatrixDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(OpenDissimilarityMatrixDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        txtDissimilarityMatrix = new QLineEdit(OpenDissimilarityMatrixDlg);
        txtDissimilarityMatrix->setObjectName(QString::fromUtf8("txtDissimilarityMatrix"));

        gridLayout->addWidget(txtDissimilarityMatrix, 0, 1, 1, 1);

        btnOpenDissimilarityMatrix = new QPushButton(OpenDissimilarityMatrixDlg);
        btnOpenDissimilarityMatrix->setObjectName(QString::fromUtf8("btnOpenDissimilarityMatrix"));

        gridLayout->addWidget(btnOpenDissimilarityMatrix, 0, 2, 1, 1);

        label_2 = new QLabel(OpenDissimilarityMatrixDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        txtMetadataFile = new QLineEdit(OpenDissimilarityMatrixDlg);
        txtMetadataFile->setObjectName(QString::fromUtf8("txtMetadataFile"));

        gridLayout->addWidget(txtMetadataFile, 1, 1, 1, 1);

        btnOpenMetadataFile = new QPushButton(OpenDissimilarityMatrixDlg);
        btnOpenMetadataFile->setObjectName(QString::fromUtf8("btnOpenMetadataFile"));

        gridLayout->addWidget(btnOpenMetadataFile, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        _2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        _2->setSpacing(6);
#endif
        _2->setContentsMargins(0, 0, 0, 0);
        _2->setObjectName(QString::fromUtf8("_2"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(spacerItem);

        btnLoadData = new QPushButton(OpenDissimilarityMatrixDlg);
        btnLoadData->setObjectName(QString::fromUtf8("btnLoadData"));

        _2->addWidget(btnLoadData);

        btnCancel = new QPushButton(OpenDissimilarityMatrixDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        _2->addWidget(btnCancel);


        verticalLayout->addLayout(_2);


        retranslateUi(OpenDissimilarityMatrixDlg);
        QObject::connect(btnLoadData, SIGNAL(clicked()), OpenDissimilarityMatrixDlg, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), OpenDissimilarityMatrixDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(OpenDissimilarityMatrixDlg);
    } // setupUi

    void retranslateUi(QDialog *OpenDissimilarityMatrixDlg)
    {
        OpenDissimilarityMatrixDlg->setWindowTitle(QApplication::translate("OpenDissimilarityMatrixDlg", "Open dissimilarity matrix", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OpenDissimilarityMatrixDlg", "Dissimilarity matrix:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtDissimilarityMatrix->setToolTip(QApplication::translate("OpenDissimilarityMatrixDlg", "Matrix indicating dissimilarity between sequences", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnOpenDissimilarityMatrix->setText(QApplication::translate("OpenDissimilarityMatrixDlg", "Open", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OpenDissimilarityMatrixDlg", "Metadata file (optional):", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtMetadataFile->setToolTip(QApplication::translate("OpenDissimilarityMatrixDlg", "Indicates metadata for each sample site", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnOpenMetadataFile->setText(QApplication::translate("OpenDissimilarityMatrixDlg", "Open", 0, QApplication::UnicodeUTF8));
        btnLoadData->setText(QApplication::translate("OpenDissimilarityMatrixDlg", "Load", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("OpenDissimilarityMatrixDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OpenDissimilarityMatrixDlg: public Ui_OpenDissimilarityMatrixDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENDISSIMILARITYMATRIXDIALOG_H
