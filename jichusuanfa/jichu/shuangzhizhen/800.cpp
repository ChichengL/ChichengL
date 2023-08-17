  #include<iostream>
  using namespace std;
  int main()
  {
    int n,m,x;
    cin>>n>>m>>x;
    int a[n+10],b[m+10];
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    for(int i=0;i<m;i++)scanf("%d",&b[i]);
    for(int i=n-1,j=0;i>=0;i--){
      while(j<=n-1&&a[i]+b[j]<x)j++;
      if(j<=n-1&&a[i]+b[j]==x)
        printf("%d %d\n",i,j);
    }
    return 0;
  }