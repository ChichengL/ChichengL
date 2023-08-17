#include<iostream>
#include<cmath>
using namespace std;
using ll =long long;
#define mod 100000000;
ll fastpower(ll base,ll power){
  ll result=1;
  while(power>0){
    if(power&1){
      result=result*base;
    }
    power>>=1;
    base=base*base;
  }
}
int main()
{
  int n,m;
  scanf("%d%d",&n,&m);
  //int a=1;
  // for(int i=1;i<=n;i++){
  //   a=a*m;
  // }

  //int a=pow(n,m);


  return 0;
}