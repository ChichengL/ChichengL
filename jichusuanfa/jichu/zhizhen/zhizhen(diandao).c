/*#include<stdio.h>
void fanzhuan(int *a,int *b){
  for(int i=0;i<10;i++){
    b[i]=a[10-1-i];
  }
  for(int i=0;i<10;i++)a[i]=b[i];
}

int main()
{
  int a[10],b[10];
  for(int i=0;i<10;i++){
    scanf("%d",&a[i]);
  }
  fanzhuan(a,b);
  for(int i=0;i<10;i++)printf("%d ",a[i]);
  return 0;
}*/
#include<stdio.h>
void fanzhuan(int *p,int *q){
  int temp;
  while(p<q){
    temp=*p;
    *p=*q;
    *q=temp;
    p++;
    q--;
  }
}

int main()
{
  int a[10],b[10];
  for(int i=0;i<10;i++){
    scanf("%d",&a[i]);
  }
  int *head=&a[0];
  int *tail=&a[9];
  fanzhuan(head,tail);
  for(int i=0;i<10;i++)printf("%d ",a[i]);
  return 0;
}