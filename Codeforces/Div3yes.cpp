#include<bits/stdc++.h>

using namespace std;

// char a[1010];
void solve()
{
  string a;
  cin >> a;
  char be=a[0];
  if(be=='Y'||b=='s'||b=='e')
  {
    for(int i = 1; i <a.length();i++)
    {
      if(be=='Y'&&a[i]!='e'){
        puts("NO");
        return ;
      }
      if(be=='s'&&a[i]!='Y'){
        puts("NO");
        return ;
      }
      if(be=='e'&&a[i]!='s')
      {
        puts("NO");
        return ;
      }
      be=a[i];
    }
    puts("YES");
  }else{
    puts("NO");
  }
}

int main()
{
  int n;
  cin >> n;
  while(n--)
  {
    solve();
  }
  return 0;
}