#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>

cv::CascadeClassifier faceDetector;
double scaleFactor = 1.05;
int minNeighbors = 1;
int flags = 0;
cv::Size minFaceSize(30, 30);
double GROUP_EPS = 0.2;

cv::Mat detectFace(cv::Mat frame) {
	cv::Mat gray(frame.size(), CV_8UC1);
	cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); //Not needed, detectMultiScale takes care of conversion of conversion to grayscale.

	std::vector<cv::Rect> faceDetected;
	faceDetector.detectMultiScale(gray, faceDetected, scaleFactor, 0, flags, minFaceSize);
	
	std::vector<int> numDetections;
	cv::groupRectangles(faceDetected, numDetections, minNeighbors, GROUP_EPS);

	for (unsigned int i = 0; i < faceDetected.size(); i++) {
		cv::Rect rect = faceDetected.at(i);
		cv::rectangle(frame, rect, cv::Scalar(0, 0, 255), 1);
		cv::putText(frame, std::to_string(numDetections[i]),
			cv::Point(rect.x, rect.y), 1, 1, cv::Scalar(0, 0, 255));
	}

	return frame;
}

int main()
{
	if (!faceDetector.load("resources/haarcascade_frontalface_alt_tree.xml")) {
		std::cout << "Failed to load classifier" << std::endl;
		getchar();
		return -1;
	}
	cv::VideoCapture capture(CV_CAP_ANY);  //Capture using any camera connected to your system
	if (!capture.isOpened())
		return -1;
	
	char key;
	cv::namedWindow("Camera_Output", 1);    //Create window
	while (true){ //Create infinte loop for live streaming
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