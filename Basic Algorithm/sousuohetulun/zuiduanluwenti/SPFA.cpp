#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int N = 1e5+10;
int h[N], w[N], e[N], ne[N], idx;
bool st[N];
int dist[N];
int n ,m;

void add(int a, int b ,int c)
{
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

int spfa()
{
  memset(dist,0x3f,sizeof dist);
  dist[1] = 0;
  queue<int>q;
  q.push(1);
  st[1] = true;
  while(!q.empty())
  {
    int t = q.front();
    q.pop();
    st[t] = false;
    for(int i = h[t]; i != -1 ; i = ne[i])
    {
      int j = e[i];
      if(dist[j] > dist[t] + w[i])
      {
        dist[j] = dist[t] + w[i];
        if(!st[j])
        {
          q.push(j);
          st[j] = true;
        }
      }
    }
  }
  if(dist[n] == 0x3f3f3f3f)return -0x3f3f3f;
  return dist[n];
}

int main()
{
  cin >> n >> m;
  
  memset(h,-1,sizeof h);

  while(m --)
  {
    int a, b, w;
    cin >> a >> b >> w;
    add(a,b,w);
  }
  int t = spfa();
  if(t == -0x3f3f3f)cout << "impossible";
  else cout << t;
  return 0;
}