const int N=1e6+5;
int to[N][26];
int total_node=1;
int cnt[N];
void add(string &s) {
	int cur=1;
	cnt[cur]++;
	for(int i=0;i<(int)s.size();i++) {
		int c=s[i]-'a';
		if(!to[cur][c])to[cur][c]=(++total_node);
		cur=to[cur][c];
		cnt[cur]++;
	}
}
int query(string &t){
	int cur=1;
	for(int i=0;i<(int)t.size();i++){
		int c=t[i]-'a';
		if(!to[cur][c])
			return 0;
		cur=to[cur][c];
	}
	return cnt[cur];
}