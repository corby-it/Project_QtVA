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
#include <cstdlib>

#include "FrameAnalyzer.h"
#include "dirent.h"
#include "utils.h"
#include "config.h"

using namespace std;
using namespace cv;
using namespace gmmstd;

FrameAnalyzer::FrameAnalyzer(string videoFilename, std::string C, int mog)
	: MOG_LEARNING_RATE(learningRate), STD_SIZE(Size(640,480)), RED(Scalar(0,0,255)), GREEN(Scalar(0,255,0)), BLUE(Scalar(255,0,0)),
	filename(videoFilename), mogType(mog), category(C){

		// inizializzazione variabili
		predictionVect = Point2d(0, 0);

		initial = true;

		leftX = 0;
		rightX = 0;
		xOffset = 0;

		avgBsTime = 0;
		avgPdTime = 0;

        lk_thresh = 0;

		// Inizializzazione utile nel caso non trovi contorni
		frameResized = Mat3b(STD_SIZE.height, 250);

		// crea le finestre dell'interfaccia
		namedWindow("Frame");
		namedWindow("FG Mask MOG");
		namedWindow("Background Subtraction and People Detector");

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
		bgName = getBgName(filename);
		cout << "Background selezionato: " << bgName << endl;

		VideoCapture bgCapture(bgName);
		if(!bgCapture.isOpened()){
			if(bgName.compare("nullo")==0){
				CvCapture* capture = 0;
				capture = cvCaptureFromCAM(0);
				IplImage* pic = cvQueryFrame( capture );
				frameInit = pic;
			}
			else{
				// errore nell'aprire il file di background
				cerr << "Impossibile aprire il file di background: " << bgName << endl;
				// TODO magari si potrebbe fare qualcosa di più user-friendly piuttosto che chiudere tutto il programma...
				system("pause");
				exit(EXIT_FAILURE);
			}
		}
		else {
			// leggo il primo frame dal file di background e lo metto in frameBg (resizato)
			bgCapture.read(frameBg);
			resize(frameBg, frameBg, STD_SIZE);
			//Inizializzo frame di background
			frameInit = frameBg.clone();
		}

		// crea l'oggetto capture
		string nome = filename;
		if(nome.compare("0")==0)
			capture = VideoCapture(0); // o 0 per webcam!
		else
			capture = VideoCapture(filename);

		if(!capture.isOpened()){
			// errore nell'aprire il file in input
			cerr << "Impossibile aprire il file video: " << filename << endl;
			// TODO magari si potrebbe fare qualcosa di più user-friendly piuttosto che chiudere tutto il programma...
			system("pause");
			exit(EXIT_FAILURE);
		}

		//Carico gli HMM per il testing
		cout << "Carico HMM per il testing..." << endl;
		//Cartella con hmm trainati
		string path = "hmm/";
		DIR* d;
		d = opendir(path.c_str());
		if(!d)
			cout << "Errore apertura cartella HMM trainati!" << endl;
		dirent* f;
		//Per tutti gli hmm presenti
		while((f = readdir(d))){
			string tmp;
			tmp = f->d_name;
			//Controllo che sia un nome di un file presente
			if(tmp.compare(".") != 0 && tmp.compare("..") != 0){
                CHMM_GMM* hmm = new CHMM_GMM(1, 1, 1);
                string pre = "hmm/"+tmp;
                char * nome_hmm = new char [pre.length()+1];
                strcpy_s(nome_hmm, pre.length()+1, pre.c_str());
                //Carico hmm e controllo esito
                if(!(hmm->LoadFromFile(nome_hmm))){
                    cout << "Errore caricamento HMM: " << nome_hmm << endl;
                }
                //Inserisco hmm nel vettore
                vhmm.push_back(*hmm);
                //Memorizzo il tipo di classe dell'hmm
                class_action.push_back(tmp.substr(tmp.find_first_of("_")+1, (tmp.size())-tmp.find_first_of("_")));
                //Distruggo l'hmm per non avere problemi di memory allocation
                hmm->~CHMM_GMM();
			}
		}
		cout << "Sono stati caricati " << vhmm.size() << " HMM" << endl;

		// inizializzo il contatore dei test effettuati
		testCount = 0;
		ok = 0;
		tot_classified = 0;

		//Creo vettore con etichette per prestazioni
		for(int i=0;i<84;++i)
			performance.push_back("bend"); 
		for(int i=0;i<89;++i) 
			performance.push_back("jack");
		for(int i=0;i<67;++i) 
			performance.push_back("jump");
		for(int i=0;i<62;++i) 
			performance.push_back("pjump");
		for(int i=0;i<42;++i) 
			performance.push_back("run");
		for(int i=0;i<53;++i) 
			performance.push_back("side");
		for(int i=0;i<57;++i) 
			performance.push_back("skip");
		for(int i=0;i<84;++i) 
			performance.push_back("walk");
		for(int i=0;i<82;++i) 
			performance.push_back("wave1");
		for(int i=0;i<81;++i) 
			performance.push_back("wave2");

}

