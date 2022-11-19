#include<stdio.h>
void max(int *p){
  int max=*p;
  int index=0;
  for(int i=0;i<10;i++){
    if(max<*(p+i)){
      max=*(p+i);
      index=i;
    }
  }
  int t=*(p+index);
  *(p+index)=*(p+9);
  *(p+9)=t;
}
void min(int *p){
  int min=*p;
  int index=0;
    for(int i=0;i<10;i++){
      if(min>*(p+i)){
        min=*(p+i);
        index=i;
      }
    }
  int t=*(p+index);
  *(p+index)=*p;
  *p=t;
  }
int main()
{
  int a[20];
  for(int i=0;i<10;i++)scanf("%d",&a[i]);
  min(a);
  max(a);
  for(int i=0;i<10;i++){
    printf("%d ",a[i]);
  }
  return 0;
}
