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
    Polygon poly;
    //order the points which can make a simple polygon if possible
    bool compare(Point a,Point b)
    {
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

} // namespace Polygonal
