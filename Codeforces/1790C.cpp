#include<iostream>
#include<algorithm>

using namespace std;

void solve()
{
  int n,cnt = 1;
  cin >> n;
  char s[100][100];
  for(int i = 0; i < n; i ++)
    for(int j = 0; j < n-1; j ++)
      cin >> s[i][j];
  // for(int i = 0; i < n; i ++)
  //   puts(s[i]); 
  for(int i = 1; i <= n; i ++) cnt*=i;
  string str="";
  for(int i = 1; i <= n; i ++)
  {
    str+=i+'0';
  }
  bool suc = false;
  for(int i = 1; i <= cnt; i ++)
  {
    next_permutation(str.begin(),str.end());
    bool f = true;
    for(int j = 0; j < n; j ++)
    {
      if(str.find(s[i])==string::npos) f = false;
    }
    if(f)
    {
      suc = true;
      break;
    }
  }
  for(auto x:str) cout << x<< ' ';
}

int main()
{
  int t;
  cin >> t;
  while(t--) solve();
}