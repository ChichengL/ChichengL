#include<iostream>
#include<unordered_map>
using namespace std;

void solve()
{
  unordered_map<char,int>m;
  string s;
  cin >> s;
  int n = s.size();
  for(char &ch : s)
  {
    ++m[ch];
  }
  int cnt = 0;
  for(auto it = m.begin(); it!= m.end(); it++)
  {
    if(it->second>=2) cnt++;
  }
  if(cnt<2) puts("NO");
  else puts("YES");
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