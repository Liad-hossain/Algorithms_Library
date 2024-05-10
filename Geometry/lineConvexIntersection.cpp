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
namespace Polygonal{
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

typedef vector<Point> Polygon;

namespace Polygonal{
    // For a convex polygon p and a line l, returns a list of segments
    // of p that are touch or intersect line l.
    // the i'th segment is considered (p[i], p[(i + 1) modulo |p|])
    // #1 If a segment is collinear with the line, only that is returned
    // #2 Else if l goes through i'th point, the i'th segment is added
    // If there are 2 or more such collinear segments for #1,
    // any of them (only one, not all) should be returned (not tested)
    // Complexity: O(lg |p|)
    vector<int> lineConvexPolyIntersection(const Polygon &p, Line l) {
        assert((int) p.size() >= 3);
        assert(l.a != l.b);

        int n = p.size();
        vector<int> ret;

        Point v = l.b - l.a;
        int lf = extremePoint(p, rotate90(v));
        int rt = extremePoint(p, rotate90(v) * double(-1));
        int olf = orient(l.a, l.b, p[lf]);
        int ort = orient(l.a, l.b, p[rt]);

        if(!olf || !ort) {
        int idx = (!olf ? lf : rt);
        if(orient(l.a, l.b, p[(idx - 1 + n) % n]) == 0)
            ret.push_back((idx - 1 + n) % n);
        else  ret.push_back(idx);
        return ret;
        }
        if(olf == ort) return ret;

        for(int i=0; i<2; ++i) {
        int lo = i ? rt : lf;
        int hi = i ? lf : rt;
        int olo = i ? ort : olf;

        while(true) {
            int gap = (hi - lo + n) % n;
            if(gap < 2) break;

            int mid = (lo + gap / 2) % n;
            int omid = orient(l.a, l.b, p[mid]);
            if(!omid) {
            lo = mid;
            break;
            }
            if(omid == olo) lo = mid;
            else hi = mid;
        }
        ret.push_back(lo);
        }
        return ret;
    }
}