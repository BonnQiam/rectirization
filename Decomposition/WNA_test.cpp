//Winding Number Algorithm

#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x, y;
};

double isLeft(Point a, Point b, Point c) {
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

bool isInside(vector<Point> polygon, Point point) {
    int windingNumber = 0;

    for (int i = 0; i < polygon.size(); i++) {
        if (polygon[i].y <= point.y) {
            if (polygon[(i + 1) % polygon.size()].y > point.y) {
                if (isLeft(polygon[i], polygon[(i + 1) % polygon.size()], point) > 0) {
                    windingNumber++;
                }
            }
        } else {
            if (polygon[(i + 1) % polygon.size()].y <= point.y) {
                if (isLeft(polygon[i], polygon[(i + 1) % polygon.size()], point) < 0) {
                    windingNumber--;
                }
            }
        }
    }

    return windingNumber != 0;
}

int main() {
    vector<Point> polygon = {{0, 0}, {0, 10}, {10, 10}, {10, 0}};
    Point point = {5, 5};

    if (isInside(polygon, point)) {
        cout << "The point is inside the polygon." << endl;
    } else {
        cout << "The point is outside the polygon." << endl;
    }

    return 0;
}
