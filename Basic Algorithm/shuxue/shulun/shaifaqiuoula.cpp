#include<iostream>
using namespace std;
typedef long long LL;
const int N = 1e6+10;
int phi[N];
bool st[N];
int prime[N],cnt;

LL get_eulers(int n)
{
  LL res = 0;
  phi[1] = 1;
  for(int i = 2; i <= n; i ++)
  {
    if(!st[i])
    {
      prime[cnt ++ ] = i;
      phi[i] = i - 1;
    }
    for(int j = 0; prime[j]<= n/i; j ++)
    {
      st[prime[j]*i] = true;
      if(i%prime[j] == 0) 
      {
        phi[i*prime[j]] = prime[j] * phi[i];
        break;
      }
      else{
        phi[i*prime[j]] = phi[i]*(prime[j]-1);
      }
    }
  }
  for(int i = 1; i <= n; i ++)
  {
    res += phi[i];
  }
  return res;
}

int main()
{
  int n;
  cin >> n;
  cout << get_eulers(n);

  return 0;
}