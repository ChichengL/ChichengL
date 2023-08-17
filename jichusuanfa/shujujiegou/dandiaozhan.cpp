#include<bits/stdc++.h>
using namespace std;

const int N=100010;

int stk[N],tt;
int main()
{
  cin.tie(NULL);
  cout.tie(NULL);//快读和快输出如果要用cin
  ios::sync_with_stdio(false);

  int m;
  //cin>>m;
  scanf("%d",&m);
  while(m--){
    int x;
    // cin>>x;
    scanf("%d",&x);
    while(tt&&stk[tt]>=x)tt--;
    if(!tt)//cout<<"-1 ";
    printf("-1 ");
    else //cout<<stk[tt]<<' ';
    printf("%d ",stk[tt]);
    stk[++tt]=x;
  }
  return 0;
}