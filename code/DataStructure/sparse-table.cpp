struct sparse{
    int logn;
    vector<vector<int>> f;
    sparse(const vector<int>& a){
        int n=(int)size(a);
        logn=__lg(n);
        f=vector(n,vector(logn+1,0));
        for(int i=0;i<n;i++) f[i][0]=a[i];
        for (int j = 1; j <= logn; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    }
    int query(int x,int y){
        int s = __lg(y - x + 1);
        return max(f[x][s], f[y - (1 << s) + 1][s]);
    }
};
