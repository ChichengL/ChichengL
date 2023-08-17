#include<iostream>
using namespace std;
const int N = 1010;
char a[N],b[N];
int f[N][N];
int n,m;
/*f[i][j] 表示在第一个序列的前i个字母中出现并且在第二个序列的前j个字母中出现的最大值
以第i个和第j个字母是否相同来划分
如果相同 f[i][j] = f[i - 1][j - 1] + 1
如果不相同 f[i][j] = max(f[i - 1][j], f[i][j - 1])
因为如果不相同，那么此时f[i][j]的值肯定不会大于f[i - 1][j]和f[i][j - 1]的最大值*/
int main()
{
    cin >> n >> m;
    cin >> a+1 >> b+1;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
        {
            f[i][j] = max(f[i-1][j],f[i][j-1]);//分别为a[i]中的不在最长子序列 和 b[j]不在最长子序列中的最大值
            if(a[i]==b[j]) f[i][j] = max(f[i][j],f[i-1][j-1]+1);
        }
    cout << f[n][m];
    return 0;
}