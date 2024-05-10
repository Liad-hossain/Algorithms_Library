struct KMP{
    vector<int>pi;
    KMP(string const& text){
        buildkmp(text);
    }
    void buildkmp(string const& text){
        int n=text.size();
        pi.resize(n);
        for(int i=1;i<n;i++){
            int j=pi[i-1];
            while(j>0 && text[i]!=text[j])j=pi[j-1];
            if(text[i]==text[j])j++;
            pi[i]=j;
        }
    }
};
