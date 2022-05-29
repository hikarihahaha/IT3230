#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<ctype.h>
using namespace std;
/* F(x) = p[0] + p[1] * x + p[2] * x^2 + ... + p[d] * x^d */
	
long n;
double a[13];
double f(double x){
    double res=0;
    for(long i=0; i<=n; i++) res = res + a[i]*pow(x,i);
    return res;
}
int main(){
    double u[100], v[100];
    long tu=0,tv=0;      
    scanf("%ld", &n);
    for (int i=0; i <= n; i++) scanf("%lf", &a[i]);
    if(a[n]>0){  
        u[0]=-1000000;
        v[0]=1000000;
    }
    else{  
    u[0]=1000000;
    v[0]=-1000000;
    } 
    while(v[tv]-u[tu]>0.00001||v[tv]-u[tu]<-0.00001){
        if(f((v[tv]+u[tu])/2)>0){
            tv++;
            v[tv]=(v[tv-1]+u[tu])/2;
        }
        else{
            tu++;
            u[tu]=(v[tv]+u[tu-1])/2;
        }
    }
    printf("%ld",long(u[tu]*1000));
    return 0;
}
