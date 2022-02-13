#include"define.h"
void tobegin()//最原始的操作界面
{
	cout<<"**********************欢迎来到选课系统!************************\n";
	cout<<"--------------------请选择你需要的操作----------------------\n";
	cout<<"======================================================\n";
	cout << "                  *  0.退出程序   *\n"
		    "                  *  1.学生登录   *\n"
	   	    "                  *  2.学生注册   *\n"
		    "                  *  3.管理员登录 *\n"
		    "                  *****************\n";
	cout<<"======================================================\n";
	int num;
	cin >> num;
	getchar();
	switch (num)
	{
	case 0:
	{
		cout << "感谢您的使用！再见！";
		exit(0); 
	}
	case 1:
		studentlog();
		break;
	case 2:
		studentcreate();
		break;
	case 3:
		adminlog();
		break;
	}
}
void adminlog()
{
	cout << "请输入管理员id：";
	char inputid[10],inputpass[10];
	gets_s(inputid);
	if (strcmp(inputid, "Admin") == 0)
	{
		int i = 0;
		B:cout << "请输入管理员密码：";
		for (i = 0; i < 10; i++)
		{
			inputpass[i] = _getch();
			if (inputpass[i] == '\r')
				break;
			if (inputpass[i] == '\b')
			{
				/*if (i == 0)
				{
					cout << "\a";
					//continue;					
				}*/
				if (i > 0)
				{

					i=i-2;
					cout << "\b \b";
				}
			}
			else
			cout << '*';
		}
		inputpass[i] = '\0';
		if (strcmp(inputpass, "admin") == 0)
		{
			printf("您以管理员身份成功登录!\n");
			system("cls");
			adminoperate();
			return;
		}
		else printf("密码错误!\n");
		goto B;
	}
	else printf("管理员id错误!\n");
	adminlog();
}
//
//为什仫注册完了之后注销用户再登录一直显示的是没有注册过，但是学生文件里确实存在数据啊
//应该是学生登录函数除了问题，感觉就根本没有读学生文件！明天继续！
void studentcreate()//注意注册的时候需要登陆成功
{
	student* newboy = new student;
	cout << "请输入您的学生id(由小写字母和数字构成,不要超过20位):";
	A:gets_s(newboy->student_id);
	if(ifinthestudent(newboy->student_id) == true)//如果这个id有人注册过
	{
		cout << "抱歉这个id已经被人注册过了！请您再次输入一个：";
		goto A;
	}
	for (int i = 0; i < strlen(newboy->student_id); i++)//判断一下输入id的合法性
	{
		char a = newboy->student_id[i];
		if (!(islower(a) || (a >= '0' && a <= '9')))
		{
			i = -1;
			cout << "检测到您输入的id不合法，注意只能包含小写字母和数字哦\n请您再次输入：";
			goto A;
		}
	}
	cout << "请输入您的密码(由小写字母和数字构成,不要超过20位)：";
	gets_s(newboy->password);
	for (int i = 0; i < strlen(newboy->password); i++)//判断一下输入密码的合法性
	{
		char a = newboy->password[i];
		if (!(islower(a) || (a >= '0' && a <= '9')))
		{
			i = -1;
			cout << "检测到您输入的密码不合法，注意只能包含小写字母和数字哦\n请您再次输入：";
			gets_s(newboy->password);
		}
	}
	FILE* fp = fopen("student.txt", "a+");//注册学生要把该学生录入学生文件里
	if (fp == NULL)
	{
		printf("打开学生文件错误!\n");
		exit(-1);
	}
	fprintf(fp, "%s,%s\n", newboy->student_id, newboy->password);
	fclose(fp);
	const char *file = ".txt";//并且要相应的创建这个学生的课表文件
	char tem[20];
	strcpy(tem, newboy->student_id);
	strcat(tem, file);
	FILE* fpp = fopen(tem, "w");//创建以学生id名为文件名的学生课表文件
	fclose(fpp);
	cout << "学生信息注册成功!您可以继续进行操作\n";
	fclose(fp);
	studentoperate(newboy->student_id);
}
void studentlog()
{

	char id[20];
	char password[20];
	cout << "请输入您的id:";
	gets_s(id);//输入学生的id
	FILE* fp = fopen("student.txt", "a+");
	if (fp == NULL)
	{
		cout << "学生信息文件打开失败!\n";
		exit(-1);
	}
	student a;
	//先看看有没有这个id号
	bool exist=0;
	while (fscanf(fp, "%[^,],%s\n", a.student_id, a.password)!=EOF) //因为是拿逗号分隔的，用正则表达式清洗逗号
	{
		if (strcmp(id, a.student_id) == 0)//有的话标记
		{
			exist = 1;
			break;
		}
		else continue;
	}
	if (exist==0)//如果没有这个id号
	{
		cout << "抱歉这个id还没有被注册,请选择您继续的操作:(1.我要注册  2.返回登录界面重新输入)\n";
		int a;
		cin >> a;
		getchar();//同样用来清洗回车
		if (a == 1)
		{ 
			fclose(fp);
			studentcreate();//调用注册函数
		}
		else if (a == 2)
		{
			fclose(fp);
			studentlog();
		}
	}
	else//如果这个id存在的话，此时a中存的数据就已经是目标数据了，不用重复遍历搜索
	{
	cout << "请输入您的密码:";
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		password[i] = _getch();
		if (password[i] == '\r')
			break;
		if (password[i] == '\b')
		{
			/*if (i == 0)
			{
				cout << "\a";
				//continue;
			}*/
			if (i > 0)
			{
				i = i - 2;
				cout << "\b \b";
			}
		}
		else
			cout << '*';
	}
	password[i] = '\0';
			if (strcmp(password, a.password) == 0)
			{
				cout << "\n**************登陆成功!**************\n";
				fclose(fp);
				ifassconnect(id);//**************************看看我的助教是否还在
				studentoperate(id);//登陆成功进入操作界面
			}
			else//密码输的不对
			{
				int count = 3;//三次机会
				while (strcmp(password, a.password) != 0&&count>1)//当密码一直不匹配时
				{
					
					count--;
					cout << "你输入的密码有错误，请重新输入!\n"<<"您还有"<<count<<"次机会\n";
					cout << "请输入您的密码:\n";
					int j = 0;
					for (j = 0; j < 10; j++)
					{
						password[j] = _getch();
						if (password[j] == '\r')
							break;
						if (password[j] == '\b')
						{
							/*if (i == 0)
							{
								cout << "\a";
								//continue;
							}*/
							if (j > 0)
							{
								j = j - 2;
								cout << "\b \b";
							}
						}
						else
							cout << '*';
					}
					password[j] = '\0';
				}
				if (strcmp(password, a.password) == 0)//如果密码对了跳出循环
				{
					cout << "\n**************登陆成功!*************\n";
					fclose(fp);
					ifassconnect(id);//**************************看看我的助教是否还在
					studentoperate(id);//登陆成功进入操作界面
				}
				else 
				{
					cout << "您的3次机会已经使用完了!\n"<<"您可以考虑重置密码(1.是 2.否)请输入:";
					int tem = 0;
					fclose(fp);
					cin >> tem;
					getchar();//清洗回车因为接下来调用的函数开头都直接有gets会吸收的
					if (tem == 1)//是的话就调用重置密码函数 
					  change_password(id);
					else if (tem == 2)//不重置就返回开始界面
					{
						system("cls");
						tobegin();
						return;
					}
				}
			}
		}
}
void change_password(char id[20])//重置密码功能
{
	char newpass[20];
	char again[20];
	A:cout << "请输入您的新密码:";
	gets_s(newpass);
	cout << "请再次输入您的新密码:";
	gets_s(again);
	if (strcmp(newpass, again) != 0)//两次输入并不一样
	{
		cout << "您两次输入的密码不一致!\n请重新再次输入密码\n";
		goto A;
	}
	else 
	{
		FILE* fp = fopen("student.txt", "r+");
		student a;
		while (fscanf(fp, "%[^,],%s\n", a.student_id, a.password))
		{
			if (strcmp(a.student_id, id)==0)//找到了id
			{
				fseek(fp, -((int)strlen(a.password)+2), 1);//将文件指针移到这一行开头
				fprintf(fp, "%s\n",newpass);//用原来的id和新的密码覆盖掉这一行
				fclose(fp);
				cout << "您的密码已经重置!\n";
				studentoperate(id);//重置完成后直接进入操作界面
				return ;
			}
		}
	}
}
void logout()
{
	system("cls");
	tobegin();
}