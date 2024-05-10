//extended version to find x,y such that ax+by=gcd(a, b)
int extended_gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  int x1, y1,d = extended_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}
//Find the total number of solutions of ax+by+c=0,
//where x1<=x<=x2 and y1<=y<=y2
int count_solutions(int a,int b,int c,int x1,int x2,int y1,int y2){
  if(!a && !b){
    if(c)return 0;
    return (x2-x1+1)*(y2-y1+1);
  }

  if(!a){
    if(c%b)return 0;
    c=-c/b;
    if(c>=y1 && c<=y2)return x2-x1+1;
    return 0;
  }

  if(!b){
    if(c%a)return 0;
    c=-c/a;
    if(c>=x1 && c<=x2)return y2-y1+1;
    return 0;
  }
  int x,y;
  int g=extended_gcd(a,b,x,y);
  if(c%g==0){
		x *= (-c / g); y *= (-c / g);
		b /= g; a /= g;
		swap(a, b); // x + ka, y - kb
		double p = (x1 - x) / (double)a, q = (x2 - x) / (double)a;
		if (p > q) swap(p, q);
		x1 = (int)ceil(p);
		x2 = (int)floor(q);

		p = (y - y1) / (double)b; q = (y - y2) / (double)b;
		if (p > q) swap(p, q);
		y1 = (int)ceil(p);
		y2 = (int)floor(q);

		x1 = max(x1, y1); x2 = min(x2, y2);
		return max(0LL, x2 - x1 + 1);
  }
  return 0;
}
//find a solution of a Linear Diophantine Equation ax+by=c
bool lde(int a, int b, int c, int &x, int &y) {
  int d = extended_gcd(abs(a), abs(b), x, y);
  if (c % d) return false;
  x *= c / d; y *= c / d;
  if (a < 0) x = -x;
  if (b < 0) y = -y;
  return true;
}
//Exists only if gcd(a,m)=1;
int inv_mod(int a, int m){
  int x, y;
  extended_gcd(a,m, x, y);
  return (m + x % m) % m;
}
// solve ax = b (mod m)
int lce(int a, int b, int m) {
  int d = gcd(a, m);
  if (d != 1){
    if (b % d) return -1;
    a /= d; b /= d; m/= d;
  }
  return b * inv_mod(a, m) % m;
}
