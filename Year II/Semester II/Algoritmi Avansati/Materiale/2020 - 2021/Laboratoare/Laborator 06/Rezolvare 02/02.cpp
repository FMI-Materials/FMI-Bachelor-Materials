#include <bits/stdc++.h>
#include "points.hpp"
using namespace std;

/**
 * Returns if the poly vector is bitonic w/ respect to value.
 * This computes STRICT monotony: it has to be strictly increasing
 * and strictly decreasing.
 * In particular, there is a single minimal and single maximal value.
 */
bool CheckMono(vector <Point> poly, function<double(Point)> value)
{
    int p_min = 0;
    for (int i = 0; i < (int)poly.size(); i++)
        if (value(poly[p_min]) > value(poly[i]))
            p_min = i;
    
    // Rotate such that first item is the smallest
    // element.
    rotate(poly.begin(), poly.begin() + p_min, poly.end());

    // Now values should increase, and then decrease.
    // up=1 -> Increasing / up=0 -> decreasing.
    bool up = 1;
    for (int i = 1; i < (int)poly.size(); i++) {
        // Equal. shouldn't happend.
        if (abs(value(poly[i]) - value(poly[i - 1])) < 1e-5)
            return false;
            
        // Decreasing.
        if (value(poly[i]) < value(poly[i - 1]))
            up = 0;

        // Supposed to be decreasing, but has to increase.
        if (value(poly[i]) > value(poly[i - 1]) && !up)
            return false;
    }
    return true;
}

// Exercise 2.
int main()
{
    auto read_point = []() -> Point {
        double x, y;
        cin >> x >> y;
        return Point({ x, y });
    };

    cout << "Cate puncte are poligonul?\n";
    int n;
    cin >> n;

    cout << "Introduceti punctele:\n";
    vector <Point> v(n);
    for (auto& p : v)
        p = read_point();

    bool x_monoton = CheckMono(v, [](auto a) { return a.x(); });
    bool y_monoton = CheckMono(v, [](auto a) { return a.y(); });

    
    cout << "Poligonul " << (x_monoton ? "" : "nu ") << "este x-monoton\n";
    cout << "Poligonul " << (y_monoton ? "" : "nu ") << "este y-monoton\n";
    return 0;
}