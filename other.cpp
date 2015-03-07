//// PROCESSING DI UN FRAME ALLA VOLTA
//// DA AGGIUNGERE AL CONTROLLO PARAMETRI
//	else if(strcmp(argv[1], "-img") == 0) {
//		//input data coming from a sequence of images
//		processImages(argv[2]);
//	}
//
//	// DICHIARAZIONE
//	void processImages(char* firstFrameFilename);
//
//	// IMPLEMENTAZIONE
//	void processImages(char* fistFrameFilename) {
//		//read the first file of the sequence
//		frame = imread(fistFrameFilename);
//		if(!frame.data){
//			//error in opening the first image
//			cerr << "Unable to open first image frame: " << fistFrameFilename << endl;
//			exit(EXIT_FAILURE);
//		}
//		//current image filename
//		string fn(fistFrameFilename);
//		//read input data. ESC or 'q' for quitting
//		while( (char)keyboard != 'q' && (char)keyboard != 27 ){
//			//update the background model
//			//ALSO HERE!!!!
//			pMOG->operator()(frame, fgMaskMOG);
//			pMOG2->operator()(frame, fgMaskMOG2);
//			//get the frame number and write it on the current frame
//			size_t index = fn.find_last_of("/");
//			if(index == string::npos) {
//				index = fn.find_last_of("\\");
//			}
//			size_t index2 = fn.find_last_of(".");
//			string prefix = fn.substr(0,index+1);
//			string suffix = fn.substr(index2);
//			string frameNumberString = fn.substr(index+1, index2-index-1);
//			istringstream iss(frameNumberString);
//			int frameNumber = 0;
//			iss >> frameNumber;
//			rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
//				cv::Scalar(255,255,255), -1);
//			putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
//				FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
//			//show the current frame and the fg masks
//			imshow("Frame", frame);
//			imshow("FG Mask MOG", fgMaskMOG);
//			imshow("FG Mask MOG 2", fgMaskMOG2);
//			//get the input from the keyboard
//			keyboard = waitKey( 30 );
//			//search for the next image in the sequence
//			ostringstream oss;
//			oss << setfill('0') << setw(8) << (frameNumber + 1);
//			//oss << (frameNumber + 1);
//			string nextFrameNumberString = oss.str();
//			string nextFrameFilename = prefix + nextFrameNumberString + suffix;
//			//read the next frame
//			frame = imread(nextFrameFilename);
//			if(!frame.data){
//				//error in opening the next image in the sequence
//				cerr << "Unable to open image frame: " << nextFrameFilename << endl;
//				exit(EXIT_FAILURE);
//			}
//			//update the path of the current frame
//			fn.assign(nextFrameFilename);
//		}
//	}




//// SCRITTURA DEL NUMERO DEL FRAME CORRENTE SUL FRAME ATTUALE
//		stringstream ss;
//		rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
//			cv::Scalar(255,255,255), -1);
//		ss << capture.get(CV_CAP_PROP_POS_FRAMES);
//		string frameNumberString = ss.str();
//		putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
//			FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
//		cerr << capture.get(CV_CAP_PROP_POS_FRAMES);