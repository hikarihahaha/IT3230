#include<iostream>
using namespace std;
int count = 0;
void biendoi(int n, int k){
    if(k==0) count++;
    else{
        biendoi(n*2, k-1);
        if((n-1)%3==0 && ((n-1)/3) % 2 == 1)
            biendoi((n-1)/3, k-1);
    }
}
int main(){
    int n, k;
    cin >>n >> k;
    biendoi(n,k);
    cout << count;
    return 0;
}