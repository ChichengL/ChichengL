#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 100010, M = 200010;

int h[N], e[M], ne[M] ,idx;
int color[N];
int n,m;

void add(int a,int b,int c)
{
  e[idx] = b, ne[idx] = h[a] ,h[a] = idx ++;
}

bool dfs(int u,int c)
{
  color[u] = c;

  for(int i = h[u]; i != -1; i = ne[i])
  {
    int j = e[i];
    if(!color[j])
    {
      if(!dfs(j,3-c))return false;//判断子节点的颜色，c为1，3-c=2，若c=2,3-c=1；
    }
    else if(color[j]==c)return false;//如果颜色相同那么是错误的
  }
  return true;
}

int main()
{
  cin >> n >> m;
  memset(h,-1,sizeof h);
  while(m--)
  {
    int a,b;
    cin >> a >> b;
    add(a,b),add(b,a);
  }
  bool flag = true;
  for(int i = 1; i <=n ; i++)
  {
    if(!color[i])
    {
      if(!dfs(i,1))
      {
        flag = false;
        break;
      }
    }
  }
  if(flag) puts("Yes");
  else puts("No");
  return 0;
}