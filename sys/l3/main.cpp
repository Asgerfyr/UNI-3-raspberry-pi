#include <iostream>
#include "display.h"
#include <unistd.h>


int main() {
    Display display(40, 40);
    display.addPoint(Point(0, 0, 1));
    display.addPoint(Point(39, 4, 2));
    display.addLine(0, 1);
    display.allPrint();

    int change = 1;
    Point& point = display.getPoint(0);
    while(1){
        std::cout << std::endl << std::endl << std::endl;
        point.setX(point.getX() + change);
        display.allPrint();
        if (point.getX() <= 0 || point.getX() >= 39) {
            change = -change;
        }
        usleep(10000); // Add a small delay to make the movement visible
    }

    return 0;
}