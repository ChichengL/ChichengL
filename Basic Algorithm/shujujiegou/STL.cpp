#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
#include<time.h>
#include<stdlib.h>
#include<set>
#include<map>
#include<unordered_map>
//pair可以任意定义两种变量
using namespace std;

int main()
{
  /*vecor
  vector<int>a(3,0);
  for(auto x:a)cout<<x<<' ';
  cout<<'\n';
  cout<<a.size()<<' '<<a.empty()<<'\n';
  a.clear();
  for(int i=0;i<10;i++)a.push_back(i);
  cout<<a.front()<<' '<<a.back()<<'\n';
  for(int i=0;i<a.size();i++)cout<<a[i]<<' ';
  puts("");
  for(auto i=a.begin();i!=a.end();i++)cout<<*i<<' ';
  puts("");
  vector<int>b(3,4),c(4,3);//支持直接比较运算，按字典序排序
  if(b>c)cout<<"b > c";
  */
  /*
  pair  看成二元结构体  还自带比较
  pair<int,string>p,q;//支持比较运算，以first为第一关键字，second为第二关键字（字典序）
  p.first=1;
  p.second="abc";
  q.first=1;
  q.second="aac";
  cout<<p.first<<' '<<p.second;
  puts("");
  if(p>q)cout<<"p > q";
  pair<int,string>p;
  p=make_pair(10,"csb");
  p={20,"lst"};
  cout<<p.first<<' '<<p.second;
  */
  /*
  string
  size(),empty(),clear()都可以
  string a="csb";
  a+="def";
  a+="GG";//支持直接加不支持减
  cout<<a<<'\n';
  cout<<a.substr(1,2)<<'\n';//第一个是起始位置第二个是子串长度 
  printf("%s",a.c_str());//a.c_str()返回起始地址
  */
  /*
  queue  队列
  queue<int>q;
  for(int i=0;i<10;i++)q.push(i);
  cout<<q.size()<<' '<<q.empty()<<endl;
  cout<<q.front()<<' '<<q.back()<<endl;
  q.pop();
  cout<<q.front();
  清空一个队列不能用clear  应该是
  q=queue<int>();
  priority_queue,优先队列由堆来实现
  push()  插入一个元素
  top()   返回堆顶元素
  pop()   弹出堆顶元素
  priority_queue<int>heap;
  heap.push(x)//从大到小排序，如果传入-x就是从小到大排序
  srand((unsigned)time(NULL));
  priority_queue<int,vector<int>,greater<int>>heap;//greater表示内置类型从小到大排序less是从大到小排序
  for(int i=0;i<10;i++){
    int t=rand()%100;
    heap.push(t);
  }
  while(!heap.empty()){
    cout<<heap.top()<<' ';
    heap.pop();
  }
  上者为小根堆 默认为大根堆(根节点为最大值)
  */
 /**
  stack
  empty(),size()
  push()  插入一个元素
  //top()   返回堆顶元素
  //pop()   弹出堆顶元素

  deque  双端队列(加强版vector)  效率较低但是功能全面
  size()  empty()  clear()  front()  back()
  push_back()从尾部插入  pop_back()从队尾删除
  push_front()   pop_back()
  */

  //set/multiset   map/multimap,基于二叉平衡树(红黑树)，动态维护有序序列
  /*
    siez()   empty()   clear()   begin()/end()  ++，--返回前驱和后继  时间复杂度O(logn)
    */
   /*
  set/multiset
  set<int>S;//set不能有重复元素有的话输入时会自动忽略   操作时间复杂度都是logn
  除了size()和empty()  为O(1);
  还支持clear()
  multiset<int>MS;//multiset能有重复元素
  insert() 插入一个数
  find()  查找一个数返回&的迭代器
  count()  返回某一个数的个数
  erase()
      (1)输入一个数x，删除所有等于这个数x的结点 O(k + logn)(k是x的个数) (2)输入一个迭代器，删除这个迭代器
  *******  lower_bound()/upper_bound();
  lower_bound返回大于等于x的最小数的迭代器  upper_bound 返回大于x的最大数的迭代器   不存在返回&
  */

  //map/multimap
  /*
    insert()插入的数是一个pair 要做映射
    erase() 输入一个pair或者迭代器
    find()和set一样 
    []可以像数组一样用但是时间复杂度是O(logn)
  
  map<string,int> a;
  a["yxc"]=1;
  cout<<a["yxc"]<<endl;
  lower_bound返回大于等于x的最小数的迭代器  upper_bound 返回大于x的最大数的迭代器   不存在返回&
  */

  /*
  unodered_set,unodered_map,unodered_multiset,unodered_multimap,哈希表
  和上面操作一样(set   和  map 那些)
  绝大部分操作时间复杂度是O(1)(增删改查)
  不支持lower_bound 和 upper_bound(因为是无序的)还有迭代器的加加减减
  unordered_map<string,int>a
  */

  /*
   bitset,压位
   比如bool  以前每个状态一个字节 1024个就要1024个字节就1024b=1kb
   压位后 一个状态只需要一位(一个字节八位)1024个状态也就只需要128个字节了
   可以省八倍空间
   bitset<10000>S     (中间是个数)
   支持  ~S(取反),&,|,^
   >>, <<
   ==, !=
   []  取某一位是0或者1
   count()  返回多少个1
   any()  判断是否至少有一个1
   none()  判断是否全为0

   set(),把所有位置弄成1  
   set(k,v) 将第k位变成v
   reset()  将所有变为0
   flip()  将所有位取反
   flip(k) 将k取反 
  */
  return 0;
}