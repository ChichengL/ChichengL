#include<stdio.h>
int COMPARE1(int q,int a[10][10],int row,int col)//判断最大值
{
    int count = 0;
    for(int i = 0;i < row;i++)
    {
        for(int j = 0;j <col;j++)
        {
           if(q>=a[i][j])
               count++;
        }
    }
    if(count==(row*col))
       return 1;
}
int COMPARE2(int q,int a[10][10],int row,int col)//判断最小值
{
    int count = 0;
    for(int i = 0;i < row;i++)
    {
        for(int j = 0;j <col;j++)
        {
           if(q<=a[i][j])
               count++;
        }
    }
    if(count==(row*col))
       return 1;
}
int main()
{
	int h = 0;//用于下面跳出循环
    int ROW = 0;//行
    int COL = 0;//列
    int max = 0,min = 1e9;
    int row1 = 0,row2 = 0,col1 = 0,col2 = 0;//坐标
    scanf("%d%d",&ROW,&COL);
    int a[10][10];//数组
    for(int i = 0;i < ROW;i++)//输入数据
    {
        for(int j = 0;j <COL;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i = 0;i < ROW; i ++){
        for(int j = 0; j<COL;j++){
            if(a[i][j]>max){
                max = a[i][j];
                row1 = i;
                col1 = j;
            }
            if(a[i][j]<min){
                min = a[i][j];
                row2 = i;
                col2 = j;
            }
        }
    }
    printf("max=%d row=%d col=%d\n",max,row1,col1);
    printf("min=%d row=%d col=%d",min,row2,col2);
    return 0;
}