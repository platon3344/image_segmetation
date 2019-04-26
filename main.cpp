#include <iostream>
#include <chrono>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <thread>
#include <mutex>

using namespace std;
using namespace cv;


Mat src,src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(255);
Mat canny_output;
std::mutex mmutex;
vector<vector<Point>> contours;
void thresh_callback();
void showImage();

int main()
{
    thresh_callback();
    thread thread_show(showImage);
//    thread thread_callback(thresh_callback);
    thread_show.join();
//    thread_callback.join();

    waitKey(0);
    return 0;
}

void thresh_callback()
{
    std::unique_lock<std::mutex> mlock(mmutex);
    src = imread("../dataset/5000.jpg");
    if(src.empty()){
        cout << "do not have image" << endl;
        return;
    }

    std::chrono::steady_clock::time_point t1 =
            std::chrono::steady_clock::now();
    cout << "rows = " << src.rows << "cols = " << src.cols << endl;
    cvtColor(src,src_gray,COLOR_BGR2GRAY);
    blur(src_gray,src_gray,Size(3,3));
    Canny(src_gray,canny_output,thresh,thresh*2,3);

    findContours(canny_output,contours,CV_RETR_EXTERNAL,
                 CHAIN_APPROX_SIMPLE,Point(0,0));

    std::chrono::steady_clock::time_point t2 =
            std::chrono::steady_clock::now();

    double tduration = std::chrono::duration_cast<std::chrono::duration<double>> (t2-t1).count();
    cout << tduration << endl;


}

void showImage()
{
    std::unique_lock<std::mutex> mlock(mmutex);
    for(size_t i = 0;i < contours.size();i++){
        Scalar color = Scalar(rng.uniform(0,255),
                              rng.uniform(0,255),
                              rng.uniform(0,255));
        drawContours(src,contours,(int)i,color,2,8,noArray(),0,Point());

    }
    namedWindow("contours",WINDOW_AUTOSIZE);
    imshow("contours",src);
}
