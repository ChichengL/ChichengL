#include<bits/stdc++.h> 
#define mod 1000000007
using namespace std;

int C(int a,int b){
    int res = 1;
    int t = a;

    while(a>t-b){
      res = (long long)(res%mod * a)%mod;
      a--;
    }
    while(b>0){
      res = res / b;
      b--;
    }
    return res;
}

int main(){
  int n;
  cin >> n;
  int res = 0;

  if(n<9)printf("0");
  else if(n==9) printf("1");
  else{
    int cur = 3;
    while(n>cur*3){
      res  = (res%mod + (long long)26*C(cur+n-cur*3,n-cur*3)%mod) % mod;
      cur+=1;
    }
    if(n==cur*3) res ++;
    printf("%d",res);
  }
  
  return 0;
}