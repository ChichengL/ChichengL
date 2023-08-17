#include<iostream>
#include<cstring>
using namespace std;

const int N=1e5+10,M=N*2;
int h[N],e[M],ne[M],idx;//做邻接表
int n,ans=N;//ans为要求的数子节点的最大值的最小值
bool st[N];//标记该数是否用过

void add(int a,int b)
{
  e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

int dfs(int u)
{
  st[u]=true;//标记已经使用
  int sum=1,res=0;//sum初始为1是因为去除该点(整段树在该点断开)它也算在连同块中
  for(int i=h[u];i!=-1;i = ne[i])
  {
    int j=e[i];//找该数指向的数
    if(!st[j])
    {
      int t=dfs(j);//找到除开头点的子段连同块数量
      res=max(res,t);//求子段中连同块的最大值
      sum+=t;//该段分叉的连同块的值（也是这段分支的总值）
    }
  }
  res=max(res,n-sum);//找到该段连同块的最大值和，所剩的最大值

  ans=min(ans,res);//全部遍历后找到全部最大连同块的最大值的最小值
  return sum;//返回该点下面的所有子节点的数目
}

int main()
{
  cin >> n;
  memset(h,-1,sizeof h);
  for(int i=0;i<n-1;i++)
  {
    int a,b;
    cin >> a >> b;
    add(a,b),add(b,a);//无向块所以两边都是相互指向
  }
  dfs(1);
  cout << ans<< endl;
  return 0;
}