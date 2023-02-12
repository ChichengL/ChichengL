#include<iostream>
using namespace std;
const int N=100010;
int a[N],s[N];
int main()
{
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>a[i];
  }
  int cnt=0;
  for(int i=0,j=0;i<n;i++){
    s[a[i]]++;
    while(s[a[i]]>1)s[a[i]]--,j++;
    cnt=max(cnt,i-j+1);
  }
  cout<<cnt;
  return 0;
}