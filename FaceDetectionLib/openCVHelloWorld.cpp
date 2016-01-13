#include <iostream>
#include <opencv2\opencv.hpp>

int main()
{
	cv::VideoCapture capture(CV_CAP_ANY);  //Capture using any camera connected to your system
	if (!capture.isOpened())
		return -1;
	
	char key;
	cv::namedWindow("Camera_Output", 1);    //Create window
	while (1){ //Create infinte loop for live streaming
		cv::Mat frame;
		capture >> frame; //Create image frames from capture

		cv::imshow("Camera_Output", frame);   //Show image frames on created window
		key = cv::waitKey(33);     //Capture Keyboard stroke
		if (char(key) == 27){
			break;      //If you hit ESC key loop will break.
		}
	}

	cv::destroyAllWindows();

	return 0;
}