#include"define.h"
void adminoperate()
{
	cout << "***************您现在是管理员身份*****************\n";
	cout << "==================================================\n";
	cout << "              * 1.注销登录          *\n"
		    "              * 2.录入课程信息      *\n"
		    "              * 3.查看全部课程信息  *\n"
		    "              * 4.增加课程          *\n"
		    "              * 5.删除课程          *\n"
		    "              * 6.修改课程          *\n"
		    "              * 7.查看具体课程      *\n";
	cout << "==================================================\n";
	cout << "请输入您选择的功能:";
	int num;
	cin >> num;
	getchar();
	switch(num)
	{
	case 1:
		logout();
		break;
	case 2:
		inputcourse();
		break;
	case 3:
		lookallcourse1();
		break;
	case 4:
		addcourse();
		break;
	case 5:
		deletecourse();
		break;
	case 6:
		changecourse();
		break;
	case 7:
		lookone();
		break;
	}
}
void inputcourse()//录入课程信息
{
	system("cls");
	cout << "请输入您想要导入的课程信息文件名称:\n";
	char filename[30];
	gets_s(filename);
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		cout << "打开课程信息文件失败!\n";
		exit(-1);
	}
	FILE* fpp = fopen("current_course.txt", "w");
	course a;
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
	, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)
	{
		fprintf(fpp, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
			, a.course_name, a.teacher_name, a.total, a.current, a.kind);
	}
	cout << "******导入课程信息成功了!********\n";
	fclose(fp);
	fclose(fpp);
	adminoperate();
}
void lookallcourse1()//查看全部课程信息(管理员和学生是同样的函数)
{
	system("cls");
	FILE* fp = fopen("current_course.txt", "a+");
	if (fp == NULL)
	{
		cout << "打开全部课程信息文件失败!\n";
		exit(-1);
	}
	cout << "全部课程信息如下:\n";
	cout << "课程ID\t" << "课程名称\t" << "          任课老师\t" << "                 上限人数 " << "已选人数\t" << "课程类型\n";
	course a;//一行一行都录到a中
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)
	{
		printf("%s\t%-30s%-30s%-10d%-10d%-10s\n", a.course_id
			, a.course_name, a.teacher_name, a.total, a.current, a.kind);
	}
	fclose(fp);
	adminoperate();
}
//
//下面这个添加函数还没有检查课程已经存在的功能
//要注意!
void addcourse()//管理员增加一门课程添加完后并展示所有课程
{
	char newname[30],newteacher[30],newkind[10];//这里是把新课程的各个信息一个个录进新变量里
	int all, cur;
	cout << "请输入要增添课程的具体信息(课程id会自动分配,无需录入)\n";
	cout << "请输入课程名称:";
	C:gets_s(newname);
	if (ifinallcourse(newname)==true)
	{
		cout << "抱歉这门课已经存在了！\n请您重新输入名称：";
		goto C;
	}
	cout << "请输入授课教师姓名:";
	gets_s(newteacher);
	cout << "请输入课程类型(专业课 或 非专业课):";
	gets_s(newkind);
	cout << "请输入课程上限人数:";
	cin >> all;
	cout << "请输入目前已选人数:";
	cin >> cur;
	FILE* fp = fopen("current_course.txt", "a+");//以读写方式打开文件
	//读最后一行的课程id
	course a;
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF);//一直读到最后
	int count = 0;
	char c1,c2,c3;
	//此时a中存的就是最后一行的数据
	c1 = a.course_id[0];
	c2 = a.course_id[1];
	c3 = a.course_id[2];
	count = (c1-'0') * 100 + (c2-'0') * 10 + (c3-'0') + 1;
	char newcount[4];
	for (int i = 0; i < 3; i++)//将新的编号存在newcount数组里
	{
		newcount[2 - i] = (count % 10)+'0';
		count /= 10;
	}
	newcount[3] = '\0';
	fseek(fp, 0, 2);//读取编号后将文件指针移到文件最后开始写新的一行课程信息
	fprintf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", newcount, 
		newname, newteacher, all, cur, newkind);//格式化增添到文件末尾
	fclose(fp);//先把这个指针关掉另起一个
	lookallcourse1();//调用查看全部课程函数来查看信息
}
void deletecourse()//指定课程id并删除这个课程当没人选该课程的情况下
{
	char delid[4];
	cout << "请输入要删除的课程id:";
	gets_s(delid);
	FILE* fp = fopen("current_course.txt", "r");
	if (fp == NULL)
	{
		cout << "打开全部课程信息文件失败!\n";
		exit(-1);
	}
	course a;
	bool flag = 0;
	//
	//建立一个临时文件向里面写信息并确保不储存要删除的课程信息最后删除原课程文件并将临时文件重命名
	FILE* fin = fopen("tmp.txt", "w");
	if (fin == NULL)
	{
		cout << "建立课程临时文件失败!";
		exit(-1);
	}
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)
	{
		flag = 0;
		if (strcmp(delid, a.course_id) == 0)//课程id一致了需要删
			flag = 1;
		if (!flag)//不是要删除的课程
			fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
				, a.course_name, a.teacher_name, a.total, a.current, a.kind);//把读到的数据写到临时文件里
		else//是要删的课程的话还得看看是否有人选课
		{
			if (a.current > 0)//如果有人选了还得录到临时文件里
			{
				cout << "抱歉,这门课已经有同学选了,无法删除!\n";
				fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
					, a.course_name, a.teacher_name, a.total, a.current, a.kind);
			}
			else cout << "删除课程信息成功了！\n";
		}
	}
	fclose(fp);
	fclose(fin);
	remove("current_course.txt");//删除原文件
	rename("tmp.txt", "current_course.txt");//将临时文件名改为原文件名
	adminoperate();
}
void changecourse()//修改课程信息同上也是建立一个临时文件来做
{
	cout << "请输入要修改的课程ID:";
	char changeid[4];
	gets_s(changeid);
	cout << "需要修改的具体字段为(1.任课教师  2.容纳人数):";
	int num;
	cin >> num;
	char newteacher[30];
	int newall;
	cout << "具体修改为:";
	getchar();
	if (num == 1)
		gets_s(newteacher);
	else if (num == 2)
		cin >> newall;
	//开始读原文件并写入临时文件
	FILE* fp = fopen("current_course.txt", "r");
	if(fp==NULL)
	{
		cout << "打开全部课程信息文件失败!\n";
		exit(-1);
	}
	course a;
	bool flag = 0;
	//
	//建立一个临时文件向里面写信息并修改对应id的课程信息
	FILE* fin = fopen("tmp.txt", "w");
	if (fin == NULL)
	{
		cout << "建立课程临时文件失败!";
		exit(-1);
	}
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)
	{
		flag = 0;
		if (strcmp(changeid, a.course_id) == 0)//课程id一致了就需要修改了
			flag = 1;
		if (!flag)//不是要删除的课程
			fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
				, a.course_name, a.teacher_name, a.total, a.current, a.kind);//把读到的数据写到临时文件里
		else //是要修改的课程还要判断修改后的人数与已选人数的大小关系
		{
			if(num==1)//改的是老师姓名
			{
				fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
					, a.course_name, newteacher, a.total, a.current, a.kind);//录入新名字
				cout << "修改成功了!\n";
			}
			else if (num == 2)//改的是人数上限
			{
				if (newall < a.current)//改后人数过小
				{
					cout << "改后人数小于当前课程已选人数,无法修改!\n";
					fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
						, a.course_name, a.teacher_name, a.total, a.current, a.kind);//录入原信息
				}
				else //改后人数大于已选人数
					fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
						, a.course_name, a.teacher_name, newall, a.current, a.kind);//录入新的上限人数
			}
		}
	}
	fclose(fp);
	fclose(fin);
	remove("current_course.txt");//删除原文件
	rename("tmp.txt", "current_course.txt");//将临时文件名改为原文件名
	adminoperate();
}
void lookone()//查看某一门课程的具体信息
{
	cout << "请输入需要查看课程的id或者名称：";//注意是名称和id都要
	char str[30];
	gets_s(str);
	int allhave=0;//存这个课程人数上限，用于最后的输出提醒还差多少人满课
	if (ifinallcourse(str) != true)//不管是输入的id还是课程名称函数都会比对的
	{
		cout << "抱歉课程文件里没有这门课！\n";
		adminoperate();
	}
	FILE* fp = fopen("current_course.txt", "r");
	if (fp == NULL)
	{
		cout << "打开课程信息问价失败！";
		exit(-1);
	} 
	course a;
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id, a.course_name,
		a.teacher_name, &a.total,&a.current, a.kind) != EOF)
	{
		if (strcmp(str, a.course_id) == 0 || strcmp(str, a.course_name) == 0)
		{
			allhave = a.total;
			cout << "==================================================\n";
			cout << a.course_id << '\t' << a.course_name << '\t' << a.teacher_name << '\t' << a.total << '\t'
				<< a.current << '\t' << a.kind << '\n';
			cout << "==================================================\n";
		}
	}
	fclose(fp);
	char theid[4];
	if (strlen(str) > 3)
		toknowid(str, theid);
	else if (strlen(str) == 3)
		strcpy(theid, str);
	cout << "您还需要查看以下哪项内容：1.查看选课学生名单 2.查看课程报名助教名单\n";
	int num;
	cout << "请输入操作编号：";
	cin >> num;
	if (num == 2)
	{
		FILE* f = fopen("assistant.txt", "r");
		if (f == NULL)
		{
			cout << "打开助教文件失败！";
			exit(-1);
		}
		char tema[4];
		char list[1000];
		bool have = 0;
		while (fscanf(f, "%s\t%s\n", tema, list) != EOF)
		{
			if (strcmp(tema, theid) == 0)//找到了对应id打印后面的助教序列
			{
				have = 1;
				cout << "目前这门课报名的助教有：" << list;
			}
		}
		if (have == 0)
			cout << "目前还没有人报名这门课的助教哦！\n";
		fclose(f);
	}
	else if (num == 1)
	{
		//打开student文件存学生id再一个个打开遍历
		FILE* fpp = fopen("student.txt", "r");
		if (fpp == NULL)
		{
			cout << "打开学生信息文件失败！";
			exit(-1);
		}
		student a[100];
		int count = 0;
		while (fscanf(fpp, "%[^,]%s\n", a[count].student_id, a[count].password) != EOF)
		{
			count++;
		}
		int havechoose = 0;
		cout << "目前选择该门课的学生有：";
		for (int i = 0; i < count; i++)
		{
			//按数组顺序一个个打开对应的个人文件找是否有对应的课程id有就打印学生的id没有继续！
			char str1[30];
			strcpy(str1,a[i].student_id);
			const char* file = ".txt";
			strcat(str1, file);
			FILE* fpp = fopen(str1, "r");
			if (fpp == NULL)
			{
				cout << "学生个人课表文件打开失败";
				exit(-1);
			}
			char m[4];//存个人课表里的课程id
			char n[20];//个人课表里的助教名字
			
			while (fscanf(fpp, "%s\t%s\n", m, n) != EOF)
			{
				if (strcmp(m, theid) == 0)
				{
					havechoose++;
					cout << a[i].student_id <<',';//要输出的是学生的id
					break;
				}

			}
		}
		fclose(fpp);
		cout << "共计" << havechoose << "名同学," << "距离满课还差" << allhave - havechoose << "名同学！\n";
	}
	adminoperate();
}