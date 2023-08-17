#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int s[N],h[N];
int n;
void dfs(int k)
{
  if(k>n){
    for(int i=1;i<=n;i++){
      cout<<s[i]<<' ';
    }
    puts("");
    return ;
  }
  for(int i=1;i<=n;i++)
  {
    if(!h[i]){
      s[k]=i;
      h[i]=1;
      dfs(k+1);
      h[i]=0;
    }
  }
}

int main()
{
  cin>>n;
  dfs(1);
  return 0;
}