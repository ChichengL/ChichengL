#include<iostream>
#include<algorithm>
using namespace std;
const int N=100010;
struct qj{
  int l,r;
}s[N];
int cmp(struct qj a,struct qj b){
  return a.l<b.l;
}
int main()
{
  int n;
  cin>>n;
  for(int i=0;i<n;i++)cin>>s[i].l>>s[i].r;
  int cnt=0;
  sort(s,s+n,cmp);
  for(int i=0;i<n;i++)
  {
    if(s[i].l<=s[i-1].r)s[i].r=max(s[i].r,s[i-1].r);
    else cnt++;
  }
//   for(int i=0;i<n;i++)
//   {
//     if(s[i].l>s[i-1].r)cnt++;
//   }
  if(cnt==0)cnt++;
  cout<<cnt;

  return 0;
}