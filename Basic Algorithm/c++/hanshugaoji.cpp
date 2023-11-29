#include<iostream>

using namespace std;
// int func(int a,int b = 20,int c = 30)
// {
//   return a+b+c;
// }

void f()
{
  cout << "调用的f()"<<endl;
}
void f(int)
{
  cout << "调用的f(int)"<<endl;
}
void f(double a)
{
  cout << "调用的f(double)"<<endl;
}
void func(int &a)
{
  cout<<"调用func(int&)"<<endl;
}
void func(const int &a)
{
  cout<<"调用func(const int&)"<<endl;
}
int main()
{
  //函数创建的时候可以带参数，如果没有传入值那么就直接使用默认参数，否则就使用传入值
  //优先级：传入>默认
  // cout << func(10)<<endl;
  // cout << func(10,60)<<endl;
  // cout << func(10,0,10)<<endl;
  /*如果某个位置已经有默认参数，那么在这个位置 往后，从左到右都必须要有默认值
    例如func(int a = 10,int b,int c,int d)是错误的*/
    /*如果函数声明有默认参数，那么函数实现就不能要   声明和实现只能有一个有默认参数  
    如int  func2(int a = 10,int b = 10)
    int func2(int a=10,int b = 10)
    {

    }
    这个是错误的*/
    /*占位参数 也可以有默认值
      函数的返回值不可以作为函数重载的条件
      返回值类型  函数名（数据类型）{}比如 int func(int =10){}*/
    /*函数可以重载  也就是 函数名称可以相同 swap(int a,int b){};和swap(double a,double b){};
    重载条件  同一作用域(可能是都是全局作用域)  函数名称相同 函数参数类型不同，或者个数不同，或者顺序不同*/
  f();
  f(10);
  f(10.0);
  int a = 10;
  const int b = 20;
  func(a); //
  func(b);//因为b是const
  func(10);//如果走上面那个那么为 int &a = 10,不合法操作  而下面那一个是 const int &a = 10合法的操作

  /*当函数重载遇上默认参数，出现二义性会报错，例如
  void func2(int a,int b = 10) 和 void func2(int a)  执行func2(10)那么会报错因为左右都可执行*/
}