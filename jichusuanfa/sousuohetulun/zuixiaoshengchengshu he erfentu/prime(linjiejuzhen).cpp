#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 510, INF = 0x3f3f3f3f;
int g[N][N],d[N];
int n, m;
bool st[N];//st数组表示是否连通
int prim()
{
  memset(d,0x3f,sizeof d);
  int res = 0;
  for(int i = 0; i < n; i ++)//每次循环选出一个点加入到生成树
  {
    int t = -1;
    for(int j = 1; j <= n; j ++)
    {
      if(!st[j]&&(t==-1||d[t]>d[j])) t = j;//如果没有在树中，且到树的距离最短，则选择该点
    }
    if(i && d[t] == INF)return 0x3f3f3f3f;
    if(i)res += d[t];//先加在更新防止形成自环
    for(int j = 1; j <= n; j ++)
      d[j] = min(d[j],g[t][j]);
     st[t] = true;
  }
  return res;
}

int main()
{
  cin >> n >> m;
  memset(g,0x3f,sizeof(g));
  while(m--)
  {
    int a, b, c;
    cin >> a >> b >> c;
    g[a][b] = g[b][a] = min(g[a][b],c);
  }
  int t = prim();
  if(t==INF)cout << "impossible";
  else cout << t;
  return 0;
}