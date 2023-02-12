#include<iostream>
#include<algorithm>
#include<unordered_map>

using namespace std;
unordered_map<int,int>primes;
const int mod = 1e9+7;
int main()
{
  int n;
  cin >> n;
  while(n -- )
  {
    int x;
    cin >> x;
    for(int i = 2; i <=x/i; i ++)
    {
        while(x%i == 0)
        {
          x/=i;
          primes[i] ++;
        }
    }
    if(x>1) primes[x] ++;
  }
  long long res = 1;
  for( auto prime: primes)
  {
    long long p = prime.first, a = prime.second, t = 1;
    while(a--) t = (t*p+1)%mod;
    res = res * t % mod;
  }
  cout << res;

  return 0;
}