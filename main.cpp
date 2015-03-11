#include "vamainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VAMainWindow w;
    // w.show();
    w.showFullScreen();

    return a.exec();
}
