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
 * Have to be stricly inside each 3 points.
 * This works because the polygon is convex.
 * @return: -1 if inside, 0 if on the edges, 1 if outside.
 */
int CheckPointInPolygon(Point p, const vector <Point>& lower, const vector <Point>& upper)
{
    // Too far left or too far right.
    if (lower[0].first > p.first || lower.back().first < p.first)
        return 1;

    // Checks the position of a point with respect to a left-right envelope.
    // 1 -> above, 0 -> on, -1 -> below
    auto check_p_line = [&](const vector <Point>& v) {
        int id = 0;
        // smart binary search.
        for (int pas = 1, cresc = 1; pas; pas = (cresc ? 2 * pas : pas / 2)) {
            int new_id = id + pas;
            if (new_id + 1 < (int)v.size() && v[new_id].first <= p.first)
                id = new_id;
            else
                cresc = 0;
        }

        double ccw = CCW(v[id], v[id + 1], p);
        if (abs(ccw) < EPS)
            return 0;
        if (ccw > 0)
            return 1;
        return -1;
    };

    // Check position relative to the upper envelope and the lower envelope.
    int up = check_p_line(upper);
    int lo = check_p_line(lower);

    // On one of the envelopes
    if (up == 0 || lo == 0)
        return 0;

    // Outside.    
    if (up == 1 || lo == -1)
        return 1;

    // Inside.
    return -1;
}

// returns lower envelope and upper envelope.
pair <vector <Point>, vector <Point>> GetPolygon()
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

    // Extract envelopes.
    vector <Point> lower_env, upper_env;
    for (int i = p_min; i != p_max; i = (i + 1) % n)
        lower_env.push_back(v[i]);
    for (int i = p_max; i != p_min; i = (i + 1) % n)
        upper_env.push_back(v[i]);
    lower_env.push_back(v[p_max]);
    upper_env.push_back(v[p_min]);

    reverse(upper_env.begin(), upper_env.end());
    return { lower_env, upper_env };
}

int main()
{
    auto [lo, up] = GetPolygon();

    while (1) {
        Point p;
        cout << "Care e punctul pe care il verificati? ";
        cin >> p.first >> p.second;

        int ans = CheckPointInPolygon(p, lo, up);

        if (ans == 0)
            cout << "Punctul este pe poligon\n";
        else if (ans == -1)
            cout << "Punctul este in poligon\n";
        else
            cout << "Punctul este inafara!\n";
    }
    return 0;
}

/*

Please enter the number of points: 4
0 0
10 0
15 5
5 10
Care e punctul pe care il verificati? 0 0
Punctul este pe poligon
Care e punctul pe care il verificati? 5 0
Punctul este pe poligon
Care e punctul pe care il verificati? -10 0
Punctul este inafara!
Care e punctul pe care il verificati? 6 9
Punctul este in poligon
Care e punctul pe care il verificati? 6 10
Punctul este inafara!
Care e punctul pe care il verificati? 100 100
Punctul este inafara!
*/