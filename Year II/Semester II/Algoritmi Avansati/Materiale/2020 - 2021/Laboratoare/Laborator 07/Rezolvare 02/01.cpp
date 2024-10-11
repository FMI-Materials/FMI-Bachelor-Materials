#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-5;
const double infinity = 1e18;

/**
 * Plane is either vertical or orizontal.
 * if plane is vertical, then the plane's equation is
 *     a * y + b <= 0
 * if plane is orizontal (not vertical), then the plane's equation is
 *     a * x + b <= 0 
*/
struct Plane {
    bool is_vertical;
    double a, b;

    void read() {
        double coef_x, coef_y, free;
        cin >> coef_x >> coef_y >> free;

        if ((abs(coef_x) <= eps && abs(coef_y) <= eps) ||
                (abs(coef_x) > eps && abs(coef_y) > eps))
            throw runtime_error("Given plane isn't orizontal / vertical!");
        if (abs(coef_x) <= eps)
            is_vertical = 1, a = coef_y, b = free;
        else
            is_vertical = 0, a = coef_x, b = free;
    }
};

/**
 * 0 if intersection is empty
 * 1 if intersection has finite area
 * 2 otherise
 */
int CheckAlignedPlanesIntersection(const vector <Plane>& planes)
{
    // Initial boundaries of the intersection.
    double x_min = -infinity, x_max = infinity, y_min = -infinity, y_max = infinity;

    // Incorporate new restrictions.
    for (Plane p : planes) {
        // Initial new restrictions to add.
        double new_min = -infinity, new_max = infinity;
        
        if (p.a > 0)
            new_max = -p.b / p.a;
        else
            new_min = -p.b / p.a;

        // Vertical plane => update y_min and y_max.
        if (p.is_vertical)
            y_min = max(y_min, new_min), y_max = min(y_max, new_max);
        else // Orizontal plane => update x_min and x_max.
            x_min = max(x_min, new_min), x_max = min(x_max, new_max);
    }

    bool is_empty = (x_min - eps > x_max) || (y_min - eps > y_max);
    bool is_infinite = (min(x_min, y_min) < -infinity / 2) ||
                       (max(x_max, y_max) > infinity / 2);

    if (is_empty)
        return 0;
    return is_infinite ? 2 : 1;
}

int main()
{
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector <Plane> planes(n);
        for (auto& p : planes)
            p.read();

        int result = CheckAlignedPlanesIntersection(planes);

        if (result == 0)
            cout << "Intersection of the semi-planes is empty!\n";
        else if (result == 1)
            cout << "Intersection of the semi-planes has a finite area!\n";
        else
            cout << "Intesection of the semi-planes has an infinite area!\n";
    }
    return 0;
}