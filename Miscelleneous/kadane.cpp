int kadane(vector<int>v){
	int max_now=0,cur_max=0;
	for(int i=0;i<(int)v.size();i++){
		cur_max=max(cur_max+v[i],v[i]);
		max_now=max(cur_max,max_now);
	}
	return max_now;
}