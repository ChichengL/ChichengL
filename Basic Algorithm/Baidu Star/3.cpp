#include<bits/stdc++.h> 

using namespace std;
int a[1000010];
void prime(int x){
  bool b[1000010];
  for(int i = 2; i<=x; i ++){
    if(!b[i]){
      while(x%i==0){
        a[i]++;
      }
      for(int j = 2; j*i<=x; j ++){
        b[j*i] = true;
      }
    }
  }
}

void power(int x,int n){
  bool b[1000010];
  unordered_map<int,int>m;
  for(int i = 2; i <=x; i ++){
    if(!b[i]){
      while(x%i==0){
        m[i]++;
      }
      for(int j = 2; j*i<=x; j ++){
        b[j*i] = true;
      }
    }
  }
  for(auto i : m){
    a[i.first]+=n*i.second;
  }
}

int main( )
{
  int n;
  cin >> n;
    for(int i = 2; i <=n ; i ++){
      prime(i);
      if(a[i]) a[i]+=n-i;
      else{
        power(i,n-i);
      }
    }
    string s = "f(" + to_string(n) + ")=";
    for(int i = 2; i <= n; i ++){
      if(a[i]>=2){
        s+=to_string(i)+"^"+to_string(a[i])+"*";
      }else if(a[i]==1){
        s+=to_string(i)+"*";
      }
    }
    s = s.substr(0,s.length()-1);
    cout << s;
    return 0;
}