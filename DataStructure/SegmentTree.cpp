template <typename T>
struct SegmentTree{
#define ls (si << 1)
#define rs (si << 1 | 1)
#define mid ((ss + se) >> 1)
    struct Info{
        T sum;
        Info() : sum(0) {}
    };
    vector<Info> st;
    vector<bool> isLazy;
    vector<T> Lazy;
    int N;
    SegmentTree(int n) : N(n){
        st.resize(4 * N);
        isLazy.resize(4 * N);
        Lazy.resize(4 * N);
    }
    void combine(Info &cur, Info &l,Info &r){
        cur.sum = max(l.sum, r.sum);
    }
    void push(int si, int l, int r){
        if (!isLazy[si])
            return;

        if (l != r){
            isLazy[ls] = 1;
            isLazy[rs] = 1;
            Lazy[ls] += Lazy[si];
            Lazy[rs] += Lazy[si];
        }

        st[si].sum += Lazy[si];
        Lazy[si] = 0;
        isLazy[si] = 0;
    }
    void build(int si, int ss, int se){
        if (ss == se){
            st[si].sum = 0;
            return;
        }
        build(ls, ss, mid);
        build(rs, mid + 1, se);
        combine(st[si], st[ls], st[rs]);
    }
    Info query(int si, int ss, int se, int l, int r){
        push(si, ss, se);
        if (ss > r || se < l)
            return Info();
        if (ss >= l && se <= r)
            return st[si];
        Info ret;
        Info d1 = query(ls, ss, mid, l, r);
        Info d2 = query(rs, mid + 1, se, l, r);
        combine(ret, d1, d2);
        return ret;
    }
    void update(int si,int ss,int se,int l,int r,T val){
        push(si, ss, se);
        if (ss > r || se < l)
            return;
        if (ss >= l && se <= r){
            isLazy[si] = 1;
            Lazy[si] = val;
            push(si, ss, se);
            return;
        }
        update(ls, ss, mid, l, r, val);
        update(rs, mid + 1, se, l, r, val);
        combine(st[si], st[ls], st[rs]);
    }
    void Build(){
        build(1, 1, N);
    }
    void Update(int l, int r, T val){
        update(1, 1, N, l, r, val);
    }
    T Query(int l, int r){
        return query(1, 1, N, l, r).sum;
    }
};
