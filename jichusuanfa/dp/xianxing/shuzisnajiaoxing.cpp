#include<iostream>
using namespace std;
const int N = 510,INF = 1e9;
int f[N][N],a[N][N],n;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= i; j ++)
            cin >> a[i][j];
            
    for(int i = 0; i <= n; i ++)
        for(int j = 0; j <= i+1;j ++)//此处i+1是为了让下一列的找到它右上角的那个数因为可能有负数存在所以必须初始化
            f[i][j] = -INF;
    f[1][1] = a[1][1];
    for(int i = 2; i <= n; i ++)
        for(int j = 1; j <= i; j ++)
            f[i][j] = max(f[i-1][j-1]+a[i][j],f[i-1][j]+a[i][j]);//这两个分别是 左上角和右上角
    int res = -INF;
    for(int i = 1; i <= n; i ++) res = max(res,f[n][i]);
    cout << res;
}