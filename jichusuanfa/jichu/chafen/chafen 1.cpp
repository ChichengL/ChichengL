#include<iostream>
using namespace std;
int main()
{
  int n,m;
  cin>>n>>m;
  int a[n+10],b[n+10];
  a[0]=b[0]=0;
  for(int i=1;i<=n;i++){
    scanf("%d",&a[i]);
    b[i]=a[i]-a[i-1];
  }
  while(m--){
    int l,r,c;
    cin>>l>>r>>c;
      b[l]+=c;
    b[r+1]-=c;
  }
  for(int i=1;i<=n;i++)a[i]=b[i]+a[i-1];
  for(int i=1;i<=n;i++)printf("%d ",a[i]);
  return 0;
}