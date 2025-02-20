namespace rho {
mt19937 rnd(chrono::steady_clock::now().
time_since_epoch().count());
const int P = 1e6 + 9;
int seq[P];
int primes[P], spf[P];
inline int add_mod(int x, int y, int m) {
return (x += y) < m ? x : x - m;
}
inline int mul_mod(int x, int y, int m) {
int res = (int) (__int128(x) * y % m);
return res;
// int res = x * y - (int)((long double)x * y / m + 0.5) * m;
// return res < 0 ? res + m : res; 
}
inline int pow_mod(int x, int n, int m) {
int res = 1 % m;
for (; n; n >>= 1) {
if (n & 1) res = mul_mod(res, x, m);
x = mul_mod(x, x, m);
}
return res;
}
// O(it * (logn)^3), it = number of rounds performed
inline bool miller_rabin(int n) {
if (n <= 2 || ((n & 1) ^ 1)) return (n == 2);
if (n < P) return spf[n] == n;
int c, d, s = 0, r = n - 1;
for (; !(r & 1); r >>= 1, s++) {}
// each iteration is a round
for (int i = 0; primes[i] < n && primes[i] < 32;
i++) {
c = pow_mod(primes[i], r, n);
for (int j = 0; j < s; j++) {
d = mul_mod(c, c, n);
if (d == 1 && c != 1 && c != (n - 1)) return
false;
c = d;
}
if (c != 1) return false; }
return true; }
void init() {
int cnt = 0;
for (int i = 2; i < P; i++) {
if (!spf[i]) primes[cnt++] = spf[i] = i;
for (int j = 0, k; (k = i * primes[j]) < P; j++)
{
spf[k] = primes[j];
if (spf[i] == spf[k]) break; } } }
// returns O(n^(1/4))
int pollard_rho(int n) {
while (1) {
	int x = rnd() % n, y = x, c = rnd() % n, u = 1,
v, t = 0;
int *px = seq, *py = seq;
while (1) {
*py++ = y = add_mod(mul_mod(y, y, n), c, n);
*py++ = y = add_mod(mul_mod(y, y, n), c, n);
if ((x = *px++) == y) break;
v = u;
u = mul_mod(u, abs(y - x), n);
if (!u) return __gcd(v, n);
if (++t == 32) {
t = 0;
if ((u = __gcd(u, n)) > 1 && u < n) return u;
} }
if (t && (u = __gcd(u, n)) > 1 && u < n) return
u;
} }
vector<int> factorize(int n) {
if (n == 1) return vector <int>();
if (miller_rabin(n)) return vector<int> {n};
vector <int> v, w;
while (n > 1 && n < P) {
v.push_back(spf[n]);
n /= spf[n];
}
if (n >= P) {
int x = pollard_rho(n);
v = factorize(x);
w = factorize(n / x);
v.insert(v.end(), w.begin(), w.end());
}
return v;
} }
void generate_divisor(vector<long long> primes, vector<long long> &divisors){
    sort(primes.begin(), primes.end());
    vector<pair<long long, long long>> pfreq;
    for (int i = 0, j; i < primes.size(); i = j) {
        j = i;
        while (j < primes.size() && primes[i] == primes[j]) j++;
        pfreq.push_back({primes[i], j - i});
    }
    divisors.push_back(1);
    for (auto [prime, count] : pfreq) {
        long long result = 1;
        vector<long long> temp;
        for (int i = 1; i <= count; i++) {
            result *= prime;
            for (auto d : divisors) {
                temp.push_back(d * result);
            }
        }
        for (auto d : temp) {
            divisors.push_back(d);
        }
    }
    sort(divisors.begin(), divisors.end());
}   
rho::init(); // shob test case er age