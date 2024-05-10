const double PI = acos(-1), EPS = 1e-9;
int dcmp(double x)
{
    return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); };
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator*(const long long p) const { return Point(x * p, y * p); }
    Point operator*(const double p) const { return Point(x * p, y * p); }
    Point operator/(const double p) const { return Point(x / p, y / p); }

    bool operator==(const Point &p) const { return dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0; }
    bool operator!=(const Point &p) const { return !(*this == p); }
    bool operator<(const Point &p) const { return dcmp(x - p.x) < 0 || (dcmp(x - p.x) == 0 && dcmp(y - p.y) < 0); }
    bool operator>(const Point &p) const { return p < *this; }
    bool operator<=(const Point &p) const { return *this < p || *this == p; }
    bool operator>=(const Point &p) const { return *this > p || *this == p; }
    friend istream &operator>>(istream &is, Point &p) { return is >> p.x >> p.y; }
    friend ostream &operator<<(ostream &os, const Point &p) { return os << p.x << " " << p.y; }
};

double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double length(Point a) { return sqrt(dot(a, a)); }
double sqLength(Point a) { return dot(a, a); }
double distance(Point a, Point b) { return length(a - b); }
double angle(Point p) { return atan2(p.y, p.x); }
double sqDist(Point P, Point Q){
    return (P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y);
}

typedef vector<Point> Polygon;
namespace Polygonal
{
    // Need for graham scan
    //Graham Scan works well for integers
    Polygon poly;
    stack<Point> S;
    Point nextToTop()
    {
        Point P = S.top();
        S.pop();
        Point res = S.top();
        S.push(P);
        return res;
    }

    double calc(Point A, Point B, Point C)
    {
        double a = sqrt((double)sqDist(A, B));
        double b = sqrt((double)sqDist(B, C));
        double c = sqrt((double)sqDist(C, A));
        return acos((b * b - c * c - a * a) / (-2 * a * c));
    }
    int orientation(Point P, Point Q, Point R)
    {
        long long ret = (Q.y - P.y) * (R.x - Q.x) - (Q.x - P.x) * (R.y - Q.y);
        if (ret < 0)
            return 2;
        if (ret > 0)
            return 1;
        return ret;
    }
    bool cmp(Point X, Point Y)
    {
        int ret = orientation(poly[0], X, Y);
        if (ret == 0)
        {
            long long dist1 = sqDist(poly[0], X);
            long long dist2 = sqDist(poly[0], Y);
            return dist1 < dist2;
        }
        else if (ret == 2)
            return true;
        else return false;
    }

    void grahamScan(Polygon &ch)
    {
        int ymin = poly[0].y, index = 0;
        int N = poly.size();
        for (int i = 1; i < N; i++)
        {
            if (poly[i].y < ymin || (poly[i].y == ymin && poly[i].x < poly[index].x))
            {
                ymin = poly[i].y;
                index = i;
            }
        }

        swap(poly[0], poly[index]);
        sort(&poly[1], &poly[N], cmp);
        S.push(poly[0]);

        for (int i = 1; i < N; i++)
        {
            while(S.size()>1&&orientation(nextToTop(),S.top(),poly[i])!=2)S.pop();
            S.push(poly[i]);
        }

        while (!S.empty())
        {
            ch.push_back(S.top());
            S.pop();
        }
    }
} // namespace Polygonal
