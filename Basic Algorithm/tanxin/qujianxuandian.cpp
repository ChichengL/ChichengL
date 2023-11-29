#include<algorithm>
#include<iostream>
using namespace std;
const int N = 100010;
struct Range
{
    int l,r;
    bool operator< (const Range &W)const
    {
        return r<W.r;
    }
}range[N];

int main()
{
    int n;
    cin >> n;
    for(int i = 0 ; i < n ; i ++)
    {
        int l,r;
        cin >> l >> r;
        range[i] = {l,r};
    }
    sort(range,range+n);
    
    int res = 0,ed = -2e9;
    for(int i = 0 ; i < n; i ++)
    {
        if(range[i].l>ed)
        {
            res ++;
            ed = range[i].r;
        }
    }
    cout << res;
}
/*假设ans是最优解，表示最多有ans个不相交的区间；cnt是可行解，表示算法求出cnt个不相交的区间
显然有ans≥cnt
反证法证明ans≤cnt。
假设ans>cnt，由最优解的含义知，最多有ans个不相交的区间，因此至少需要ans个点才能覆盖所有区间，而根据算法知，只需cnt个点就能覆盖全部区间，且cnt<ans，这与前边分析至少需要ans个点才能覆盖所有区间相矛盾，故ans≤cnt综上所述ans=cnt*/