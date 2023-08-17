#include<iostream>

using namespace std;

int main()
{
  string s = "";
  int i = 1;
  while(s.size()<100)
  {
    if(i%3==0) s+='F';
    if(i%5==0) s+='B';
    i++;
  }
  int n,m;
  cin >> n;
  while(n--)
  {
    cin >> m;
    string str;
    cin >> str;
    if(s.find(str)!=string::npos) puts("YES");
    else puts("NO");
  }
}