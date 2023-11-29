#include<iostream>
using namespace std;
/*void qsort(int *a,int left,int right){
  if(left>right)
  return ;
  int t=a[left];
  int i=left;
  int j=right;
  while(i!=j){
    while(j>i&&a[j]>=t)j--;//找到小于基准值的数
    while(j>i&&a[i]<=t)i++;//找到大于基准值的数
    if(j>i){
      int s=a[i];
      a[i]=a[j];
      a[j]=s;
    }
  }
  a[left]=a[i];
  a[i]=t;
  qsort(a,left,i-1);
  qsort(a,i+1,right);

}*/
void qsort(int *a,int left,int right){
  if(left>=right)return ;
  int i=left-1,j=right+1,x=a[(left+right)>>1];
  while(i<j){
    do i++;while(a[i]<x);
    do j--;while (a[j]>x);
    if(i<j)swap(a[i],a[j]);
  }
qsort(a,left,j);
    qsort(a,j+1,right);
}
int main()
{
  int n;
  cin>>n;
  int a[n+10];
  for(int i=0;i<n;i++)cin>>a[i];
  //qsort(a,0,n-1);
  qsort(a,0,n-1);
  for(int i=0;i<n;i++)cout<<a[i]<<" ";
  return 0;
}