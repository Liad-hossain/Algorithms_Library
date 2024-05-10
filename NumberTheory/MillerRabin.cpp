int binpower(int base,int e,int mod) {
int result=1;base%=mod;
while(e){
if(e & 1)
result = (__int128)result * base % mod;
base = (__int128)base * base % mod;e >>= 1;}
return result;
}
bool check_composite(int n, int a, int d, int s) {
int x = binpower(a, d, n);
if (x == 1 || x == n - 1)
return false;
for (int r = 1; r < s; r++) {
x = (__int128)x * x % n;
if (x == n - 1)
return false;}
return true;
};
// best
bool MillerRabin(int n) {
if (n < 2) return false;
int r = 0;
int d = n - 1;
while ((d & 1) == 0) {d >>= 1;r++;}
//for(int a:{2,3,5,7}) //for int
for (int a:{2,3,5,7,11,13,17,19,23,29,31,37}) {
if (n == a) return true;
if (check_composite(n, a, d, r)) return false;}
return true; }
bool MillerRabin(int n, int iter=5) {
if(n<4)return n == 2 || n == 3;
int s = 0;
int d = n - 1;
while ((d & 1) == 0) {d >>= 1;s++;}
for (int i = 0; i < iter; i++) {
int a = 2 + rand() % (n - 3);
if (check_composite(n, a, d, s)) return false;}
return true; }