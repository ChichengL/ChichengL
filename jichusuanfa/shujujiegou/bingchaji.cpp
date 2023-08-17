#include<iostream>
using namespace std;

const int N=100010;

int p[N];//父亲节点
int find(int x)//返回x的祖宗节点+路径压缩
{
  if(p[x]!=x)p[x]=find(p[x]);//路径压缩
  return p[x];
}
int main()
{
  int n,m;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)p[i]=i;
  while(m--)
  {
    int a,b;
    char op[2];
    scanf("%s%d%d",op,&a,&b);
    if(op[0]=='M')p[find(a)]=find(b);//返祖归宗
    else{
      if(find(a)==find(b))printf("Yes\n");
      else printf("No\n");
    }
  }
  return 0;
}