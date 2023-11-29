#include<bits/stdc++.h> 

using namespace std;
typedef pair<int,int>PII;

int power(int x,int n){
  int ans = 1;
  while(n--) ans*=x;
  return ans;
}

int calc(int x1,int y1,int x2,int y2){
    return power((x1-x2),2)+power((y1-y2),2);
}

PII s[200010];

int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 0; i < n; i ++){
        int x,y;
        cin >> x >> y;
        s[i] = {x,y};
    }
    int ans = 0;
    while(m--){
        string t;
        int x,y;
        cin >> t >> x >> y;
        if(t=="add") s[n++] = {x,y};
    	else{
            int max1 = 0;
            for(auto t:s){
                int x1 = t.first, y1 = t.second;
                max1 = max(max1,calc(x,y,x1,y1));
            }
            ans = max(ans,max1);
        }
    }
    cout << ans;
    return 0;
}