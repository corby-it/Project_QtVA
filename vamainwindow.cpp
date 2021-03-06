#include "vamainwindow.h"
#include "ui_vamainwindow.h"

#include <opencv2/opencv.hpp>

#include <qpixmap.h>
#include <qtimer.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <QValidator>

#include "conversionutility.h"

using namespace cv;
using namespace std;

const QString VAMainWindow::styleOk = QString("font: 75 14pt \"Ubuntu\"; color: rgb(2, 170, 77);");
const QString VAMainWindow::styleErr = QString("font: 75 14pt \"Ubuntu\"; color: rgb(170, 0, 0);");

VAMainWindow::VAMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::VAMainWindow)
{
    ui->setupUi(this);

    // dimensioni fisse della finestra
    setFixedSize(this->geometry().width(), this->geometry().height());

    progressLabel = new QLabel("Open a video file...");

    videoEnded = false;

    progressBar = new QProgressBar();
    progressBar->setMaximum(100);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);

    ui->statusBar->addWidget(progressLabel, 20);
    ui->statusBar->addWidget(progressBar, 20);
    ui->statusBar->setSizeGripEnabled(false);

    ui->buttonStartProcessing->setEnabled(false);
    ui->buttonStopProcessing->setEnabled(false);

    ui->editLk->setValidator(new QIntValidator(0, 200, this));
    ui->editLk->setEnabled(false);

    ui->labelClass->setStyleSheet(styleOk);

    connect(ui->buttonStartProcessing, SIGNAL(clicked()), this, SLOT(onButtonStartProcessingClicked()));
    connect(ui->buttonStopProcessing, SIGNAL(clicked()), this, SLOT(onButtonStopProcessingClicked()));

    connect(ui->actionApri_Video, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAbout_VA_Project, SIGNAL(triggered()), this, SLOT(showCredits()));

}

void VAMainWindow::openFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Video (*.avi)");
    dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if(dialog.exec()){
        fileNames = dialog.selectedFiles();
        selectedFile = fileNames.at(0).toStdString();

        frameAnalyzer = new FrameAnalyzer(selectedFile);
        if(frameAnalyzer->isOpened()){
            ui->buttonStartProcessing->setEnabled(true);

            ui->editLk->setEnabled(true);
            ui->editLk->setText(QString::number(frameAnalyzer->lk_thresh));

            progressLabel->setText("Opened video file: "+QString(selectedFile.data()));
        }

    }
}

void VAMainWindow::onButtonStartProcessingClicked()
{
    progressLabel->setText("Processing...");
    progressBar->setValue(0);
    progressBar->setMaximum(frameAnalyzer->getFrameCount());

    double fps = frameAnalyzer->getFrameRate();
    int interval = 1/fps;

    frameAnalyzer->lk_thresh = ui->editLk->text().toInt();

    ui->editLk->setEnabled(false);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processStep()));
    timer->start(interval);

    ui->buttonStopProcessing->setEnabled(true);
    ui->buttonStartProcessing->setEnabled(false);

    if(videoEnded){
        ui->historylist->clear();
        videoEnded = false;
    }
}

void VAMainWindow::onButtonStopProcessingClicked()
{
    timer->stop();

    ui->editLk->setEnabled(true);

    ui->buttonStartProcessing->setEnabled(true);
    ui->buttonStopProcessing->setEnabled(false);
}

