#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
bool cmp(vector<int>&A,vector<int>&B){
  if(A.size()!=B.size())return A.size()>B.size();
  for(int i=A.size()-1;i>=0;i--)
    if(A[i]!=B[i])return A[i]>B[i];
  return true;
}
vector<int>cf(vector<int>&A,vector<int>&B){
  int t=0,k=1;
  vector<int>C(100010);
  for(int i=0;i<B.size();i++){
    for(int j=0;j<A.size();j++){
      if(i<B.size()&&j<A.size())t+=A[j]*B[i];
      C.push_back(t%10);
      t/=10;
    }
  }
  while(C.size()>1&&C.back()==0)C.pop_back();
  return C;
}
int main()
{
  string a,b;
  cin>>a>>b;
  vector<int>A,B;
  for(int i=a.size()-1;i>=0;i--)A.push_back(a[i]-'0');
  for(int i=b.size()-1;i>=0;i--)B.push_back(b[i]-'0');
  if(cmp(A,B)){
    auto C=cf(A,B);
  for(int i=C.size()-1;i>=0;i--)printf("%d",C[i]);
  }else{
    auto C=cf(B,A);
  for(int i=C.size()-1;i>=0;i--)printf("%d",C[i]);
  }
  return 0;
}