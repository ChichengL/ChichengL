#include<iostream>
using namespace std;

const int N=100010;

int a[N],tt=-1,hh;

int search(string a){
  if(a=="push")return 1;
  if(a=="pop")return 2;
  if(a=="empty")return 3;
  if(a=="query")return 4;
  return 0;
}
int main()
{
  int m;
  cin>>m;
  while(m--){
    string op;
    int x;
    cin>>op;
    if(search(op)==1){
      cin>>x;
      a[++tt]=x;
    }else if(search(op)==2){
      hh++;
    }else if(search(op)==3){
      if(hh<=tt)cout<<"NO"<<endl;
      else cout<<"YES"<<endl;
    }else{
      cout<<a[hh]<<endl;
    }
  }
  return 0;
}