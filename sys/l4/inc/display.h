#include <vector>
//has matrix and array of points where you can place points on matrix print it out get the points
#include "matrix.h"
#include "point.h"

#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
    Display(int rows, int cols);
    void addPoint(const Point& point);
    void addLine(const Point& start, const Point& end);
    void addLine(const int P_index1, const int P_index2);
    void placePoints();
    void placeLines();
    void generate_line(const Point& point1, const Point& point2);
    void clearDisplay();
    void print() const;
    void allPrint();
    std::vector<Point> getPoints();
    Point& getPoint(int index);
    int getPointCount() const;
    ~Display();
private:
    Matrix matrix_;
    std::vector<Point> points_;
    std::vector<std::pair<Point, Point>> Lines;
    int pointCount_;
};

#endif // DISPLAY_H