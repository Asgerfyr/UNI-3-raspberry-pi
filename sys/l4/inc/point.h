#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(int x, int y, int value = 1);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    int getValue() const;
    void setValue(int value);
private:
    int x_;
    int y_;
    int value_;
};

#endif // POINT_H