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

// returns 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(Point a, Point b, Point c)
{
    return dcmp(cross(b - a, c - a));
}

struct Segment
{
    Point a, b;
    Segment() { a = {0, 0}, b = {0, 0}; }
    Segment(Point aa, Point bb) : a(aa), b(bb) {}
};
typedef Segment Line;

namespace Linear
{
    // returns true if point p is on segment s
    bool onSegment(Point p, Segment s)
    {
        return dcmp(cross(s.a - p, s.b - p)) == 0 && dcmp(dot(s.a - p, s.b - p)) <= 0;
    }

    // returns true if segment p && q touch or intersect
    bool segmentsIntersect(Segment p, Segment q, Point &o)
    {
        if (onSegment(p.a, q) || onSegment(p.b, q))
            return true;
        if (onSegment(q.a, p) || onSegment(q.b, p))
            return true;

        double c1 = cross(p.b - p.a, q.a - p.a);
        double c2 = cross(p.b - p.a, q.b - p.a);
        double c3 = cross(q.b - q.a, p.a - q.a);
        double c4 = cross(q.b - q.a, p.b - q.a);
        bool ok = ((dcmp(c1) * dcmp(c2) < 0) && (dcmp(c3) * dcmp(c4) < 0));
        if (ok)
        {
            Point P = p.a, v = p.b - p.a, Q = q.a, w = q.b - q.a;
            Point u = P - Q;
            o = P + v * (cross(w, u) / cross(v, w));
        }
        return ok;
    }

    bool linesParallel(Line p, Line q)
    {
        return dcmp(cross(p.b - p.a, q.b - q.a)) == 0;
    }

    // lines are represented as a ray from a point: (point, vector)
    // returns false if two lines (p, v) && (q, w) are parallel or collinear
    // true otherwise, intersection point is stored at o via reference
    bool lineLineIntersection(Point p, Point v, Point q, Point w, Point &o)
    {
        // static_assert(is_same<Tf, Ti>::value);
        if (dcmp(cross(v, w)) == 0)
            return false;
        Point u = p - q;
        o = p + v * (cross(w, u) / cross(v, w));
        return true;
    }

    // returns false if two lines p && q are parallel or collinear
    // true otherwise, intersection point is stored at o via reference
    bool lineLineIntersection(Line p, Line q, Point &o)
    {
        return lineLineIntersection(p.a, p.b - p.a, q.a, q.b - q.a, o);
    }

} // namespace Linear
