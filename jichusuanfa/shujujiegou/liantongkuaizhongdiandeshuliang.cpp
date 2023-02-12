#include<iostream>

using namespace std;

const int N=100010;
int p[N],n,m,s[N];

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
  for(int i=1;i<=n;i++){
    p[i]=i;
    s[i]=1;
  }

  while(m--)
  {
    char op[2];
    int a,b;
    cin>>op;
    if(op[0]=='C'){
      cin>>a>>b;
      if(find(a)==find(b))continue;
      s[find(b)]+=s[find(a)];
      p[find(a)]=find(b);
    }else if(op[1]=='1'){
      cin>>a>>b;
      if(find(a)==find(b))printf("Yes\n");
      else printf("No\n");
    }else {
      cin>>a;
      printf("%d\n",s[find(a)]);
    }
  }

  return 0;
}