void VAMainWindow::processStep(){

    if(!frameAnalyzer->processFrame()){
        timer->stop();

        progressLabel->setText("End of file reached");

        QMessageBox msgbox;
        msgbox.setText("End of file reached");
        msgbox.exec();

        ui->buttonStartProcessing->setEnabled(true);
        ui->buttonStopProcessing->setEnabled(false);
        ui->editLk->setEnabled(true);

        videoEnded = true;

        // reinizializzo il frameAnalyzer con lo stesso video, cos� pu� ripartire
        frameAnalyzer = new FrameAnalyzer(selectedFile);

        return;
    }

    bool correct = frameAnalyzer->isCorrectClassification();

    if(frameAnalyzer->getCurrentClass().compare("nullo") != 0){
        if(correct)
            ui->labelClass->setStyleSheet(styleOk);
        else
            ui->labelClass->setStyleSheet(styleErr);

        ui->labelClass->setText(frameAnalyzer->getCurrentClass());
    }

    QList<QListWidgetItem *> items = ui->historylist->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);

    ui->labelRecall->setText(QString::number(((double)items.size() / frameAnalyzer->totActions) * 100, 'f', 2) + "%");
    ui->labelPerc->setText(QString::number(frameAnalyzer->getCurrentPerc(), 'f', 2) + "%");

    if(correct){
        bool add = true;
        foreach(QListWidgetItem *item, items){
            if(item->text().compare(frameAnalyzer->getCurrentClass()) == 0){
                add = false;
                break;
            }
        }

        if(add)
            ui->historylist->addItem(frameAnalyzer->getCurrentClass());
    }

    if(!frameAnalyzer->getOutputBuffer().isEmpty())
        ui->editConsole->appendPlainText(frameAnalyzer->getOutputBuffer());

    progressBar->setValue(frameAnalyzer->getCurrentFramePos());

    Mat& frame = frameAnalyzer->getCurrentFrame();
    Mat& fgMask = frameAnalyzer->getCurrentFGMask();
    Mat& frameResized = frameAnalyzer->getCurrentFrameResized();
    Mat& frameDrawn = frameAnalyzer->getCurrentFrameDrawn();
    Mat& histoX = frameAnalyzer->getHistoX();
    Mat& histoY = frameAnalyzer->getHistoY();
    Mat& BB = frameAnalyzer->getBB();

    QPixmap pixFrame = cvMatToQPixmap(frame);
    QPixmap pixFGMask = cvMatToQPixmap(fgMask);
    QPixmap pixFrameResized = cvMatToQPixmap(frameResized);
    QPixmap pixFrameDrawn = cvMatToQPixmap(frameDrawn);
    QPixmap pixHistoX = cvMatToQPixmap(histoX);
    QPixmap pixHistoY = cvMatToQPixmap(histoY);
    QPixmap pixBB = cvMatToQPixmap(BB);

    if(pixFrame.isNull())
        ui->labelFrame->setText("Immagine NULL");
    else
        ui->labelFrame->setPixmap(pixFrame.scaled(ui->labelFrame->size(),Qt::IgnoreAspectRatio));

    if(pixFGMask.isNull())
        ui->labelBS->setText("Immagine NULL");
    else
        ui->labelBS->setPixmap(pixFGMask.scaled(ui->labelBS->size(),Qt::IgnoreAspectRatio));

    if(pixFrameResized.isNull())
        ui->labelFrameResized->setText("Immagine NULL");
    else
        ui->labelFrameResized->setPixmap(pixFrameResized.scaled(ui->labelFrameResized->size(),Qt::KeepAspectRatio));

    if(pixBB.isNull())
        ui->labelBB->setText("Immagine NULL");
    else
        ui->labelBB->setPixmap(pixBB.scaled(ui->labelBB->size(),Qt::KeepAspectRatio));

    if(pixFrameDrawn.isNull())
        ui->labelPD->setText("Immagine NULL");
    else
        ui->labelPD->setPixmap(pixFrameDrawn.scaled(ui->labelPD->size(),Qt::IgnoreAspectRatio));

    if(pixHistoX.isNull())
        ui->labelHistoX->setText("Immagine NULL");
    else
        ui->labelHistoX->setPixmap(pixHistoX.scaled(ui->labelHistoX->size(),Qt::IgnoreAspectRatio));

    if(pixHistoY.isNull())
        ui->labelHistoY->setText("Immagine NULL");
    else
        ui->labelHistoY->setPixmap(pixHistoY.scaled(ui->labelHistoY->size(),Qt::IgnoreAspectRatio));

}

void VAMainWindow::showCredits()
{
    QMessageBox::about(this,
                       "About VA Project...",
                       "<h1>VA Action Recognition Project</h1> \
                       \
                       <p>Computer vision action recognition project by:</p> \
                       \
                       <ul> \
                           <li>Corbelli Andrea</li> \
                           <li>Palazzi Andrea</li> \
                           <li>Borghi Guido</li> \
                       </ul> \
                       \
                       <p>Anno Accademico 2013/2014</p>");
}

VAMainWindow::~VAMainWindow()
{
    delete ui;
}
