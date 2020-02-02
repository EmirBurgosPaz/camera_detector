#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorMOG2();
    VideoCapture cap;

    if (!cap.open(0))
        return 0;
    for (;;)
    {
        Mat frame, fgMask;
        cap >> frame;
        if (frame.empty()) break; 

        pBackSub->apply(frame, fgMask);

        rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
            cv::Scalar(255, 255, 255), -1);
        imshow("Camara", frame);
        imshow("Presiona w para finalizar", fgMask);
        if (waitKey(1) == 'w') break;  
    }

    return 0;
}