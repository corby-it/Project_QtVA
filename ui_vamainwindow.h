/********************************************************************************
** Form generated from reading UI file 'vamainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VAMAINWINDOW_H
#define UI_VAMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VAMainWindow
{
public:
    QAction *actionApri_Video;
    QAction *actionExit;
    QAction *actionAbout_VA_Project;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelHistoX;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelHistoY;
    QGroupBox *boxPD;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelPD;
    QGroupBox *boxFrame;
    QVBoxLayout *verticalLayout;
    QLabel *labelFrame;
    QGroupBox *boxBs;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelBS;
    QGroupBox *boxFrameResized;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelFrameResized;
    QLabel *labelBB;
    QGroupBox *boxOptions;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *editLk;
    QPushButton *buttonStartProcessing;
    QPushButton *buttonStopProcessing;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *labelClass;
    QLabel *label;
    QLabel *labelPerc;
    QLabel *label_6;
    QLabel *labelRecall;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLabel *label_5;
    QPlainTextEdit *editConsole;
    QListWidget *historylist;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;

    void setupUi(QMainWindow *VAMainWindow)
    {
        if (VAMainWindow->objectName().isEmpty())
            VAMainWindow->setObjectName(QStringLiteral("VAMainWindow"));
        VAMainWindow->resize(1250, 700);
        actionApri_Video = new QAction(VAMainWindow);
        actionApri_Video->setObjectName(QStringLiteral("actionApri_Video"));
        actionExit = new QAction(VAMainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout_VA_Project = new QAction(VAMainWindow);
        actionAbout_VA_Project->setObjectName(QStringLiteral("actionAbout_VA_Project"));
        centralWidget = new QWidget(VAMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(10);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        labelHistoX = new QLabel(groupBox);
        labelHistoX->setObjectName(QStringLiteral("labelHistoX"));
        labelHistoX->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        verticalLayout_6->addWidget(labelHistoX);


        verticalLayout_5->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        verticalLayout_7 = new QVBoxLayout(groupBox_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        labelHistoY = new QLabel(groupBox_2);
        labelHistoY->setObjectName(QStringLiteral("labelHistoY"));
        labelHistoY->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        verticalLayout_7->addWidget(labelHistoY);


        verticalLayout_5->addWidget(groupBox_2);


        gridLayout->addLayout(verticalLayout_5, 1, 1, 1, 1);

        boxPD = new QGroupBox(centralWidget);
        boxPD->setObjectName(QStringLiteral("boxPD"));
        boxPD->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        verticalLayout_4 = new QVBoxLayout(boxPD);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        labelPD = new QLabel(boxPD);
        labelPD->setObjectName(QStringLiteral("labelPD"));
        labelPD->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        labelPD->setScaledContents(false);

        verticalLayout_4->addWidget(labelPD);


        gridLayout->addWidget(boxPD, 1, 0, 1, 1);

        boxFrame = new QGroupBox(centralWidget);
        boxFrame->setObjectName(QStringLiteral("boxFrame"));
        boxFrame->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        verticalLayout = new QVBoxLayout(boxFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelFrame = new QLabel(boxFrame);
        labelFrame->setObjectName(QStringLiteral("labelFrame"));
        labelFrame->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        labelFrame->setScaledContents(false);

        verticalLayout->addWidget(labelFrame);


        gridLayout->addWidget(boxFrame, 0, 0, 1, 1);

        boxBs = new QGroupBox(centralWidget);
        boxBs->setObjectName(QStringLiteral("boxBs"));
        boxBs->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        verticalLayout_2 = new QVBoxLayout(boxBs);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelBS = new QLabel(boxBs);
        labelBS->setObjectName(QStringLiteral("labelBS"));
        labelBS->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        labelBS->setScaledContents(false);

        verticalLayout_2->addWidget(labelBS);


        gridLayout->addWidget(boxBs, 0, 1, 1, 1);

        boxFrameResized = new QGroupBox(centralWidget);
        boxFrameResized->setObjectName(QStringLiteral("boxFrameResized"));
        boxFrameResized->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        horizontalLayout_3 = new QHBoxLayout(boxFrameResized);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelFrameResized = new QLabel(boxFrameResized);
        labelFrameResized->setObjectName(QStringLiteral("labelFrameResized"));
        labelFrameResized->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0, 0);"));
        labelFrameResized->setScaledContents(false);

        horizontalLayout_3->addWidget(labelFrameResized);

        labelBB = new QLabel(boxFrameResized);
        labelBB->setObjectName(QStringLiteral("labelBB"));
        labelBB->setMinimumSize(QSize(0, 150));
        labelBB->setMaximumSize(QSize(16777215, 150));
        labelBB->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(labelBB);


        gridLayout->addWidget(boxFrameResized, 0, 2, 1, 1);

        boxOptions = new QGroupBox(centralWidget);
        boxOptions->setObjectName(QStringLiteral("boxOptions"));
        boxOptions->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        verticalLayout_8 = new QVBoxLayout(boxOptions);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(boxOptions);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setStyleSheet(QStringLiteral("font: 75 10pt \"MS Shell Dlg 2\";"));

        horizontalLayout->addWidget(label_2);

        editLk = new QLineEdit(boxOptions);
        editLk->setObjectName(QStringLiteral("editLk"));
        sizePolicy1.setHeightForWidth(editLk->sizePolicy().hasHeightForWidth());
        editLk->setSizePolicy(sizePolicy1);
        editLk->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(editLk);

        buttonStartProcessing = new QPushButton(boxOptions);
        buttonStartProcessing->setObjectName(QStringLiteral("buttonStartProcessing"));
        sizePolicy1.setHeightForWidth(buttonStartProcessing->sizePolicy().hasHeightForWidth());
        buttonStartProcessing->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qtva/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonStartProcessing->setIcon(icon);

        horizontalLayout->addWidget(buttonStartProcessing);

        buttonStopProcessing = new QPushButton(boxOptions);
        buttonStopProcessing->setObjectName(QStringLiteral("buttonStopProcessing"));
        sizePolicy1.setHeightForWidth(buttonStopProcessing->sizePolicy().hasHeightForWidth());
        buttonStopProcessing->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/qtva/icons/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonStopProcessing->setIcon(icon1);

        horizontalLayout->addWidget(buttonStopProcessing);


        verticalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(boxOptions);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setStyleSheet(QStringLiteral("font: 75 12pt \"Ubuntu\";"));

        horizontalLayout_2->addWidget(label_3);

        labelClass = new QLabel(boxOptions);
        labelClass->setObjectName(QStringLiteral("labelClass"));
        sizePolicy1.setHeightForWidth(labelClass->sizePolicy().hasHeightForWidth());
        labelClass->setSizePolicy(sizePolicy1);
        labelClass->setMinimumSize(QSize(80, 0));
        labelClass->setMaximumSize(QSize(80, 16777215));
        labelClass->setStyleSheet(QLatin1String("font: 75 14pt \"Ubuntu\";\n"
"color: rgb(2, 170, 77);"));

        horizontalLayout_2->addWidget(labelClass);

        label = new QLabel(boxOptions);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setStyleSheet(QStringLiteral("font: 75 12pt \"Ubuntu\";"));

        horizontalLayout_2->addWidget(label);

        labelPerc = new QLabel(boxOptions);
        labelPerc->setObjectName(QStringLiteral("labelPerc"));
        sizePolicy1.setHeightForWidth(labelPerc->sizePolicy().hasHeightForWidth());
        labelPerc->setSizePolicy(sizePolicy1);
        labelPerc->setMinimumSize(QSize(80, 0));
        labelPerc->setMaximumSize(QSize(80, 16777215));
        labelPerc->setStyleSheet(QLatin1String("font: 75 14pt \"Ubuntu\";\n"
"color: rgb(2, 170, 77);"));

        horizontalLayout_2->addWidget(labelPerc);

        label_6 = new QLabel(boxOptions);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setStyleSheet(QStringLiteral("font: 75 12pt \"Ubuntu\";"));

        horizontalLayout_2->addWidget(label_6);

        labelRecall = new QLabel(boxOptions);
        labelRecall->setObjectName(QStringLiteral("labelRecall"));
        sizePolicy1.setHeightForWidth(labelRecall->sizePolicy().hasHeightForWidth());
        labelRecall->setSizePolicy(sizePolicy1);
        labelRecall->setMinimumSize(QSize(80, 0));
        labelRecall->setMaximumSize(QSize(80, 16777215));
        labelRecall->setStyleSheet(QLatin1String("font: 75 14pt \"Ubuntu\";\n"
"color: rgb(2, 170, 77);"));

        horizontalLayout_2->addWidget(labelRecall);


        verticalLayout_8->addLayout(horizontalLayout_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(boxOptions);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(boxOptions);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        editConsole = new QPlainTextEdit(boxOptions);
        editConsole->setObjectName(QStringLiteral("editConsole"));
        sizePolicy.setHeightForWidth(editConsole->sizePolicy().hasHeightForWidth());
        editConsole->setSizePolicy(sizePolicy);
        editConsole->setStyleSheet(QStringLiteral("font: 8pt \"Consolas\";"));
        editConsole->setReadOnly(true);
        editConsole->setBackgroundVisible(false);

        gridLayout_2->addWidget(editConsole, 1, 0, 1, 1);

        historylist = new QListWidget(boxOptions);
        historylist->setObjectName(QStringLiteral("historylist"));
        sizePolicy.setHeightForWidth(historylist->sizePolicy().hasHeightForWidth());
        historylist->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(historylist, 1, 1, 1, 1);


        verticalLayout_8->addLayout(gridLayout_2);


        gridLayout->addWidget(boxOptions, 1, 2, 1, 1);

        VAMainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(VAMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VAMainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(VAMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1250, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        VAMainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionApri_Video);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionAbout_VA_Project);

        retranslateUi(VAMainWindow);

        QMetaObject::connectSlotsByName(VAMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VAMainWindow)
    {
        VAMainWindow->setWindowTitle(QApplication::translate("VAMainWindow", "VA Project - Action Recognition", 0));
        actionApri_Video->setText(QApplication::translate("VAMainWindow", "Open Video", 0));
        actionExit->setText(QApplication::translate("VAMainWindow", "Exit", 0));
        actionAbout_VA_Project->setText(QApplication::translate("VAMainWindow", "About VA Project...", 0));
        groupBox->setTitle(QApplication::translate("VAMainWindow", "X Histogram", 0));
        labelHistoX->setText(QApplication::translate("VAMainWindow", "TextLabel", 0));
        groupBox_2->setTitle(QApplication::translate("VAMainWindow", "Y Histogram", 0));
        labelHistoY->setText(QApplication::translate("VAMainWindow", "TextLabel", 0));
        boxPD->setTitle(QApplication::translate("VAMainWindow", "People Detection", 0));
        labelPD->setText(QApplication::translate("VAMainWindow", "TextLabel", 0));
        boxFrame->setTitle(QApplication::translate("VAMainWindow", "Original Frame", 0));
        labelFrame->setText(QApplication::translate("VAMainWindow", "TextLabel", 0));
        boxBs->setTitle(QApplication::translate("VAMainWindow", "Background Subtraction", 0));
        labelBS->setText(QApplication::translate("VAMainWindow", "TextLabel", 0));
        boxFrameResized->setTitle(QApplication::translate("VAMainWindow", "Frame Resized", 0));
        labelFrameResized->setText(QString());
        labelBB->setText(QString());
        boxOptions->setTitle(QApplication::translate("VAMainWindow", "Output", 0));
        label_2->setText(QApplication::translate("VAMainWindow", "LK Thresh", 0));
        editLk->setText(QString());
        buttonStartProcessing->setText(QApplication::translate("VAMainWindow", "Start", 0));
        buttonStopProcessing->setText(QApplication::translate("VAMainWindow", "Pause", 0));
        label_3->setText(QApplication::translate("VAMainWindow", "Action:", 0));
        labelClass->setText(QApplication::translate("VAMainWindow", "--", 0));
        label->setText(QApplication::translate("VAMainWindow", "Precision:", 0));
        labelPerc->setText(QApplication::translate("VAMainWindow", "--", 0));
        label_6->setText(QApplication::translate("VAMainWindow", "Recall:", 0));
        labelRecall->setText(QApplication::translate("VAMainWindow", "--", 0));
        label_4->setText(QApplication::translate("VAMainWindow", "Output", 0));
        label_5->setText(QApplication::translate("VAMainWindow", "History ", 0));
        editConsole->setPlainText(QString());
        menuFile->setTitle(QApplication::translate("VAMainWindow", "File", 0));
        menuAbout->setTitle(QApplication::translate("VAMainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class VAMainWindow: public Ui_VAMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VAMAINWINDOW_H
