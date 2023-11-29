#include<bits/stdc++.h> 
#define N 1000010
using namespace std;
bool b[N];
int main( )
{
    int n,k,x;
    int res = 0;
    memset(b,0,sizeof(b));
    cin >> n >> k;
    unordered_map<int,int>map;
    
    for(int i = 1; i <= n; i ++)
    {
        cin >>x;
        if(map[x]==0){
            map[x] = i;
        }else{
            if(i-map[x]<=k && !b[x]){
              res ^= x;
              b[x] = true;
            }
        }
    }
    
    cout << (res^0);
    return 0;
}