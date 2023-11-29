#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10;
char g[N][N];
int n;
int dx[5] = {-1, 0, 1, 0,0}, dy[5] = {0, 1, 0, -1,0};

void turn(int x,int y)
{
    for(int i = 0; i < 5; i ++)
    {
        int a = x + dx[i], b = y + dy[i];
        if(a>=0&&a<5&&b>=0&&b<5)
        {
            g[a][b] = '0'+('1'-g[a][b]);
        }
    }
}

int check()
{
    int ans = 1e9;
    for(int k = 0; k < 1 << 5; k ++)
    {
        int res = 0;
        char back[N][N];
        memcpy(back,g,sizeof g);
        for(int i = 0; i < 5; i ++)// k单纯只是保存了第一行按开关的32种方式，与输入数据无关。
        {
            if(k>>i&1)//第一行的五个开关也是可以按动的，不同的按动会有不同的结果共有2的5次方种结果
            {
                res++;
                turn(0,i);
            }
        }
        for(int i = 0; i < 4; i ++)
            for(int j = 0; j < 5; j ++)
                if(g[i][j]=='0')
                {
                    res++;
                    turn(i+1,j);
                }
        bool success = true;
        for(int i = 0; i < 5; i ++)
            if(g[4][i]=='0'){
              success = false;
              break;  
            } 
        if(success) ans = min(ans,res);
        memcpy(g,back,sizeof back);
    }
    if(ans>6) return -1;
    return ans;
}

int main()
{
    cin >> n;
    while (n -- )
    {
        for(int i = 0; i < 5; i ++) cin >> g[i];
        cout << check()<<'\n';
    }
}
