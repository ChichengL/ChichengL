#include<iostream>
using namespace std;
const int N = 310;
int f[N][N];
int s[N];
int n;

int main()
{
    cin >> n;
    for(int i = 1; i <= n ; i ++) cin >>s[i];
    for(int i = 1; i <= n ; i ++) s[i] += s[i-1];
    
    for(int len = 2; len <= n; len ++)//区间长度
    {
        for(int i = 1; i + len - 1<= n; i ++)//起点，和终点
        {
            int l = i, r = i+len-1;
            f[l][r] = 1e9;
            for(int k = l; k < r; k ++)//小区间内的任意一点
            {
                f[l][r] = min(f[l][r],f[l][k]+f[k+1][r]+s[r]-s[l-1]);
                /*f[i[[k]代表合成[i~k]这个区间的最小代价，f[k+1][j]代表合成[k+1,j]区间的最小代价
f[i][k] + f[k+1][j]代表的是合成[i~k]这一堆石子和合成[k+1~j]这一堆石子代价
s[j]-s[i-1]代表的合并[i~k] [k+1~j] 这两堆石子的代价*/
            }
        }
    }
    cout << f[1][n];//在1到n这个区间内的最小代价
}

#include<iostream>
using namespace std;
const int N = 310;
int f[N][N];
int a[N];
int n;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> a[i];
    for(int i = 1; i <= n; i ++) a[i] += a[i-1];
    for(int i = n; i >= 1; i--)//倒着计算可以保证f[i][j] = min(f[i][j],f[i][k]+f[k+1][j]+a[j]-a[i-1]计算准确
    //因为在[i,j]中的f数据全被计算过
    {
        for(int j = i; j <= n; j ++)
        {
            if(i==j)
            {
                continue;
            }
            f[i][j] = 1e9;
            for(int k = i; k < j; k ++)
            {
                f[i][j] = min(f[i][j],f[i][k]+f[k+1][j]+a[j]-a[i-1]);
            }
        }
    }
    cout << f[1][n];
}