#include<stdio.h>
#include<string.h>
void f(char *s,int m,int n,char *p,char *q){
  for(int i=0;i<n-m;i++){
    *s=*(q+i);
    s++;
  }
  for(int i=0;i<m;i++){
    *s=*(p+i);
    s++;
  }
  *s='\0';
}

int main()
{
  char s[30],s2[30];
  gets(s);
  int m,n;
  scanf("%d",&m);
  n=strlen(s);
  char *head=s;
  char *tail=s+m;
  f(s2,m,n,head,tail);
  printf("%s",s2);
  return 0;
}