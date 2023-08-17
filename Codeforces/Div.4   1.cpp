#include<iostream>
#include<algorithm>
using namespace std;

int a[110];

int main()
{
  int n;
  cin >> n;
  while(n--)
  {
    int m;
    cin >> m;
      for(int i = 0;i < m; i ++) cin >> a[i];
      sort(a,a+m);
      bool flag = true;
      for(int i = 1; i < m; i ++){
        if(a[i]==a[i-1]){
          flag = false;
          break;
        }
      }
      if(flag)puts("YES");
      else puts("NO");
  }
  return 0;
}