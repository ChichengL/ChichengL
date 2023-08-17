#include<iostream>
using namespace std;

const int N=20;
bool row[N],col[N],dg[N],udg[N];
char g[N][N];
int n;
void dfs(int x,int y,int u)
{
  if(y==n)y=0,x++;
  if(x==n)
  {
    if(u==n)
    {
      for(int i=0;i < n;i ++)puts(g[i]);
      puts("");
    }
    return ;
  }
  //不放皇后
  dfs(x,y+1,u);

  //放皇后
  if(!row[x]&&!col[y]&&!dg[y-x+n]&&!udg[x+y])//dg相当于y=x+c  c=y-x 但是这里y-x可能为负数所以加上n udg相当于y=-x+c  c=x+y
  {
    g[x][y]='Q';
    row[x]=col[y]=udg[x+y]=dg[n - x + y]=true;
    dfs(x,y+1,u+1);
    row[x]=col[y]=udg[x+y]=dg[n - x + y]=false;
    g[x][y]='.';
  }
}
int main()
{
  cin>>n;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      g[i][j]='.';
  dfs(0,0,0);
  return 0;
}