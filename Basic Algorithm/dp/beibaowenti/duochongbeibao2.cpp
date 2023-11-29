//背包问题优化为一维，如果使用非本层的那么体积就要从大到小开始枚举，否则从小开始枚举可能后面大体积用的小体积 j-v[i]已经被污染了

#include<iostream>
using namespace std;
const int N = 25000;
int f[N],v[N],w[N],n,m;

int main()
{
    cin >> n >> m;
    int cnt = 0;
    for(int i = 1; i <= n; i ++)
    {
        int a,b,s;
        cin >> a >> b >> s;
        int k = 1;
        while(k<=s)
        {
            cnt++;
            v[cnt] = a * k;
            w[cnt] = b * k;
            s-=k;
            k*=2;
        }
        /*利用二进制存储那么可以抽出所有的在0到s之间的任何数就不用再乘直接将多份打包   
        比如v,w,s分别为3 5 7，则可以打包为3*1,3*2,3*4,另一个也相同这样需要哪个的时候直接用就OK了*/
        if(s>0)
        {
            cnt ++;
            v[cnt] = a * s;
            w[cnt] = b * s;
        }
    }
    n = cnt;
    for(int i = 1; i <= n; i ++)
        for(int j = m; j >= v[i]; j --)
            f[j] = max(f[j], f[j-v[i]]+w[i]);
            
    cout << f[m];
    return 0;
}