#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
IplImage* image = 0;
IplImage* gray = 0;

int main(int argc, char** argv, int wParam)
{

	image = cvLoadImage("Image.jpg");
	gray = cvCreateImage(cvGetSize(image), 8, 1);

	cvCvtColor(image, gray, CV_BGR2GRAY);
	cvThreshold(gray, gray, 128, 255, CV_THRESH_BINARY_INV);

	CvMemStorage* storage = cvCreateMemStorage(0);

	CvSeq* contours = 0;
	cvFindContours(gray, storage, &contours, sizeof(CvContour),
		CV_RETR_TREE, CV_CHAIN_APPROX_NONE, cvPoint(0, 0)); // Поиск контуров 

	for (CvSeq* c = contours; c != NULL; c = c->h_next)
	{
		CvRect Rect = cvBoundingRect(c); // Поиск ограничивающего прямоугольника
		if (Rect.width < 30 || Rect.width > 60) continue; // Маленькие контуры меньше 50 пикселей не нужны
		cvRectangle(image, cvPoint(Rect.x, Rect.y), cvPoint(Rect.x + Rect.width, Rect.y + Rect.height), CV_RGB(255, 0, 0), 2);
	}

	/**
	* Rescale IplImage
	*/

	const int new_width = (int)((float)image->width * 0.75);
	const int new_height = (int)((float)image->height * 0.55);
	IplImage* resizedImg = cvCreateImage(cvSize(new_width, new_height), image->depth, image->nChannels);
	cvResize(image, resizedImg);


	cvReleaseMemStorage(&storage);
	//cvNamedWindow("Result", CV_WINDOW_FREERATIO);
	cvShowImage("Result", resizedImg);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&gray);
	return 0;
}