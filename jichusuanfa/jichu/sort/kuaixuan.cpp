#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5+10;
int q[N];
int n,k;

int quick_sort(int l,int r,int k)
{
    if(l==r) return q[l];
    int i = l - 1, j = r + 1;
    int x = q[(l+r)/2];
    while(i<j)
    {
        do i++;while(q[i]<x);
        do j--;while(q[j]>x);
        if(i<j) swap(q[i],q[j]);
    }
    int sl = j - l + 1;
    if(k<=sl) return quick_sort(l,j,k);
    
    return quick_sort(j+1,r,k-sl);
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i < n; i ++) cin >> q[i];
    cout << quick_sort(0,n-1,k);
}