#include "ball.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Ball::Ball(Mat *frame, float x0, float y0, Scalar color):
    frame_(frame),
    x0_(x0),
    y0_(y0),
    radius_(32.f),
    color_(color),
    lineSize_(5),
    smth_(8) {
}

float &Ball::getY0() {
    return y0_;
}

unsigned &Ball::getRadius() {
    return radius_;
}

void Ball::draw() {
    circle(*frame_, Point(x0_, y0_),radius_, color_, lineSize_, smth_);
}

void Ball::update() {
    y0_ += 10.f;
    this->draw();
}

bool Ball::isContain(pair<int, int> point) {

    if ((point.first >= x0_ - radius_) && (point.first <= x0_ + radius_)
            && (point.second >= y0_ - radius_) && (point.second <= y0_ + radius_)) {
        return 1;
    }

    return 0;
}

