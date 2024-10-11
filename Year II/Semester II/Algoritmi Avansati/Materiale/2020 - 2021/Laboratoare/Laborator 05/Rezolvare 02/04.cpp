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
 * Returns the convex hull.
 */
vector <Point> ConvexHull(vector <Point> points)
{
    auto get_enveloppe = [&]() {
        vector <Point> v;
        for (auto p : points) {
            while (v.size() >= 2 &&
                    CCW(v[v.size() - 2], v.back(), p) <= 0)
                v.pop_back();
            v.push_back(p);
        }
        v.pop_back();
        return v;
    };

    sort(points.begin(), points.end());
    auto v1 = get_enveloppe();

    reverse(points.begin(), points.end());
    auto v2 = get_enveloppe();

    for (auto i : v2)
        v1.push_back(i);

    return v1;
}

double Dist(Point a, Point b)
{
    return sqrt((b.first - a.first) * (b.first - a.first) +
                (b.second - a.second) * (b.second - a.second));
}

vector <Point> ComputeTSP(vector <Point> points)
{
    set <Point> points_left;
    vector <Point> act = ConvexHull(points);
    for (auto i : points)
        points_left.insert(i);
    for (auto i : act)
        points_left.erase(i);

    // Adding distance to point.
    auto distance_offset = [&](Point p, int poz) {
        double ans = Dist(act[poz], p) + Dist(p, act[(poz + 1) % act.size()]);
        ans -= Dist(act[poz], act[(poz + 1) % act.size()]);
        return ans;
    };

    // Fraction for point.
    auto check_rap_point = [&](Point p, int poz) {
        double ans = Dist(act[poz], p) + Dist(p, act[(poz + 1) % act.size()]);
        ans /= Dist(act[poz], act[(poz + 1) % act.size()]);
        return ans;
    };

    // While not all points are added, check one more point.
    while (!points_left.empty()) {
        // Best point and position found so far.
        double best_rap = 1e18;
        Point best_point;
        int best_poz;

        // Checking best point and edge.
        for (auto i : points_left) {
            // Best position for the point i.
            int id = 0;
            double best_dist = 1e18;

            // Checking all available positions.
            for (int poz = 0; poz < (int)act.size(); poz++) {
                double d_act = distance_offset(i, poz);

                // If the position is better for point i, update.
                if (d_act < best_dist)
                    best_dist = d_act, id = poz;
            }

            // If point i is better than the best point, update.
            double rap_act = check_rap_point(i, id);
            if (rap_act < best_rap)
                best_rap = rap_act, best_point = i, best_poz = id;
        }

        // Inserting point.
        points_left.erase(best_point);
        act.insert(act.begin() + best_poz + 1, best_point);
    }

    return act;
}

// returns lower enveloppe and upper enveloppe.
vector <Point> GetPoints()
{
    int n;
    cout << "Please enter the number of points: ";
    cin >> n;

    vector <Point> v(n);
    for (auto& [a, b] : v)
        cin >> a >> b;

    int p_min = 0, p_max = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] < v[p_min])
            p_min = i;
        if (v[i] > v[p_max])
            p_max = i;
    }
    return v;
}

int main()
{
    auto points = GetPoints();
    auto ans = ComputeTSP(points);

    cout << "Answer: ";
    for (auto i : ans)
        cout << "(" << i.first << ", " << i.second << ")  -->  ";
    cout << "(" << ans[0].first << ", " << ans[0].second << ")\n";
    return 0;
}

/**
 * Input:
    8
    10 0
    4 4
    0 10
    -4 4
    -10 0
    -4 -4
    0 -10
    4 -4
 * Answer:
 (-10, 0)  -->  (-4, -4)  -->  (0, -10)  -->  (4, -4)  -->  (10, 0)  -->  (4, 4)  -->  (0, 10)  -->  (-4, 4)  -->  (-10, 0)
 * 
 */