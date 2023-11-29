#include<bits/stdc++.h> 

using namespace std;
const int N = 1e5+10;
int a[N],m[N];
int main( )
{
    int n,k;
    cin >> n >> k;
    bool f = true;
    for(int i = 1; i <= n; i ++){
        cin >> a[i] >> m[i];
    }
    int t = 0;
    for(int i = 1; i <= n; i ++){
        while(m[i]--){
            if(f){
                a[i]-=k;
                f = false;
            }
            if(a[i]<=0) continue;
            while(a[i]>0){
                a[i]-=1;
                t +=1;
            }
            f = true;
        }
    }
    cout << t;
    return 0;
}