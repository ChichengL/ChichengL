#include<iostream>
#include<queue>
using namespace std;
const int N = 110;
typedef struct{
  int vexs[N][N];
  int arcs[N];
  int vexnum,arcnum;
  bool state[N];
  int d[N];
}AMGraph;


void Init(AMGraph&G)
{
  cin >> G.vexnum >> G.arcnum;
  for(int i = 1; i <= G.vexnum; i ++)
    for(int j = 1; j <= G.vexnum; j ++)
      G.state[i] = false,G.vexs[i][j] = 0x3f3f3f3f,G.d[i] = 0x3f3f3f3f;
  for(int i = 0; i < G.arcnum; i ++)
  {
    int x,y,d;
    cin >> x >> y >> d;
    G.vexs[x][y] = min(G.vexs[x][y],d);
  }
}

int Dij(AMGraph &G)
{
  G.d[1] = 0;
  for(int i = 0; i < G.vexnum; i ++)
  {
    int t = -1;
    for(int j = 1; j <= G.vexnum; j++)
      if(!G.state[j] && (t==-1 || G.d[t]>G.d[j]))
        t = j;
      G.state[t] = true;
      for(int j = 1; j <= G.vexnum; j ++)
      {
        G.d[j] = min(G.d[j],G.d[t]+G.vexs[t][j]);
      }
  }
  return G.d[G.vexnum];
}

int main()
{
  AMGraph G;
  Init(G);
  cout << Dij(G);
}