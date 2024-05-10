int ext_gcd(int a,int b,int *x,int *y){
	if(a==0) {
		*x = 0;*y = 1;
		return b;
	}
	int x1,y1;
	int d=ext_gcd(b%a,a,&x1,&y1);
	*x=y1-(b/a)*x1;
	*y=x1;
	return d;
}
//pair of remainder and mod
pair<int, int> crt(vector<pair<int,int>> &A){
	int n =(int) A.size();
	// Initially x = a_0 (mod m_0)
	int a1 = A[0].first;
	int m1 = A[0].second;
	// Merge the solution with remaining equations
	for(int i=1;i<n;i++) {
		int a2=A[i].first;
		int m2=A[i].second;
		int g=__gcd(m1, m2);
		if(a1%g!=a2%g) return {-1,-1}; // No solution exists
		// Merge the two equationsint p, q;
		int p,q;
		ext_gcd(m1/g,m2/g,&p,&q);
		int mod=m1/g*m2; // LCM of m1 and m2
		// We need to be careful about overflow
  int x=(int)((__int128)a1*(m2/g)%mod*q%mod+
          (__int128)a2*(m1/g)%mod*p%mod)%mod;
		// Merged equation
		a1=x;
		if(a1<0) a1+=mod; //Result is not suppose to be negative
		m1=mod;
	}
	return {a1,m1};
}
void solve(){
	int n;cin>>n;vector<pair<int,int>> a;
	for(int i=1;i<=n;i++){int val,mod;cin>>val>>mod;
	a.push_back({val,mod});}pair<int,int> ans= crt(a);
	// ans.first = the lowest number where the conditions satisfy
	// ans.second = the harmonic number where a valid ans exits

	// if the solution needs to be in range l to r then...
	int res=ans.ff;
	if(ans.ff<l){
		int div=(l-ans.ff+ans.ss-1)/ans.ss;
        res=ans.ff+div*ans.ss;
	}
}
