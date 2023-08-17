#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int N = 1e5+10;
int h[N], w[N], e[N], ne[N], idx;
bool st[N];
int dist[N],cnt[N];
int n ,m;

void add(int a, int b ,int c)
{
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

int spfa()
{
  queue<int>q;
  for(int i = 1; i <= n; i ++)
  {
    st[i] = true;
    q.push(i);
  }

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
        cnt[j] = cnt[t] + 1;
        if(cnt[j] >= n)return true;
        if(!st[j])
        {
          q.push(j);
          st[j] = true;
        }
      }
    }
  }
  return false;
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
  if(spfa())puts("Yes");
  else puts("No");
  return 0;
}