#include <bits/stdc++.h>
using namespace std;
long bin_search (long arr[], long value, long left, long right){
    long ans = -1;
    while(left <= right){ // day so da sap xep
        int mid = (left + right) / 2;
        if (arr[mid] <= value){
            ans = mid;
            left = mid + 1;
        } // th nho pham vi tim kiem ben phai
        else right = mid - 1;// thu nho pham vi tim kiem o ben trai mid
    }
    return ans; 
}
int main(){
    long n, m, check, count;
    cin>>n>>m;
    long a[n+5], b[m+5];
    for(long i=0; i<n; i++) cin >> a[i];
    for(long i=0; i<m; i++) cin >> b[i];
    sort(a, a+n);
    for(long i =0; i<m; i++){
        check = b[i];
        if (check < a[0]) cout << "0" << endl;
        else {
            long location = bin_search(a, check, 0, n-1);
            count = location + 1;
            cout<< count << endl;
        }
    }
    return 0;
}