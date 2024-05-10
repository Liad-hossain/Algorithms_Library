const double PI = acos(-1), EPS = 1e-9;
int dcmp(double x){
    return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}
struct Point{
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
//angle between the line of two points and positive x-axis
double angle(Point p,Point q){
    q.x-=p.x,q.y-=p.y;
    if(q.x>=0 && q.y>=0)return atan2(q.y,q.x);
    else if(q.x<=0 && q.y>=0)return PI-atan2(q.y,-q.x);
    else if(q.x<=0 && q.y<=0)return PI+atan2(-q.y,-q.x);
    return 2*PI-atan2(-q.y,q.x);
}
//Angle Between Two Lines
//First Line is p1,p2 & second is p2,p3
double LineAngle(Point p1,Point p2,Point p3){
    double a=(p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y);
    double b=(p3.x-p1.x)*(p3.x-p1.x)+(p3.y-p1.y)*(p3.y-p1.y);
    double c=(p3.x-p2.x)*(p3.x-p2.x)+(p3.y-p2.y)*(p3.y-p2.y);
    double angle=acos((a+b-c)/(2*sqrt(a*b)));
    angle=(angle*180)/PI;
    return angle;
}
double degTorad(double a){
    return a * (PI / 180);
}
double radTodeg(double a){
    return a * (180 / PI);
}
// returns angle between oa, ob in (-PI, PI]
double angleBetween(Point a, Point b){
    double ans = angle(b) - angle(a);
    return ans <= -PI ? ans + 2 * PI : (ans > PI ? ans - 2 * PI : ans);
}

// Rotate a ccw by rad radians
Point rotate(Point a, double rad){
    return Point(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}
// rotate a ccw by angle th with cos(th) = co && sin(th) = si
Point rotatePrecise(Point a, double co, double si){
    return Point(a.x * co - a.y * si, a.x * si + a.y * co);
}
Point rotate90(Point a) { return Point(-a.y, a.x); }
// scales vector a by s such that length of a becomes s
Point scale(Point a, double s){
    return a / length(a) * s;
}

// returns an unit vector perpendicular to vector p
Point normal(Point p){
    double l = length(p);
    return Point(-p.y / l, p.x / l);
}
// returns 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(Point a, Point b, Point c){
    return dcmp(cross(b - a, c - a));
}
// returns true for point above x axis or on negative x axis
bool half(Point p){
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
// to be used in sort() function
bool polarComp(Point p, Point q){
    return make_tuple(half(p), 0) < make_tuple(half(q), cross(p, q));
}
struct Segment{
    Point a, b;
    Segment() { a = {0, 0}, b = {0, 0}; }
    Segment(Point aa, Point bb) : a(aa), b(bb) {}
};
typedef Segment Line;
namespace Linear{
    // returns true if point p is on segment s
    bool onSegment(Point p, Segment s){
        return dcmp(cross(s.a - p, s.b - p)) == 0 && dcmp(dot(s.a - p, s.b - p)) <= 0;
    }
    // returns true if segment p && q touch or intersect
    bool segmentsIntersect(Segment p, Segment q, Point &o){
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
    bool linesParallel(Line p, Line q){
        return dcmp(cross(p.b - p.a, q.b - q.a)) == 0;
    }
    // lines are represented as a ray from a point: (point, vector)
    // returns false if two lines (p, v) && (q, w) are parallel or collinear
    // true otherwise, intersection point is stored at o via reference
    bool lineLineIntersection(Point p, Point v, Point q, Point w, Point &o){
        // static_assert(is_same<Tf, Ti>::value);
        if (dcmp(cross(v, w)) == 0)
            return false;
        Point u = p - q;
        o = p + v * (cross(w, u) / cross(v, w));
        return true;
    }
    // returns false if two lines p && q are parallel or collinear
    // true otherwise, intersection point is stored at o via reference
    bool lineLineIntersection(Line p, Line q, Point &o){
        return lineLineIntersection(p.a, p.b - p.a, q.a, q.b - q.a, o);
    }
    // returns the distance from point a to line l
    double distancePointLine(Point p, Line l){
        return abs(cross(l.b - l.a, p - l.a) / length(l.b - l.a));
    }
    // returns the shortest distance from point a to segment s
    double distancePointSegment(Point p, Segment s){
        if (s.a == s.b)return length(p - s.a);
        Point v1 = s.b - s.a, v2 = p - s.a, v3 = p - s.b;
        if (dcmp(dot(v1, v2)) < 0)
            return length(v2);
        else if (dcmp(dot(v1, v3)) > 0)
            return length(v3);
        else
            return abs(cross(v1, v2) / length(v1));
    }
    // returns the shortest distance from segment p to segment q
    double distanceSegmentSegment(Segment p, Segment q){
        Point o;
        if (segmentsIntersect(p, q, o))
            return 0;
        double ans = distancePointSegment(p.a, q);
        ans = min(ans, distancePointSegment(p.b, q));
        ans = min(ans, distancePointSegment(q.a, p));
        ans = min(ans, distancePointSegment(q.b, p));
        return ans;
    }
    // returns the projection of point p on line l
    Point projectPointLine(Point p, Line l){
        Point v = l.b - l.a;
        return l.a + v * ((double)dot(v, p - l.a) / dot(v, v));
    }
} // namespace Linear

typedef vector<Point> Polygon;
namespace Polygonal{
    double signedPolygonArea(Polygon p){
        double ret = 0;
        for (int i = 0; i < (int)p.size() - 1; i++)
            ret += cross(p[i] - p[0], p[i + 1] - p[0]);
        return ret / 2;
    }
    //if the convex polygon is central symmetry or not
    bool CentralSymmetryConvex(Polygon &p){
        int n=p.size();
        if(n&1)return false;
        for(int i=0;i<n;i++){
            int i2=(i+1)%n;
            int j=(i+n/2)%n;
            int j2=(j+1)%n;
            double dx1=p[i].x-p[i2].x,dy1=p[i].y-p[i2].y;
            double dx2=p[j].x-p[j2].x,dy2=p[j].y-p[j2].y;
            if(fabs(dx1+dx2)<=EPS && fabs(dy1+dy2)<=EPS)continue;
            return false;
        }
        return true;
    }
    //count the number of points on border of a simple polygon
    int borderPoints(Polygon &p){
        int border=0;
        int n=p.size();
        for(int i=0;i<n;i++){
            int dx=abs(p[i].x-p[(i+1)%n].x);
            int dy=abs(p[i].y-p[(i+1)%n].y);
            border+=__gcd(dx,dy);
        }
        return border;
    }
    // given a polygon p of n vertices, generates the convex hull in ch
    // in CCW && returns the number of vertices in the convex hull
    //Monotone Chain Algorithm
    int convexHull(Polygon p, Polygon &ch){
        sort(p.begin(), p.end());
        int n = p.size();
        ch.resize(n + n);
        int m = 0; // preparing lower hull
        for (int i = 0; i < n; i++){
            while (m > 1 && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1])) <= 0)
                m--;
            ch[m++] = p[i];
        }
        int k = m; // preparing upper hull
        for (int i = n - 2; i >= 0; i--){
            while (m > k && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= 0)
                m--;
            ch[m++] = p[i];
        }
        if (n > 1)m--;
        ch.resize(m);
        return m;
    }
    // Need for graham scan
    //Graham Scan works well for integers
    Polygon poly;
    stack<Point> S;
    Point nextToTop(){
        Point P = S.top();
        S.pop();
        Point res = S.top();
        S.push(P);
        return res;
    }
    double calc(Point A, Point B, Point C){
        double a = sqrt((double)sqDist(A, B));
        double b = sqrt((double)sqDist(B, C));
        double c = sqrt((double)sqDist(C, A));
        return acos((b * b - c * c - a * a) / (-2 * a * c));
    }
    int orientation(Point P, Point Q, Point R){
        long long ret = (Q.y - P.y) * (R.x - Q.x) - (Q.x - P.x) * (R.y - Q.y);
        if (ret < 0)return 2;
        if (ret > 0)return 1;
        return ret;
    }
    bool cmp(Point X, Point Y){
        int ret = orientation(poly[0], X, Y);
        if (ret == 0){
            long long dist1 = sqDist(poly[0], X);
            long long dist2 = sqDist(poly[0], Y);
            return dist1 < dist2;
        }
        else if (ret == 2)return true;
        else return false;
    }

