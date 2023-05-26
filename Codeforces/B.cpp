#include<iostream>
#include<algorithm>
#include<deque>
#include<numeric>
using namespace std;

void solve()
{
  int n,k;
  cin >> n >> k;
  long long a[n+1]={0};
  for (int i = 1; i <= n; i++)
  {
    /* code */
    cin >> a[i];
  }
  sort(a+1,a+1+n);
  for(int i = 1; i <= n; i ++) a[i]+=a[i-1];
  long long ans = 0;
  int L = 0, R = n - k;
  while(R<=n)
  {
    ans = max(a[R]-a[L],ans);
    R++;
    L+=2;
  }
  cout << ans << '\n';
}

int main()
{
  int t;
  cin >> t;
  while(t--)
  {
    solve();
  }
}