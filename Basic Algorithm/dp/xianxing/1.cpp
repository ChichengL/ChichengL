#include<stdio.h>  
  
int main()  
{  
    int n, cnt = 0;  
    char s[100] = {0}; // 初始化s数组为0  
    scanf("%d", &n);  
    if (n == 0) { // 处理n为0的情况  
        printf("0");  
        return 0;  
    }  
    while (n)  
    {  
        s[cnt++] = n % 7 + '0';  
        n /= 7;  
    }  
    for (int i = 0; i < cnt / 2; i++)  
    {  
        char t = s[i];  
        s[i] = s[cnt-i-1];  
        s[cnt-i-1] = t;  
    }  
    printf("%s", s);  
    return 0;  
}