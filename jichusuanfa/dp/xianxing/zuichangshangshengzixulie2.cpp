#include<iostream>
using namespace std;
const int N = 100010;

int n;
int a[N];
int q[N];

int main()
{
  cin >> n;
  for(int i = 0; i < n; i ++) cin >> a[i];

  int len = 0;
  q[0] = -2e9; //保证必定能找到某个数
  for(int i = 0; i < n; i ++)
  {
    int l = 0, r = len;
    while(l<r)
    {
      int mid = l+r+1 >> 1; // 因为求的是l = mid 所以 mid = l+r + 1;
      if(q[mid] < a[i])//找到小于ai的最大数
      {
        l = mid;
      }else r = mid - 1;
    }
    len = max(len , r + 1);
    q[r+1] = a[i];//qr是小于ai的数所以直接q(r+1) = ai;
  }
  cout << len;
}