#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>

cv::CascadeClassifier faceDetector;
double scaleFactor = 1.05;
int minNeighbors = 3;
int flags = 0;
cv::Size minFaceSize(30, 30);

cv::Mat detectFace(cv::Mat frame) {
	cv::Mat gray(frame.size(), CV_8UC1);
	cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faceDetected;
	faceDetector.detectMultiScale(gray, faceDetected, scaleFactor, minNeighbors, flags, minFaceSize);

	for each (cv::Rect rect in faceDetected)
		cv::rectangle(frame, rect, cv::Scalar(0, 0, 255), 1);

	return frame;
}

int main()
{
	if (!faceDetector.load("haarcascade_frontalface_alt_tree.xml")) {
		std::cout << "Failed to load classifier" << std::endl;
		getchar();
		return -1;
	}
	cv::VideoCapture capture(CV_CAP_ANY);  //Capture using any camera connected to your system
	if (!capture.isOpened())
		return -1;
	
	char key;
	cv::namedWindow("Camera_Output", 1);    //Create window
	while (1){ //Create infinte loop for live streaming
		cv::Mat frame;
		capture >> frame; //Create image frames from capture

		cv::Mat faceDetectedFrame = detectFace(frame);

		cv::imshow("Camera_Output", faceDetectedFrame);   //Show image frames on created window
		key = cv::waitKey(1);     //Capture Keyboard stroke
		if (char(key) == 27){
			break;      //If you hit ESC key loop will break.
		}
	}

	cv::destroyAllWindows();

	return 0;
}