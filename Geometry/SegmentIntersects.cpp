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
        Point P = p.a, v = p.b - p.a, Q = q.a, w = q.b - q.a;
        Point u = P - Q;
        if(dcmp(cross(v, w))==0)
            return false;
        o = P + v * (cross(w, u) / cross(v, w));
        if(onSegment(p.a, q) || onSegment(p.b, q))
            return true;
        if(onSegment(q.a, p) || onSegment(q.b, p))
            return true;

        double c1 = cross(p.b - p.a, q.a - p.a);
        double c2 = cross(p.b - p.a, q.b - p.a);
        double c3 = cross(q.b - q.a, p.a - q.a);
        double c4 = cross(q.b - q.a, p.b - q.a);
        return ((dcmp(c1) * dcmp(c2) < 0) && (dcmp(c3) * dcmp(c4) < 0));
    }

} // namespace Linear