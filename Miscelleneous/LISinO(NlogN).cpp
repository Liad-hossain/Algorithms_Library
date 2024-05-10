vector<int> List;
int A[N],LIS[N];
void calculate_LIS(){
List.clear();
for (int i = 0; i < N; i++){
	auto low=lower_bound(List.begin(),List.end(),A[i]);
	LIS[i] = (low - List.begin());
	if (low == List.end()) List.pb(A[i]);
	else *low = A[i];
}}