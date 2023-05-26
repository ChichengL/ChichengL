#include<iostream>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while(T--)
  {
    int n,k;
    cin >> n >> k;
    int cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < n; i ++)
    {
      int l,r;
      cin >> l >> r;
      if(l==k)cnt1++;
      if(r==k)cnt2++;
    }
    if(cnt1&&cnt2) puts("YES");
    else puts("NO");
  }
}