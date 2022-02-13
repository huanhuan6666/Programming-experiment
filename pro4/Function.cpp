#include"define.h"
extern int allcount;
extern node allpoly[100];


void operate(char *string)//判断合法性并合理调用运算函数
{
	//检测合法性
	//检查首尾
	char begin=string[0];
	char end=string[strlen(string)-1];
	if(begin!='$'&&begin!='('&& !isalpha(begin))
	{
		cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
		return;
	}
	if(end!=')'&&end!='!'&& !isalpha(end))
	{
		cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
		return;
	}
	for(int i=0;i<strlen(string)-1;i++)
	{
		char cur=string[i];
		char next=string[i+1];
		if((cur=='+'||cur=='*')&&(next!='('&&next!='$'&&!isalpha(next)))
		{
			cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
			return;
		}
		else if(cur=='$')
		{
			if(next!='[')
			{
				cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
				return;
			}
			i=i+2;
			int p;
			int douhao=0,douhaocou=0;
			for(p=i;p<strlen(string)&&string[p]!=']';p++)
			{
				if(string[p]==',')
				{ 
					douhao=p;
					douhaocou++;
				}	
			}//看逗号个数0个1个多个
			if(p==strlen(string)||douhaocou>1||douhaocou==0)
			{
				cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
				return;
			}
			int diancou1=0,diancou2=0;
			bool hanum1=0,hanum2=0;
			for(int k=i;string[k]!=',';k++)
			{
				if(string[k]=='.') diancou1++;
				else if(isdigit(string[k])) hanum1=1;
				else if(string[k]!='-')
				{
				cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
                                return;
				}
			}
			for(int v=douhao+1;v<p;v++)
			{
				if(string[v]=='.') diancou2++;
				else if(isdigit(string[v])) hanum2=1;
				else if(string[v]!='-')
				{
 				cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
                                return;
				}
			}
			if(diancou1>1||hanum1==0||diancou2>1||hanum2==0)
			{
				cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
				return;
			}
			i=p;
		}
		else if(cur=='!'&&(next!='*'&&next!='+'&&next!=')'))
		{
			cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
			return ;
		}
		else if(cur=='('&&(next!='('&&next!='$'&&!isalpha(next)))
		{
			cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
			return;
		}
		else if(isalpha(cur))
		{
			while(i<strlen(string)&&isalpha(string[i]))
				i++;
			i--;
			if(i<strlen(string)-1&&string[i+1]!='+'&&string[i+1]!='*'&&string[i+1]!=')'
				&&string[i+1]!='!')
			{
				cout<<"\033[1;31m抱歉您的输入不合法，请检查\n\033[0m";
				return;
			}
		}
	}
	stack<node> stk_poly;//保存操作项
	stack<char*> stk_opt;//保存操作符
	for(int i=0;i<strlen(string);i++)
	{
		//如果是操作数名直接入栈
		if(isalpha(string[i]))//如果是字母就有可能是操作项
		{
			char *temname=new char[20];//临时名字开在堆区放混淆emmm
			int j=0;
			for(j=0;isalpha(string[i]);i++,j++)
			{
				temname[j]=string[i];
			}
			i--;
			temname[j]='\0';
			int k=0;
			for(k=0;k<allcount;k++)
			{
				//找到确实有这个名字的多项式
				//直接压多项式哦
				if(strcmp(allpoly[k].name,temname)==0)
				{
					node hetem;
					//strcpy(hetem.name,allpoly[k].name);
					hetem.length=allpoly[k].length;
					for(int m=0;m<50;m++)
					hetem.coe[m]=allpoly[k].coe[m];
					stk_poly.push(hetem);
					break;
				}
				
			}
			if(k==allcount)//到最后都没有找见这个名字的多项式
			{
				cout<<"\033[1;31m您还没有输过多项式\033[0m"<<temname<<"\033[1;31m哦\n\033[0m";
				return;
			}
			delete(temname);
		}
		else if(string[i]!=' ')//操作符 不要空格
		{
			//左括号直接入栈
			if(string[i]=='(') 
			{
				char* tem=new char[2];
				tem[0]='(';
				tem[1]='\0';
				stk_opt.push(tem);
			}
			//右括号弹出栈顶直到遇到左括号
			else if(string[i]==')')
			{
				while(strcmp(stk_opt.top(),"(")!=0)
				{
					if(stk_opt.top()[0]=='+')
                                        {
                                                node tem1=stk_poly.top();
                                                stk_poly.pop();
                                                node tem2=stk_poly.top();
                                                stk_poly.pop();
                                                node tem=sum(tem1,tem2);
                                                stk_poly.push(tem);
                                        }
                                        else if(stk_opt.top()[0]=='*')
                                        {
                                                node tem1=stk_poly.top();
                                                stk_poly.pop();
                                                node tem2=stk_poly.top();
                                                stk_poly.pop();
                                                node tem=multiply(tem1,tem2);
                                                stk_poly.push(tem);
                                        }
                                        else if(stk_opt.top()[0]=='!')
                                        {
                                                node tem1=stk_poly.top();
                                                stk_poly.pop();
                                                node tem=seek(tem1);
           					stk_poly.push(tem);
                                        }
                                        else if(stk_opt.top()[0]=='$')
                                        {
                                                char *num1=new char[10];
                                                char *num2=new char[10];
                                                int h=0,j=0,x=0;
                                for(h=2,j=0;stk_opt.top()[h]!=',';h++,j++)
                                        num1[j]=stk_opt.top()[h];
                                        num1[j]='\0';
                                for(++h,x=0;stk_opt.top()[h]!=']';h++,x++)
                                        num2[x]=stk_opt.top()[h];
                                        num2[x]='\0';
                                        node tem1=stk_poly.top();
                                        stk_poly.pop();
                                        double begin=numhelp(num1);
                                        double end=numhelp(num2);
                                        node tem=integral(tem1,begin,end);
                                        stk_poly.push(tem);
					delete(num1);
					delete(num2);
                                        }
				stk_opt.pop();
				}
				if(strcmp(stk_opt.top(),"(")==0) 
				stk_opt.pop();
				//將这一对括号丢弃
			}
			//如果是定积分需要特殊处理
			/*else if(string[i]=='$')
			{
				char *tem=new char[50];
				int m=0;
				for(m=0;string[i]!=']';i++,m++)
				tem[m]=string[i];
				tem[m]=string[i];
				tem[m+1]='\0';
				stk_opt.push(tem);
			}*/
			//栈为空或栈顶为左括号直接入栈，$要特殊处理
			else if(stk_opt.empty()||strcmp(stk_opt.top(),"(")==0)
			{ 
				if(string[i]=='$')
				{
				char *tem=new char[50];
                                int m=0;
                                for(m=0;string[i]!=']';i++,m++)
                                tem[m]=string[i];
                                tem[m]=string[i];
                                tem[m+1]='\0';
                                stk_opt.push(tem);
				}
				else
				{
				char *tem=new char[2];
				tem[0]=string[i];
				tem[1]='\0';
				stk_opt.push(tem);
				}
			}
			//优先级大或等栈顶直接入栈 $要特殊处理
			else if(pri(string[i])>=pri(stk_opt.top()[0]))
			{
				if(string[i]=='$')
				{
				char *tem=new char[50];
                                int m=0;
                                for(m=0;string[i]!=']';i++,m++)
                                tem[m]=string[i];
                                tem[m]=string[i];
                                tem[m+1]='\0';
                                stk_opt.push(tem);

				}
				else
				{
				char *tem=new char[2];
				tem[0]=string[i];
				tem[1]='\0';
				stk_opt.push(tem);
				}
			}
			else
			{
			//优先级小则弹出栈顶直到大于等于栈顶或遇见(或栈弹空了
				while(!stk_opt.empty()&&strcmp(stk_opt.top(),"(")!=0&&pri(string[i])<pri(stk_opt.top()[0]))
				{
					if(stk_opt.top()[0]=='+')
					{
						node tem1=stk_poly.top();
						stk_poly.pop();
						node tem2=stk_poly.top();
						stk_poly.pop();
						node tem=sum(tem1,tem2);
						stk_poly.push(tem);
					}
					else if(stk_opt.top()[0]=='*')
					{
						node tem1=stk_poly.top();
						stk_poly.pop();
						node tem2=stk_poly.top();
						stk_poly.pop();
						node tem=multiply(tem1,tem2);
						stk_poly.push(tem);
					}
					else if(stk_opt.top()[0]=='!')
					{
						node tem1=stk_poly.top();
						stk_poly.pop();
						node tem=seek(tem1);
						stk_poly.push(tem);
					}
					else if(stk_opt.top()[0]=='$')
					{
						char* num1=new char[10];
						char* num2=new char[10];
						int h=0,j=0,x=0;
				for(h=2,j=0;stk_opt.top()[h]!=',';h++,j++)
					num1[j]=stk_opt.top()[h];
					num1[j]='\0';
				for(++h,x=0;stk_opt.top()[h]!=']';h++,x++)
					num2[x]=stk_opt.top()[h];
					num2[x]='\0';
					node tem1=stk_poly.top();
					stk_poly.pop();
					double begin=numhelp(num1);
					double end=numhelp(num2);
					node tem=integral(tem1,begin,end);
					stk_poly.push(tem);
					delete(num1);
					delete(num2);
					}
					stk_opt.pop();
				}
				if(stk_opt.empty()||pri(string[i])>=pri(stk_opt.top()[0])||strcmp(stk_opt.top(),"(")==0)
				{
					if(string[i]=='$')
					{
					char *tem=new char[50];
                                	int m=0;
                                	for(m=0;string[i]!=']';i++,m++)
                                	tem[m]=string[i];
                                	tem[m]=string[i];
                               		tem[m+1]='\0';
                                	stk_opt.push(tem);

					}
					else
					{
					char *tem=new char[2];
					tem[0]=string[i];
					tem[1]='\0';
					stk_opt.push(tem);
					}
				}
			}
				
		}
	}
	while(!stk_opt.empty())//弹出操作符直到空
	{
		if(stk_opt.top()[0]=='+')
                {
                        node tem1=stk_poly.top();
                        stk_poly.pop();
                        node tem2=stk_poly.top();
                        stk_poly.pop();
                        node tem=sum(tem1,tem2);
                        stk_poly.push(tem);
                }
                else if(stk_opt.top()[0]=='*')
                {
                        node tem1=stk_poly.top();
                        stk_poly.pop();
                        node tem2=stk_poly.top();
                        stk_poly.pop();
                        node tem=multiply(tem1,tem2);
                        stk_poly.push(tem);
                }
                else if(stk_opt.top()[0]=='!')
                {
                        node tem1=stk_poly.top();
                        stk_poly.pop();
                        node tem=seek(tem1);
			stk_poly.push(tem);
                }
                else if(stk_opt.top()[0]=='$')
                {
                        char *num1=new char[10];
                        char *num2=new char[10];
                        int h=0,j=0,x=0;
                        for(h=2,j=0;stk_opt.top()[h]!=',';h++,j++)
                                 num1[j]=stk_opt.top()[h];
                        num1[j]='\0';
                        for(++h,x=0;stk_opt.top()[h]!=']';h++,x++)
                                 num2[x]=stk_opt.top()[h];
                        num2[x]='\0';
                        node tem1=stk_poly.top();
                        stk_poly.pop();
                        double numbegin=numhelp(num1);
                        double numend=numhelp(num2);
                        node tem=integral(tem1,numbegin,numend);
                        stk_poly.push(tem);
			delete(num1);
			delete(num2);
                 }
		 stk_opt.pop();
	}
	//数据栈里的最后一项就是最终结果
	coutresult(string,stk_poly.top());
	stk_poly.pop();
	return;
	
}
//將积分区间里的字符串转化为浮点数返回
double numhelp(char *num)
{
	if(num[0]!='-')
      {
	if(num[0]=='.')//开头就是小数点
	{
		double result=0;
		for(int i=1;i<strlen(num);i++)
		{
			double coe=1;
			for(int j=1;j<=i;j++)
			coe/=10;
			result+=coe*(num[i]-'0');
		}
		return result;
	}
	else if(num[strlen(num)-1]=='.')//结尾是小数点
	{
		double result=0;
		for(int i=0;i<strlen(num)-1;i++)
		{
			double coe=1;
			for(int j=i;j<strlen(num)-2;j++)
			coe*=10;
			result+=coe*(num[i]-'0');
		}
		return result;
	}
	else
	{
		double result=0,result1=0,result2=0;
		int i=0,j=0;
		for(i=0;num[i]!='.'&&i<strlen(num);i++)
		{
			double coe=1;
			int p;
			for(p=i+1;num[p]!='.'&&p<strlen(num);p++)
			coe*=10;
			result1+=coe*(num[i]-'0');
		}
		for(j=i+1;j<strlen(num);j++)
		{
			double coe=1;
			for(int q=1;q<=j-i&&q<strlen(num);q++)
			coe/=10;
			result2+=coe*(num[j]-'0');
		}
		result=result1+result2;
		return result;
	}
      }
    else if(num[0]=='-')//是负数
    {
	if(num[1]=='.')//开头就是小数点
        {
                double result=0;
                for(int i=2;i<strlen(num);i++)
                {
                        double coe=1;
                        for(int j=2;j<=i;j++)
                        coe/=10;
                        result+=coe*(num[i]-'0');
                }
                return -result;
        }
        else if(num[strlen(num)-1]=='.')//结尾是小数点
        {
                double result=0;
                for(int i=1;i<strlen(num)-1;i++)
                {
                        double coe=1;
                        for(int j=i;j<strlen(num)-2;j++)
                        coe*=10;
                        result+=coe*(num[i]-'0');
                }
	 	return -result;
        }
        else
        {
                double result=0,result1=0,result2=0;
                int i=0,j=0;
                for(i=1;num[i]!='.'&&i<strlen(num);i++)
                {
                        double coe=1;
                        int p;
                        for(p=i+1;num[p]!='.'&&p<strlen(num);p++)
                        coe*=10;
                        result1+=coe*(num[i]-'0');
                }
                for(j=i+1;j<strlen(num);j++)
                {
                        double coe=1;
                        for(int q=1;q<=j-i&&q<strlen(num);q++)
                        coe/=10;
                        result2+=coe*(num[j]-'0');
                }
                result=result1+result2;
                return -result;
	}
    }
	
}
int pri(char ch)
{
	if(ch=='!') return 4;
	else if(ch=='$') return 3;
	else if(ch=='*') return 2;
	else if(ch=='+') return 1;
}
void cinpoly()
{
	int temlength=0;
        cout<<"\033[1;34m请输入多项式长度：\033[0m";
        cin>>temlength;
        allpoly[allcount].length=temlength;
        cout<<"\033[1;34m请依次输入多项式的系数(不同项之间用空格隔开):\033[0m";
        double temcoe;
        for(int j=temlength-1;j>=0;j--)
        {
                cin>>temcoe;
                allpoly[allcount].coe[j]=temcoe;
        }
        getchar();
        char temname[10];
        A:cout<<"\033[1;34m请输入多项式的名称：\033[0m";
        cin>>temname;
        for(int i=0;i<allcount;i++)
        {
                if(strcmp(temname,allpoly[i].name)==0)
                {
                        cout<<"\033[1;31m该名称已存在，请您换一个名称\n\033[0m";
         		goto A;
                }
        }
        strcpy(allpoly[allcount].name,temname);
        allcount++;

}
void coutresult(char* string,node poly)//输出结果辅助函数
{
	//不输出表达式里的空格
	for(int i=0;i<strlen(string);i++)
		if(string[i]!=' ') cout<<string[i];
	cout<<'=';
	int thelength=poly.length;
	bool quanling=1;
	for(int p=0;p<thelength;p++)
	{
		if(poly.coe[p]!=0)
		quanling=0;
	}
	if(quanling==1)
	{
		cout<<'0'<<endl;
		return;
	}
	if(thelength==1)//就一个常数项
	{
		cout<<poly.coe[0]<<endl;
		return;
	}
	for(int j=poly.length-1;j>=0;j--)
	{                        
				if(j==0)    
                                {
        	                if(poly.coe[j]>0&&j<thelength-1)
                                cout<<'+'<<poly.coe[j];
                                else if(poly.coe[j]>0&&j==thelength-1)
                                cout<<poly.coe[j];
                                else if(poly.coe[j]<0)  
                                cout<<poly.coe[j];
                                }
                                else if(j==1)
                                {//注意系数1不输出
                                if(poly.coe[j]==1&&j==thelength-1)
                                cout<<'x';
				else if(poly.coe[j]>0&&j==thelength-1)
				cout<<poly.coe[j]<<'x';
                                else if(poly.coe[j]==1&&j<thelength-1)
                                cout<<"+x";
				else if(poly.coe[j]>0&&j<thelength-1)
				cout<<'+'<<poly.coe[j]<<'x';
                                else if(poly.coe[j]==-1)
                                cout<<"-x";
				else if(poly.coe[j]<0)
				cout<<poly.coe[j]<<'x';
                                }
                                else if(poly.coe[j]<0
                                ||(poly.coe[j]>0&&j==thelength-1))
				{
				if(poly.coe[j]!=1)
                                cout<<poly.coe[j]<<"x^"<<j;
				else cout<<"x^"<<j;
				}
                                else if(poly.coe[j]>0)
				{
				if(poly.coe[j]!=1)
				cout<<'+'<<poly.coe[j]<<"x^"<<j;
				else cout<<"+x^"<<j;
				}
	}
	cout<<endl;
}
void lookpoly()//查看多项式
{
	getchar();
        cout<<"\033[1;34m请输入多项式的名称：\033[0m";
        char temname[10];
        cin>>temname;
        int i=0;
        for(i=0;i<=allcount;i++)
        {
                if(strcmp(allpoly[i].name,temname)==0)//找到了就降幂输出
                {
                        cout<<temname<<'=';
                        int thelength=allpoly[i].length;
			if(thelength==1)
			{
				cout<<allpoly[i].coe[0];
				return;
			}
                        for(int j=thelength-1;j>=0;j--)
                        {
                        //若系数为0则不输出那一项
                                if(j==0)
                                {
                                if(allpoly[i].coe[j]>0&&j<thelength-1)	
                                cout<<'+'<<allpoly[i].coe[j];
				else if(allpoly[i].coe[j]>0&&j==thelength-1)
				cout<<allpoly[i].coe[j];
                                else if(allpoly[i].coe[j]<0)     
				cout<<allpoly[i].coe[j];
                                }
                                else if(j==1)
                             {
                                if(allpoly[i].coe[j]>0&&j==thelength-1)
				{
				if(allpoly[i].coe[j]!=1)
                                cout<<allpoly[i].coe[j]<<'x';
				else cout<<'x';
				}
				else if(allpoly[i].coe[j]>0&&j<thelength-1)
				{
				if(allpoly[i].coe[j]!=1)
				cout<<'+'<<allpoly[i].coe[j]<<'x';
				else cout<<"+x";
				}
                                else if(allpoly[i].coe[j]<0)
				{
				if(allpoly[i].coe[j]!=-1)
                                cout<<allpoly[i].coe[j]<<'x';
				else cout<<"-x";
                                }
			     }
                                else if(allpoly[i].coe[j]<0
                                ||(allpoly[i].coe[j]>0&&j==thelength-1))
				{
				if(allpoly[i].coe[j]==1) 
				cout<<"x^"<<j;
				else if(allpoly[i].coe[j]==-1)
				cout<<"-x^"<<j;
				else 
                                cout<<allpoly[i].coe[j]<<"x^"<<j;
				}
                                else if(allpoly[i].coe[j]>0)
				{
				if(allpoly[i].coe[j]!=1)
                                cout<<'+'<<allpoly[i].coe[j]<<"x^"<<j;
				else cout<<"+x^"<<j;
				}
                         }
                         cout<<endl;
                         break;//输出完了就跳出
                }
        }
        if(i>allcount)//到最后都没有输出那就是没有
        {
                cout<<"\033[1;31m抱歉，没有这个名称的多项式\n\033[0m";
        }
}
node sum(node poly1,node poly2)
{
	node result={0};
	if(poly1.length>=poly2.length)
		result.length=poly1.length;
	else 
		result.length=poly2.length;
	for(int i=0;i<result.length;i++)
		result.coe[i]=poly1.coe[i]+poly2.coe[i];
	return result;
}
node multiply(node poly1,node poly2)
{
	node result={0};
	result.length=poly1.length+poly2.length-1;//结果长度等于两个长度相加减一
	for(int i=0;i<poly1.length;i++)//i和j分别代表多项式x的次数
		for(int j=0;j<poly2.length;j++)
		{
		//完全展开得到result的不同次数项的系数
			result.coe[i+j]+=poly1.coe[i]*poly2.coe[j];
		}
	return result;
}
node seek(node poly)
{
	node result=poly;
	//先把系数整体后移
	for(int i=0;i<result.length-1;i++)
	result.coe[i]=result.coe[i+1];
	//长度减一
	result.coe[result.length-1]=0;
	--result.length;
	//系数乘以次数加一
	for(int i=0;i<result.length;i++)
	result.coe[i]=result.coe[i]*(i+1);
	return result;
	
}
node integral(node poly,double begin,double end)
{
	node result=poly;
	//先把系数整体前移
	for(int i=result.length;i>0;--i)
	result.coe[i]=result.coe[i-1];
	//长度加一
	result.coe[0]=0;
	++result.length;
	//系数除以次数减一
	for(int i=result.length-1;i>=1;i--)
	result.coe[i]=result.coe[i]/i;
	double beginvalue=0,endvalue=0;
	for(int i=0;i<result.length;i++)
	{
	//tem求不同次小项的值
		double tem=result.coe[i];
		for(int j=1;j<=i;j++)
		tem*=begin;
		beginvalue+=tem;
	}
	for(int i=0;i<result.length;i++)
	{
		double tem=result.coe[i];
		for(int j=1;j<=i;j++)
		tem*=end;
		endvalue+=tem;
	}
	node resultpoly={0};
	resultpoly.length=1;
	resultpoly.coe[0]=endvalue-beginvalue;
	return resultpoly;
}
void solution()
{
	cout << "\033[1;34m请输入多项式名称：\033[0m";
	char thename[10];
	cin >> thename;
	node thepoly;
	int i = 0;
	for (i = 0; i < allcount; i++)
		if (strcmp(allpoly[i].name, thename) == 0)
		{
			for (int m = 0; m < 50; m++)
				thepoly.coe[m] = allpoly[i].coe[m];
			thepoly.length = allpoly[i].length;
			break;
		}
	if (i == allcount)
	{
	cout <<"\033[1;31m抱歉没有这个多项式哦\n\033[0m";
	 return;
	}
	node seekpoly = seek(thepoly);//导数
	double x = 1, each=1,nextx=0, y=0, k=0;
	double gap = 0;
	do 
	{
		y = 0;
		k = 0;
		nextx = x;
		for (int i = 0; i < thepoly.length; i++)
		{
			each = thepoly.coe[i];
			for (int j = 0; j < i; j++)
				each *= nextx;
			y += each;//求出此时函

		}
		for (int i = 0; i < seekpoly.length; i++)
		{
			each = seekpoly.coe[i];
			for (int j = 0; j < i; j++)
				each *= nextx;
			k += each;
		}
		if (k == 0)
		{
			if (y == 0)
			{
				cout << thename << " \033[1;34m存在的实数根为：\033[0m" << x << endl;
				return;
			}
			else k++;
		}
		x = nextx - y / k;
		gap = fabs(x - nextx);
	}while (gap>= 1e-5);
	cout << thename << " \033[1;34m存在的实数根为：\033[0m" << x << endl;
}

