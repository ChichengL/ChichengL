#include<stdio.h>
int cnt=0;
void cd(char *p){
  while(*p!='\0'){
    p++;
    cnt++;
  }
}

int main()
{
  char s1[100],s2[100];
  gets(s1);
  cd(s1);
  printf("%d",cnt);
  return 0;
}
