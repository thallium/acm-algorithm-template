//given some words and a passage, find how many words appeared in the passage
#include<bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define ms(a, x) memset(a, x, sizeof(a))
#define endl '\n'
using namespace std;

const int N=1e6+5;
namespace AC{
    int tr[N][26],tot=0;
    int e[N],fail[N];
    queue<int> q;
    void ini(){
        ms(tr,0);
        ms(fail,0);
        ms(e,0);
        tot=0;
    }
    void insert(string s){
        int u=0;
        forn(i,s.length()){
            int c=s[i]-'a';
            if(tr[u][c]==0) tr[u][c]=++tot;
            u=tr[u][c];
        }
        e[u]++;
    }
    void build(){
        forn(i,26) if(tr[0][i]) q.push(tr[0][i]);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            forn(i,26){
                if(tr[u][i]){
                    fail[tr[u][i]]=tr[fail[u]][i];
                    q.push(tr[u][i]);
                }
                else tr[u][i]=tr[fail[u]][i];
            }
        }
    }
    int query(string t){
        int u=0,res=0;
        forn(i,t.length()){
            u=tr[u][t[i]-'a'];
            for(int j=u;j&&e[j]!=-1;j=fail[j]){
                res+=e[j];
                e[j]=-1;
            }
        }
        return res;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    AC::ini();
    int n;
    cin>>n;
    string st;
    while(n--){
        cin>>st;
        AC::insert(st);
    }
    AC::build();
    cin>>st;
    cout<<AC::query(st)<<endl;
    return 0;
}
