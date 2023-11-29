#include<iostream>

using namespace std;
#define PI 3.1415926
/*struct 默认权限是公共的
class 默认权限是私有的
成员属性设置为私有的好处 可以自己控制读写权限   对于写的可以检测数据的有效性
struct 中可以有其他的struct 同样class里面也是可以的 
*/
//假如 class Point{};那么如果要在类外函数实现 那么要表明作用域 如void Point::setX(int x){m_x = x};
class Circle
{
  //访问权限
  /*public 公共权限 成员 类内，类外都可访问
  protected 保护权限 成员 类内可以访问，而类外不行 儿子也可以访问父亲的保护内容
  private 私有权限 成员 类内可以访问，而类外不行  儿子不可以访问父亲的私有内容*/
  public:
    //属性
    int m_r;
    //行为
    double zc()
    {
      return 2*PI*m_r;
    }
};
class Student
{
  public:
    string xm;
    string xh;
    void xmfz(string a)
    {
      xm = a;
    }
    void xhfz(string a)
    {
      xh=a;
    }
    void print()
    {
      cout << "姓名"<<xm<<endl;
      cout <<"学号"<<xh<<endl;
    }
};
int main()
{
  //通过圆类创建
  Circle c1;
  c1.m_r=10;
  // cout << "圆的周长"<<c1.zc()<<endl;
  Student s;
  string a = "202231061006";
  string b = "陈双彬";
  s.xhfz(a);
  s.xmfz(b);
  s.print();
}