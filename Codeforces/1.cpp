#include<bits/stdc++.h>
using namespace std;

int main()
{
  vector<pair<int,int>>res;
  for(int i = 1; i <= 5; i ++)
  {
    res.push_back({i,i*2});
  }
  vector<pair<int,int>>::iterator s = res.begin();

  for(int i = 1; i <= n; i ++)
    if(*(s.first)==i) *(s.first)++;
  for(auto p: res)
  {
    cout <<p.first << ' ' << p.second <<'\n';
  }
}