int FrameAnalyzer::getFrameCount(){
	if(capture.isOpened()){
		return (int)capture.get(CV_CAP_PROP_FRAME_COUNT);
	}
	else return -1;
}

int FrameAnalyzer::getCurrentFramePos(){
	if(capture.isOpened()){
		return (int)capture.get(CV_CAP_PROP_POS_FRAMES);
	}
	else return -1;
}

const VideoCapture& FrameAnalyzer::getCapture(){
	return capture;
}

void FrameAnalyzer::release(){
	//delete capture object
	capture.release();
}

double FrameAnalyzer::getFrameRate(){
    return capture.get(CV_CAP_PROP_FPS);
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

	//cerr << endl << "FILE: " << filename << endl;
	//cerr << "CURRENT FRAME: " << getCurrentFramePos() << " / " << getFrameCount() << "\t";

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
	int morph_size = 3;
	Mat element = getStructuringElement( MORPH_CROSS, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
	morphologyEx( fgMaskMOG, fgMaskMOG, MORPH_CLOSE, element );
	/*medianBlur(fgMaskMOG, fgMaskMOG, 3);*/
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
		//cout << "ALL CONTOURS: " << contours.size() << " INBOUND: " << inBoundContours.size() << endl;

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
		if(largestContourIndex >= 0)
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
		leftX = centroidX - 130;
		if(leftX < 0)
			leftX = 0;
		rightX = centroidX + 130;
		if(rightX > STD_SIZE.width)
			rightX = STD_SIZE.width;

		// Se il centroide è all'interno del frame, ritaglia la ROI
		if (IsInBounds(centroidX, 0, STD_SIZE.width) && IsInBounds(centroidY, 0, STD_SIZE.height)) {
			Rect newRect = Rect(leftX, 0, abs(rightX-leftX), STD_SIZE.height);
			frameResized = Mat3b(STD_SIZE.height, 260);
			frameResized = frame(newRect);


		}
	}
	// ---------------------------------------------------------------------------------------------


	// HOG PEOPLE DETECTION ------------------------------------------------------------------------
	// people detection solo sui frame pari
	if(((int)capture.get(CV_CAP_PROP_POS_FRAMES)) % 4 == 0)	{

		vector<Rect> found, found_filtered;
		double t = (double)getTickCount();
		// run the detector with default parameters. to get a higher hit-rate
		// (and more false alarms, respectively), decrease the hitThreshold and
		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
		hog.detectMultiScale(frameResized, found, 0, Size(8,8), Size(0,0), 1.05, 1);
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
		//cout << "FOUND: " << found.size() << "FOUND FILTERED " << found_filtered.size() << endl;
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

	// Creo un rettangolo che contiene la silhouette del soggetto, su cui sono calcolate le features
	//Trovo sulla mask i pixel di foreground (diversi da 0)
	Mat nonZeroCoordinates;
	findNonZero(fgMaskMOG,nonZeroCoordinates);

	//Controllo che ci siano effettivamente almeno un po' di punti di foreground (soglia manuale magari da migliorare)
	if(nonZeroCoordinates.rows>=4){
		Rect bb = boundingRect(nonZeroCoordinates);		
		//Controllo che il bb non abbia preso troppo frame (a causa del background non ancora riconosciuto)
		if(bb.x != 0 && bb.y != 0){
			Mat boundingBox = fgMaskMOG(bb).clone();
			rectangle(frameDrawn,bb,Scalar(255,255,255),1);

			// -------------------- CALCOLO DELL'ISTOGRAMMA--------------------------------
			int numberBins = 20; // numero di bin del feature vector (sarà costituito concatenando due vettori da 10)
			vector<double> featureVector(numberBins, 0);

			vector<Mat> histogramImages(2);
			if(getCurrentFramePos()%1 == 0) {
				//fgMaskMOG -> versione vecchia, boundingBox -> versione nuova
				computeFeatureVector(boundingBox, numberBins, featureVector, histogramImages, true);
                histoX = histogramImages[0];
                histoY = histogramImages[1];

				if(!test){ //Se non è un test calcolo i file di train
					string fName(filename);
					fName = fName.substr(fName.find_last_of("/\\")+1);
					fName.replace(fName.find("."),fName.length(), ".txt"); 
					writeFeatureVectorToFile(category, fName, featureVector);
					//computeFeatureVector ( fgMaskMOG, closestRect, numberBins, featureVector, histogramImages, createThe2HistogramImages );
				}
				else{
					double maxLk = DBL_MIN;
					string maxClass = "";

					if (vHMMTester.size() < windowNum && (testCount % windowsStep)==0){
                        vHMMTester.push_back(HMMTester(vhmm, class_action, rand()%100, filename, lk_thresh));
					}

					for (size_t i=0; i<vHMMTester.size(); ++i){
						string res = vHMMTester[i].testingHMM(featureVector);
						//cout << "Confronto: " << res << " e " << performance[getCurrentFramePos()] << endl;
						if(res.compare("nullo") == 0){
						} 
						//Confronto etichetta data di mezza finestra prima con classificazione data
						else{//se ho almeno tot frame
							//res potrebbe terminare con un numero per via dei nomi del dataset, elimino questa possibilità
							char c = (char)res[res.size()-1];
							if( (c>48 && c<57) && res.compare("wave1") != 0 && res.compare("wave2") != 0){
								res = res.substr(0, res.size()-1);
								cout << res << endl;
							}
							if(res.compare(performance[getCurrentFramePos()-(windowSize/2)]) == 0){
								ok++;
								tot_classified++;
								if(tot_classified!=0 /*&& (getCurrentFramePos() == getFrameCount())*/)
									cout << "CORRETTO:\t" << ok << "/" << tot_classified << "\t" << ((double)ok/(double)tot_classified)*100 << " %" << endl << endl;
								printLog("out_log.txt", res, performance[getCurrentFramePos()-(windowSize/2)]);
							}
							else if(res.compare(performance[getCurrentFramePos()-(windowSize/2)]) != 0){
								tot_classified++;
								cout << "ERRORE" << "\t" << ((double)ok/(double)tot_classified)*100 << " %" << endl << endl;
								printLog("out_log.txt", res, performance[getCurrentFramePos()-(windowSize/2)]);
							}
						}

						/*pair<double,string> c = vHMMTester[i].getClassification();
						if(c.first > maxLk){
						maxLk = c.first;
						maxClass = c.second;
						}*/

						if (vHMMTester[i].countFrame() == windowSize){
							vHMMTester.erase(vHMMTester.begin());
                            vHMMTester.push_back(HMMTester(vhmm, class_action, rand()%100, filename, lk_thresh));
						}

						//cout << "Classificatore " << i << " - LK: " <<  c.first << "\tClass: " << c.second << "\tID: " << vHMMTester[i]._id << "\tcon frame:" << vHMMTester[i].countFrame() << endl;
					}

					//cout << "\tCLASSIFICAZIONE: " << maxClass << " con likelihood: " << maxLk << endl << endl;
					//cout << getCurrentFramePos() << endl;
					testCount++;
					
				}


				// Disegna gli istogrammi
				for(size_t i=0; i<histogramImages.size(); ++i)
					imshow("Histogram "+to_string(i+1), histogramImages[i]);
			}


		}
	}

	//show the current frame and the fg masks
	imshow("Frame", frame);
	imshow("frameResized", frameResized);
	imshow("FG Mask MOG - Silhouette", fgMaskMOG);
	imshow("Background Subtraction and People Detector", frameDrawn);

	return true;
}

void FrameAnalyzer::printLog(string nome, string classified, string real){
	ofstream out_log(nome, fstream::out | fstream::app);

	int b, e;
	b = getCurrentFramePos()-(windowSize);
	e = getCurrentFramePos();

	for(int i=b;i<e;++i){
		out_log << performance[i].substr(0, 1);
	}
	out_log << "|CLASS|" << classified << "|REALE|" << real << endl << endl;
}

void FrameAnalyzer::drawRectOnFrameDrawn( Rect closestRect, Mat frameDrawn, cv::Scalar color, int thickness, int xOffset) {

	closestRect.x += cvRound(closestRect.width*0.1) + xOffset;
	closestRect.width = cvRound(closestRect.width*0.8);
	closestRect.y += cvRound(closestRect.height*0.07);
	closestRect.height = cvRound(closestRect.height*0.8);
	rectangle(frameDrawn, closestRect.tl(), closestRect.br(), color, thickness);

}

string FrameAnalyzer::getBgName(string filename){
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
		string file_name = filename;
		if(file_name.compare("0")==0){
			return "nullo";
		}
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

//void FrameAnalyzer::testingHMM(vector<double> featureVector){
//
//	//-----------------TESTING----------------------
//	//Fatto solo se c'è una bounding box valida (DA OTTIMIZZARE)
//
//	//Per ottenere likelihood massima
//	double max = DBL_MIN;
//	double max_other = DBL_MIN;
//	int best = 0;
//
//	//Accumulo le features frame per frame
//	vfeatures.push_back(featureVector);
//
//	//Per ogni HMM trovato nella cartella
//	for(int i=0;i<vhmm.size();++i){
//
//		//Ottengo matrice di transizione
//		Mat_<double> A;
//		A = vhmm[i].m_A; 
//
//		//Valuto l'HMM
//		typedef vector<vector<double>>::iterator iter_vf;
//		const iter_vf ivf_init = vfeatures.begin();
//		const iter_vf ivf_final = vfeatures.end();
//		//Calcolo la logLikelihood
//		//cout << "Calcolo la logLikelihood dell'HMM: " << tmp  << " basandomi su: " << vfeatures.size() << " frame" << endl;
//		//cout << "Calcolo lk con frame " << vfeatures.size() << endl;
//		double loglk = vhmm[i].LogLikelihood(ivf_init, ivf_final, &A);
//		//cout << tmp << "\t" << loglk << endl;
//
//		//Genero alcune stringhe utili
//		string file_name = filename;
//		file_name = file_name.substr(file_name.find_last_of("\\")+1, file_name.length()-file_name.find_last_of("\\")-5);
//
//		//Verifico se è massimo e se l'hmm non è lo stesso dell'azione
//		if((loglk>max && loglk==loglk) && (class_action[i].compare(file_name) != 0)){
//			max = loglk;
//			best = i;
//		}
//
//		string tipo = class_action[best].substr(class_action[best].find_first_of("_")+1, class_action[best].length()-class_action[best].find_first_of("_"));
//		string tipo_file = file_name.substr(file_name.find_first_of("_")+1, file_name.length()-file_name.find_first_of("_"));
//
//		//Trovo il valore massimo di un hmm di un altro tipo di azione
//		if((loglk>max_other && loglk==loglk) && (tipo.compare(tipo_file) != 0))
//			max_other = loglk;
//
//	}//fine while
//
//	cout << "CLASSIFICAZIONE: " << class_action[best].substr(class_action[best].find_first_of("_")+1, class_action[best].length()-class_action[best].find_first_of("_"));
//	cout << " SICURO AL: " << (max/max_other)*100 << "%" << endl;
//
//	//system("pause");
//}
