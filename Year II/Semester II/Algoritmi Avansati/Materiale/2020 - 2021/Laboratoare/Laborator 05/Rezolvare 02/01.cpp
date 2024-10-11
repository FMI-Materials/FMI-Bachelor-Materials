#include <bits/stdc++.h>
using namespace std;

typedef pair <double, double> Point;
const double EPS = 1e-6;

// Pozitive if a, b and c are in counter clockwise order.
int CCW(Point a, Point b, Point c)
{
    b.first -= a.first;
    b.second -= a.second;
    c.first -= a.first;
    c.second -= a.second;

    return b.first * c.second - b.second * c.first;
}

int main()
{
    Point P, Q, R;
    cin >> P.first >> P.second;
    cin >> Q.first >> Q.second;
    cin >> R.first >> R.second;

    double ccw = CCW(P, Q, R);

    if (abs(ccw) < EPS)
        cout << "Puncte coliniare!\n";
    else if (ccw < 0)
        cout << "Viraj dreapta!\n";
    else
        cout << "Viraj stanga!\n";

    return 0;
}