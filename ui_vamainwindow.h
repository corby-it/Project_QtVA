/********************************************************************************
** Form generated from reading UI file 'vamainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
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
    QGroupBox *boxFrameResized;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelFrameResized;
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
    QGroupBox *boxOptions;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *labelClass;
    QLabel *label;
    QLabel *labelPerc;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *editLk;
    QPlainTextEdit *editConsole;
    QPushButton *buttonStartProcessing;
    QPushButton *buttonStopProcessing;
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
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(10);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        boxFrameResized = new QGroupBox(centralWidget);
        boxFrameResized->setObjectName(QStringLiteral("boxFrameResized"));
        verticalLayout_3 = new QVBoxLayout(boxFrameResized);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        labelFrameResized = new QLabel(boxFrameResized);
        labelFrameResized->setObjectName(QStringLiteral("labelFrameResized"));
        labelFrameResized->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        labelFrameResized->setScaledContents(false);

        verticalLayout_3->addWidget(labelFrameResized);


        gridLayout->addWidget(boxFrameResized, 0, 2, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
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

        boxOptions = new QGroupBox(centralWidget);
        boxOptions->setObjectName(QStringLiteral("boxOptions"));
        horizontalLayoutWidget_2 = new QWidget(boxOptions);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 381, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("font: 75 12pt \"Ubuntu\";"));

        horizontalLayout_2->addWidget(label_3);

        labelClass = new QLabel(horizontalLayoutWidget_2);
        labelClass->setObjectName(QStringLiteral("labelClass"));
        labelClass->setStyleSheet(QLatin1String("font: 75 14pt \"Ubuntu\";\n"
"color: rgb(2, 170, 77);"));

        horizontalLayout_2->addWidget(labelClass);

        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("font: 75 12pt \"Ubuntu\";"));

        horizontalLayout_2->addWidget(label);

        labelPerc = new QLabel(horizontalLayoutWidget_2);
        labelPerc->setObjectName(QStringLiteral("labelPerc"));
        labelPerc->setStyleSheet(QLatin1String("font: 75 14pt \"Ubuntu\";\n"
"color: rgb(2, 170, 77);"));

        horizontalLayout_2->addWidget(labelPerc);

        horizontalLayoutWidget = new QWidget(boxOptions);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 70, 151, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        editLk = new QLineEdit(horizontalLayoutWidget);
        editLk->setObjectName(QStringLiteral("editLk"));

        horizontalLayout->addWidget(editLk);

        editConsole = new QPlainTextEdit(boxOptions);
        editConsole->setObjectName(QStringLiteral("editConsole"));
        editConsole->setGeometry(QRect(10, 110, 381, 191));
        editConsole->setStyleSheet(QStringLiteral("font: 8pt \"Consolas\";"));
        editConsole->setReadOnly(true);
        editConsole->setBackgroundVisible(false);
        buttonStartProcessing = new QPushButton(boxOptions);
        buttonStartProcessing->setObjectName(QStringLiteral("buttonStartProcessing"));
        buttonStartProcessing->setGeometry(QRect(180, 70, 100, 31));
        buttonStopProcessing = new QPushButton(boxOptions);
        buttonStopProcessing->setObjectName(QStringLiteral("buttonStopProcessing"));
        buttonStopProcessing->setGeometry(QRect(290, 70, 100, 31));

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
        boxFrameResized->setTitle(QApplication::translate("VAMainWindow", "Frame Resized", 0));
        labelFrameResized->setText(QApplication::translate("VAMainWindow", "TextLabel", 0));
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
        boxOptions->setTitle(QApplication::translate("VAMainWindow", "Output", 0));
        label_3->setText(QApplication::translate("VAMainWindow", "Classificazione:", 0));
        labelClass->setText(QApplication::translate("VAMainWindow", "TextLabel", 0));
        label->setText(QApplication::translate("VAMainWindow", "Corretta al:", 0));
        labelPerc->setText(QApplication::translate("VAMainWindow", "TextLabel", 0));
        label_2->setText(QApplication::translate("VAMainWindow", "LK Thresh", 0));
        editConsole->setPlainText(QString());
        buttonStartProcessing->setText(QApplication::translate("VAMainWindow", "Start Processing", 0));
        buttonStopProcessing->setText(QApplication::translate("VAMainWindow", "Stop processing", 0));
        menuFile->setTitle(QApplication::translate("VAMainWindow", "File", 0));
        menuAbout->setTitle(QApplication::translate("VAMainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class VAMainWindow: public Ui_VAMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VAMAINWINDOW_H
