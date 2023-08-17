#include<iostream>
using namespace std;
const int N = 20, M = 1 << N;
int w[N][N];
int f[M][N];//m是状态 N 是点
int n;

int main()
{
  cin >> n;
  for(int i = 0; i < n; i ++)
    for(int j = 0; j < n; j ++)
      cin >> w[i][j];
  memset(f,0x3f,sizeof f);
  f[1][0] = 0;//从0到0 走过0 ，所以0的状态是1 且距离是0；
  for(int i = 0; i < 1 << n; i ++)
  {
    for(int j = 0; j < n; j ++)//j表示走到哪一个点
    {
      if(i >> j & 1)
      {
        for(int k = 0; k < n; k ++)//k表示走到j这个点之前,以k为终点的最短距离
        {
          if((i-(1<<j)>>k & 1))//i除去j点后 还要包括k点
          {
             f[i][j] = min(f[i][j],f[i-(1<<j)][k]+w[k][j])//从k转移到j
          }
        }
      }
    }
  }
  cout << f[(1<<n) - 1][n-1]//(1<<n)-1是为了表示所以的点状态都为1；
}