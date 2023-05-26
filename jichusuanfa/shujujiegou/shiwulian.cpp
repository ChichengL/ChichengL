#include<iostream>

using namespace std;
const int N = 1e5+10;
int p[N],d[N];//d[i]是 i 到 i父节点的距离
int n,m;

int find(int x)
{
  if(p[x]!=x)
  {
    int u = find(p[x]);//找到根节点
    d[x]+=d[p[x]];//x到父节点的距离+父节点到根节点的距离
    p[x]=u; //让父节点变为根节点
  }
  return p[x];
}

int main()
{
  cin >> n >> m;
  int res = 0;
  for(int i = 1; i <= n; i ++) p[i] = i;
  while(m--)
  {
    int t,x,y;
    cin >> t >> x >> y;
    if(x>n||y>n) res++;
    else
    {
      int px = find(x),py = find(y);
      if(t==1)
      {
        if(px==py&&(d[x]-d[y])%3) res++;
        else if(px!=py)
        {
          p[px] = p[y];
          d[px] = d[y] - d[x];
        }
      }else
      {
        if(px==py&&(d[x]-d[y]-1)%3) res++;
        else if(px!=py)
        {
          p[px]=p[y];
          d[px] = d[y]-d[x]+1;
        }
      }
    }
  }
  cout << res;
}