#include<iostream>

using namespace std;

const int N=100010;

int s[N][26],cnt[N];
int n,idx;
void add(char str[])
{
  int p=0;
  for(int i=0;str[i];i++)
  {
    int u=str[i]-'a';
    if(!s[p][u])s[p][u]=++idx;
    p=s[p][u];
  }
  cnt[p]++;
}
int query(char str[])
{
  int p=0;
  for(int i=0;str[i];i++)
  {
    int u=str[i]-'a';
    if(!s[p][u])return 0;
    p=s[p][u];
  }
  return cnt[p];
}
int main()
{
  // cin.tie(NULL);
  // ios::sync_with_stdio(false);
  //上面相当于是关闭了stdio头文件的内容导致scanf，printf，putchar，getchar都不可以用
  scanf("%d",&n);
  while(n--){
    char op,str[N];
    cin>>op;
    if(op=='I'){
      cin>>str;
      add(str);
    }else{
      cin>>str;
      printf("%d\n",query(str));
    }
  }

  return 0;
}