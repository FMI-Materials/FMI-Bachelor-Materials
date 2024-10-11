#include <bits/stdc++.h>
using namespace std;

typedef pair <double, double> Point;
const double EPS = 1e-6;

int CCW(Point a, Point b, Point c)
{
    b.first -= a.first;
    b.second -= a.second;
    c.first -= a.first;
    c.second -= a.second;

    return b.first * c.second - b.second * c.first;
}

/**
 * Ideea:
 * 1. Take the first point to be the one with smallest index.
 * 2. Compute the CH as we would usually.
 * 3. Remove the last few points which shouldn't be there.
 */
vector <Point> ConvexHull(vector <Point> points)
{
    // Position of smallest point, which we know is part of the
    // convex hull.
    int p_min = 0;
    for (int i = 1; i < (int)points.size(); i++)
        if (points[i] < points[p_min])
            p_min = i;
    rotate(points.begin(), points.begin() + p_min, points.end());

    // Now we know the first point of `points` is part of the CH.
    vector <Point> ans;

    // Incrementally adding points.
    for (auto p : points) {
        while (ans.size() >= 2 &&
                CCW(ans[ans.size() - 2], ans.back(), p) <= 0)
            ans.pop_back();
        ans.push_back(p);
    }

    // Now all is OK except the last few points which may have to be
    // removed from the CH.

    while (ans.size() >= 3 && CCW(ans[ans.size() - 2], ans.back(), ans[0]) <= 0)
        ans.pop_back();

    // Computed the new CH. Return the answer.
    return ans;
}

int main()
{
    int n;
    cout << "Cate puncte? ";
    cin >> n;
    vector <Point> points(n);
    
    for (auto& [a, b] : points)
        cin >> a >> b;

    cout << "Inchiderea conexa:\n";

    for (auto [a, b] : ConvexHull(points))
        cout << "  { " << a << ' ' << b << "}\n";
    return 0;
}