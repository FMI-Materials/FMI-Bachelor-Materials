#include <bits/stdc++.h>
#include "points.hpp"
using namespace std;

/**
 * Returns 0 if both edges are legal.
 * Returns 1 if AC is illegal.
 * Returns 2 if BD is illegal.
 */
int CheckIllegalManual(Point A, Point B, Point C, Point D)
{
    // Just get all the angles,
    // and sort them increasingly.
    // Then, just compare lexicografically.
    auto generate_angles = [](Point A, Point B, Point C) {
        return vector <double>({
            Angle(A, B, C),
            Angle(B, C, A),
            Angle(C, A, B)
        });
    };

    auto anglesABC = generate_angles(A, B, C);
    auto anglesCDA = generate_angles(B, C, D);

    auto anglesBCD = generate_angles(B, C, D);
    auto anglesDAB = generate_angles(D, A, B);

    auto angles1 = anglesABC;
    angles1.insert(angles1.end(), anglesCDA.begin(), anglesCDA.end());

    auto angles2 = anglesBCD;
    angles2.insert(angles2.end(), anglesDAB.begin(), anglesDAB.end());

    sort(angles1.begin(), angles1.end());
    sort(angles2.begin(), angles2.end());

    for (int i = 0; i < (int)angles1.size(); i++) {
        if (abs(angles1[i] - angles2[i]) < 1e-5)
            continue;
        return (angles1[i] < angles2[i] ? 1 : 2);
    }

    return 0;
}


/**
 * Returns 0 if both edges are legal.
 * Returns 1 if AC is illegal.
 * Returns 2 if BD is illegal.
 */
int CheckIllegalGeometric(Point A, Point B, Point C, Point D)
{
    // Edge AC is illegal if D is inside of the
    // circle circumscribed to ABC.
    // If D is outside, then edge BD is illegal.
    auto [center, radius] = CircumscribedCircle(A, B, C);
    double d = Dist(D, center);

    if (abs(d - radius) < 1e-5)
        return 0;
    
    if (d < radius)
        return 1;
    return 2;
}

// Exercise 4.
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

    int legality = CheckIllegalGeometric(A, B, C, D);

    if (legality == 0)
        cout << "Ambele diagonale sunt legale!\n";
    else if (legality == 1)
        cout << "Muchia AC este ilegala!\n";
    else
        cout << "Muchia BD este ilegala!\n";

    return 0;
}
