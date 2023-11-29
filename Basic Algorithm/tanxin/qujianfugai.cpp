#include<algorithm>
#include<iostream>
using namespace std;

const int N = 100010;
struct Range
{
    int l,r;
    bool operator< (const Range &W)const 
    {
        return l<W.l;
    }
}range[N];

//先排序然后    再在能覆盖一部分目标区间里找到右值最大那个，再把st更新为那个
int main()
{
    int n,st,ed;
    cin >>st >>ed;
    cin >> n;
    for(int i = 0; i < n; i ++)
    {
        int l,r;
        cin >> l >> r;
        range[i]={l,r};
    }
    
    sort(range,range+n);
    int res = 0;
    bool success = false;
    for(int i = 0; i < n; i ++)
    {
        int j = i,r = -2e9;//r切记要放在内部
        /*例如4  5
              2
              4 5 
              11 12这个例子 r在外部的话 r经过第一次循环后始终为5 ，不能更新了此时区间是断掉的但是 第一个if不会循环*/
        while(j<n && range[j].l<= st)
        {
            r = max(r,range[j].r);
            j++;
        }
        if(r<st)
        {
            res = -1;
            break;
        }
        res ++;
        if(r>=ed)
        {
            success = true;
            break;
        }
        st = r;
        i = j-1;
        
    }
    if(!success) res = -1;
    cout << res;
}