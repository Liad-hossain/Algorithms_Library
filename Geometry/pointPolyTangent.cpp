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
long long sqDist(Point P, Point Q){
    return (P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y);
}


// returns 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(Point a, Point b, Point c){
    return dcmp(cross(b - a, c - a));
}


typedef vector<Point> Polygon;
namespace Polygonal
{
    // Tested : https://toph.co/p/cover-the-points
    // Calculate [ACW, CW] tangent pair from an external point
    constexpr int CW = -1, ACW = 1;
    bool isGood(Point u, Point v, Point Q, int dir) { return orient(Q, u, v) != -dir; }
    Point better(Point u, Point v, Point Q, int dir) { return orient(Q, u, v) == dir ? u : v; }
    Point pointPolyTangent(const Polygon &pt, Point Q, int dir, int lo, int hi) {
        while(hi - lo > 1) {
        int mid = (lo + hi) / 2;
        bool pvs = isGood(pt[mid], pt[mid - 1], Q, dir);
        bool nxt = isGood(pt[mid], pt[mid + 1], Q, dir);

        if(pvs && nxt) return pt[mid];
        if(!(pvs || nxt)) {
            Point p1 = pointPolyTangent(pt, Q, dir, mid + 1, hi);
            Point p2 = pointPolyTangent(pt, Q, dir, lo, mid - 1);
            return better(p1, p2, Q, dir);
        }

        if(!pvs) {
            if(orient(Q, pt[mid], pt[lo]) == dir)         hi = mid - 1;
            else if(better(pt[lo], pt[hi], Q, dir) == pt[lo])   hi = mid - 1;
            else  lo = mid + 1;
        }
        if(!nxt) {
            if(orient(Q, pt[mid], pt[lo]) == dir)         lo = mid + 1;
            else if(better(pt[lo], pt[hi], Q, dir) == pt[lo])   hi = mid - 1;
            else  lo = mid + 1;
        }
        }

        Point ret = pt[lo];
        for(int i = lo + 1; i <= hi; i++) ret = better(ret, pt[i], Q, dir);
        return ret;
    }
    // [ACW, CW] Tangent
    pair<Point, Point> pointPolyTangents(const Polygon &pt, Point Q) {
        int n = pt.size();
        Point acw_tan = pointPolyTangent(pt, Q, ACW, 0, n - 1);
        Point cw_tan = pointPolyTangent(pt, Q, CW, 0, n - 1);
        return make_pair(acw_tan, cw_tan);
    }
} // namespace Polygonal
