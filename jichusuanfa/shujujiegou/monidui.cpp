#include<iostream>

using namespace std;

const int N=1e5+10;

int h[N],hp[N],ph[N];//ph[k]=i对应第k个插入的数在数组中的位置  hp[i]是当前位置的数对应数组中的第几个插入
int n,idx,Size;

void heap_swap(int a,int b)
{
  swap(ph[hp[a]],ph[hp[b]]);
  swap(hp[a],hp[b]);
  swap(h[a],h[b]);
}
void down(int u)
{
  int t=u;
  if(2*u<=Size&&h[t]>h[2*u])t=2*u;
  if(2*u+1<=Size&&h[t]>h[2*u+1])t=2*u+1;
  if(u!=t)
  {
    heap_swap(u,t);
    down(t);
  }
}
void up(int u)
{
  while(u/2&&h[u]<h[u/2]){
    heap_swap(u,u/2);
    u/=2;
  }
}
int main()
{
  cin>>n;
  while(n--)
  {
    string op;
    int k,x;
    cin>>op;
    if(op=="I")
    {
      cin>>x;
      idx++;
      Size++;
      h[Size]=x;
      ph[idx]=Size;
      hp[Size]=idx;
      up(Size);
    }else if(op=="PM"){
      cout<<h[1]<<endl;
    }else if(op=="DM"){
      heap_swap(1,Size);
      Size--;
      down(1);
    }else if(op=="D"){
      cin>>k;
      k=ph[k];
      heap_swap(k,Size);
      Size--;
      down(k),up(k);
    }else{
      cin>>k>>x;
      k=ph[k];
      h[k]=x;
      down(k),up(k);
    }
  }
  return 0;
}