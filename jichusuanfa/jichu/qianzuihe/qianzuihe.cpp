#include<iostream>
using namespace std;
int main()
{
  int n,m;
  cin>>n>>m;
  int a[n+10],s[n+10];
  s[0]=0;
  for(int i=1;i<=n;i++){
  scanf("%d",&a[i]);
  s[i]=s[i-1]+a[i];
  }
  while(m--){
    int l,r;
    cin>>l>>r;
   cout<<s[r]-s[l-1]<<endl; 
  }
  return 0;
}