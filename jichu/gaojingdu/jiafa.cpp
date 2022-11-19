#include<iostream>
#include<cstring>
using namespace std;
int s1[100010]={0},s2[100010]={0},s3[100010]={0};
int main()
{
  string a,b;
  cin>>a>>b;
  int cnt1=0,cnt2=0;
  for(int i=a.size()-1;i>=0;i--){
    s1[cnt1++]=a[i];
  }
  for(int i=b.size()-1;i>=0;i--){
    s2[cnt2++]=b[i];
  }
  int k=0;
  for(int i=0;i<max(cnt1,cnt2);i++){
    s3[k]=s1[i]+s2[i];
    if(s3[k]>=10){
      s3[k]-=10;
      k++;
    s3[k]++;
    }
  }
  for(int i=k;i>=0;i--){
    cout<<s3[i];
  }
  return 0;
}