#include<iostream>

using namespace std;

const int N = 2e5+10;
int tree[N];
int n;

int lowbit(int x)
{
  return x&-x;
}

void update(int i,int val)
{
  while(i<n)
  {
    tree[i]+=val;
    i += lowbit(i);
  }
}

int query(int i)
{
  int sum = 0;
  while(i)
  {
    sum+=tree[i];
    i -= lowbit(i);
  }
  return sum;
}

int main()
{
  cin >> n;
  for(int i = 1; i <= n ; i++)
    update(i,i);
    cout << query(3) << endl;
    cout << query(3)-query(1) << endl;
}