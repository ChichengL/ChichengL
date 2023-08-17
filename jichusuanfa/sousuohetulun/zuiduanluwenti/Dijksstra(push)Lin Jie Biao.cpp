#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=1e5+10;
int h[N],e[N],w[N],ne[N],idx;
int dist[N];
int n,m;
bool st[N];
void add(int a,int b,int c)
{
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra()
{
  memset(dist, 0x3f,sizeof dist);
  dist[1] = 0;

  for(int i = 0; i < n; i++)
  {
    int t = -1;
    for(int j = 1 ; j <= n; j ++ )
    {
      if(!st[j]&&(t == -1||dist[t]>dist[j]))//遍历 dist 数组，找到没有确定最短路径的节点中距离源点最近的点t
      {
        t = j;
      }
    }
    st[t] = true;
    for(int j = h[t];j != -1 ;j = ne[j] )//遍历 t 所有可以到达的节点 i
    {
      int x = e[j];
      dist[x] = min(dist[x], dist[t] + w[j]);
    }
  }
  if(dist[n] == 0x3f3f3f3f)return -1;
  else return dist[n];
}

int main()
{
  cin >> n >> m;

  memset(h, -1, sizeof h);

  for(int i = 0; i < m; i ++ )
  {
    int a, b, c;
    cin >> a >> b >> c;
    add(a,b,c);
  }
  int t = dijkstra();
  cout << t;
  return 0;
}

