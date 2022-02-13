#include <bits/stdc++.h>
using namespace std;

vector<int>value,lt,start,endd;
int tim;
vector<long>ftree;

void dfs(int node, int p, vector<int>adj[]){
    start[node] = tim;
    lt[tim++] = value[node];
    for(int c : adj[node]){
        if(c != p){
            dfs(c,node,adj);
        }
    }
    endd[node] = tim;
    lt[tim++] = value[node];
}

long sumFt(int i){
    long sum = 0;
    while(i > 0){
        sum += ftree[i];
        i -= (i & -i);
    }
    return sum;
}

void addFt(int i, long val){
    while(i < lt.size()){
        ftree[i] += val;
        i += (i & -i);
    }
}

void buildFt(){
    for(int i = 1; i<tim; i++){
        addFt(i,lt[i]);
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    value.resize(n+1);
    lt.resize(2*n+5);
    start.resize(n+1);
    endd.resize(n+1);
    tim = 1;

    vector<int>adj[n+1];
    for(int i = 1; i<=n; i++)cin>>value[i];

    for(int i = 1; i<n; i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0,adj);
    ftree.resize(lt.size());
    buildFt();

    while(q-->0){
        int t;
        cin>>t;
        if(t == 1){
            int v,val;
            cin>>v>>val;

            long delta = val;
            delta -= value[v];

            value[v] = val;
            addFt(start[v],delta);
            addFt(endd[v],delta);
        }else{
            int v;
            cin>>v;
            long sum = sumFt(endd[v])-sumFt(start[v]-1);
            sum = sum/2;
            cout<<sum<<"\n";
        }
    }

    return 0;
}