    void grahamScan(Polygon &ch){
        int ymin = poly[0].y, index = 0;
        int N = poly.size();
        for (int i = 1; i < N; i++){
            if (poly[i].y < ymin || (poly[i].y == ymin && poly[i].x < poly[index].x)){
                ymin = poly[i].y;index = i;
            }
        }
        swap(poly[0], poly[index]);
        sort(&poly[1], &poly[N], cmp);
        S.push(poly[0]);
        for (int i = 1; i < N; i++){
            while(S.size()>1&&orientation(nextToTop(),S.top(),poly[i])!=2)S.pop();
            S.push(poly[i]);
        }
        while (!S.empty()){
            ch.push_back(S.top());
            S.pop();
        }
    }
    //order the points which can make a simple polygon if possible
    bool compare(Point a,Point b){
        int tt = dcmp(cross(a-poly[0],b-poly[0]));
        if(tt == 0)
        return (length(a-poly[0]) < length(b-poly[0]));
        else return tt > 0;
    }
    bool simplePolygon(Polygon &ch){
        if(poly.size()<3)return false;
        sort(poly.begin(),poly.end());
        sort(poly.begin()+1,poly.end(),compare);
        int tmp = 0,n=poly.size();
        for(int i = n-2;i > 0;i--)
            if(( dcmp(cross((poly[n-1]-poly[0]),(poly[i]-poly[0]))))!=0){
                tmp = i;
                break;
            }
        if(tmp == 0)return false;
        reverse(poly.begin()+tmp+1,poly.end());
        for(int i=0;i<n;i++){
            ch.push_back(poly[i]);
        }
        return true;
    }
    // for a point o and strictly convex polygon p returns:
    //  -1 if o is strictly inside p
    //  0 if o is on a segment of p
    //  1 if o is strictly outside p
    // computes in O(logn) for counter-clockwise direction
    inline int pointInConvex(Point &x, Polygon &p){
        int n = p.size();
        if(n < 3)return 1;
        int a =cross(p[1]-p[0], x-p[0]), b =cross(p[n-1]-p[0],x-p[0]);
        if (a < 0 || b > 0)return 1;
        int l = 1, r = n - 1;
        while (l + 1 < r){
            int mid = l + r >> 1;
            if (cross(p[mid]-p[0], x-p[0]) >= 0)
                l = mid;
            else
                r = mid;
        }
        int k =cross(p[r]-p[l], x-p[l]);
        if(k<0)return 1;
        if(k==0)return 0;
        if (l == 1 && a == 0)return 0;
        if (r == n - 1 && b == 0)return 0;
        return -1;
    }
    // for a point o and polygon p returns:
    //   -1 if o is strictly inside p
    //  0 if o is on a segment of p
    //  1 if o is strictly outside p
    // computes via winding numbers
    int pointInPolygon(Point o, Polygon p){
        using Linear::onSegment;
        int wn = 0, n = p.size();
        for (int i = 0; i < n; i++){
            int j = (i + 1) % n;
            if (onSegment(o, Segment(p[i], p[j])) || o == p[i])return 0;
            int k = dcmp(cross(p[j] - p[i], o - p[i]));
            int d1 = dcmp(p[i].y - o.y);
            int d2 = dcmp(p[j].y - o.y);
            if (k > 0 && d1 <= 0 && d2 > 0)wn++;
            if (k < 0 && d2 <= 0 && d1 > 0)wn--;
        }
        return wn ? -1 : 1;
    }
    // Extreme Point for a direction is the farthest point in that direction
    // poly is a convex polygon, sorted in CCW, doesn't contain redundant points
    // u is the direction for extremeness
    int extremePoint(const Polygon &poly, Point u = Point(0, 1)) {
        int n = (int) poly.size();
        int a = 0, b = n;
        while(b - a > 1) {
        int c = (a + b) / 2;
        if(dcmp(dot(poly[c]-poly[(c+1)%n],u))>=0&&dcmp(dot(poly[c]-poly[(c-1+n)%n],u))>=0)return c;
        bool a_up = dcmp(dot(poly[(a + 1) % n] - poly[a], u)) >= 0;
        bool c_up = dcmp(dot(poly[(c + 1) % n] - poly[c], u)) >= 0;
        bool a_above_c = dcmp(dot(poly[a] - poly[c], u)) > 0;
        if(a_up && !c_up) b = c;
        else if(!a_up && c_up) a = c;
        else if(a_up && c_up) {
            if(a_above_c) b = c;
            else a = c;
        }
        else {
            if(!a_above_c) b = c;
            else a = c;
        }
        }
        if(dcmp(dot(poly[a] - poly[(a + 1) % n], u)) > 0 && dcmp(dot(poly[a] - poly[(a - 1 + n) % n], u)) > 0)
        return a;
        return b % n;
    }
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

