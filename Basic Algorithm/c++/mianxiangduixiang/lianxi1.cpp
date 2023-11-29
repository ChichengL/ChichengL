#include"iostream"
#include"cmath"
using namespace std;

class Circle
{
  private:
    int x;
    int y;
    int r;
  public:
    void setx(int x1)
    {
      x=x1;
    }
    void sety(int y1)
    {
      y = y1;
    }
    void setr(int r1)
    {
      r=r1;
    }
    bool pd(int x1,int y1)
    {
      double s = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
      if(s - r>1e-6) return false;
      else return true;
    }
};

int main()
{
  Circle c;
  c.setx(0);
  c.sety(0);
  c.setr(10);
  if(c.pd(11,0))
  {
    cout << "点在圆内"<<'\n';
  }
  else cout << "点不在圆内"<<'\n';
}