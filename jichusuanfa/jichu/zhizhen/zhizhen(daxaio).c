#include<stdio.h>
int max(int *p){
  int max=*p;
  int index=0;
  for(int i=0;i<10;i++){
    if(max<*(p+i)){
      max=*(p+i);
      index=i;
    }
  }
  return index;
}
int min(int *p){
  int min=*p;
  int index=0;
  for(int i=0;i<10;i++){
    if(min>*(p+i)){
      min=*(p+i);
      index=i;
    }
  }
  return index;
}
int main()
{
  int a[20];
  for(int i=0;i<10;i++)scanf("%d",&a[i]);
  printf("最大值下标:%d，最小值下标:%d",max(a),min(a));
  return 0;
}
