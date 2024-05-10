int g (int n) {
return n ^ (n >> 1);
}
int rev_g (int g) {
int n = 0;
for (; g; g >>= 1)
n ^= g;
return n;
}
//property:g(i)=g(i-1)^(1 << lsb(i))