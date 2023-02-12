#include<iostream>
using namespace std;
typedef unsigned long long ULL;
const int N=100010,P=131;//P=13331;
char s[N];
ULL h[N],p[N];
int n,m;
ULL get(int l,int r)
{
  return h[r]-h[l-1]*p[r-l+1];//相当于r到l（包括l）的子字符串的哈希值
  
}
int main()
{
  cin>>n>>m;
  cin>>s+1;
  p[0]=1;
  for(int i=1;i<=n;i++)
  {
    p[i]=p[i-1]*P;
    h[i]=h[i-1]*P+s[i];
  }
  while(m--)
  {
    int l1,l2,r1,r2;
    cin>>l1>>r1>>l2>>r2;
    if(get(l1,r1)==get(l2,r2))puts("Yes");
    else puts("No");
  }

  return 0;
}
