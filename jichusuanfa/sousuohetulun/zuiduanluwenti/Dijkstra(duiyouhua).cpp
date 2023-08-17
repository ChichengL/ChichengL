#include<iostream>
#include<cstring>
#include<queue>

using namespace std;
typedef pair<int,int> PII;
const int N=1e6+10;
int n, m;
int h[N], w[N], e[N], ne[N], idx;//w是权重
int dist[N];
bool st[N];

void add(int a,int b, int c)
{ 
  e[idx] = b, ne[idx] = h[a], w[idx]=c, h[a] = idx ++;//利用邻接表存储n和m都较多
}
int dijkstra()
{
  memset(dist, 0x3f, sizeof dist);
  dist[1] = 0;

  priority_queue<PII,vector<PII>,greater<PII>>heap;//创建小根堆
  heap.push({0,1});//第一个是距离，第二个是编号
  //因为pair是以第一个为关键进行比较的要找到距离最近的那个那么就要将距离放在第二位
  while(heap.size())
  {
    auto t = heap.top();
    heap.pop();

    int ver = t.second ,distance = t.first;
    if(st[ver]) continue;//如果这个出现过 
    st[ver] = true;//该点未出现过就加入
    for(int i = h[ver]; i != -1; i = ne[i])
    {
      int j = e[i];
      if(dist[j] > distance + w[i])
      {
        dist[j] = distance + w[i];
        heap.push({dist[j],j});
      }
    }
  }
  if(dist[n] == 0x3f3f3f3f)return -1;
  return dist[n];
}
int main()
{
  cin >> n >> m;
  
  memset(h, -1, sizeof h);

  while(m--)
  {
    int a, b, c;
    cin >> a >> b >>c;
    add(a,b,c);
  }
  int t = dijkstra();
  cout << t;
  return 0;
}