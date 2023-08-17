#include<iostream>

using namespace std;
typedef long long LL;
int exgcd(int a,int b,int &x,int &y)
{
  if(b==0)
  {
    x = 1, y = 0;
    return a;
  }
  int d = exgcd(b,a%b,y,x);
  y -=a/b*x;
  return d;
}


int main()
{
  int n;
  cin >> n;
  while(n -- )
  {
    int a,b,x,y,m;              // ax + my = b;
                                // ax0 + my0 = b;
    cin >> a >> b >> m;
    int d = exgcd(a,m,x,y);     //  a(x-x0)/gcd(a,m) == m(y-y0) / gcd(a,m);a/gcd(a,m)与m/gcd(a,m)互质所以  (x-x0) 一定包含 m / gcd(a,m)这个因子
    if(b % d)puts("impossible");  //裴蜀定理 说明了对任何 整数 a、b和它们的最大公约数 d，关于 未知数 x和y的线性不定方程（称为裴蜀等式）：若a,b是整数,且 gcd (a,b)=d，那么对于任意的整数x,y,ax+by都一定是d的倍数，特别地，一定存在整数x,y，使ax+by=d成立。
    //b % d 不为0 则 b不是d的倍数 则 b ≠ ax + by 
    else cout << (LL)x*(b/d)%m << endl;
  }

  return 0;
}