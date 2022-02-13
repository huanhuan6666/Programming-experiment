#include<iostream>
using namespace std;
#include<stdlib.h>
#include<cmath>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stack>
struct node
{
	char name[10];//多项式名称
	int length;//多项式长度
	double coe[50];//多项式系数
};
int pri(char ch);//不同操作符对应优先级
double numhelp(char *num);//积分区间字符串转数字函数
void cinpoly();//输入多项式函数
void coutresult(char *string,node poly);//输出结果辅助函数
void lookpoly();//查看多项式函数
void operate(char *string);//混合运算辅助模块
node multiply(node poly1,node poly2);//乘法函数返回node型数据
node sum(node poly1,node poly2);//加法函数
node seek(node poly);//求导函数
node integral(node poly, double begin, double end);//积分函数
void solution();//求根函数
void inverse();//求逆函数
node jian(node beijian,node jian);//减法函数
void division();//除法函数
