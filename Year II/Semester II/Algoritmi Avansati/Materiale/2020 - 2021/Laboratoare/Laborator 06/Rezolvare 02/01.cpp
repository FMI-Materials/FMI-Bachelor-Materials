#include <bits/stdc++.h>
#include "points.hpp"
using namespace std;

mt19937 rnd(time(0));

/**
 * Casts a ray from source to a random direction.
 * @return -1 if inside, 0 if on an edge, 1 if outside.
 * As the ray is choosen randomly, no need to check for additional restraints
 * like intersection on vertices or stuff like this.
 */
int CastRay(vector <Point> poly, Point source)
{
    // Getting a random destination for our ray.
    uniform_real_distribution<double> random_distr(1e9, 2e9);
    Point dest({ random_distr(rnd), random_distr(rnd) });

    int cnt = 0;
    for (int i = 0; i < (int)poly.size(); i++) {
        Point urm = poly[(i + 1) % poly.size()];
        cnt += (CheckIntersection(poly[i], urm, source, dest) == 1);
        if (IsOnSegment(poly[i], urm, source))
            return 0;
    }

    return ((cnt & 1) ? -1 : 1);
}

// Exercise 1.
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

    cout << "Introduceti punctul de verificat:\n";
    Point source = read_point();

    int rez = CastRay(v, source);

    if (rez == -1)
        return cout << "Punctul este inauntrul poligonului!\n", 0;
    if (rez == 0)
        return cout << "Punctul este pe poligon!\n", 0;
    cout << "Punctul este inafara poligonului!\n";
    return 0;
}