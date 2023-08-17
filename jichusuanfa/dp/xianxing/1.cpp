#include<iostream>
using namespace std;
int add(int a,int b)
{
  return a+b;
}
int main()
{
  int & r = add(1,2);
  int *p = add(1,2);
  add(3,4);
  cout << "&后:"<<r<<endl;
  cout << "指针：" << *p;
}