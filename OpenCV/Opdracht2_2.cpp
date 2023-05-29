#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;



/*void main() {

	string path = "Resources/test.png";
	Mat img = imread(path);

	string path2 = "Resources/BrutusGustavus.JPG";
	Mat img2 = imread(path2);
	Mat imgGray, imgBlur, imgCanny;
	Mat img2Gray, img2Blur, img2Canny, img2CannyResize;

	int threshold1 = 0, threshold2 = 0;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	cvtColor(img2, img2Gray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
	GaussianBlur(img2Gray, img2Blur, Size(7, 7), 5, 0);

	namedWindow("Trackbars");
	createTrackbar("Threshold 1", "Trackbars", &threshold1, 100);
	createTrackbar("Threshold 2", "Trackbars", &threshold2, 100);

	while (true)
	{
		Canny(imgBlur, imgCanny, threshold1, threshold2);
		Canny(img2Blur, img2Canny, threshold1, threshold2);

		resize(img2Canny, img2CannyResize, Size(), 0.5, 0.5);

		/*imshow("Image", img);
		imshow("Image Gray", imgGray);
		imshow("Image Blur", imgBlur);#1#
		imshow("Image Canny", imgCanny);
		imshow("Image 2 Canny", img2CannyResize);
		waitKey(1);
	}
}*/