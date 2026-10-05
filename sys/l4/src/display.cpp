#include "display.h"
#include <iostream>

Display::Display(int rows, int cols):
    matrix_(rows, cols),
    points_(),
    Lines(),
    pointCount_(0) {
}

void Display::addPoint(const Point& point) {
    points_.push_back(point);
    pointCount_++;
}

void Display::addLine(const Point& start, const Point& end) {
    Lines.push_back(std::make_pair(start, end));
}

void Display::addLine(const int P_index1, const int P_index2) {
    if (P_index1 >= 0 &&
    static_cast<size_t>(P_index1) < points_.size() &&
    P_index2 >= 0 &&
    static_cast<size_t>(P_index2) < points_.size()) {
        Lines.push_back(std::make_pair(points_[P_index1], points_[P_index2]));
    }
}

void Display::placePoints() {
    for (const auto& point : points_) {
        matrix_.set(point.getX(), point.getY(), point.getValue());
    }
}


void Display::placeLines() {
    // Place all lines on the matrix between 2 points
    // insrts value of the first point

    for (const auto& line : Lines) {
        generate_line(line.first, line.second);
    }
}

void Display::clearDisplay() {
    matrix_.clear();
}

void Display::print() const {
    matrix_.print();
}

void Display::allPrint(){
    clearDisplay();
    placeLines();
    print();
}

std::vector<Point> Display::getPoints() {
    return points_;
}

Point& Display::getPoint(int index){
    return points_[index];
}

int Display::getPointCount() const {
    return pointCount_;
}

Display::~Display() {
}


void Display::generate_line(const Point& point1, const Point& point2){
    // Place all points on the matrix between 2 points
    // Inserts the value of the first point
    
    int x1 = point1.getX();
    int y1 = point1.getY();
    int x2 = point2.getX();
    int y2 = point2.getY();
    
    int value = point1.getValue();
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    
    int error = dx - dy;
    
    while (true) {
        matrix_.set(x1, y1, value);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * error;

        if (e2 > -dy) {
            error -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            error += dx;
            y1 += sy;
        }
    }
}