    // returns the longest line segment of l that is inside or on the
    // simply polygon p. O(n lg n). TESTED: TIMUS 1955
    double longestSegInPoly(Line l, const Polygon &p)
    {
        using Linear::lineLineIntersection;
        int n = p.size();
        vector<pair<double, int>> ev;
        for (int i = 0; i < n; ++i)
        {
            Point a = p[i], b = p[(i + 1) % n], z = p[(i - 1 + n) % n];
            int ora = orient(l.a, l.b, a), orb = orient(l.a, l.b, b), orz = orient(l.a, l.b, z);
            if (!ora)
            {
                double d = dot(a - l.a, l.b - l.a);
                if (orz && orb)
                {
                    if (orz != orb)
                        ev.emplace_back(d, 0);
                }
                else if (orz)
                    ev.emplace_back(d, orz);
                else if (orb)
                    ev.emplace_back(d, orb);
            }
            else if (ora == -orb)
            {
                Point ins;
                lineLineIntersection(l, Line(a, b), ins);
                ev.emplace_back(dot(ins - l.a, l.b - l.a), 0);
            }
        }
        sort(ev.begin(), ev.end());

        double ret = 0, cur = 0, pre = 0;
        bool active = false;
        int sign = 0;
        for (auto &qq : ev)
        {
            int tp = qq.second;
            double d = qq.first;
            if (sign)
            {
                cur += d - pre;
                ret = max(ret, cur);
                if (tp != sign)
                    active = !active;
                sign = 0;
            }
            else
            {
                if (active)
                    cur += d - pre, ret = max(ret, cur);
                if (tp == 0)
                    active = !active;
                else
                    sign = tp;
            }
            pre = d;
            if (!active)
                cur = 0;
        }

        ret /= length(l.b - l.a);
        return ret;
    }

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
