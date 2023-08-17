#include<bits/stdc++.h>
using namespace std;
 const int N=1e5+10;
 int s[N],h[N];
vector<int>a;
int n;
void dfs(int k)
{
  if(k>n){
    for(int i=0;i<n;i++){
      cout<<a[i]<<' ';
    }
    puts("");
    return ;
  }
  for(int i=1;i<=n;i++)
  {
    if(!h[i]){
      a.push_back(i);
      h[i]=1;
      dfs(k+1);
      h[i]=0;
      a.pop_back();
    }
  }
}

int main()
{
  cin>>n;
  dfs(1);
  return 0;
}