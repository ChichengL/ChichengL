#include<stdio.h>

void fanzhuan(int (*p)[3],int (*q)[3]){
  for(int i=0;i<3;i++){
      for(int k=0;k<3;k++){
        *(*(q+i)+k)=*(*(p+k)+i);
      }
  }
}


int main()
{
  int a[3][3],b[3][3];
  for(int i=0;i<3;i++)
    for(int j=0;j<3;j++){
      scanf("%d",&a[i][j]);
    }
  fanzhuan(a,b);
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      printf("%d ",b[i][j]);
    }
    printf("\n");
}
  return 0;
}