#include<iostream>
#include<algorithm>

using namespace std;

void divide(int n)
{
  for(int i = 2; i <= n / i; i ++)
  {
    int s = 0;
    while(n%i == 0)
    {
      n/=i;
      s++;
    }
    if(s)printf("%d %d\n",i,s);
  }
  if(n>1) printf("%d %d\n",n,1);
  puts("");
}

int main()
{
  int n;
  cin >> n;
  while(n -- )
  {
    int x;
    cin >> x;
    divide(x);
  }
  return 0;
}