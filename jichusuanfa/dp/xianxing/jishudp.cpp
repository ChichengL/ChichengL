#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

int get(vector<int>num,int l,int r)
{
  int res  = 0;
  for(int i = l; i >= r; i --)
    res =  res *10 + num[i];
  return res;
}

int power10(int x)
{
  int res = 1;
  while(x--) res *=10;//求后面的多少位数
  return res;
}

int count(int n,int x)
{
  if(!n) return 0;

  vector<int>num;//把n的每一位弄出来
  while(n)
  {
    num.push_back(n%10);
    n/=10;
  }
  n = num.size();
  int res = 0;//答案
  for(int i = n - 1 - !x; i >= 0; i --)//当x为0从第二位开始枚举
  {
    if(i < n-1)//除开第一位
    {
      res += get(num,n-1,i+1) * power10(i);//倒着存储的  因为要求到i前面的数
      if(!x) res -= power10(i);
    }
    if(num[i]==x)res += get(num,i-1,0)+1;
    else if(num[i]>x) res += power10(i);
  }
  return res;
}

int main()
{
  int a,b;
  while(cin >> a >> b, a||b)
  {
    if(a>b)swap(a,b);
    for(int i = 0; i < 10; i ++)
      cout << count(b,i)-count(a-1,i)<<' ';
    cout << endl;
  }
}


#include <iostream>
# include <cmath>
using namespace std;

int dgt(int n) // 计算整数n有多少位
{
    int res = 0;
    while (n) ++ res, n /= 10;
    return res;
}

int cnt(int n, int i) // 计算从1到n的整数中数字i出现多少次 
{
    int res = 0, d = dgt(n);
    for (int j = 1; j <= d; ++ j) // 从右到左第j位上 数字i出现多少次 
    {
        // l和r是第j位左边和右边的整数 (视频中的abc和efg); dj是第j位的数字
        int p = pow(10, j - 1), l = n / p / 10, r = n % p, dj = n / p % 10;
        // 计算第j位左边的整数小于l (视频中l = 000 ~ abc - 1)的情况 左边不等于abc的时候 说明都是比abc小的数字  
        if (i) res += l * p; //如果不是统计数字0 左边直接乘p就行了 n=ab3xxx p=1000  
//n=1236055 6000-6999这里1000  第j位上的6出现了p次 但是左边还有16000-16999 26000-26999 36000-36999...1226000-1226999 共左边数字l（即123）个 所以是l*p 
        else if (!i && l) res += (l - 1) * p; // 统计的数字i = 0, 左边高位不能全为0(视频中xxx = 001 ~ abc - 1) 
//少了0000-0999的一种情况 从10000-10999 开始 ... 1220000-1220999 13000-13999 共(l-1)次 

// 计算第j位左边的整数等于l (视频中l = abc)的情况 只会和*j位后面的数*有关



//下面就是l的左边相等的情况 对第j位上 不会多算6000-6999 ...1226000-1226999里面的任意个集合 123开始的情况
        if ( (dj > i) && (i || l) ) res += p;//第j位比现在统计的数字大 就可以直接加上p中情况 
// n=1236055  则有1235000-1235999 999+1种情况 即p种 
//当统计的数字i==0 且 l==0， 举例  n=123456 l==0 第j位为1  就是p=100000 此时000000-099999是不成立的 因为我要统计第j位为i的时候 有多少个这样的 数 而此时   000000-099999 显然和 100000-199999 第j-1位为2的时候重复了

        if ( (dj == i) && (i || l) ) res += r + 1;//这是r有多少个 就是多少个+1
//if(dj==i) n=1236055  1236000-1236055   即55+1种情况
//当统计的数字i==0 且 l==0， 举例  n=123456 l==0且i==0 就是000000 -0123456 而这个时候显然和 第j-1的位的时候重复了100000-109999

//if(dj>i) n=1236000 则有1237000-1237999 所以是0 

    }
    return res;
}

int main()
{
    int a, b;
    while (cin >> a >> b , a)
    {
        if (a > b) swap(a, b);
        for (int i = 0; i <= 9; ++ i) cout << cnt(b, i) - cnt(a - 1, i) << ' ';
        cout << endl;
    }
    return 0;
}
