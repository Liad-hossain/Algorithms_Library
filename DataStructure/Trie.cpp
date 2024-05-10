const int N=2e6+5;
int to[N][2],cnt[N],tot_node=1;
//Here all the binary bits of x are added from MSB
void add(int x){
    int cur=1;
    for(int i=30;i>=0;i--){
        int b=(x&(1<<i))?1:0;
        if(!to[cur][b])to[cur][b]=++tot_node;
        cur=to[cur][b];
        cnt[cur]++;
    }
}
//Here all the binary bits are removed from trie in the order they are added
void remove(int x){
    int cur=1;
    for(int i=30;i>=0;i--){
        int b=(x&(1<<i))?1:0;
        int prev=cur;
        cur=to[cur][b];
        cnt[cur]--;
        if(!cnt[cur])to[prev][b]=0;
    }
}
//It's a query to get the maximum xor with x from the trie
int query(int x){
    int cur=1,res=0;
    for(int i=30;i>=0;i--){
        int b=(x&(1<<i))?0:1;
        if(to[cur][b] && cnt[to[cur][b]]){
            cur=to[cur][b];
            res+=(1<<i);
        }
        else cur=to[cur][b^1];
    }
    return res;
}