void inverse()
{
  	cout << "\033[1;34m请输入多项式名称：\033[0m";
        char thename[10];
        cin >> thename;
        node thepoly;
        int i = 0;
        for (i = 0; i < allcount; i++)
                if (strcmp(allpoly[i].name, thename) == 0)
                {
                        for (int m = 0; m < 50; m++)
                                thepoly.coe[m] = allpoly[i].coe[m];
                        thepoly.length = allpoly[i].length;
                        break;
                }
        if (i == allcount)
        {
               cout << "\033[1;31m抱歉没有这个多项式哦\n\033[0m";
               return;
        }
	if(thepoly.coe[0]==0)
	{
		cout<<thename<<"\033[1;34m没有逆元\033[0m\n";
		return;
	}
	else
	{
		node result={0};
		result.length=thepoly.length;
		result.coe[0]=1/thepoly.coe[0];
		for(int k=1;k<thepoly.length;k++)
		{
		for(int i=0;i<=k-1;i++)
		result.coe[k]+=-result.coe[i]*(thepoly.coe[k-i]/thepoly.coe[0]);
		
		}
		char string[20];
		strcpy(string,thename);
		strcat(string,"-1");
		cout<<"\033[1;34m逆元为：\033[0m";
		coutresult(string,result);
	}
	

}
void division()
{
	cout << "\033[1;34m请输入被除多项式的名称：\033[0m";
        char thename1[10];
        cin >> thename1;
        node thepoly1;
        int i = 0;
        for (i = 0; i < allcount; i++)
                if (strcmp(allpoly[i].name, thename1) == 0)
                {
                        for (int m = 0; m < 50; m++)
                                thepoly1.coe[m] = allpoly[i].coe[m];
                        thepoly1.length = allpoly[i].length;
                        break;
                }
	if (i == allcount)
        {
               cout << "\033[1;31m抱歉没有这个多项式哦\n\033[0m";
               return;
        }
	cout << "\033[1;34m请输入除数多项式的名称：\033[0m";
        char thename2[10];
        cin >> thename2;
        node thepoly2;
        for (i = 0; i < allcount; i++)
                if (strcmp(allpoly[i].name, thename2) == 0)
                {
                        for (int m = 0; m < 50; m++)
                                thepoly2.coe[m] = allpoly[i].coe[m];
                        thepoly2.length = allpoly[i].length;
                        break;
                }
        if (i == allcount)
        {
               cout << "\033[1;31m抱歉没有这个多项式哦\n\033[0m";
               return;
        }
	if(thepoly2.length==1&&thepoly2.coe[0]==0)//被除数是0
	{
		cout<<"\033[1;31m被除式为0无法计算\n\033[0m";
		return;
	}
	if(thepoly2.length>thepoly1.length)//被除式的次数比除数高
	{
		cout<<"商=0\n";
		char stringh[20];
		strcpy(stringh,"余数");
		coutresult(stringh,thepoly1);
	}
	else 
	{
		node shang={0};
		node yushu={0};
		node beijian=thepoly1;
		int gap=beijian.length-thepoly2.length;
		shang.length=gap+1;
		shang.coe[gap]=beijian.coe[beijian.length-1]/thepoly2.coe[thepoly2.length-1];
		yushu=jian(beijian,multiply(shang,thepoly2));
		beijian=yushu;
		while(yushu.length>=thepoly2.length)
		{
			gap=beijian.length-thepoly2.length;
			shang.coe[gap]=beijian.coe[beijian.length-1]/thepoly2.coe[thepoly2.length-1];
			node tem={0};
			tem.coe[gap]=shang.coe[gap];
			tem.length=gap+1;
			yushu=jian(beijian,multiply(tem,thepoly2));
			beijian=yushu;
		}
		if(yushu.length<thepoly2.length)
		{
			char stringi[20];
			strcpy(stringi,"商");
			coutresult(stringi,shang);
			char stringk[20];
			strcpy(stringk,"余数");
			coutresult(stringk,yushu);
		}
		return;
	}

}
node jian(node beijian,node jian)//减法函数
{
	node result=beijian;
	if(beijian.length>=jian.length)
		result.length=beijian.length;
	else result.length=jian.length;
	for(int i=0;i<result.length;i++)
	{
		result.coe[i]=beijian.coe[i]-jian.coe[i];
	}
	for(int i=result.length-1;i>=0;i--)
		if(!result.coe[i]) result.length--;
		else break;
	return result;
}
