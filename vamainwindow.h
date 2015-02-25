#ifndef VAMAINWINDOW_H
#define VAMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QGroupBox>
#include <QRadioButton>
#include <QProgressBar>

#include <cstring>

#include "FrameAnalyzer.h"

namespace Ui {
class VAMainWindow;
}

class VAMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VAMainWindow(QWidget *parent = 0);
    ~VAMainWindow();


private slots:
    void onButtonStartProcessingClicked();
    void processStep();
    void openFile();
    void showCredits();

private:
    Ui::VAMainWindow *ui;

    QTimer *timer;
    FrameAnalyzer *frameAnalyzer;

    QLabel *progressLabel;
    QProgressBar *progressBar;

    std::string selectedFile;
};

#endif // VAMAINWINDOW_H
