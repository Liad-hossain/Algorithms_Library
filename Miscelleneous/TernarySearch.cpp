//On real number
void Ternary_search(){
	/// ekhane answer always double a hoy
	/// ’U’ or ’Ulta U’ ei duita function e kaj kore
	/// 100 ta iteration chalaite hoy
	double l=0,r=1e9;
	lp(i,1,100)
	{
		double mid1=(2*l+r)/3.0;
		double mid2=(l+2*r)/3.0;
		/// For ’U’ function. Find the minimum value
		if(function(mid1)>function(mid2))
			l=mid1;
		else r=mid2;
		/// For ’Ulta U’ function. Find the
		//maximum value
		if(function(mid1)<function(mid2))
			l=mid1;
			else r=mid2;
	}
}
//On Integer number
void Ternary_search(){
	int lo = -1, hi = n;
	while (hi - lo > 1){
	    int mid = (hi + lo)>>1;
	    //For maximum point 'Ulta U'
	    if (f(mid) > f(mid + 1)) 
	         hi = mid;
	    else 
	         lo = mid; 
	}
}