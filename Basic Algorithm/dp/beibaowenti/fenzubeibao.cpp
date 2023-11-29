//背包问题优化为一维，如果使用非本层的那么体积就要从大到小开始枚举，否则从小开始枚举可能后面大体积用的小体积 j-v[i][k]已经被污染了
//比如求f[i][7] = max(f[i][7],f[i-1][j-v[i]]+w[i]);如果v[i]为3 那么从小开始枚举那么可能会使本该用f[i-1][j-v[i]]+w[i]结果变为了f[i][j-v[i]]+w[i];

#include<iostream>
using namespace std;
const int N = 110;
int v[N][N],w[N][N];
int f[N],n,m,s[N];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++)
    {
        cin >> s[i];
        for(int j = 0; j < s[i]; j ++)
        {
            cin >> v[i][j] >> w[i][j];
        }
    }
    
    for(int i = 1; i <= n; i ++)
    {
        for(int j = m; j >=0 ;j --)
        {
            for(int k = 0; k < s[i]; k ++)
                if(v[i][k]<=j) f[j] = max(f[j],f[j-v[i][k]]+w[i][k]);
        }
    }
    cout << f[m];
    
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

const int N=110;
int f[N][N];  //只从前i组物品中选，当前体积小于等于j的最大值
int v[N][N],w[N][N],s[N];   //v为体积，w为价值，s代表第i组物品的个数
int n,m,k;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        for(int j=0;j<s[i];j++){
            cin>>v[i][j]>>w[i][j];  //读入
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            f[i][j]=f[i-1][j];  //不选
            for(int k=0;k<s[i];k++){
                if(j>=v[i][k])     f[i][j]=max(f[i][j],f[i-1][j-v[i][k]]+w[i][k]);  
            }
        }
    }
    cout<<f[n][m]<<endl;
}

#include<iostream>
using namespace std;
const int N = 110;
int f[N],n,m;
int v[N][N],w[N][N],s[N];

int main()
{
  cin >> n >> m;
  for(int i = 1; i <= n; i ++)
  {
    cin >>s[i];
    for(int j = 0; j < s[i]; j ++)
      cin >> v[i][j] >> w[i][j];
  }
  for(int i = 1; i <= n; i ++)
  {
    for(int j = m; j >= 0; j --)
    {
      for(int k = 0; k < s[i]; k ++)
      {
        if(v[i][k]<=j) f[j] = max(f[j], f[j-v[i][k]]+w[i][k]);
      }
    }
  }
  cout << f[m];
}