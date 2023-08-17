#include<queue>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int N = 100010;
struct Range
{
    int l,r;
    bool operator< (const Range & W)const
    {
        return l<W.l;
    }
}range[N];

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++)
    {
        int l,r;
        cin >>l >> r;
        range[i] = {l,r};
    }
    sort(range,range+n);
    priority_queue<int,vector<int>,greater<int>>heap;//用一个小根堆来存储每个组的最大右端点值
    
    for(int i = 0; i < n; i ++)
    {
        auto r = range[i];
        if( heap.empty() || heap.top() >= r.l) heap.push(r.r);
            /*否则（heap.empty() || heap.top() >= r.l），需要新开一个组，直接将当前区间的右端点push进堆即可。*/
        else 
        {
          /*若目前查看的区间的左端点大于小根堆堆顶的值(range[i].l > heap.top())，那么至少说明，当前区间能放到这个组中，则将堆顶元素pop出来，堆中存入新的最大右端点代表这个组。*/
            heap.pop();
            heap.push(r.r);
        }
    }
    cout << heap.size();
}
