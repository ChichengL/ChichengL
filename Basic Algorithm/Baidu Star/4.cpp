#include<bits/stdc++.h> 

using namespace std;
const int N = 1e6+10, M = 1e5+10;
int a[N],b[N],c[N];
int s[M],t[M];

int main( )
{
    int n,m;
    cin >> n >> m;
    for(int i = 0; i < n; i ++){
        cin >> s[i];
    }
    for(int i = 0 ; i < n; i ++){
        cin >> t[i];
    }
    for(int i = 0; i < m; i ++){
        cin >> a[i] >> b[i] >> c[i];
    }
    return 0;
}