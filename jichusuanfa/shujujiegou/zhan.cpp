#include<iostream>
using namespace std;

const int N=100010;

int stk[N],tt;

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
      stk[++tt]=x;
    }else if(search(op)==2){
      --tt;
    }else if(search(op)==3){
      if(tt)cout<<"NO"<<endl;
      else cout<<"YES"<<endl;
    }else{
      cout<<stk[tt]<<endl;
    }
  }
  return 0; 
}