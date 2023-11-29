#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 510, INF = 0x3f3f3f3f,M = 2e5+10;
int h[N],e[M],ne[M],w[M],d[N],idx;
int n, m;
bool st[N];
void add(int a,int b,int c)
{
  e[idx] = b,w[idx] = c,ne[idx] = h[a],h[a] = idx ++;
}
int prim()
{
  memset(d,0x3f,sizeof d);
  int res = 0;
  for(int i = 0; i < n; i ++)
  {
    int t = -1;
    for(int j = 1; j <= n; j ++)
    {
      if(!st[j]&&(t==-1||d[t]>d[j])) t = j;
    }
    if(i && d[t] == INF)return 0x3f3f3f3f;
    if(i)res += d[t];
    for(int j = h[t]; j != -1; j = ne[j])
    {
      int x = e[j];
      d[x] = min(d[x],w[j]);
    }
     st[t] = true;
  }
  return res;
}

int main()
{
  cin >> n >> m;
  //memset(w,0x3f,sizeof(w));
  memset(h,-1,sizeof h);
  while(m--)
  {
    int a, b, c;
    cin >> a >> b >> c;
    add(a,b,c),add(b,a,c);
  }
  int t = prim();
  if(t==INF)cout << "impossible";
  else cout << t;
  return 0;
}