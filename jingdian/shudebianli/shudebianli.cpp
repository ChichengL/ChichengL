#include<iostream>
#include<vector>

using namespace std;

const int N = 35;
vector<int>level[N];
int a[N],b[N],p[N];
int n;

void build(int al,int ar,int bl,int br,int d)
{
  if(al>ar)return ;
  int val = a[ar];
  int k = p[val];
  level[d].push_back(val);
  build(al,al+k-1-bl,bl,k-1,d+1);
  build(al+k-bl,ar-1,k+1,br,d+1);
}

int main()
{
  cin >> n;
  for(int i = 0; i < n ; i ++) cin >> a[i];
  for(int i = 0; i < n; i ++) cin >> b[i];
  for(int i = 0; i < n; i ++) p[b[i]] = i;

  build(0,n-1,0,n-1,0);
  for(int i = 0; i < n; i ++)
    for(auto p : level[i])
      cout << p << ' ';
      return 0;
}