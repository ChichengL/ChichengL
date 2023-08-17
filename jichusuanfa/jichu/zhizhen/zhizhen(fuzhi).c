#include<stdio.h>
#include<string.h>
void f(char *s,char *s2,int m,int n){
  for(int i=m-1;i<n;i++){
    *s2=*(s+i);
    s2++;
  }
  *s2='\0';
}
int main()
{
  char s[30],s2[30];
  gets(s);
  int m,n=strlen(s);
  scanf("%d",&m);
  f(s,s2,m,n);
  printf("%s",s2);
  return 0;
}