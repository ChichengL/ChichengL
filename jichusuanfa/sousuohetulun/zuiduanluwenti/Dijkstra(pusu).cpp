#include<iostream>
#include<cstring>
using namespace std;
//朴素Dijkstra算法
//先d[1]=0,d[x]= +无穷(0x3f3f3f3f)
const int N = 510;
int g[N][N];//为稠密阵所以用邻接矩阵存储
int d[N];
bool st[N];//用于记录该点的最短距离是否已经确定
int n , m;

int dijkstra()
{
  memset(d,0x3f,sizeof d);
  d[1]=0;//到自己距离为0

  for(int i = 0; i < n; i ++)
  {
    int t = -1;
    for(int j = 1 ; j <= n ; j ++)
    {
      if( !st[j] && (t == -1 || d[t]>d[j]))
      {
        t = j;
      }
    }
    st[t]=true;//找到一个t点
    
    for(int j = 1 ; j <= n ; j ++)
      d[j]=min(d[j],d[t] + g[t][j]); 
  }
  if(d[n] == 0x3f3f3f3f)return -1;
  return d[n];
}
int main()
{
  scanf("%d %d",&n,&m);
  
  memset(g,0x3f,sizeof g);//初始化图 因为是求最短路径
  while(m -- )
  {
    int a , b , c ;
    scanf("%d%d%d",&a,&b,&c);
    g[a][b]=min(g[a][b],c);//如果发生重边的情况则保留最短的一条边
  }
  int t=dijkstra();
  printf("%d",t);
  return 0;
}