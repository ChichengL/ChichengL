#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=510,M=10010;

int n, m, k;
int dist[N], backup[N];//backup备份数组

struct Edge{
  int a, b, w;
}edges[M];//存储边 a -> b的权重为w

int bellman_ford()
{
  memset(dist, 0x3f, sizeof dist);
  dist[1] = 0;
  for(int i = 0 ; i < k ; i ++ )
  {
    memcpy(backup,dist,sizeof dist);
    for(int j = 0 ; j < m; j ++ )
    {
      int a = edges[j].a, b = edges[j].b, w = edges[j].w;
      dist[b] = min(dist[b], backup[a] + w);//防止出现串联的情况
    }
  }
  if(dist[n]>0x3f3f3f3f / 2)return -0x3f3f3f;
  return dist[n];
}

int main()
{
  cin >> n >> m >> k;

  for(int i = 0 ;i < m ; i ++)
  {
    int a, b, w;
    cin >> a >> b >> w;
    edges[i]={a,b,w};
  }
  int t = bellman_ford();
  if(t==-0x3f3f3f)puts("impossible");
  else cout << t << '\n';
  return 0;
}