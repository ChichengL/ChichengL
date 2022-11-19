#include<iostream>
#include<cstring>
#define mod 100003
//拉拉链法
using namespace std;

const int N=100010;

int h[N],e[N],ne[N],idx;
void insert(int x)
{
  int t=(x%mod+mod)%mod;
  e[idx]=x;
  ne[idx]=h[t];
  h[t]=idx++;
}
bool find(int x)
{
  int t=(x%mod+mod)%mod;
  for(int i=h[t];i!=-1;i=ne[i]){
    if(e[i]==x)return true;
  }
  return false;
}
int main()
{
  cin.tie(NULL);
  memset(h,-1,sizeof h);
  int n;
  cin>>n;
  while(n--)
  {
    char op;
    int x;
    cin>>op>>x;
    if(op=='I')insert(x);
    else{
      if(find(x))puts("Yes");
      else puts("No");
    }
  }
  return 0;
}
//开放地址法
// const int N=200003,null=0x3f3f3f3f;

// int h[N];

// int find(int x)
// {
//   int t=(x%N+N)%N;
//   while(h[t]!=null&&h[t]!=x){
//     t++;
//     if(t==N)t=0;
//   }
//   return t;
// }
// int main()
// {
//   cin.tie(NULL);
//   memset(h,null,sizeof h);
//   int n;
//   cin>>n;
//   while(n--)
//   {
//     char op;
//     int x;
//     cin>>op>>x;
//     int k=find(x);
//     if(op=='I')h[k]=x;
//     else{
//       if(h[k]!=null)puts("Yes");
//       else puts("No");
//     }
//   }
//   return 0;
// }