#include<stdio.h>
void fz(char *p,char *q){
  while(*p!='\0'){
    *q=*p;
    q++;
    p++;
  }
  *p='\0';
}

int main()
{
  char s1[100],s2[100];
  gets(s1);
  fz(s1,s2);
  puts(s2);
  return 0;
}
