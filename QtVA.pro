#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T09:50:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtVA
TEMPLATE = app

win32 {

    INCLUDEPATH += "C:\\opencv\\build\\include" \
                   "C:\\opencv\\build\\include\\opencv" \
                   "C:\\opencv\\build\\include\\opencv2"

    CONFIG(debug, debug | release) {

        LIBS += -L"C:\\opencv\\build\\x86\\vc12\\lib" \
            -lopencv_core248d \
            -lopencv_imgproc248d \
            -lopencv_highgui248d \
            -lopencv_ml248d \
            -lopencv_video248d \
            -lopencv_features2d248d \
            -lopencv_calib3d248d \
            -lopencv_objdetect248d \
            -lopencv_contrib248d \
            -lopencv_legacy248d \
            -lopencv_flann248d \
            -lopencv_nonfree248d
    }

    CONFIG(release, debug | release) {
        LIBS += -L"C:\\opencv\\build\\x86\\vc12\\lib" \
            -lopencv_core248 \
            -lopencv_imgproc248 \
            -lopencv_highgui248 \
            -lopencv_ml248 \
            -lopencv_video248 \
            -lopencv_features2d248 \
            -lopencv_calib3d248 \
            -lopencv_objdetect248 \
            -lopencv_contrib248 \
            -lopencv_legacy248 \
            -lopencv_flann248 \
            -lopencv_nonfree248
    }
}

SOURCES += main.cpp\
        vamainwindow.cpp \
        FrameAnalyzer.cpp

HEADERS  += vamainwindow.h \
    dirent.h \
    FrameAnalyzer.h \
    utils.h \
    conversionutility.h

FORMS    += vamainwindow.ui
