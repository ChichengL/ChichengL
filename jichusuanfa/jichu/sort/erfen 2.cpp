#include<iostream>
#include<cmath>
using namespace std;
int main()
{
  double x;
  scanf("%lf",&x);
  if(x>=0){
  double y=pow(x,1.0/3);
  printf("%.6lf",y);
  }else{
    x*=-1;
    double y=pow(x,1.0/3);
    printf("-%.6lf",y);
  }
  return 0;
}