#include<iostream>
using namespace std;
typedef long long LL;
const int N = 100010,mod = 1e9+7;
int fact[N],infact[N];

int qmi(int a,int k,int p)
{
  int res = 1;
  while(k)
  {
    if(k&1) res = (LL)res * a % p;
    k>>=1;
    a = (LL) a * a % p;
  }
  return res;
}

int main()
{
  fact[0]=infact[0]=1;//ax≡1(mod n) 逆元的存在可以让乘以这个逆元表示除以这个逆元对应数；
  for(int i = 1; i < N; i ++)
  {
    fact[i] = (LL)fact[i-1] * i % mod;
    infact[i]=(LL)infact[i-1]*qmi(i,mod-2,mod) % mod;
  }
  int n;
  cin >> n;
  while(n -- )
  {
    int a,b;
    cin >> a >> b;
    cout << (LL)fact[a]*infact[b]%mod*infact[a-b]%mod<<'\n';
  }

  return 0;
}