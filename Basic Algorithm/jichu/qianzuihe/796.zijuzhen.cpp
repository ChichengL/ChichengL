#include<iostream>
#include<string.h>
using namespace std;
int main()
{
  int n,m,q;
  cin>>n>>m>>q;
  int a[n+10][m+10],s[n+10][m+10];
  memset(s,0,sizeof(s));
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      scanf("%d",&a[i][j]);
      s[i][j]=s[i][j-1]+a[i][j]+s[i-1][j]-s[i-1][j-1];
    }
    s[i+1][0]=s[i][m];
  }
  while(q--){
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
   cout<<s[x2][y2]+s[x1-1][y1-1]-s[x2][y1-1]-s[x1-1][y2]<<endl; 
  }
  return 0;
}