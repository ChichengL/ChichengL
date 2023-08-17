#include<iostream>

using namespace std;
int cnt;
bool st[1000010];
int primes[1000010];
// void get_primes(int n)//埃氏筛
// {
//   for(int i = 2; i <= n ; i ++) 
//   {
//     if(!st[i])
//     {
//       primes[cnt ++] = i;
//       for(int j = i + i; j <= n; j += i) st[j] = true;
//     }
//   }
// }
void get_primes(int n)//线性筛   只会被最小质因子筛掉一次
{
  for(int i = 2 ;i <= n; i ++)
  {
    if(!st[i])
    {
      primes[cnt ++] = i;
    }
    for(int j = 0;primes[j]<= n / i; j ++)
      {
        st[primes[j]*i] = true;
        if(i % primes[j] == 0) break;
      }
  }
}
int main()
{
  int n;
  cin >> n;
  get_primes(n);

  cout << cnt;
}