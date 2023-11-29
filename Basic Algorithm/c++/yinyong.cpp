#include<iostream>

using namespace std;
void swap1(int *a,int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
void swap2(int &a1,int &b1)//相当于创建a的别名a1指向a的内容
{
  int temp = a1;
  a1= b1;
  b1 = temp;
}

// int& test1()
// {
//   int a = 10;
//   return a;
// }
// int &test2()
// {
//   static int a = 10;
//   return a;
// }
int main()
{
  // // int a = 10,b = 20;
  // // //引用比指针语法更方便，引用类似于指针
  // // swap1(&a,&b);//地址传入
  // // cout << "指针" << "a="<<a<< ' '<< "b="<< b<<'\n';
  // // swap2(a,b);
  // // cout << "引用" << "a="<<a<< ' '<< "b="<< b<<'\n';

  // /*引用可作为函数值
  //   1.不能返回局部变量，若要返回函数里面的值则可以加个static 将其放入堆中
  //   2.引用的函数可以作为左值
  // */
  // //  int &ref=test1();
  // int &ref2=test2();//如果函数做左值，那么必须返回引用
  
  // // cout << "ref="<<ref<<endl;
  // // cout << "ref="<<ref<<endl;
  
  // cout << "ref2"<<ref2<<endl;
  // cout << "ref2"<<ref2<<endl;
  // test2() = 1000;
  // cout << "ref2"<<ref2<<endl;
  // cout << "ref2"<<ref2<<endl;

  /*引用的本质是指针常量,指针常量是指针指向不可修改 比如int a = 10, b = 20;如果int& ref = a;那么进行ref = b;是错误的.
  同时创建引用时是需要赋值的,初始化之后就不可改变！！！ 
  引用必须引用一块合法的空间，即int &ref = 10;是错误的，BUT const int &ref = 10;是正确的因为相当于进行了 int temp = 10; const int &ref = temp;*/

  /*如果进行改下操作 int a = 10;  int &res = a;
  相当于是int * const ref = &a;
  ref = 20,就相当于*ref=20 */
  /*如果引用作为函数的形参，不想修改该值可以加上const 
  比如int a = 10;   f(a);
  f(const int &ref) 可以保护ref防止a被修改*/
}