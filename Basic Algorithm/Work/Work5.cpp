#include<iostream>

using namespace std;

const int N = 100010;
int a[N],temp[N];
int n;

void merge_sort(int l,int r)
{
    if(l>=r) return;
    int mid = (l+r)/2;
    merge_sort(l,mid);
    merge_sort(mid+1,r);
    int i = l, j = mid+1, k = 0;
    while(i<=mid && j<=r)
    {
        if(a[i]<=a[j])
        {
            temp[k++] = a[i++];
        }else{
            temp[k++] = a[j++];
        }
    }
    while(i<=mid) temp[k++] = a[i++];
    while(j<=r) temp[k++] = a[j++];
    for(int i = l,j = 0; i <= r; i ++,j ++)
        a[i] = temp[j];
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i ++) cin >> a[i];
    merge_sort(0,n-1);
    for(int i = 0; i < n; i ++)
        cout << a[i] << ' ';
}