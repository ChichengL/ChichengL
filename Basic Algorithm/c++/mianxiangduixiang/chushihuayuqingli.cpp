#include<iostream>

using namespace std;

//构造函数初始化对象成员，析构函数对象销毁前自动调用，用于清理    两者都会自动调用
/*语法
  构造函数   类名(){}  无返回值也没有void 可以有参数所以可重载  无需手动能自动调用只会调用一次
  析构函数   ~类名(){} 无返回值也没void 没有参数所以不能重载    销毁前才会调用无需手动能自动调用只会调用一次
    不写也行 编译器会自动创造*/
    /*构造函数分为  有参和无参或者  普通和拷贝 
      调用方式  括号
               显示
               隐式转换*/
              //类
class Person
{
  public:
  Person()
  {
    cout << "无参构造函数的调用"<<endl;
  }
  Person(int a,int height)
  {
    age = a;
    m_Height = new int(height);
    cout << "有参构造函数的调用"<<endl;
  }
  //拷贝构造函数
  Person(const Person &p)
  {
    
    cout << "Person 拷贝构造函数调用"<<endl;
    age=p.age;

    m_Height =new int(*p.m_Height);//深拷贝操作，在堆区重新神奇空间，进行拷贝操作
  }

  ~Person()
  {
    //通常是将堆区开辟的数据释放干净，如果有堆区的数据，那么最好自己提供拷贝函数，防止浅拷贝带来的问题
    if(m_Height!=NULL)
    {
      delete m_Height;//如果是浅拷贝那么在释放的时候会出现重复释放
      m_Height = NULL;//防止出现野指针
    }
    cout << "析构函数的调用"<<endl;
  }
  
  int age;
  int *m_Height;//以便开辟在堆区 


};

  /*初始化列表   语法:    构造函数():属性1(值1),属性2(值2)....{}
  */
class P
{
  public:
  // P(int a,int b,int c)
  // {
  //   ma = a;
  //   mb = b;
  //   mc = c;
  // }
  //   P():ma(10),mb(20),mc(30){};//这样有点呆板可以这样该
    P(int a,int b,int c):ma(a),mb(b),mc(c){};
    int ma;
    int mb;
    int mc;
};
void test01()
{
  // 括号法 
  // Person p1;//默认构造函数的调用
  // Person p2(10);
  // Person p3(p2);
  // 注意事项 调用默认构造函数的时候，不要加();  如果加了()，相当于是函数的声明
  // cout << p2.age<<endl;
  // cout << p3.age<<endl;

  // 显示法
  // Person p1;
  // Person p2 = Person(10);//有参构造
  // Person p3 = Person(p2);//拷贝构造

  // Person(10);//匿名对象，当行执行结束后，系统会立即回收匿名对象
  // cout <<"aaaaaaaaaaaaaa"<<'\n';
  /*注意事项
    不要用拷贝构造函数初始化匿名对象
    如Person(p3)  编译器会认为 Person(p3) ==  Person p3 对象声明*/

    // 隐式法
    // Person p4 = 10;//相当于Person p4 = Person(10);
    // Person p5 = p4;//拷贝构造 

    // 拷贝构造函数使用时机 
    // 1.使用一个已经创建完毕的对象来初始化一个新对象 Person p2(p1) 
    //   2.值传递的方式给函数参数传值 void dowork(Person p){}  void test02(){Person p;dowork(p)} 调用无参构造函数和拷贝构造函数
    //   3.值方式返回局部对象Person dowork2(){Person p1;return p1} void test03(){Person p = dowork2()}调用无参构造函数和拷贝构造函数   p1 和p是不同的  返回p1 的时候拷贝了p1的值让他为p2 ， 然后p=p2 
    //   如果用户定义有参构造函数 c++ 不在提供默认的无参构造，但是会提供默认拷贝构造
    //   比如Person(int a){age = a},只写了这一个的话那么  Person b是错误的 但是Person b(10)是正确的
    //   如果用户定义拷贝构造函数，那么c++不会提供其他构造函数
    //   创建一个类的时候每个类都添加至少3钟函数 1.默认构造(空实现) 2.析构函数(空实现)  3.拷贝构造(值拷贝)
 }
 void test02()
 {
  Person p1(18,160);
  cout << "p1的年龄和身高为:"<<p1.age<<' ' << *p1.m_Height<<endl;
  Person p2(p1);
  cout << "p2的年龄和身高为:"<<p1.age<<' ' << *p1.m_Height<<endl;
  //Person p2(p1)如果利用编译器提供的拷贝函数(也就是自己没写！！！)，会做浅拷贝操作，使得堆区内存重复释放，比如有个p1内有成员是指针指向一个确定值的空间，然后p2进行(浅拷贝操作)那么会使p2的相应的指针指向同一个地址，然后在调用析构函数的时候会使得该地址被重复释放
  //浅拷贝的问题可以利用深拷贝来解决是不同对象的指针指向不同地址，就不会重复释放
 }

