##include<iostream>
using namespace std;
const int N = 1010;
int dp[N][N];
int v[N],w[N];

int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++)
    {
        cin >> v[i] >> w[i];
    }
    for(int i = 1; i <= n ;i ++)
    {
        for(int j = 0; j <= m; j ++)
        {
            dp[i][j] = dp[i-1][j]; // 当当前物品的体积大时那么该结果就为上一层的结果
            if(j>=v[i]) dp[i][j] = max(dp[i][j],dp[i-1][j-v[i]]+w[i]);//如果不是那么就比较
        }
    }
    cout <<dp[n][m];

    return 0;
}
// #include<iostream>
// using namespace std;
// const int N = 1010;
// int f[N];
// int v[N],w[N];
// int n,m;
// int main()
// {
//     cin >> n >> m;
//     for(int i = 1; i <= n; i ++) cin >> v[i] >> w[i];

//     for(int i = 1; i <= n; i ++)
//         for(int j = m; j >=v[i]; j --)//逆序更新是为了防止使用到已经更新的那一个数  比如
//         //可能会变为f[i][j-v[i]]+w[i] 这种结果而不是以前的结果
//             f[j] = max(f[j],f[j-v[i]]+w[i]);

//     cout << f[m];

//     return 0;
// }


