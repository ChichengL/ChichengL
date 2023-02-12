#include<iostream>
#include<algorithm>

using namespace std;
const int N = 20;
int p[N];
int n,m;

int main()
{
  cin >> n >> m;
  for(int i = 0; i < m; i ++) cin >> p[i];
  for(int i = 1; i < 1<<m; i ++)
  {
    int t = 1,cnt = 0;
    for(int j = 0; j < m; j ++)
    {
      if(i>>j&1)
      {
        cnt ++;
        if((long long)t*p[j]>n)
        {
          t = -1;
          break;
        }
        t *=p[j];
      }
    }
    if(t!=-1)
    {
      if(cnt%2) res +=n/t;
      else res -=n/t;
    }
  }
  cout << res;

  return 0;
}