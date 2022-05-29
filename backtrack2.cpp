#include<bits/stdc++.h>
using namespace std;
 
int n;
int a[16][16];
bool visited[16] = {false};
int res = INT_MAX;
void input(){
    cin >>n;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j)
            cin >> a[i][j];
    }
}
 
bool checkz(){
    for(int i=1;i<=n;i++){
        if (visited[i] == false){
            return false;
        }
    }
    return true;
}
 
void Try(int u,int cnt){
    
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    input();
    process();

    return 0;
}