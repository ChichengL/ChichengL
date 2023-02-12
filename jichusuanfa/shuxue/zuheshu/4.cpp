  #include<iostream>
  #include<algorithm>
  #include<vector>

  using namespace std;

  const int N = 5010;
  int prime[N],cnt,sum[N];
  bool st[N];

  void get_prime(int n)
  {
    for(int i = 2; i <= n; i ++)
    {
      if(!st[i])prime[cnt++] = i;
      for(int j = 0; prime[j]<= n/i; j ++)
      {
        st[prime[j]*i] = true;
        if(i%prime[j]==0)break;
      }
    }
  }

  vector<int> mul(vector<int> a,int b)
  {
    int t = 0;
    vector<int>res;
    for(int i = 0; i < a.size(); i ++)
    {
      t+= a[i] * b;
      res.push_back(t%10);
      t/=10;
    }
    while(t){
      res.push_back(t%10);
      t/=10;
    }
    return res;
  }

  int get(int a,int p)
  {
    int res = 0;
    while(a)
    {
      res += a/p;
      a/=p;
    }
    return res;
  }

  int main()
  {
    int a,b;
    cin >> a >> b;
    get_prime(a);

    for(int i = 0; i < cnt; i ++)
    {
      int p = prime[i];
      sum[i]=get(a,p)-get(b,p)-get(a-b,p);
    }

    vector<int>res;
    res.push_back(1);
    for(int i = 0; i < cnt; i ++)
      for(int j = 0; j < sum[i]; j ++)
        res = mul(res,prime[i]);
    for(int i = res.size()-1;i >= 0; i --) cout << res[i];

    return 0;
  }