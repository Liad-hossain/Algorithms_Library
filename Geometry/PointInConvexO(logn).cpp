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
    // for a point o and strictly convex polygon p returns:
    //  -1 if o is strictly inside p
    //  0 if o is on a segment of p
    //  1 if o is strictly outside p
    // computes in O(logn) for counter-clockwise direction
    inline int pointInConvex(Point &x, Polygon &p){   
        int n = p.size();
        if (n < 3)
            return 1;
        int a =cross(p[1]-p[0], x-p[0]), b =cross(p[n-1]-p[0],x-p[0]);
        if (a < 0 || b > 0)
            return 1;
        int l = 1, r = n - 1;
        while (l + 1 < r)
        {
            int mid = l + r >> 1;
            if (cross(p[mid]-p[0], x-p[0]) >= 0)
                l = mid;
            else
                r = mid;
        }
        int k =cross(p[r]-p[l], x-p[l]);
        if(k<0)return 1;
        if(k==0)return 0;
        if (l == 1 && a == 0)
            return 0;
        if (r == n - 1 && b == 0)
            return 0;
        return -1;
    }

} // namespace Polygonal