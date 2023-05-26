#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;

void solve()
{
  int n,m;
  cin >> n >> m;
  string a,b;
  cin >> a >> b;
  reverse(b.begin(),b.end());
  a = a+b;
  int res = 0;
  for(int i = 1; i < n+m; i ++)
    if(a[i]==a[i-1]) res++;
    if(res>1) puts("NO");
    else puts("YES");
}

int main()
{
  int T;
  cin >> T;
  while(T--) solve();
}