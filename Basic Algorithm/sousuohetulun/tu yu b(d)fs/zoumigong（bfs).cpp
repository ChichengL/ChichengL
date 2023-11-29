#include<iostream>
#include<queue>
#include<cstring>

using namespace std;
typedef pair<int,int>PII;
const int N=110;
queue<PII>q;
int g[N][N],d[N][N];//g是存储的图形,d是存储的距离
int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};//用向量存储方向分别是左、上、右、下
int n,m;

int bfs()
{
  q.push({0,0});//存入初始点
  while(q.size())
  {
    auto t=q.front();
    q.pop();//已使用
    for(int i=0;i<4;i++)
    {
      int x = t.first+dx[i], y = t.second+dy[i];
      if(x >= 0&&x<n&&y>=0&&y<m &&d[x][y]==-1&& g[x][y] == 0)//-1表示没有走过
      {
        d[x][y]=d[t.first][t.second]+1;
        q.push({x,y});
      }
    }
  }
   return d[n-1][m-1];
}

int main()
{
  cin>>n>>m;
  for(int i=0;i<n;i++)  
    for(int j=0;j<m;j++)
      cin>>g[i][j];
  memset(d,-1,sizeof d);//初始化标记以便确定那个点没有用过
  d[0][0]=0;
  cout << bfs()<< endl;
  return 0;
}