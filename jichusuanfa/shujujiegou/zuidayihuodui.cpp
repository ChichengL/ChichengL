#include<iostream>

using namespace std;

const int N=(1e5+10)*31;

int s[N][2],idx,n;
int a[N];
void add(int x)
{
  int p=0;
  for(int i=30;i>=0;i--)
  {
    int u=x>>i&1;
    if(!s[p][u])s[p][u]=++idx;
    p=s[p][u];
  }
}
int query(int x)
{
  int p=0,res=0;
  for(int i=30;i>=0;i--)
  {
    int u=x>>i&1;
    if(s[p][!u]){
      p=s[p][!u];
      res=res*2+!u;
    }
    else{
      p=s[p][u];
      res=res*2+u;
    }
  }
  return res;
}
int main()
{
  scanf("%d",&n);
  for(int i=0;i<n;i++) scanf("%d",&a[i]);

  int res=0;

  for(int i=0;i<n;i++)
  {
    add(a[i]);
    int t=query(a[i]);
    res=max(res,t^a[i]);
  }
  printf("%d",res);
  return 0;
}