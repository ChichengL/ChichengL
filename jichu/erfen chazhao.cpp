#include<iostream>

using namespace std;

const int N=1e5+10;
int a[N];
int n,m;

int main()
{
  cin>>n>>m;
  for(int i=0;i<n;i++)cin>>a[i];
  while(m--){
    int x;
    cin>>x;
    int l=0,r=n-1;
    while(l<r){
      int mid=l+r>>1;
      if(a[mid]>=x)r=mid;
      else l=mid+1;
    }
    if(a[l]!=x)cout<<"-1 -1"<<endl;
    else{
      cout<<l<<' ';
      int l=0,r=n-1;
      while(l<r){
        int mid=l+r+1>>1;//防止进入死循环当r-1=l时r为要查找的数时就不会缩小范围  所以要加一
        if(a[mid]<=x)l=mid;
        else r=mid-1;
      }
      cout<<l<<endl;
    }
  }
  return 0;
}