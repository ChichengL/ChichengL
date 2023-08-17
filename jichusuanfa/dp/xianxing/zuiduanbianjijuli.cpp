#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N =1010;
char a[N],b[N];
int n,m;
int f[N][N];//f[i][j]表示从a[i] 到 b[j]所需要的操作
int main()
{
    cin >> n >> a + 1;
    cin >> m >> b + 1;
    for(int i = 0; i <= m; i ++) f[0][i] = i;//a为空的时候变成b只能添加
    for(int i = 0; i <= n; i ++) f[i][0] = i;
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= m; j ++)
        {
            f[i][j] = min(f[i-1][j]+1,f[i][j-1]+1);//对应者删和增
            if(a[i]!=b[j]) f[i][j] = min(f[i][j],f[i-1][j-1]+1);
            else f[i][j] = min(f[i][j],f[i-1][j-1]);
        }
    }
    cout << f[n][m];
}