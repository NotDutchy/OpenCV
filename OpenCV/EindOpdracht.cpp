#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Project 2 - Document Scanner  //////////////////////

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode, imgWarp, imgCrop, imgText;
vector<Point> initialPoints, docPoints;
float w = 420, h = 596;

Mat preProcessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);
	return imgDil;
}

vector<Point> getContours(Mat image) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(image, contours, -1, Scalar(255, 0, 255), 2);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	vector<Point> biggest;
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area << endl;

		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {

				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0],conPoly[i][1] ,conPoly[i][2] ,conPoly[i][3] };
				maxArea = area;
			}
			drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 10, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

vector<Point> reorder(vector<Point> points)
{
	vector<Point> newPoints;
	vector<int>  sumPoints, subPoints;

	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
	Point2f src[4] = { points[0],points[1],points[2],points[3] };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;
}

Mat getText(Mat image)
{
	Mat rgb = image;
	pyrDown(image, rgb);

	cv::Mat grayImage;
	cv::cvtColor(rgb, grayImage, cv::COLOR_BGR2GRAY);

	Mat grad;
	Mat morphKernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(grayImage, grad, MORPH_GRADIENT, morphKernel);

	cv::threshold(grad, grayImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

	Mat mask = Mat::zeros(grayImage.size(), CV_8UC1);
	std::vector<std::vector<cv::Point>> contours;
	vector<Vec4i> hierarchy;
	cv::findContours(grayImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
		Rect rect = boundingRect(contours[idx]);
		Mat maskROI(mask, rect);
		maskROI = Scalar(0, 0, 0);
		drawContours(mask, contours, idx, Scalar(255, 255, 255), 4);

		RotatedRect rrect = minAreaRect(contours[idx]);
		double r = (double)countNonZero(maskROI) / (rrect.size.width * rrect.size.height);

		Scalar color;
		int thickness = 1;
		if (r > 0.25 && (rrect.size.height > 8 && rrect.size.width > 8)) 
		{
			thickness = 2;
			color = Scalar(0, 255, 0);
		}
		else
		{
			thickness = 1;
			color = Scalar(0, 0, 255);
		}

		Point2f pts[4];
		rrect.points(pts);
		for (int i = 0; i < 4; i++)
		{
			line(rgb, Point((int)pts[i].x, (int)pts[i].y), Point((int)pts[(i + 1) % 4].x, (int)pts[(i + 1) % 4].y), color, thickness);
		}
	}
	return rgb;
}

void main() {

	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	// Preprpcessing - Step 1 
	imgThre = preProcessing(imgOriginal);

	// Get Contours - Biggest  - Step 2
	initialPoints = getContours(imgThre);
	//drawPoints(initialPoints, Scalar(0, 0, 255));
	docPoints = reorder(initialPoints);
	//drawPoints(docPoints, Scalar(0, 255, 0));

	// Warp - Step 3 
	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//Crop - Step 4
	int cropVal = 5;
	Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
	imgCrop = imgWarp(roi);
	imgText = getText(imgCrop);

	imshow("Image", imgOriginal);
	//imshow("Image Dilation", imgThre);
	//imshow("Image Warp", imgWarp);
	imshow("Image Crop", imgCrop);
	imshow("Woorden en letters", imgText);
	waitKey(0);

}