void test03()
{
  // P p(10,20,30);
  P p(10,20,30);
  cout << p.ma << ' ' << p.mb << ' ' << p.mc << endl;
}
class Phone
{
  public:
    string PhoneName;
  Phone(string name):PhoneName(name){}
};
class People
{
  public:
    string mname;
    Phone mPhone;
    People(string name,string phonename):mname(name),mPhone(phonename){};//
};
void test04()
{
  People p("张三","Iphone14ProMax1TB");
  cout << p.mname << "拿着"<< p.mPhone.PhoneName<< endl;
}
/* 对于静态成员变量

使用**static**修饰

1.所有对象共享同一份数据

2.在编译阶段分配内存

3.类内声明，类外初始化

 对于静态成员函数

1.所有对象共享一个函数

2.静态函数只能访问静态成员变量
静态成员变量 不属于某个对象上，所有对象都共享一份数据
静态变量有两种访问方式
1.通过对象进行访问，2 通过类名进行访问*/
class LH
{
  public:
    static int m_a;
    static void func()
    {
      m_a = 100;
      //m_b = 200; 这个是错误的
      cout<<"静态成员函数调用"<<endl;
    }
    int m_b;
    private:
      static void func2()
      {
        cout << "func2的调用"<<endl;
      }
    
};
int LH::m_a = 100;//如果改变那么就全部改变
void test05()
{
  LH l,r;
  cout << l.m_a<<endl;
  cout << r.m_a << endl;
}
void test06()
{
  //1
  LH l;
  cout << l.m_a<< endl;
  //2
  cout << LH::m_a << endl;
}
void test07()
{
  LH l;
  l.func();
  LH::func();
}
void test08()
{
  // LH::func2();这是错误的  类外访问不到私有静态函数
}

/*空对象占用内存空间为1

c++编译器会给每个空对象也分配一个字节空间，是为了区分空对象占内存的位置

每个空对象也应该有一个独一无二的字节*/
class W
{
  public:
    int m_a;//非静态成员变量 属于类的对象上
    static int m_b;//静态成员变量 不属于类的对象上
    void func(){}// 非静态成员函数  不属于类对象上
};
int W::m_b = 0;

void test09()
{
  W w;
  cout << sizeof(w);
}

class O
{
  public:
    int age;
    O(int age)
    {
      this->age = age;
    }
    O& oando(O &p)//返回本体要引用的返回
    {
      this->age+=p.age;
      return *this;//返回的o2
    }
};

void test10()
{
  O o(18);
  cout << o.age<<endl;
}
void test11()
{
  O o1(18);
  O o2(18);
  o2.oando(o1);
  o2.oando(o1).oando(o1).oando(o1).oando(o1).oando(o1);//如果oando是void类型那么就不可以，but如果是返回类成员就OK啦
  cout << o1.age << endl;
  cout << o2.age<< endl;
}
//空指针调用成员函数
class Pw
{
  public:
    void show()
    {
      cout << "this Pw show()"<<endl;
    }
    void ShowM()
    {
      if(this==NULL)
      {
        return ;
      }
      cout << "m = " << this->m << endl;
    }
    int m;
};
void test12()
{
  Pw *p = NULL; 
  p->show();
  p->ShowM();
}
int main()
{
  // test01();
//  test02();
  // test03();
  // test04();
  // test05();
  // test06();
  // test07();
  // test09();
  // test10();
  // test11();
  test12();
  return 0;
}