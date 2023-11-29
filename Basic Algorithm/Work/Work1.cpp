// #include<iostream>

// using namespace std;

// struct SqList{
//   int *data; //动态数组
//   int length; //表长
//   int maxSize; //最大容量
// };

// void InitList(SqList &L, int size){
//   L.data = new int[size]; //分配空间
//   L.length = 0; //初始长度为0
//   L.maxSize = size; //初始最大容量为size
// }

// void MergeList(SqList A, SqList B, SqList &C){
//   InitList(C, A.length + B.length); //初始化C，最大容量为A和B的长度之和
//   int i = 0, j = 0, k = 0; //i,j,k分别指向A,B,C的当前位置
//   while(i < A.length && j < B.length){ //当A和B都有元素时
//     if(A.data[i] < B.data[j]){ //如果A的元素小于B的元素
//       C.data[k++] = A.data[i++]; //将A的元素复制到C，并移动指针
//     }else if(A.data[i] > B.data[j]){ //如果A的元素大于B的元素
//       C.data[k++] = B.data[j++]; //将B的元素复制到C，并移动指针
//     }else{ //如果A和B的元素相等
//       C.data[k++] = A.data[i++]; //将A或B的元素复制到C，并移动指针，去掉重复元素
//       j++; 
//     }
//   }
//   while(i < A.length){ //如果A还有剩余元素
//     C.data[k++] = A.data[i++]; //将剩余元素复制到C，并移动指针
//   }
//   while(j < B.length){ //如果B还有剩余元素
//     C.data[k++] = B.data[j++]; //将剩余元素复制到C，并移动指针
//   }
//   C.length = k; //更新C的长度
// }

// int main()
// {
//   SqList A,B,C;
//   InitList(A,5);
//   InitList(B,5);
//   int cnt = 0;
//   for(int i = 1; i <= 6; i ++)
//   {
//     if(i%2) A.data[cnt] = i;
//     else B.data[cnt++] = i;
//   }
//   A.length = B.length = 3;
//   MergeList(A,B,C);

//   for(int i = 0; i < C.length ; i ++)
//   {
//     cout << C.data[i] << ' ';
//   }
// }



#include<iostream>

using namespace std;

//定义链表结点结构体
typedef struct LNode{
  int data; //数据域
  struct LNode *next; //指针域
}LNode, *LinkList;

//初始化链表
void InitList(LinkList &L){
  L = (LNode*)malloc(sizeof(LNode)); //分配头结点空间
  L->next = NULL; //头结点指针域置空
}

//合并两个链表
void MergeList(LinkList A, LinkList B, LinkList &C){
  InitList(C); //初始化C
  LNode *p = A->next, *q = B->next, *r = C; //p,q,r分别指向A,B,C的第一个结点
  while(p && q){ //当A和B都有元素时
    if(p->data < q->data){ //如果A的元素小于B的元素
      r->next = p; //将A的元素链接到C
      p = p->next; //移动p指针
      r = r->next; //移动r指针
    }else if(p->data > q->data){ //如果A的元素大于B的元素
      r->next = q; //将B的元素链接到C
      q = q->next; //移动q指针
      r = r->next; //移动r指针
    }else{ //如果A和B的元素相等
      r->next = p; //将A或B的元素链接到C，并去掉重复元素
      p = p->next; //移动p指针
      q = q->next; //移动q指针
      r = r->next; //移动r指针
    }
  }
  if(p){ //如果A还有剩余元素
    r->next = p; //将剩余元素链接到C
  }
  if(q){ //如果B还有剩余元素
    r->next = q; //将剩余元素链接到C
  }
}

void insert(LinkList &L,int x)
{
  LNode* p = L;
  while(p->next)
    p = p->next;
  LNode* q = (LNode*)malloc(sizeof(LNode));
  q->data = x;
  q->next = NULL;
  p->next = q;
}

//打印链表
void PrintList(LinkList L){
  LNode *p = L->next; //p指向第一个结点
  while(p){ //当p不为空时
    printf("%d ", p->data); //输出p的数据域，用空格隔开
    p = p->next; //移动p指针
  }
  printf("\n"); //换行
}

//释放内存
void DestroyList(LinkList &L){
  LNode *p = L, *q; //p,q分别指向当前结点和下一个结点
  while(p){
    q = p->next; //q指向下一个结点
    free(p); //释放当前结点空间
    p = q; //p指向下一个结点
  }
  L = NULL; //头指针置空
}

//测试代码是否正确
int main(){
  LinkList A, B, C; //定义三个链表
  
  InitList(A); //初始化A 
  InitList(B); //初始化B
  
  for(int i = 1; i <= 6; i ++)
  {
    if(i%2) insert(A,i);
    else insert(B,i);
  }
  
  MergeList(A, B, C); //合并A和B，得到C
  
  PrintList(C); //打印C，应该输出1,2,3,4,5,6
  
  DestroyList(A); //释放A
  DestroyList(B); //释放B
  DestroyList(C); //释放C
  
  return 0;
}
