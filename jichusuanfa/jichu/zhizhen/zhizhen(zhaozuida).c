#include<stdio.h>
#include<string.h>
int main(){
  char s[6],max[6];
  scanf("%s",s);
  strcpy(max,s);
  while(1){
    scanf("%s",s);
    if (strcmp(s,"*****")==0)
    {
      break;
    }
    if(strcmp(max,s)<0){
      strcpy(max,s);
    }
  }
  printf("%s",max);
  return 0;
}