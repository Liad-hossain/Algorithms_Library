#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
using namespace __gnu_pbds;
template <class T>
using oset = tree<T, null_type, less<T>, rb_tree_tag,
tree_order_statistics_node_update>;
#define debug(x) cout<<(#x)<<" is "<<(x)<<endl;
struct custom_hash {
 static uint64_t splitmix64(uint64_t x) {
   x += 0x9e3779b97f4a7c15;
   x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
   x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
   return x ^ (x >> 31);
 }
 size_t operator()(uint64_t x) const {
   static const uint64_t FIXED_RANDOM =
   chrono::steady_clock::now().time_since_epoch().count();
   return splitmix64(x + FIXED_RANDOM);
 }
};

mt19937 rng(chrono::steady_clock::now().
            time_since_epoch().count());
long long x=
uniform_int_distribution<long long>(l, r)(rng);
