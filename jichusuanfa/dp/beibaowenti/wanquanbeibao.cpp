#include<iostream>
using namespace std;
const int N = 1010;
int f[N][N];
int v[N],w[N];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i = 1 ; i <= n ;i ++)
    {
        cin>>v[i]>>w[i];
    }

    for(int i = 1 ; i<=n ;i++)
        for(int j = 0 ; j<=m ;j++)
            for(int k = 0 ; k*v[i]<=j ; k++)//用了k个物品
                f[i][j] = max(f[i][j],f[i-1][j-k*v[i]]+k*w[i]);

    cout<<f[n][m]<<endl;
}

#include<iostream>
using namespace std;
const int N = 1010;
int f[N][N];
int v[N],w[N];
int n,m;
// 二维优化
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> v[i] >> w[i];

    for(int i = 1; i <= n; i ++)
        for(int j = 0; j <= m; j ++)
        {
            f[i][j] = f[i-1][j];
            if(j>=v[i]) f[i][j] = max(f[i][j] , f[i][j-v[i]]+w[i]);
            /*f[i][j] = max(f[i-1][j],f[i-1][j-v]+w,f[i-1][j-2*v]+2*w,....)
                f[i][j-v] = max(f[i-1][j-v], f[i-1][j-2*v]+w,f[i-1][j-3*v]+2*w,.....)
                所以f[i][j] 可以为max(f[i-1][j],f[i][j-v[i]]+w[i])*/
        }
    cout << f[n][m] ;
    return 0;
}
//背包问题优化为一维，如果使用非本层的那么体积就要从大到小开始枚举，否则从小开始枚举可能后面大体积用的小体积 j-v[i]已经被污染了
#include<iostream>
using namespace std;
const int N = 1010;
int f[N],v[N],w[N];
int n,m;
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> v[i] >> w[i];

    for(int i = 1; i <= n; i ++)
        for(int j = v[i]; j <= m; j ++)
            f[j] = max(f[j],f[j-v[i]]+w[i]);//由二维转化而来 因为用到的是f[i][j-v]所以不用考虑01背包问题中是否被提前更新那个问题
            //所以可以直接变为f[j-v[i]]  而不是从逆序开始
    cout << f[m];

    return 0;
}
