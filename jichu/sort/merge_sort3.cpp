#include<iostream>
using namespace std;
typedef long long ll;
const int N=100010;
int n;
int a[N],temp[N];
ll merge_sort(int l,int r){
  if(l>=r)return 0;
  int mid=l+r>>1;
  ll cnt=merge_sort(l,mid)+merge_sort(mid+1,r);
  int i=l,j=mid+1,k=0;
  while(i<=mid&&j<=r){
    if(a[i]<=a[j])temp[k++]=a[i++];
    else {
      temp[k++]=a[j++];
      cnt+=mid-i+1;
    }
  }
  while(i<=mid)temp[k++]=a[i++];
  while(j<=r)temp[k++]=a[j++];
  for(int i=l,j=0;i<=r;i++,j++){
    a[i]=temp[j];
  }
  return cnt;
}

int main(){
  cin>>n;
  for(int i=0;i<n;i++)scanf("%d",&a[i]);

  cout<<merge_sort(0,n-1);
  
  return 0;
}