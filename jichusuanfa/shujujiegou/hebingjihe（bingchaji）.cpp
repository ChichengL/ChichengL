#include<iostream>

using namespace std;

const int N=100010;
int p[N],n,m;

int find(int x)
{
  if(p[x]!=x)p[x]=find(p[x]);
  return p[x];
}
int main()
{
  scanf("%d%d",&n,&m);
  cin.tie(NULL);
  cout.tie(NULL);
  for(int i=1;i<=n;i++)p[i]=i;

  while(m--)
  {
    char op;
    int a,b;
    cin>>op>>a>>b;

    if(op=='M'){
      p[find(a)]=find(b);
    }else{
      if(find(a)==find(b))printf("Yes\n");
      else printf("No\n");
    }
  }

  return 0;
}