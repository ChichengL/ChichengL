#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
const int N = 12,M = 1 << N;
int n,m;

long long  f[N][M];// 第一维表示列， 第二维表示所有可能的状态
bool st[M];//存储每种状态是否有奇数个连续的0，如果奇数个0是无效状态，如果是偶数个零置为true。

int main()
{
  while(cin >> n >> m, n||m)
  {
    memset(f,0,sizeof f);
    for(int i = 0 ; i < 1 << n; i ++)
    {
      st[i] = true;
      int cnt = 0;
      for(int j = 0; j < n; j ++)
      {
        if(i>>j & 1)//i >> j位运算，表示i（i在此处是一种状态）的二进制数的第j位；
        // &1为判断该位是否为1，如果为1进入if
        {
          if(cnt&1)//这一位为1，看前面连续的0的个数，如果是奇数（cnt &1为真）则该状态不合法
            st[i] = false;//判断连续的0是否是奇数个
          cnt = 0;
        }
        else {
          cnt ++;
        }
      }
      if(cnt & 1) st[i] = false;//最下面的那一段判断一下连续的0的个数
    }
    f[0][0] = 1;
    for(int i = 1; i <= m; i ++)
    {
      for(int j = 0; j < 1<<n; j ++)
      {
        for(int k = 0; k < 1 << n; k ++)
        {
          if((j&k)==0 &&st[j|k])// j & k == 0 表示 i 列和 i - 1列同一行不同时捅出来  j|k不存在连续奇数个0
          // st[j | k] == 1 表示 在 i 列状态 j， i - 1 列状态 k 的情况下是合法的.
            f[i][j] += f[i-1][k];// 当前列的方案数就等于之前的第i-1列所有状态k的累加。
        }
      }
    }
    cout << f[m][0]<<endl;//f[m][0]表示 前m-1列都处理完，并且第m-1列没有伸出来的所有方案数。
  }
}