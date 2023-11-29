#include<iostream>
using namespace std;

const int N=20;
int path[N];
bool col[N],dg[N],udg[N];
char g[N][N];
int n;
void dfs(int u)
{
  if(u==n)
  {
    for(int i=0;i<n;i++)
    {
      puts(g[i]);
    }
    puts("");
    return ;
  }
  for(int i=0;i<n;i++)
  {                                      //udg 相当于 y=-x+c  c=x+y  dg 相当于y=x+c  c=y-x
    if(!col[i]&&!udg[u+i]&&!dg[i-u+n])//udg[u + i]表示u行i列的对角线是否有棋子  dg[n -u +i ]表示第u行的i列反对角线是否有棋子  //col判断的该处的那一列(竖着的)
    {
      g[u][i]='Q';
      col[i]=udg[u+i]=dg[i-u+n]=true;
      dfs(u+1);
      col[i]=udg[u+i]=dg[i-u+n]=false;
      g[u][i]='.';
    }
  }
}
int main()
{
  cin>>n;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      g[i][j]='.';
  dfs(0);
  return 0;
}