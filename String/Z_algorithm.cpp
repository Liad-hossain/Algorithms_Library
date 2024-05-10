struct z_algorithm{
    vector<int>z;
    z_algorithm(string const& text){
        z_function(text);
    }
    void z_function(string const& text){
        int n=text.size();
        z.resize(n,0);
        for(int i=1,l=0,r=0;i<n;i++){
            if(i<=r)z[i]=min(r-i+1,z[i-l]);
            while(i+z[i]<n && text[z[i]]==text[i+z[i]])++z[i];
            if(i+z[i]-1>r)l=i,r=i+z[i]-1;              
        }
    }
};
