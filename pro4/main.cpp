#include"define.h"
int allcount=0;
node allpoly[100]={0};
int main()
{
	cout<<"\033[1;33m======================\033[0m"<<"\033[1;32m多项式计算器\033[0m"<<"\033[1;33m=====================\033[0m\n";
	cout<<"\033[1;34m0.退出 1.输入 2.混合运算 3.求根  4.求逆元  5.查看 6.除法\033[0m\n";
	cout<<"\033[1;33m=======================================================\033[0m\n";
	int func=0;
	cout<<"\033[1;34m请输入您要选择的功能：(填数字)\033[0m";
	while(1)
	{
		cin>>func;
		if(cin.fail()||(func!=0&&func!=1&&func!=2&&func!=3&&func!=4&&func!=5&&func!=6))
		{
		cout<<"\033[1;31m没有这个功能，请检查并重新输入:(填数字)\033[0m";
		cin.clear();
		cin.ignore(100,'\n');
		}
		else if(!(func!=0&&func!=1&&func!=2&&func!=3&&func!=4&&func!=5&&func!=6))
		break;
	}
	while(func!=0)
	{
		if(func==1)
		{
			M:cinpoly();
			char mm;
			cout<<"\033[1;34m是否继续输入?(y/n):\033[0m";
			cin>>mm;
			if(mm=='y') goto M;
		}
		else if(func==3)
		{
			K:solution();
			char kk;
			cout<<"\033[1;34m是否继续求根?(y/n):\033[0m";
			cin>>kk;
			if(kk=='y') goto K;
		}
		else if(func==4)
		{
			F:inverse();
			char pp;
			cout<<"\033[1;34m是否继续求逆元?(y/n)\033[0m";
			cin>>pp;
			if(pp=='y') goto F;
			
		}
		else if(func==5)
		{
			N:lookpoly();
			char nn;
			cout<<"\033[1;34m是否继续查看?(y/n):\033[0m";
			cin>>nn;
			if(nn=='y') goto N;
		}
		else if(func==6)
		{
			J:division();
			char jj;
			cout<<"\033[1;34m是否继续作除法?(y/n)\033[0m";
			cin>>jj;
			if(jj=='y') goto J;
		}
		else if(func==2)
		{
			S:cout<<"\033[1;34m请输入表达式：\033[0m";
			char string[100];
			cin>>string;
			operate(string);
			char pp;
			cout<<"\033[1;34m是否继续计算?(y/n):\033[0m";
			cin>>pp;
			if(pp=='y') goto S;
		}
		cout<<"\033[1;33m======================\033[0m"<<"\033[1;32m多项式计算器\033[0m"<<"\033[1;33m=====================\033[0m\n";
        	cout<<"\033[1;34m0.退出 1.输入 2.混合运算 3.求根  4.求逆元  5.查看 6.除法\033[0m\n";
        	cout<<"\033[1;33m=======================================================\033[0m\n";
		cout<<"\033[1;34m请输入您要选择的功能：(填数字)\033[0m";
		
		while(1)
		{
			cin>>func;
			if(cin.fail()||(func!=0&&func!=1&&func!=2&&func!=3&&func!=4&&func!=5&&func!=6))
			{
			cout<<"\033[1;31m没有这个功能，请检查并重新输入：(填数字)\033[0m";
			cin.clear();
			cin.ignore(100,'\n');
			}
			else if(!(func!=0&&func!=1&&func!=2&&func!=3&&func!=4&&func!=5&&func!=6))
			break;
		}
	}
	cout<<"\033[1;33m+++++++++++++++++++++++++++\033[0m\n";
	cout<<"\033[1;32m+感谢您的使用，再见！(^V^)+\033[0m\n";
	cout<<"\033[1;33m+++++++++++++++++++++++++++\033[0m\n";
	return 0;
}
