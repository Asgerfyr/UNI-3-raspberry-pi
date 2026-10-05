#include "point.h"


Point::Point(int x, int y, int value):
    x_(x), y_(y), value_(value) {
}

int Point::getX() const {
    return x_;
}

int Point::getY() const {
    return y_;
}

void Point::setX(int x) {
    x_ = x;
}

void Point::setY(int y) {
    y_ = y;
}

int Point::getValue() const {
    return value_;
}

void Point::setValue(int value) {
    value_ = value;
}
