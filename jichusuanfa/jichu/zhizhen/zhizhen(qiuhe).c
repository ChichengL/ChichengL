#include<stdio.h>
void qiuhe(int (*a)[3]){
  for(int i=0;i<5;i++){
    int total=0;
    for(int j=0;j<3;j++){
      total+=*(*(a+i)+j);
    }
    printf("第%d行的元素总和是%d\n",i,total);
  }
}
int main()
{
  int a[5][3];
  for(int i=0;i<5;i++)
    for(int j=0;j<3;j++)
      scanf("%d",&a[i][j]);
  qiuhe(a);
  return 0;
}