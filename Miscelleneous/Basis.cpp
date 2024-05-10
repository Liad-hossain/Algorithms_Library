struct Basis{
    static const int B=30;
    int basis[B],sz=0;
    void init(){
        memset(basis,0,sizeof(basis));
    }
    void init(int x){
        memset(basis,0,sizeof(basis));
        insert(x);
    }
    void insert(int mask){
        for(int i=B-1;i>=0;i--){
            if(mask>>i&1){
                if(basis[i])mask^=basis[i];
                else{
                    basis[i]=mask;
                    ++sz;
                    break;
                }
            }
        }
    }
    int max_xor(){
        int ans=0;
        for(int i=B-1;i>=0;i--){
            ans=max(ans,ans^basis[i]);
        }
        return ans;
    }
    void merge(const Basis &a){
        for(int i=0;i<B;i++){
            if(a.basis[i])insert(a.basis[i]);
        }
    }
};