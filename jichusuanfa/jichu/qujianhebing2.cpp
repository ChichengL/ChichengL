#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int,int>>S;

void merge(vector<pair<int,int>>&S){
  vector<pair<int,int>>s;
  sort(S.begin(),S.end());
  int l=-2e9,r=-2e9;
  for(auto item :S){
    if(r<item.first){
      if(l!=-2e9)s.push_back({l,r});
      l=item.first;
      r=item.second;
    }else r=max(r,item.second);
  }
  if(l!=-2e9)s.push_back({l,r});
  S=s;
}

int main()
{
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    int l,r;
    cin>>l>>r;
    S.push_back({l,r});
  }
  merge(S);
  cout<<S.size();
  return 0;
}