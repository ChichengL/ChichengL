#include<iostream>
using namespace std;
int main()
{
  double x;
  scanf("%lf",&x);
  double l=-10000,r=10000;
  double mid=(l+r)/2;
  while(r-l>=1e-7){
    mid=(l+r)/2;
    if(mid*mid*mid<=x)l=mid;
    else r=mid;
  }
  printf("%.6lf",l);
}