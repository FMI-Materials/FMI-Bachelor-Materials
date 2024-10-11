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

    /**
     * Returns the support line of the semiplane
     */
    double GetSupportLine() const {
        return -b / a;
    }

    /**
     * Returns true if the point is contained in the half-plane.
     */
    bool Contains(double x, double y) {
        if (is_vertical)
            return a * y + b < 0;
        return a * x + b < 0;
    }
};

/**
 * Takes a point and a bunch of vertical and
 * orizontal lines, and returns the minimal area
 * or a rectangle strictly including the point, or
 * -1 if no such point exists
 */
double GetMinimalEnclosingRectangleArea(const vector<Plane>& planes, double x, double y)
{
    // Best rectangle found so far.
    double x_lo = -infinity, x_hi = infinity;
    double y_lo = -infinity, y_hi = infinity;

    for (Plane p : planes) {
        // If the plane doesn't contain our point just skip it.
        if (!p.Contains(x, y))
            continue;
            
        // Coordonates of the vertical / orizontal line.
        double l = p.GetSupportLine();

        // Vertical line. Update x.
        if (!p.is_vertical) {
            if (l < x)
                x_lo = max(x_lo, l);
            if (l > x)
                x_hi = min(x_hi, l);
        }
        else { // Orizontal line. Update y.
            if (l < y)
                y_lo = max(y_lo, l);
            if (l > y)
                y_hi = min(y_hi, l);
        }
    }

    if (min(x_lo, y_lo) < -infinity / 2 || max(y_hi, y_hi) > infinity / 2)
        return -1;
    
    return (x_hi - x_lo) * (y_hi - y_lo);
}

int main()
{
    int t;
    cin >> t;

    // All tests.
    while (t--) {
        // Read query point.
        double x, y;
        cin >> x >> y;

        // Read planes.
        int n;
        cin >> n;
        vector <Plane> planes(n);
        for (auto& p : planes)
            p.read();

        // Compute answer.
        double result = GetMinimalEnclosingRectangleArea(planes, x, y);

        if (result < 0)
            cout << "There isn't any rectangle w/ the required property!\n";
        else
            cout << "There is a rectangle, and its area is at least " << result << "!\n";
    }
    return 0;
}