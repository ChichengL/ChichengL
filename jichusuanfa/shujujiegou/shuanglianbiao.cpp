#include<iostream>

using namespace std;

const int N=1e5+10;

int e[N],l[N],r[N],idx;
//左边界为0，右边界为1
//让左边界的右边指向右边界，右边界的左边指向左边界
void inti()
{
  //因为0,1用了idx从2起
  idx=2;
  l[1]=0;
  r[0]=1;
}
void add(int k,int x)
{
  e[idx]=x;
  r[idx]=r[k];
  l[idx]=l[r[k]];
  l[r[k]]=idx;
  r[k]=idx;
  idx++;
}
void remove(int k)
{
  r[l[k]]=r[k];
  l[r[k]]=l[k];
}

int main()
{
  int n;
  scanf("%d",&n);
  inti();
  while(n--)
  {
    char op[5];
    int k,x;
    scanf("%s",op);
    if(op[0]=='L'){
      cin>>x;
      add(0,x);//从左边界的右边插入插入
    }else if(op[0]=='R'){
      cin>>x;
      add(l[1],x);//在右边界的左边插入一个数就是从尾部插入
    }else if(op[0]=='D'){
      cin>>k;
      remove(k+1);
    }else{
      cin>>k>>x;
      if(op[1]=='L'){
        add(l[k+1],x);
      }else{
        add(k+1,x);
      }
    }
  }
  for(int i=r[0];i!=1;i=r[i])
    cout<<e[i]<<' ';
  return 0;
}