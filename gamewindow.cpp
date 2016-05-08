#include "gamewindow.hpp"
#include <iostream>

using namespace cv;
using namespace std;

GameWindow::GameWindow():
    capture_(0),
    score_(0),
    WIDTH_(capture_.get(CV_CAP_PROP_FRAME_WIDTH)),
    HEIGHT_(capture_.get(CV_CAP_PROP_FRAME_HEIGHT)),
    timer_(15) {
}

void GameWindow::run() {
    if(!capture_.isOpened()) {
        std::cerr << "Error with web cam" << std::endl;
    }

    char key;
    namedWindow("Balls", 1);

    while (1) {
        if (!capture_.read(frame_)) {
            cerr << "Cannot read a frame from video stream" << endl;
            break;
        }

        update();


        imshow("Balls", frame_);
        key = cvWaitKey(4);
        if(key == 27) {
            break;
        }
    }

}

void GameWindow::update() {
    if(timer_ == 15) {
        timer_ = 0;
        balls_.push_back(Ball(&frame_, rand() % WIDTH_, 0,
                              Scalar(rand() % 256, rand() % 256, rand() % 256)));
    }

    pair<int, int> playerPosition = handlePlayer();

    for(auto it = balls_.begin(); it != balls_.end(); ++it) {
        it->update();

        if(it->isContain(playerPosition)) {
            ++score_;
            cout << score_ << endl;
            it = balls_.erase(it++);
        } else if((it->getY0() - it->getRadius() / 2) > HEIGHT_) {
            it = balls_.erase(it++);
        }
        putText(frame_, to_string(score_), Point(WIDTH_ / 2, HEIGHT_ / 4), CV_FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 3, 8);
    }

    if(timer_ == 15) {
        timer_ = 0;
    }
    ++timer_;
}

pair<int, int> GameWindow::handlePlayer() {
    int iLowH = 75;
    int iHighH = 130;

    int iLowS = 150;
    int iHighS = 255;

    int iLowV = 60;
    int iHighV = 255;

    Mat imgHSV;

    cvtColor(frame_, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    Mat imgThresholded;

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

    //morphological opening (removes small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    //morphological closing (removes small holes from the foreground)
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    //Calculate the moments of the thresholded image
    Moments oMoments = moments(imgThresholded);

    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;

    // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
    if (dArea > 10000)
    {
        //calculate the position of the ball
        int posX = dM10 / dArea;
        int posY = dM01 / dArea;

        return make_pair(posX, posY);
    }

//    Лень, лень, лень
    return make_pair(-500, -500);
}
