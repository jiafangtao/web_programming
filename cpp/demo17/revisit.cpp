//
// Created by Bruce Jia on 2022/5/25.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Company {
    string name;

    void print() {
        std::cout << name << std::endl;
    }
};

void f_val(Company c) {
    c.name = "changed";
    c.print();
}

void f_ref(Company& c ) {
    c.name = "changed 2";
    c.print();
}

int main_1() {
    {
        Company c { "autodesk"};
        c.print();
        f_val(c);
        c.print();
    }

    std::cout << "===========================" << std::endl;
    {
        Company c { "autodesk"};
        c.print();
        f_ref(c);
        c.print();
    }

    return 0;
}

struct Point2D {
    double x;
    double y;
};

ostream & operator << (ostream& os, const Point2D & pt) {
    os << "(" << pt.x << ", " << pt.y << ")" << std::endl;
    return os;
}

void printsPoints(const vector<Point2D>& points) {
    for_each(points.begin(), points.end(), [](auto & pt) {
        std::cout << pt << std::endl;
    });
}

void processPoints(vector<Point2D> & points) {

    printsPoints(points);

    // Note here the type passed to lambda is a reference so the points can
    // get modified. Otherwise, if passed as vale=ue the vector is not changed.
    for_each(points.begin(), points.end(), [](auto & pt){
        pt.x = 10.00 * pt.x;
        pt.y = 10.00 * pt.y;
    });

    printsPoints(points);
}

int main() {
    vector<Point2D> pts;
    pts.push_back(Point2D{1.11, 1.00});
    pts.push_back(Point2D{2.22, 2.00});

    processPoints(pts);
}

void create_point_refs() {
    Point2D pt1{11.11, 11.11};
    Point2D pt2{22.22, 22.22};

    auto ref1 = std::ref(pt1);
    auto ref2 = std::ref(pt2);
    vector<std::reference_wrapper<Point2D>> points;

    points.push_back(ref1);
    points.push_back(ref2);
}
