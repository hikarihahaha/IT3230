#include<bits/stdc++.h>
using namespace std;
#define ll long long 
int a[50][50], m, n;
int *x = (int*)malloc(n * m * sizeof(int));
bool chuaxet[100];
void check(int *x, int m, int n){
    int row = 1, col = 1;
    bool ok = true;
    for(int i=1; i<= m+n-2; ++i){
        if(x[i] == 0) row += 1; //go down
        else col += 1; // go right
        if(a[row][col] == 0 || row > m || col > n)
            ok = false;
            break;
    }
    if(ok){
        for(int i=1; i<= m+n-2; ++i){
            if(x[i]==0) cout << "D";
            else cout<< "R";
        }
        cout << endl;
    }
}

void backtrack(int i){
    for(int j=0; j<=1; ++j){
        x[i] = j;
        if(i == m + n - 2) check(x, m, n);
        else backtrack(i+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    while(m <=0 || n<=0) scanf("%d%d", &m, &n);
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            cin >> a[i][j];
        }
    }
    for(int i=0; i<m; ++i){
        for(int j=0; i<n; ++j){
            x[i*n + j] = a[i][j];
        }
    }
    for(int z=0; z< m*n; ++z){
        cout << x[z] << " ";
    }
    backtrack(0);
    return 0;
}