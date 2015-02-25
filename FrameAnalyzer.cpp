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

#include "FrameAnalyzer.h"
#include "dirent.h"
#include "utils.h"

using namespace std;
using namespace cv;

FrameAnalyzer::FrameAnalyzer(string videoFilename, int mog)
    : MOG_LEARNING_RATE(0.05f), STD_SIZE(Size(640,480)), RED(Scalar(0,0,255)), GREEN(Scalar(0,255,0)), BLUE(Scalar(255,0,0)),
	filename(videoFilename), mogType(mog) {

		// inizializzazione variabili
		predictionVect = Point2d(0, 0);

		initial = true;

		leftX = 0;
		rightX = 0;
		xOffset = 0;

		avgBsTime = 0;
		avgPdTime = 0;

		// Inizializzazione utile nel caso non trovi contorni
		frameResized = Mat3b(STD_SIZE.height, 250);

		// crea le finestre dell'interfaccia
//		namedWindow("Frame");
//		namedWindow("FG Mask MOG");
//		namedWindow("Background Subtraction and People Detector");

		// impostazione del background suppressor
		switch (mogType){
		case 0:
			pMOG = new BackgroundSubtractorMOG(); break; //MOG approach
		case 1:
			pMOG = new BackgroundSubtractorMOG2(); break; //MOG2 approach
		}

		// imposto il pepole detector
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

		// inizializzo il background
		bgName = getBgName2(filename);
		cout << "Background selezionato: " << bgName << endl;

		VideoCapture bgCapture(bgName);
		if(!bgCapture.isOpened()){
			// errore nell'aprire il file di background
			cerr << "Impossibile aprire il file di background: " << bgName << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
		else {
			// leggo il primo frame dal file di background e lo metto in frameBg (resizato)
			bgCapture.read(frameBg);
			resize(frameBg, frameBg, STD_SIZE);
			//Inizializzo frame di background
			frameInit = frameBg.clone();
		}

		// crea l'oggetto capture
		capture = VideoCapture(filename); // o 0 per webcam!
		if(!capture.isOpened()){
			// errore nell'aprire il file in input
			cerr << "Impossibile aprire il file video: " << filename << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}

}

int FrameAnalyzer::getFrameCount(){
	if(capture.isOpened()){
		return capture.get(CV_CAP_PROP_FRAME_COUNT);
	}
	else return -1;
}

int FrameAnalyzer::getCurrentFramePos(){
	if(capture.isOpened()){
		return capture.get(CV_CAP_PROP_POS_FRAMES);
	}
	else return -1;
}

const VideoCapture& FrameAnalyzer::getCapture(){
	return capture;
}

double FrameAnalyzer::getFrameRate(){
    return capture.get(CV_CAP_PROP_FPS);
}

void FrameAnalyzer::release(){
	//delete capture object
	capture.release();
}

bool FrameAnalyzer::isOpened(){
    return capture.isOpened();
}

Mat& FrameAnalyzer::getCurrentFrame(){
    return frame;
}

Mat& FrameAnalyzer::getCurrentFGMask(){
    return fgMaskMOG;
}

Mat& FrameAnalyzer::getCurrentFrameResized(){
    return frameResized;
}

Mat& FrameAnalyzer::getCurrentFrameDrawn(){
    return frameDrawn;
}

Mat& FrameAnalyzer::getHistoX(){
    return histoX;
}

Mat& FrameAnalyzer::getHistoY(){
    return histoY;
}

// Ritorna true se è andato tutto bene, false se non è riuscita a leggere un frame (cioè il video è finito)
bool FrameAnalyzer::processFrame() {

	//read the current frame
	if(!capture.read(frame)) {
		cerr << "Video terminato." << endl;
		return false; //Altrimenti esce di botto
	}

	// Resize dei frame in input alla dimensione standard
	resize(frame, frame, STD_SIZE);

	//Per la webcam messa male di mak
	//flip(frame, frame, -1);

	//Copio il frame per ottenere quello su cui disegnare i rettangoli
	frameDrawn = frame.clone();

	// BACKGROUND SUBTRACTION --------------------------------------------

	double s = (double)getTickCount();

	if(initial){
		pMOG->operator()(frameInit, fgMaskMOG, MOG_LEARNING_RATE);
		initial = false;
	}
	else
		pMOG->operator()(frame, fgMaskMOG, MOG_LEARNING_RATE);

	s = (double)getTickCount() - s;
	avgBsTime += s*1000./cv::getTickFrequency();

	// FILTERING e MORFOLOGIA SU fgMaskMOG per ottenere una silhouette migliore 
	//dilate(fgMaskMOG, fgMaskMOG, Mat(), Point(-1, -1), 2, 1, 1);
	// Applica chiusura morfologica per migliorare il risultato della sogliatura
	medianBlur(fgMaskMOG, fgMaskMOG, 5);
	/*int morph_size = 3;
	Mat element = getStructuringElement( MORPH_CROSS, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
	morphologyEx( fgMaskMOG, fgMaskMOG, MORPH_CLOSE, element );*/

	// disegna una bounding box BLU attorno alle zone di foreground
	std::vector<std::vector<cv::Point> > contours;
	std::vector<std::vector<cv::Point> > inBoundContours;
	std::vector<cv::Vec4i> hierarchy;
	// passo un clone di fgMaskMOG per fare in modo che non la modifichi
	findContours( fgMaskMOG.clone(), contours, hierarchy, RETR_CCOMP, cv::CHAIN_APPROX_TC89_KCOS);

	// ---------------------------------------------------------------------------------------------
	// Trova il centro di massa di ogni contorno (trovato dopo il filtering)
	// Calcola poi il centroide della nuvola di punti per stabilire il punto centrale del movimento
	// Se tolti i commenti, in giallo i centri di massa dei contorni. In rosso il centroide complessivo.
	vector<int> cmContoursX, cmContoursY;
	int centroidX, centroidY;
	if(contours.size() > 0) {
		for ( size_t i=0; i<contours.size(); ++i ){
			Moments mo = moments(contours[i], true);
			Point2d result = Point2d(mo.m10/mo.m00 , mo.m01/mo.m00);
			// Controlla che il centro di massa del contorno sia nel range dell'immagine
			if( IsInBounds(int(result.x), 0, STD_SIZE.width) && IsInBounds(int(result.y), 80, (STD_SIZE.height))){
				cmContoursX.push_back(result.x);
				cmContoursY.push_back(result.y);
				inBoundContours.push_back(contours[i]);
				// [DEBUG] Disegna la posizione del centro di massa e del boundingRect del contorno
				rectangle(frameDrawn, boundingRect(contours[i]), Scalar(255,0,0), 1);
				circle(frameDrawn, result, 3, Scalar(0,255,255), 3);
			}
		}
		cout << "ALL CONTOURS: " << contours.size() << "\tINBOUND: " << inBoundContours.size() << endl;

		// Trova il contorno di area maggiore per poter dare un maggior peso alla sua posizione
		int largestContourIndex = -1;
		int largestArea = -1;
        for (size_t i=0; i<inBoundContours.size(); ++i) {
			if(contourArea(inBoundContours[i]) > largestArea) {
				largestArea = contourArea(inBoundContours[i]);
				largestContourIndex = i;
			}
		}
		// [DEBUG] Disegna il boundingRect del contorno di area maggiore
		rectangle(frameDrawn, boundingRect(inBoundContours[largestContourIndex]), BLUE, 3);


		// CALCOLA LA POSIZIONE DEL CENTROIDE
		// Le coordinate di ogni centro di massa sono pesate con l'area del rispettivo rettangolo
		double totAreas = 0.0;
		centroidX = 0; centroidY = 0;
		for_each(inBoundContours.begin(), inBoundContours.end(),
			[&totAreas] (vector<Point> inBoundContour) {totAreas += contourArea(inBoundContour);});
		for(size_t i=0; i<cmContoursX.size(); ++i)
			centroidX += cmContoursX[i] * contourArea(inBoundContours[i]);
		centroidX /= totAreas;
		for(size_t i=0; i<cmContoursY.size(); ++i)
			centroidY += cmContoursY[i] * contourArea(inBoundContours[i]);
		centroidY /= totAreas;
		circle(frameDrawn, Point2d(centroidX, centroidY), 7, RED, 3);
		
		

		// Dimensioni della ROI (questa parte si può collassare nella successiva secondo me)
		leftX = centroidX - 125;
		if(leftX < 0)
			leftX = 0;
		rightX = centroidX + 125;
		if(rightX > STD_SIZE.width)
			rightX = STD_SIZE.width;

		// Se il centroide è all'interno del frame, ritaglia la ROI
		if (IsInBounds(centroidX, 0, STD_SIZE.width) && IsInBounds(centroidY, 0, STD_SIZE.height)) {
			Rect newRect = Rect(leftX, 0, abs(rightX-leftX), STD_SIZE.height);
			frameResized = Mat3b(STD_SIZE.height, 250);
			frameResized = frame(newRect);


		}
	}
	// ---------------------------------------------------------------------------------------------


	// HOG PEOPLE DETECTION ------------------------------------------------------------------------
	// people detection solo sui frame pari
	if( ((int)capture.get(CV_CAP_PROP_POS_FRAMES)) % 2 == 0){

		vector<Rect> found, found_filtered;
		double t = (double)getTickCount();
		// run the detector with default parameters. to get a higher hit-rate
		// (and more false alarms, respectively), decrease the hitThreshold and
		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
		hog.detectMultiScale(frameResized, found, 0, Size(8,8), Size(0,0), 1.05, 2);
		t = (double)getTickCount() - t; 
		//cout << "detection time = " << t*1000./cv::getTickFrequency() << " - found objects: " << found.size() << endl;
		avgPdTime += t*1000./cv::getTickFrequency();

		size_t i, j;
		for( i = 0; i < found.size(); i++ ) {
			Rect r = found[i];
			for( j = 0; j < found.size(); j++ )
				if( j != i && (r & found[j]) == r)
					break;
			if( j == found.size() )
				found_filtered.push_back(r);
		}

		// se trova più di una persona scorre tutti i risulati e tiene il rettangolo il cui centro
		// è più vicino al centroide di movimento (quello che più probabilmente contiene la persona reale),
		// in questo modo si elimina la possibilità di avere due persone detected in scena.
		if(found_filtered.size() > 0){

			xOffset = leftX;

			Point2d movementCentroid(centroidX, centroidY);

			tmpClosestRect = found_filtered[0];
			Point2d closestRectCenter(tmpClosestRect.x + tmpClosestRect.width/2 , tmpClosestRect.y + tmpClosestRect.height/2 );
			double closestDistance = norm(closestRectCenter - movementCentroid);

			for(i = 1; i < found_filtered.size(); i++){
				Rect currRect = found_filtered[i];
				Point2d currRectCenter(currRect.x + currRect.width/2 , currRect.y + currRect.height/2 );
				double currDistance = norm(currRectCenter - movementCentroid);

				if(currDistance < closestDistance){
					closestDistance = currDistance;
					tmpClosestRect = currRect;
				}
			}

			// se ho trovato il rettangolo più vicino aggiorno il predictionVect

			predictionVect.x = sign(tmpClosestRect.x - closestRect.x);
			predictionVect.y = sign(tmpClosestRect.y - closestRect.y);

			closestRect = tmpClosestRect;

			// Disegna il rettangolo sul frame
			drawRectOnFrameDrawn(closestRect, frameDrawn, GREEN, 4, xOffset);

		}
		else {
			// frame pari ma non è stata trovata la persona
			if((predictionVect.x != 0) || (predictionVect.y!=0)) {
				closestRect.x += predictionVect.x;
				closestRect.y += predictionVect.y;
				drawRectOnFrameDrawn(closestRect, frameDrawn, GREEN, 4, xOffset);

			}
		}
	}
	else {
		// frame dispari
		if((predictionVect.x != 0) || (predictionVect.y!=0)) {
			closestRect.x += predictionVect.x;
			closestRect.y += predictionVect.y;
			// Disegna il rettangolo sul frame
			drawRectOnFrameDrawn(closestRect, frameDrawn, GREEN, 4, xOffset);
		}
	}


	// -------------------- CALCOLO DELL'ISTOGRAMMA--------------------------------
	int numberBins = 10;
	vector<double> featureVector(numberBins, 0);

    bool createThe2HistogramImages = true;
	vector<Mat> histogramImages(2);

	if(closestRect.area()>0){
		computeFeatureVector ( fgMaskMOG, closestRect, numberBins, featureVector, histogramImages, createThe2HistogramImages );

        histoX = histogramImages[0];
        histoY = histogramImages[1];

//		if(createThe2HistogramImages) {
//            for(size_t i=0; i<histogramImages.size(); ++i)
//				imshow("Histogram "+to_string(i+1), histogramImages[i]);
//		}
	}


	//show the current frame and the fg masks
//	imshow("Frame", frame);
//	imshow("frameResized", frameResized);
//	imshow("FG Mask MOG - Silhouette", fgMaskMOG);
//	imshow("Background Subtraction and People Detector", frameDrawn);


	return true;
}

void FrameAnalyzer::drawRectOnFrameDrawn( Rect closestRect, Mat frameDrawn, cv::Scalar color, int thickness, int xOffset) {

	closestRect.x += cvRound(closestRect.width*0.1) + xOffset;
	closestRect.width = cvRound(closestRect.width*0.8);
	closestRect.y += cvRound(closestRect.height*0.07);
	closestRect.height = cvRound(closestRect.height*0.8);
	rectangle(frameDrawn, closestRect.tl(), closestRect.br(), color, thickness);

}

string FrameAnalyzer::getBgName(char* filename){

	stringstream ss;
	ss << "backgrounds/";

	string strFname(filename);
	strFname = strFname.substr(strFname.find_first_of("/")+1);

	if(strcmp(strFname.data(), "daria_bend.avi") == 0 || strcmp(strFname.data(), "daria_jack.avi") == 0 ||strcmp(strFname.data(), "daria_wave1.avi") == 0 ||strcmp(strFname.data(), "daria_wave2.avi") == 0){
		ss << "bg_015.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "denis_bend.avi") == 0 || strcmp(strFname.data(), "daria_jack.avi") == 0 || strcmp(strFname.data(), "denis_pjump.avi") == 0 || strcmp(strFname.data(), "denis_wave1.avi") == 0 || strcmp(strFname.data(), "denis_wave2.avi") == 0 ){
		ss << "bg_026.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "eli_bend.avi") == 0 || strcmp(strFname.data(), "eli_pjump.avi") == 0 ||strcmp(strFname.data(), "eli_wave1.avi") == 0 ||strcmp(strFname.data(), "eli_wave2.avi") == 0){
		ss << "bg_062.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "ido_bend.avi") == 0 || strcmp(strFname.data(), "ido_jack.avi") == 0 || strcmp(strFname.data(), "ido_pjump.avi") == 0 || strcmp(strFname.data(), "ido_wave1.avi") == 0 || strcmp(strFname.data(), "ido_wave2.avi") == 0){
		ss << "bg_062.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "ira_bend.avi") == 0 || strcmp(strFname.data(), "ira_jack.avi") == 0 || strcmp(strFname.data(), "ira_pjump.avi") == 0 || strcmp(strFname.data(), "ira_wave1.avi") == 0 || strcmp(strFname.data(), "ira_wave2.avi") == 0){
		ss << "bg_007.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "lena_bend.avi") == 0 || strcmp(strFname.data(), "lena_pjump.avi") == 0 || strcmp(strFname.data(), "lena_wave1.avi") == 0 || strcmp(strFname.data(), "lena_wave2.avi") == 0 || strcmp(strFname.data(), "daria_pjump.avi") == 0){
		ss << "bg_038.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "lyova_bend.avi") == 0 || strcmp(strFname.data(), "lyova_jack.avi") == 0 || strcmp(strFname.data(), "lyova_pjump.avi") == 0 || strcmp(strFname.data(), "lyova_wave1.avi") == 0 || strcmp(strFname.data(), "lyova_wave2.avi") == 0){
		ss << "bg_046.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "moshe_bend.avi") == 0 || strcmp(strFname.data(), "moshe_pjump.avi") == 0 ||strcmp(strFname.data(), "moshe_wave1.avi") == 0 ||strcmp(strFname.data(), "moshe_wave2.avi") == 0 ||strcmp(strFname.data(), "moshe_walk.avi") == 0){
		ss << "bg_070.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "shahar_walk.avi") == 0 || strcmp(strFname.data(), "shahar_pjump.avi") == 0 ||strcmp(strFname.data(), "shahar_wave1.avi") == 0 ||strcmp(strFname.data(), "shahar_wave2.avi") == 0){
		ss << "bg_079.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "moshe_jack.avi") == 0 ){
		ss << "moshe_bg_run.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "shahar_jack.avi") == 0 || strcmp(strFname.data(), "eli_jack.avi") == 0){
		ss << "shahar_bg_run.avi";
		return ss.str();
	}
	else if(strcmp(strFname.data(), "lena_jack.avi") == 0 ){
		ss << "lena_bg_jack.avi";
		return ss.str();
	}
	else { // se non ne trova nessuno ritorna il video originale
		ss.clear();
		cout << "Filename non trovato!" << endl;
		ss << "dataset/" << strFname;
		return ss.str();
	}
}

string FrameAnalyzer::getBgName2(string filename){
	string path = "backgrounds/";
	vector<string> name_bg;

	DIR* dir;
	dir = opendir(path.c_str());

	//Carico il vettore con i nomi dei file presenti nella cartella backgrounds
	if(dir){
		dirent* file;
		while((file = readdir(dir))){
			string tmp = file->d_name;
			if( (tmp.compare(".") != 0) && (tmp.compare("..") != 0) && (tmp.compare("Thumbs.db") != 0)){
				name_bg.push_back(tmp);
			}
		}
	}
	else{
		cout << "Percorso cartella background errato!" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	//Carico il primo frame del video dato in input
    VideoCapture video(filename);
	if(!video.isOpened()){
		cout << "Impossibile aprire per inizializzare il background il video: " << filename << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	Mat3b frame;
	video.read(frame);

	//Cerco a quale background assomiglia di più
	int min = INT_MAX;
	string best; 

	//Per ogni video di background
    for(size_t i=0; i<name_bg.size(); ++i){

		//Apro il video di background
		string prefix = "backgrounds/";
		prefix.append(name_bg[i]);
		VideoCapture vid_bg(prefix); 
		if(!video.isOpened()){
			cout << "Impossibile aprire il video di background: " << filename << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
		else{

			//Carico il primo fotogramma
			Mat3b frame_bg;
			vid_bg.read(frame_bg);

			//Calcolo la distanza
			int score = 0;
			for(int c=0; c<frame.cols;++c){
				for(int r=0; r<frame.rows; ++r){
					score +=  abs(((int)frame(r,c)[0]) - ((int)frame_bg(r,c)[0]));
					score +=  abs(((int)frame(r,c)[1]) - ((int)frame_bg(r,c)[1]));
					score +=  abs(((int)frame(r,c)[2]) - ((int)frame_bg(r,c)[2]));
				}
			}

			//Verifico se è la migliore distanza
			if(score<min){
				min = score;
				best = name_bg[i];
			}
		}
	}

	//Costruisco il path corretto
	path.append(best);

	return path;

}

FrameAnalyzer::~FrameAnalyzer(void){}
