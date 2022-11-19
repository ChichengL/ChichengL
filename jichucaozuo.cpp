#include<bits/stdc++.h>
using namespace std;
int main()
{
  //string a,b;//string相当于插入 a[];
  //cin>>a;//cin的速度比scanf慢很多，大数据用scanf
  // //如果要读入空格那么应该为getline(cin,a);
  // getline(cin,a);

  // //cout<<a;
  // cout<<a.size();//输出a的大小
  // cout<<a.back();//输出a的最后一位
  // cout<<a.empty();//如果a为空输出1否则为0；
  
  // a.append("123");//向最后为插入字符串
  // a.erase(0,3);//位置不能超出最后那个不删除，如1234ABCD；输出4ABCD；
  // string可以直接比较大小
  // // cout<<a.substr(1,2);//输出子字符串，起始和结束不能超过
  
  // 1.输出string  用for
  // for(int i=0;i<a.size();i++)cout<<a[i];
  // 2.用foreach但是不能有下标
  //for(char i :a)cout<<i;
  
  // int m,n;
  // cin>>m>>n;
  // cout<<max(m,n)<<endl<<min(m,n);
  // double c;
  // cin>>c;
  // cout<<abs(c);

  int a[5]={0,1,2,3,4};
  reverse(a,a+2);//反转[0,2);
  for(int i:a)cout<<i<<' ';
  sort(a,a+5);
  for(int i:a)cout<<i<<' ';
  return 0;
}