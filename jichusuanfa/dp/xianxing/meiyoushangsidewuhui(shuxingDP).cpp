#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
const int N = 6010;
int n;

int happy[N];
int h[N],e[N],ne[N],idx;
int f[N][2];//0为不选u，1为选u
bool has_father[N];
/*f[u][0] = ∑max(f[si][0],f[si][1])   si表示以上一节点为u的子节点
  f[u][1] = ∑f[si][0]*/

void add(int a,int b)
{
  e[idx] = b, ne[idx] = h[a], h[a] = idx ++;//邻接表存储树
}

void dfs(int u)
{
  f[u][1] = happy[u];
  for(int i = h[u]; i != -1; i = ne[i])
  {
    int j = e[i];
    dfs(j);
    f[u][0]+=max(f[j][0],f[j][1]);
    f[u][1] += f[j][0];
  }
}
int main()
{
  cin >> n;
  for(int i = 1; i <= n; i ++) cin >> happy[i];
  memset(h,-1,sizeof h);
  for(int i = 0; i < n-1; i ++)
  {
    int a,b;
    cin >> a >> b;
    has_father[a] = true;
    add(b,a);
  }
  int root = 1;
  while(has_father[root])root++;
  dfs(root);
  cout << max(f[root][0],f[root][1]);

  return 0;
}