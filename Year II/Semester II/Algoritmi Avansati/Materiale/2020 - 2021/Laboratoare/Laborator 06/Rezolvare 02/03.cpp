#include <bits/stdc++.h>
#include "points.hpp"
using namespace std;

// Exercise 3.
int main()
{
    auto read_point = []() -> Point {
        double x, y;
        cin >> x >> y;
        return Point({ x, y });
    };

    cout << "Introduceti cele 4 puncte:\n";
    Point A = read_point(), B = read_point(),
          C = read_point(), D = read_point();

    // Call CircumscribedCircle from "points.hpp".
    auto [center, radius] = CircumscribedCircle(A, B, C);
    
    double dist = Dist(D, center);

    if (abs(dist - radius) < 1e-5)
        return cout << "Punctul este pe cerc!!\n", 0;
    
    if (dist < radius)
        return cout << "Punctul este in cerc!!\n", 0;

    cout << "Punctul este inafara cercului!!\n";
    return 0;
}