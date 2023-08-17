#include<stdio.h>
int a[10];
void print(){
  for(int i=0;i<10;i++){
    printf("%d ",a[i]);
  }
  printf("\n---------------\n");
}

int main(){
  for(int i=0;i<10;i++){
    a[i]=rand()%20;
  }
  print();
  for(int i=0;i<10;i++){
    int k=i,temp=a[i];
    for(int j=i+1;j<10;j++){
      if(temp>a[j]){
        temp=a[j];
        k=j;
      }
    }
    int t=a[i];
    a[i]=a[k];
    a[k]=t;
  }
  print();
  return 0;
}