#include <opencv/cv.h> 
#include <opencv/highgui.h> 
#include <stdio.h>

int main(void)
{
int H_MIN = 0;
int H_MAX = 255;
int S_MIN = 0;
int S_MAX = 255;
int V_MIN = 0;
int V_MAX = 255;

cvCreateTrackbar("H_MIN", "HSV ENTRADA", &H_MIN, 256, NULL); //Hue
cvCreateTrackbar("H_MAX", "HSV ENTRADA", &H_MAX, 256, NULL);
cvCreateTrackbar("S_MIN", "HSV ENTRADA", &S_MIN, 256, NULL); //Saturation
cvCreateTrackbar("S_MAX", "HSV ENTRADA", &S_MAX, 256, NULL);
cvCreateTrackbar("V_MIN", "HSV ENTRADA", &V_MIN, 256, NULL); //Value
cvCreateTrackbar("V_MAX", "HSV ENTRADA", &V_MAX, 256, NULL);

int R_MIN = 100;
int R_MAX = 100;
int G_MIN = 100;
int G_MAX = 100;
int B_MIN = 100;
int B_MAX = 100;

cvCreateTrackbar("R_MIN", "RGB SAIDA", &R_MIN, 256, NULL);
cvCreateTrackbar("R_MAX", "RGB SAIDA", &R_MAX, 256, NULL);
cvCreateTrackbar("G_MIN", "RGB SAIDA", &G_MIN, 256, NULL);
cvCreateTrackbar("G_MAX", "RGB SAIDA", &G_MAX, 256, NULL);
cvCreateTrackbar("B_MIN", "RGB SAIDA", &B_MIN, 256, NULL);
cvCreateTrackbar("B_MAX", "RGB SAIDA", &B_MAX, 256, NULL);

IplImage* frame;
IplImage* hsv_frame;
IplImage* threshold_hsv_frame;

CvMemStorage* storage = cvCreateMemStorage (0);
CvSeq* contours=0;

CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);

cvNamedWindow("HSV ENTRADA", CV_WINDOW_AUTOSIZE);
cvNamedWindow("HSV", CV_WINDOW_AUTOSIZE);
cvNamedWindow("Threshold HSV", CV_WINDOW_AUTOSIZE);
cvNamedWindow("Camera", CV_WINDOW_AUTOSIZE);
cvNamedWindow("RGB SAIDA", CV_WINDOW_AUTOSIZE);

frame = cvQueryFrame( capture );
hsv_frame = cvCreateImage(cvSize( frame->width, frame->height), IPL_DEPTH_8U, 3);
threshold_hsv_frame = cvCreateImage(cvSize( frame->width, frame->height), IPL_DEPTH_8U, 1);


while(cvWaitKey(10)!=27)
{
    frame = cvQueryFrame( capture );
    if( !frame ) break;

    cvCvtColor(frame, hsv_frame, CV_BGR2HSV);
    cvInRangeS(hsv_frame, cvScalar(H_MIN, S_MIN, V_MIN), cvScalar( H_MAX, S_MAX, V_MAX) , threshold_hsv_frame);

    cvFindContours(threshold_hsv_frame, storage, &contours, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    cvDrawContours(frame, contours, CV_RGB(R_MIN, G_MIN, B_MIN), CV_RGB(R_MAX, G_MAX, B_MAX), 0, CV_FILLED, 8 );

    cvShowImage("Camera", frame);
    cvShowImage("HSV", hsv_frame);
    cvShowImage("Threshold HSV", threshold_hsv_frame);
}
cvReleaseCapture( &capture );

cvDestroyAllWindows();

return 0;
}
