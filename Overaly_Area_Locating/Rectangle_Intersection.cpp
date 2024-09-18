/*
The rectangle intesection problem tries to find all intersection between N different rectangles.

One naive approach would be to check every rectangle against every rectangle; this would take O(N^2) time for N rectangles. A better approach would be the use a sweep line; this sweep line would stop when we cross the left boundary of a rectangle, and this rectangle is added to the set of active rectangles. When we cross the right boundary of a rectangle, we remove the rectangle from the set of active rectangles.

We must then report all intersections between a newly activated rectangle that lie on the scan line, and the set of active rectangles. To do this, we just have to check if the vertical segment of the rectangle overlap. The key to a good solution is to organize the active rectangles so that intersection,deletion, and detection are executed efficiently.

I have choosed to use a Min-Priority Queue to manage the insertion and deletion. A pass thru a sorted array of x values of rectangles would work too.

I am simply testing the current segment against active segments, but a data structure like an interval tree could be used. This would yiels an execution time of O(Nlg(N)+F) where F is the number of rectangle intersections and N the number of line segments inserted in the interval tree

Notice how the sets of active rectangle evolves as the sweep line advances.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Rectangle {
    int x, y, w, h, id;
};

struct Event {
    int x;
    int type; // 0 for start, 1 for end
    int rectId;
};

struct Intersection {
    int x, y;
};

class SweepLine {
public:
    void addRectangle(const Rectangle& rect) {
        rectangles.push_back(rect);
        events.push_back({rect.x, 0, rect.id}); // Start event
        events.push_back({rect.x + rect.w, 1, rect.id}); // End event
    }

    void process() {
        std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
            return a.x < b.x || (a.x == b.x && a.type < b.type);
        });

        for (const auto& event : events) {
            if (event.type == 0) {
                active.push_back(rectangles[event.rectId]);
                checkIntersections(active.back());
            } else {
                removeRectangle(event.rectId);
            }
        }

        printIntersections();
    }

private:
    std::vector<Rectangle> rectangles;
    std::vector<Event> events;
    std::vector<Rectangle> active;
    std::vector<Intersection> intersections;

    void checkIntersections(const Rectangle& rect) {
        for (const auto& activeRect : active) {
            if (isIntersecting(rect, activeRect)) {
                intersections.push_back({rect.x, activeRect.y});
            }
        }
    }

    bool isIntersecting(const Rectangle& a, const Rectangle& b) {
        return !(a.x + a.w <= b.x || b.x + b.w <= a.x || a.y + a.h <= b.y || b.y + b.h <= a.y);
    }

    void removeRectangle(int id) {
        active.erase(std::remove_if(active.begin(), active.end(),
            [id](const Rectangle& r) { return r.id == id; }), active.end());
    }

    void printIntersections() {
        for (const auto& intersection : intersections) {
            std::cout << "Intersection at: (" << intersection.x << ", " << intersection.y << ")\n";
        }
    }
};

int main() {
    SweepLine sweepLine;
    sweepLine.addRectangle({20, 20, 60, 60, 0});
    sweepLine.addRectangle({30, 60, 107, 120, 1});
    sweepLine.addRectangle({70, 90, 215, 120, 2});
    sweepLine.addRectangle({40, 130, 200, 150, 3});
    sweepLine.addRectangle({140, 20, 90, 40, 4});
    sweepLine.addRectangle({120, 40, 20, 120, 5});
    sweepLine.addRectangle({300, 50, 100, 40, 6});
    sweepLine.addRectangle({700, 50, 90, 20, 7});

    sweepLine.process();
    return 0;
}
