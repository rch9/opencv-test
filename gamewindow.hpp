#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include "ball.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <list>

class GameWindow
{
public:
    GameWindow();
    void run();
private:
    cv::VideoCapture capture_;
    cv::Mat frame_;
    int score_;
    std::list<Ball> balls_;
    int WIDTH_;
    int HEIGHT_;
    int timer_;

//    void handleBalls(std::list<Ball> &balls);
    void update();
    std::pair<int, int> handlePlayer();
};

#endif // GAMEWINDOW_HPP
