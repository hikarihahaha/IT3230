#include<iostream>
using namespace std;

long long giaithua(int n){
    if(n > 1) return n*giaithua(n-1);
    else return 1;
}
int main(){
    int n;
    do{
        cin >> n;
        if (n == 0) break;
        cout << giaithua(n) << endl;
    } while(1);
    return 0;
}