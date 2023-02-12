#include<iostream>
using namespace std;
const int N=1000010;
int a[N],q[N];
int main()
{
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);

  int n,k;
  cin>>n>>k;
  for(int i=0;i<n;i++)scanf("%d",&a[i]);
  int hh=0,tt=-1;
  for(int i=0;i<n;i++){
    if(hh<=tt&&i-k+1>q[hh])hh++;
    while(hh<=tt&&a[q[tt]]>=a[i])tt--;
    q[++tt]=i;
    if(i>=k-1)printf("%d ",a[q[hh]]);
  }
  puts("");
  hh=0,tt=-1;
  for(int i=0;i<n;i++){
    if(hh<=tt&&i-k+1>q[hh])hh++;
    while(hh<=tt&&a[q[tt]]<=a[i])tt--;
    q[++tt]=i;
    if(i>=k-1)printf("%d ",a[q[hh]]);
  }
  return 0;
}
