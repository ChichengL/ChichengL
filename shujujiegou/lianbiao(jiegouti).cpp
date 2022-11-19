#include<iostream>
using namespace std;
typedef struct Node{
  int date;
  Node *next;
}LinkNode;
void createNode(LinkNode *&L,int a[],int n)
{
  LinkNode *s,*r;
  r=(LinkNode *)malloc(sizeof(LinkNode));
  for(int i=0;i<n;i++)
  {
    s=(LinkNode *)malloc(sizeof(LinkNode));
    s->date=a[i];
    r->next=s;
    r=s;
  }
  r->next=NULL;
}
void headinsert()
