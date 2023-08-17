#include<iostream>
using namespace std;
int N=100010;
int a[100010],temp[100010];
void merge_sort(int *a,int l,int r){
  if(l>=r)return ;
  int mid=(l+r)>>1;
  merge_sort(a,l,mid);
  merge_sort(a,mid+1,r);
  int k=0,i=l,j=mid+1;
  while(i<=mid&&j<=r){
    if(a[i]<=a[j])temp[k++]=a[i++];
    else temp[k++]=a[j++];
  }
  while(i<=mid)temp[k++]=a[i++];
  while(j<=r)temp[k++]=a[j++];
  for(i=l,j=0;i<=r;i++,j++){
    a[i]=temp[j];
  }
}
int main()
{
  int n;
  scanf("%d",&n);
  for(int i=0;i<n;i++)scanf("%d",&a[i]);
  merge_sort(a,0,n-1);
  for(int i=0;i<n;i++)printf("%d ",a[i]);
  return 0;
}