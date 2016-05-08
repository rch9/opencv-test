#ifndef BALL_HPP
#define BALL_HPP

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <utility>


class Ball
{
public:
    Ball(cv::Mat *frame, float x0, float y0, cv::Scalar color);
    void draw();
    void update();

    float &getY0();
    unsigned &getRadius();
    bool isContain(std::pair<int, int> point);

private:
//public:
    cv::Mat *frame_;
    float x0_, y0_;
    unsigned radius_;
    cv::Scalar color_;
    int lineSize_;
    int smth_;
};
#endif // BALL_HPP
