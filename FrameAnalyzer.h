#pragma once

#include <opencv2/video/background_segm.hpp>
#include <opencv2/opencv.hpp>
//C
#include <stdio.h>
#include <stdlib.h>
//C++
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <cstdint>
#include <cstring>
// Qt
#include <qimage.h>
#include <qpixmap.h>

template <typename T>  bool IsInBounds(const T& value, const T& low, const T& high) {
	return !(value < low) && !(high < value);
}

template <typename T> int sign (T val) {
	return (T(0)<val) - (val<T(0));
}

class FrameAnalyzer {

private:

	// ------------------ COSTANTI -------------------------------
	const cv::Size STD_SIZE; // Risoluzione a cui viene resizato qualsiasi frame
	const float MOG_LEARNING_RATE; // Learning rate della BG subtraction (sia per MOG che MOG2)
	const cv::Scalar RED;
	const cv::Scalar GREEN;
	const cv::Scalar BLUE;

	// ------------------ VARIABILI -------------------------------
    std::string filename;
	std::string bgName;

	int mogType;

	cv::Mat frame; //current frame
	cv::Mat frameDrawn; //frame su cui disegnare i rettangoli
	cv::Mat frameBg; // frame di background
	cv::Mat frameInit; //frame di inizializzazione background
    cv::Mat histoX;
    cv::Mat histoY;

	cv::Mat fgMaskMOG; //fg mask generated by MOG method

	cv::Ptr<cv::BackgroundSubtractor> pMOG; //MOG Background subtractor

	cv::HOGDescriptor hog; // Hog detector

	cv::VideoCapture capture; // stream video

	cv::Rect closestRect;
	cv::Rect tmpClosestRect;

	// vettore di predizione
	cv::Point2d predictionVect;

	//Inizializzazione background
	bool initial;

	// Variabili utilizzate nell'estrazione dell'area di interesse
	int leftX;
	int rightX;
	int xOffset;

	// Inizializzazione utile nel caso non trovi contorni
	cv::Mat3b frameResized;

    // ------------------ METODI -------------------------------

	void drawRectOnFrameDrawn( cv::Rect closestRect, cv::Mat frameDrawn, cv::Scalar color, int thickness, int xOffset);
	std::string getBgName(char* filename);
    std::string getBgName2(std::string filename);


public:
	int keyboard;
	float avgBsTime;
	float avgPdTime;

	// costruttore con parametri, il primo � il nome del file da aprire,
	// il secondo � il tipo di background suppression (0=MOG, 1=MOG2),
	// di default sono entrambi a zero, cio�, lettura da webcam e MOG.
    FrameAnalyzer(std::string filename=0, int mog=0);

	// Processa un singolo frame, restituisce true se � andato tutto bene, false se non � riuscita
	// a leggere un frame dal videoCapture, cio� se il video � finito
	bool processFrame();

	// ritorna il numero totale di frame, -1 se qualcosa � andato storto (es: video non aperto)
	int getFrameCount();

	// ritorna il frame corrente, -1 se qualcosa � andato storto (video finito o non aperto)
	int getCurrentFramePos();

	// chiama release sull'oggetto capture, da fare come ultimissima cosa
	void release();

	// ritorna l'oggetto VideoCapture come const, se per caso dovesse servire
	const cv::VideoCapture & getCapture();

    bool isOpened();

    double getFrameRate();

    cv::Mat & getCurrentFrame();
    cv::Mat & getCurrentFGMask();
    cv::Mat & getCurrentFrameResized();
    cv::Mat & getCurrentFrameDrawn();
    cv::Mat & getHistoX();
    cv::Mat & getHistoY();

	// Distruttore
	~FrameAnalyzer(void);


};

