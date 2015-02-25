// C++
#include <iostream>
#include <algorithm>
#include <numeric>	//accumulate
// OPENCV
#include <opencv2/opencv.hpp>



/*---------------------------------------------------------------------------------------------------------------------
	La funzione drawHist restituisce un'immagine in bianco e nero con rappresentato l'istogramma passato come parametro.
	E' tutt'altro che perfetta, va resa molto più parametrica per ottenere un'immagine più customizzata sulle nostre
	esigenze, ma intanto dovrebbe dare un'idea di come sono fatti gli istogrammi.
---------------------------------------------------------------------------------------------------------------------*/
cv::Mat1b drawHist(const std::vector<double> &hist, cv::Size imageSize) {
	unsigned dimX = imageSize.width + 10;
	unsigned dimY = imageSize.height;
	unsigned binW = dimX/hist.size();
	cv::Mat1b histImg(dimY,dimX,uchar(0));
	cv::normalize(hist,hist,1.0,0.0,cv::NORM_MINMAX);
	for (unsigned i=0; i<hist.size(); ++i) {
		cv::Point p1(5+(i*binW),dimY-5);
		cv::Point p2(5+(i*binW)+binW,dimY-5 - unsigned(hist[i]*(dimY-10)));
		rectangle(histImg,p1,p2,cv::Scalar(255),-1);
	}
	return histImg;
}



/*---------------------------------------------------------------------------------------------------------------------
	La funzione quantize trasforma un istogramma da un numero di bin pari a old_dim
	ad un numero di bin pari a new_dim. Non sono sicuro al 100% che sia priva di bug. 
---------------------------------------------------------------------------------------------------------------------*/
void quantize(std::vector<double> &hist, double old_dim, double new_dim) {
	int scalef = floor(old_dim / new_dim);
	
	int k=1;
	for(int i=0;i<new_dim;++i) {
		for(int j=0;j<scalef-1;++j) {
			hist[i] += hist[k++]; 
		}
		hist[i] /= scalef;
	}
	hist.resize(new_dim);
}



/*---------------------------------------------------------------------------------------------------------------------
	La funzione sumToOne normalizza un istogramma (vector<double>) facendo sì che la somma di tutti i valori
	contenuti nell'istogramma sia uguale a 1. Questa sono sicuro al 100% che sia priva di bug.
---------------------------------------------------------------------------------------------------------------------*/
void sumToOne (std::vector<double>& histo) {
	double total = std::accumulate(histo.begin(), histo.end(), 0.0);
	std::for_each(histo.begin(), histo.end(), [&total] (double &val) {val /= total;});
}




/*---------------------------------------------------------------------------------------------------------------------
	La funzione computeFeatureVector serve a calcolare il vettore di feature di un frame.

	INPUT:	Mat &frame:						il frame di cui calcolare il feature vector
			Rect peopleRect:				il rettangolo in cui il PD ha individuato la persona
			int bins:						numero di bin del feature vector (pare vezzani usasse 10 bin)
			vector<double> featureVector:	il feature vector da riempire
			vector<Mat> &histogramImages:	vettore di due elementi che è riempito con le immagini dei due istogrammi
			bool createHistImages:			flag che indica se devono o meno essere create le immagini dei due istogrammi

	OUTPUT: void							(è tutto passato per reference, quindi sono modificati i parametri)

---------------------------------------------------------------------------------------------------------------------*/
void computeFeatureVector ( cv::Mat &frame, cv::Rect peopleRect, int bins, std::vector<double> &featureVector,
						   std::vector<cv::Mat> &histogramImages, bool createHistImages) {

	//	Per calcolare PI mi muovo da peopleRect.y a (peopleRect.y+peopleRect.height)
	//	scorrendo la silhouette per fette orizzontali.
	//	Per calcolare THETA mi muovo invece da peopleRect.x a (peopleRect.x+peopleRect.width)
	//	scorrendo la silhouette per fette verticali.

	std::vector<double> hist_pi		= std::vector<double>(peopleRect.height);
	std::vector<double> hist_theta	= std::vector<double>(peopleRect.width);

	int yOffset = peopleRect.y;
	int xOffset = peopleRect.x;

	for (int i = yOffset; i<(yOffset+peopleRect.height); ++i)
		hist_pi[i-yOffset] = countNonZero(frame.row(i));
	
	for (int i = xOffset; i<(xOffset+peopleRect.width); ++i) 
		hist_theta[i-xOffset] = countNonZero(frame.col(i));

	if(createHistImages){
		// Salva in un vettore le visualizzazioni grafiche dei due istogrammi
		// [Le istruzioni di transpose e flip ruotano il primo istogramma di 90° in senso orario]
		histogramImages[0] = drawHist(hist_pi, cv::Size(640,480));
		histogramImages[1] = drawHist(hist_theta, cv::Size(640,480));
		/*transpose(histogramImages[0], histogramImages[0]);  
		flip(histogramImages[0], histogramImages[0], 1); */
	}

	// Normalizzazione dei due istogrammi in modo che la somma dei valori sia = 1
	sumToOne(hist_pi);
	sumToOne(hist_theta);

	// Quantizzazione dei due istogrammi per ridurre il numero di bin a K/2
	quantize(hist_pi,	 hist_pi.size(),	bins/2);
	quantize(hist_theta, hist_theta.size(), bins/2);

	// Crea il feature vector (è passato per reference) concatenando i due istogrammi 'pi' e 'theta'
	featureVector = hist_pi;	
	featureVector.insert( featureVector.end(), hist_theta.begin(), hist_theta.end() );
}














