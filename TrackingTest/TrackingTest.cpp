#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/tracking.hpp>
#include <stdio.h>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using namespace cv;
using namespace std;

void MyFilledCircle(Mat img, Point center);

int main(int argc, char** argv)
{
    cout << "hello there...";
    waitKey(1);
    
    Mat frame;
    
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    

    // declares all required variables
    Rect roi;
    Point roi_center;
    //Mat frame;
    // create a tracker object
    Ptr<Tracker> tracker = TrackerKCF::create();
    // set input video
    //std::string video = argv[1];
    //VideoCapture cap(video);
    // get bounding box
    cap >> frame;
    roi = selectROI("tracker", frame);
    //quit if ROI was not selected
    if (roi.width == 0 || roi.height == 0)
        return 0;
    // initialize the tracker
    tracker->init(frame, roi);
    // perform the tracking process
    printf("Start the tracking process, press ESC to quit.\n");
    for (;; ) {
        // get frame from the video
        cap >> frame;
        // stop the program if no more images
        if (frame.rows == 0 || frame.cols == 0)
            break;
    

        // update the tracking result
        tracker->update(frame, roi);
        roi_center = (roi.br() + roi.tl()) * 0.5;
        // draw the tracked object
        rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
        circle(frame, roi_center, 5, Scalar(0, 255, 0), FILLED, LINE_8);
        
        putText(frame, 
            "x:"+to_string(roi_center.x)+" y:"+to_string(roi_center.y),
            Point(20, 20),
            FONT_HERSHEY_SIMPLEX,
            1,
            Scalar(0, 255, 0),
            1,
            1);
        // show image with the tracked object
        imshow("tracker", frame);
        //quit on ESC button
        if (waitKey(1) == 27)break;
    }
    return 0;
}

void MyFilledCircle(Mat img, Point center)
{
    circle(img,
        center,
        img.rows / 8,
        Scalar(0, 0, 255),
        FILLED,
        LINE_8);
}
