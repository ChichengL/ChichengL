#include<iostream>
using namespace std;
const int N = 1010;
int a[N],f[N];
int n;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> a[i];
    
    for(int i = 1; i <= n; i ++)
    {
        f[i] = 1;//自己本身算一个
        for(int j = 1; j < i; j ++)
        {
            if(a[j]<a[i])//如果单调上升的话
            {
                f[i] = max(f[i],f[j]+1);
            }
        }
    }
    int res = 0;
    for(int i = 1; i <= n; i ++) res = max(res,f[i]);
    cout << res;
    return 0;
}