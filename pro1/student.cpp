#include"define.h"
void studentoperate(char id[20])
{
	cout << "*****************您现在以学生身份***************\n";
	cout << "================================================\n";
	cout << "                * 1.注销登录         *\n"
		    "                * 2.查看课程信息     *\n"
		    "                * 3.选课             *\n"
		    "                * 4.查看个人课表     *\n"
		    "                * 5.退课             *\n"
		    "                * 6.举手报名助教     *\n"
		    "                * 7.选择个人助教     *\n"
		    "                * 8.重置密码         *\n"
		    "                * 9.看看谁选我当助教 *\n"
		    "                *10.我要退学         *\n"
		    "                **********************\n";
	cout << "================================================\n";
	cout << "请输入所选择的功能:";
	int num;
	cin >> num;
	getchar();
	switch (num)
	{
	case 1:
		logout();
		break;
	case 2:
		lookallcourse2(id);
		break;
	case 3:
		choosemy(id);
		break;
	case 4:
		lookmy(id);
		break;
	case 5:
		deletemy(id);
		break;
	case 6:
		tobe_assistant(id);
		break;
	case 7:
		choose_assistant(id);
		break;
	case 8:
		change_password(id);
		break;
	case 9:
		lookwhochoose(id);
		break;
	case 10:
		giveup(id);
		break;
	}
}
void lookallcourse2(char id[20])//查看全部课程信息
{
	system("cls");
	FILE* fp = fopen("current_course.txt", "a+");
	if (fp == NULL)
	{
		cout << "打开全部课程信息文件失败!\n";
		exit(-1);
	}
	cout << "全部课程信息如下:\n";
	cout << "课程ID\t" << "课程名称\t" << "            任课老师\t" << "                 上限人数 " << "已选人数\t" << "课程类型\n";
	course a;//一行一行都录到a中
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)
	{
		printf("%s\t%-30s%-30s%-10d%-10d%-10s\n", a.course_id
			, a.course_name, a.teacher_name, a.total, a.current, a.kind);
	}
	fclose(fp);
	studentoperate(id);
}
void choosemy(char id[20])//既要改current_course文件也要改学生个人课表文件
{
	cout << "请输入您要选择的课程id(注意是课程id哦)：";
	char chooseid[4];
	M:gets_s(chooseid);
	if (ifinmycourse(id, chooseid) == true)
	{
		cout << "您已经选了这门课了！请重新输入哦：";
		goto M;
	}
	FILE* fp = fopen("current_course.txt", "r");//要读取判断是否已达上限并做出相应修改
	if (fp == NULL)
	{
		cout << "打开课程信息文件失败!";
		exit(-1);
	}
	FILE* fin = fopen("tem.txt", "w");//还是建立临时文件写完改名
	if (fin == NULL)
	{
		cout << "打开临时文件失败！\n";
		exit(-1);
	}
	course a;
	bool flag = 1;//判断课程是否已经满了1表示已经满了
	bool flag1 = 0;//判断课程文件里是否有这门课0表示没有
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
		,a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)//遍历原课程文件往临时文件里写
	{
		if (strcmp(chooseid, a.course_id) == 0)//在课程文件里找到了这个课往临时文件里写改动后的数据
		{
			flag1 = 1;
			if (a.current == a.total)//课程人数已达上限不用改写原来的
			{
				flag = 1;//标记flag表示这门课已经满了
				fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
					, a.course_name, a.teacher_name, a.total, a.current, a.kind);
			}
			if (a.current < a.total)//可以选故要改变文件里选课人数
			{
				flag = 0;//表示没有满
				fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
					, a.course_name, a.teacher_name, a.total, a.current + 1, a.kind);//将已选人数加一
			}
				
		}
		else//如果这门课不需要改动就直接往临时文件里写
		{
			fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
				, a.course_name, a.teacher_name, a.total, a.current, a.kind);
		}
	}
	fclose(fp);//课程文件修改完毕
	fclose(fin);
	remove("current_course.txt");
	rename("tem.txt", "current_course.txt");
	if (flag1 == 0)
	{
		cout << "抱歉没有这门课的id哦！\n";
		cout << "是否重新输入？1.是 2.返回学生功能界面：";
		int m;
		cin >> m;
		getchar();//吸收回车
		if (m == 1)choosemy(id);
		else if (m == 2)studentoperate(id);
	}
	//修改学生的个人课表文件(课程\t助教)
	//
	char str1[30];
	strcpy(str1, id);
	const char* file = ".txt";
	strcat(str1, file);
	FILE* fpp = fopen(str1, "r+");
	if (fpp == NULL)
	{
		cout << "学生个人课表文件打开失败++--";
		exit(-1);
	}
	//注意学生课表文件始终按照课程id升序排列
	mycourse *newchoose=new mycourse;
	strcpy(newchoose->mycourseid, chooseid);//将新选择的课程存到mycourse型数据中
	strcpy(newchoose->theassistant, "null");
	newchoose->next = NULL;
	int newidcount = 100 * (newchoose->mycourseid[0] - '0') + 10 * (newchoose->mycourseid[1] - '0') 
		+ (newchoose->mycourseid[2]-'0');
	if (flag == 0 && flag1==1)//如果可以选这门课就需要改动个人课表文件
	{
		int num = 0, eachidcount=0;
		mycourse* head = NULL;//创建个人课程链表方便插入
		mycourse* tail = NULL;//这里用尾插法存
		char tem1[4];
		char tem2[20];
		while (fscanf(fpp, "%s\t%s", tem1, tem2) != EOF)
		{
			mycourse* p = new mycourse;
			strcpy(p->mycourseid, tem1);
			strcpy(p->theassistant, tem2);
			p->next = NULL;
			num++;
			if (head == NULL)
				head = p;
			else tail->next = p;
			tail = p;
		}
		if (num == 0)//如果个人课表文件还是个空文件
		{
			//直接写到个人课表文件里
			fprintf(fpp, "%s\t%s\n", newchoose->mycourseid, newchoose->theassistant);
			fclose(fpp);
			cout << "选课成功了！\n";
			studentoperate(id);
		}
		if (num == 10)
		{
			cout << "您已选择的课程已经达到10门上限不可选课!";
			studentoperate(id);//返回学生操作界面
		}
		else//如果已经有其他课程则需比较
		{
			mycourse* pre = head;
			mycourse* tem = head;
			while (tem)//将新选的课程插入到链表中
			{
				eachidcount = 100 * (tem->mycourseid[0] - '0') + 10 * (tem->mycourseid[1] - '0')
					+ (tem->mycourseid[2] - '0');
				if (newidcount < eachidcount)//找到新选的课程id小于列表中的课程id
				{
					if (pre == tem)//插到头部
					{
						newchoose->next = tem;
						head = newchoose;
					}
					else//插到中间
					{
						newchoose->next = pre->next;
						pre->next = newchoose;
					}
					break;//插好了就跳出循环往文件里写
				}
				pre = tem;
				tem = tem->next;
			}
			if (tem == NULL)//一直到最后都没找到说明要插到链表最后
			{
				pre->next = newchoose;
			}
		fseek(fpp, 0, 0);//文件指针移到开头重新覆盖掉
		while(head)
		{
			fprintf(fpp, "%s\t%s\n", head->mycourseid, head->theassistant);
			head = head->next;
		}
		fclose(fpp);
		cout << "选择课程成功!\n";
		studentoperate(id);
		}
	}
}

void tobe_assistant(char id[20])//举手报名助教并修改assistant文件
{
	FILE* f = fopen("assistant.txt", "r+");//读助教文件看看这个id是否出现了2次********************注意助教文件不一定存在!
	if (f == NULL)
	{
		cout << "打开助教文件失败!\n";
		exit(-1);
	}
	int count = 0;
	char gap='0';
	char temid[4];
	char myid[20];//助教姓名在助教文件里是用逗号隔开的
	while (fscanf(f, "%s\t",temid) != EOF)//这里是用来读取每一行开头的课程id
	{
		gap = '0';
		//读完开头的课程id继续读的就是助教名字了
		while (gap!='\n'&&fscanf(f, "%[^,\n]", myid) != EOF)//读到回车表示这一行结束了需要跳出另起一行
		{
			gap=fgetc(f);//读一个符号，逗号或者回车
			if (strcmp(myid, id) == 0)//如果找到了我的id次数加一
				count++;
		}
	}
	if (count == 2)
	{
		fclose(f);
		cout << "您报名的助教个数已达上限，无法报名!\n";
		studentoperate(id);//返回学生功能界面
	}
	
	cout << "请输入您要报名助教的课程名称或者课程id:";
	char str[30];
	gets_s(str);
	char trueid[4];
	if (strlen(str) > 3)//如果长度过长就得知是名称
		toknowid(str, trueid);//得到名称对应的id
	
	if( ifinmycourse(id,str) )//如果有打开助教文件加上自己的名字
		{
		//判断一下自己是否已经报过这门课的助教了
		fseek(f, 0, 0);
		char a[4];
		char b[20];
		char c='\0';
		while (fscanf(f, "%s\t", a) != EOF)//先读学号
		{
			if (strcmp(a, str) == 0 || strlen(str) > 3 && strcmp(a, trueid) == 0)//找到这门课
				while (c != '\n' && fscanf(f, "%[^,\n]", b) != EOF)
				{
					c = fgetc(f);
					if (strcmp(b, id) == 0)//这门课的助教里有我的名字了
					{
						fclose(f);
						cout << "您已经是这门课的助教了哦！请您选择继续的操作(1.我要报名别的助教 2.返回学生功能界面)：";
						int q;
						cin >> q;
						getchar();
						if (q == 1)
							tobe_assistant(id);
						else if (q == 2)
							studentoperate(id);
					}
				}
			else
			{
				char alllist[2000];
				fscanf(f, "%s\n", alllist);//如果不是这门课就读一大行
			}
		}	
		fseek(f, 0, 0);//把助教文件指针移到开头
		FILE* fin = fopen("temass.txt", "w");
		if (fin == NULL)
		{
			cout << "打开临时助教文件失败！";
			exit(-1);
		}
		int flag = 0;//判断助教文件里是否有这个课0表示没有
		char assid[4];//助教文件里课程id
		char allass[2000];//这个课程id下所有的助教一长串带逗号
		while (fscanf(f, "%s\t%s\n", assid,allass) != EOF)//找助教文件里有没有这个id有的话添加姓名没有的话新建一行
		{
			
			if (strcmp(assid, str) == 0||strlen(str)>3&&strcmp(assid,trueid)==0)//助教文件里有这门课,注意助教文件里找的是课程id而不是课程名称
			{
				flag = 1;
				fprintf(fin, "%s\t%s,%s\n",assid, allass, id);//把这一行全写到临时文件里最后加上自己的名字
			}
			else//如果不是这门课要加名字就直接往临时文件里写
			{
				fprintf(fin, "%s\t%s\n", assid, allass);
			}
		}
		if (flag == 0)//如果助教文件原先就没有人报名这个课
		{
			if (strlen(str) > 3)
				fprintf(fin, "%s\t%s\n", trueid, id);
			else
				fprintf(fin, "%s\t%s\n", str, id);
		}
		fclose(fin);
		fclose(f);
		remove("assistant.txt");
		rename("temass.txt", "assistant.txt");
		cout << "报名课程助教成功了！\n";
		studentoperate(id);
	}
	
	else //这个课并不在我的个人课表里
	{
		fclose(f);
		cout << "您并没有选这门课!\n";
		cout << "是否进入选课界面?(1. 是  2.否，返回学生功能界面)\n";
		int a;
		cin >> a;
		getchar();//吸收回车
		if (a == 1) choosemy(id);
		else if (a == 2)
			studentoperate(id);
	}
}	
void lookmy(char id[20])//查看个人课表
{
	char str1[25];
	strcpy(str1, id);
	const char* file = ".txt";//打开个人课表文件
	strcat(str1, file);
	FILE* fp = fopen(str1, "r");
	if (fp == NULL)
	{
		cout << "学生个人课表文件打开失败";
		exit(-1);
	}
	mycourse* head = NULL;//创建个人课程链表方便插入
	mycourse* tail = NULL;//这里用尾插法存
	char tem1[4];
	char tem2[20];
	while (fscanf(fp, "%s\t%s\n",tem1,tem2) != EOF)//把个人课表里的课程id和助教
		                                                            //先读到链表里再在课程文件里找名称
	{
		mycourse* p = new mycourse;
		strcpy(p->mycourseid, tem1);
		strcpy(p->theassistant, tem2);
		p->next = NULL;
		if (head == NULL)
			head = p;
		else tail->next = p;
		tail = p;
		
	}
	fclose(fp);
	FILE* fpp = fopen("current_course.txt", "a+");
	if (fpp == NULL)
	{
		cout << "打开课程文件失败!\n";
		exit(-1);
	}
	mycourse* head1 = head;
	while (head1)
	{
		//fseek(fpp, 0, 0);//*******************************?是否有必要因为都是按照顺序排列的
		int tem1, tem2;
		course a;
		while (fscanf(fpp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id, a.course_name, a.teacher_name,
			&a.total, &a.current, a.kind) != EOF)//把课程文件里的一行读到a里再判断
		{
			if (strcmp(a.course_id, head1->mycourseid) == 0)
			{
				strcpy(head1->mycoursename, a.course_name);//找到匹配的id就把课程文件里的信息对应写到节点里
				strcpy(head1->myteacher, a.teacher_name);
				strcpy(head1->mykind, a.kind);
				break;//写好了就跳出循环
			}
		}
		head1 = head1->next;
	}
	fclose(fpp);
	cout << "您目前所选的课程有:\n";
	cout << "******************************************\n";
	cout << "课程id\t课程名称\t授课教师\t课程类型\t个人助教\n";
	int count1 = 0, count2 = 0;
	while (head)
	{
		cout << head->mycourseid << '\t' << head->mycoursename << '\t' << head->myteacher << '\t' 
			<< head->mykind << '\t'<< head->theassistant << '\n';
		if (strcmp(head->mykind, "专业课") == 0) count1++;
		else if (strcmp(head->mykind, "非专业课") == 0) count2++;
		head = head->next;
	}
	cout << "*******************************************\n";
	if (count1 < MAJ || count2 < UMA)
		cout << "根据学院要求:目前所选的课程数不达标!仍差" << MAJ - count1 << "门专业课，"
		<< "以及" << UMA - count2 << "门非专业课!请及时选课!\n";
	else cout << "您目前所选的课程数已达标!\n";
	studentoperate(id);
}
void choose_assistant(char id[20])//为自己某门课选择助教,要改变个人课表文件
{
	//看看自己课表里有没有这个课和之前当助教有类似之处，可复制粘贴
	cout << "请输入您要选择助教的课程名称或者课程id:";
	char str[30];
	gets_s(str);
	char trueid[4];
	if (strlen(str) > 3)//如果长度过长就得知是名称
		toknowid(str, trueid);//得到名称对应的id
	if (ifinmycourse(id, str))//如果我的课表里有这门课
	{
		//则打开助教文件打印报名助教
		
			FILE* f = fopen("assistant.txt", "r");
			if (f == NULL)
			{
				cout << "打开助教教文件失败!\n";
				exit(-1);
			}
			//打印出这门课当前报名的助教
			//可能还没有人报名，也可能有人报名了
			bool have = 0;
			char assid[4], ass[20];//助教文件里课程id和对应报名的的助教
			while (fscanf( f, "%s\t", assid) != EOF)//找助教文件里有没有这个id有的话打印姓名没有的话提示没有
			{
				if (strcmp(assid, str) == 0||strlen(str)>3&&strcmp(assid,trueid)==0)//助教文件里有这门课,注意助教文件里找的是课程id而不是课程名称
				{
					have = 1;//have赋值成1表示有人报名这个课的助教
					char theall[2000];
					cout << "当前报名这门课助教的同学有:";
					fscanf(f, "%s\n", theall);//打印一大串即可
					cout << theall;
					fclose(f);//打印完了助教文件指针就可以关了
					cout << "\n请在上述的助教中，选择你的个人助教:";
					//
					//
					//需要改动个人课表文件
					char ichooseass[20];
					gets_s(ichooseass);
					char  str1[25];
					strcpy(str1, id);
					const char* file = ".txt";//打开个人课表文件
					strcat(str1, file);
					FILE* fp = fopen(str1, "r+");
					if (fp == NULL)
					{
						cout << "学生个人课表文件打开失败";
						exit(-1);
					}
					mycourse my;
					while (fscanf(fp, "%s\t%s", my.mycourseid, my.theassistant) != EOF)
					{
						//在个人课表里找这个课程，注意匹配的是课程id
						if (strcmp(my.mycourseid, str) == 0 || strlen(str) != 3 && strcmp(my.mycourseid, trueid) == 0)
						{
							if (strcmp(my.theassistant, "null") != 0)
							{
								cout << "这门课您已经选择助教了!\n是否重选一次(1.是 2.否，返回学生功能界面)";
								int cho;
								cin >> cho;
								getchar();
								fclose(fp);
								if (cho == 1 && strlen(str) == 3) changemyassistant(id, str, ichooseass);//这里写个函数来将选择的助教的名字替换原来的null或者旧名字               ; 
								else if (cho == 1 && strlen(str) != 3) changemyassistant(id, trueid, ichooseass);
								
							}
							else//表示这门课助教处还是null则可以改动
							{
								//调用上面提到的那个函数
								fclose(fp);
								if (strlen(str) == 3) changemyassistant(id, str, ichooseass);//这里写个函数来将选择的助教的名字替换原来的null或者旧名字               ; 
								else if (strlen(str) != 3) changemyassistant(id, trueid, ichooseass);
								
							}
							cout << "操作成功\n";
							studentoperate(id);
						}
					}
					fclose(fp);
				}
				else //如果此时并不是这门课的id就
				{
					char alllist[2000];
					fscanf(f, "%s\n", alllist);
				}
			}
			fclose(f);
		if (have == 0)
		{
			cout << "抱歉这门课还没有人报名助教!\n是否报名助教(1.是 2.否，返回学生功能界面)";
			int num;
			cin >> num;
			getchar();
			if (num == 1) tobe_assistant(id);
			else if (num == 2) studentoperate(id);
		}
	}
	else 
	{
		cout << "您并没有选这门课!\n";
		cout << "是否进入选课界面?(1. 是  2.否，返回学生功能界面)\n";
		int a;
		cin >> a;
		getchar();
		if (a == 1) choosemy(id);
		else if (a == 2)
			studentoperate(id);
	}
}
void deletemy(char id[20])//学生退课，要改动个人课表文件，改动课程文件里的选课人数
{
	cout << "请输入课程名称或者课程id：";
	char str[30];
	gets_s(str);
	if (ifinmycourse(id, str) == false)
	{
		cout << "抱歉您没有选这门课！";
		studentoperate(id);
	}
	char trueid[4];
	if (strlen(str) > 3)
		toknowid(str, trueid);
	else if (strlen(str) == 3)
		strcpy(trueid, str);
	char  str1[25];
	strcpy(str1, id);
	const char* file = ".txt";//打开个人课表文件
	strcat(str1, file);
	FILE* f = fopen(str1, "r");//修改课表建立临时文件
	if (f == NULL)
	{
		cout << "打开学生个人课表文件失败！";
		exit(-1);
	}
	FILE* fin = fopen("tem.txt", "w");
	if (fin == NULL)
	{
		cout << "打开临时文件失败！";
		exit(-1);
	}
	char a[4];//因为删除时不用考虑排序的问题这里直接用两个数组存储
	char b[20];
	while (fscanf(f, "%s\t%s\n", a, b) != EOF)
	{
		if (strcmp(a, trueid) != 0)//不是这门课就写
		{
			fprintf(fin, "%s\t%s\n", a, b);

		}
	}
	fclose(f);
	fclose(fin);
	remove(str1);
	rename("tem.txt", str1);//写好了删除改名即可
	FILE* fp = fopen("current_course.txt", "r");//同样修改课程信息文件也是建立临时文件
	if (fp == NULL)
	{
		cout << "打开课程信息文件失败！";
		exit(-1);
	}
	FILE* fn = fopen("tem2.txt", "w");
	if (fn == NULL)
	{
		cout << "打开临时文件失败！";
		exit(-1);
	}
	course c;
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id, c.course_name, c.teacher_name,
		&c.total, &c.current, c.kind) != EOF)
	{
		if (strcmp(c.course_id, trueid) == 0)//如过id对了将这门课的已选人数减一
			fprintf(fn, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id, c.course_name, c.teacher_name,
				c.total, c.current - 1, c.kind);
		else
			fprintf(fn, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id, c.course_name, c.teacher_name,
				c.total, c.current, c.kind);
	}
	fclose(fp);
	fclose(fn);
	remove("current_course.txt");
	rename("tem2.txt", "current_course.txt");
	FILE* fpp = fopen("assistant.txt", "r");
	if (fpp == NULL)
	{
		cout << "打开助教文件失败！";
		exit(-1);
	}
	FILE* fi = fopen("tem3.txt", "w");
	if (fi == NULL)
	{
		cout << "打开临时文件失败！";
		exit(-1);
	}
	int flag = 0;
	char m[4];//存助教文件里的课程id
	char n[2000];//存助教文件里的助教序列带逗号
	while (fscanf(fpp, "%s\t", m) != EOF)
	{
		flag = 0;
		int h = 0;
		char tem = '\0';
		while (tem != '\n')
		{
			h++;//记录文件指针向后走了多少个字符
			tem = fgetc(fpp);
			if (tem == ',')
			{
				flag = 1;//表示后面有逗号，不会出现删除后助教姓名为空的情况
				break;
			}
		}
		if (flag == 1)
		{
			fseek(fpp, -h, 1);//把文件指针移到原位
			fprintf(fi, "%s\t", m);
			if (strcmp(m, trueid) == 0)//如果在助教文件里找到了要退的id找到自己并删除
			{
				int n = 0;
				char p[20];//存每一个助教名字
				char q = '0';
				while (q != '\n' && fscanf(fpp, "%[^,\n]", p) != EOF)
				{
					if (strcmp(p, id) != 0&&(q=='0'||q==','))//不是自己的名字并且在最前面或者中间
					{
						if(q=='0')//在最前面
						fprintf(fi, "%s", p);
						else if (q == ',')//在中间
						{
							if (n == 0)//如果前面不是要删除的名字
							{
								fputc(q, fi);//要把逗号写上
								fprintf(fi, "%s", p);
							}
							
							else if(n==1)//如果前面是要删除的名字
							{
								fprintf(fi, "%s", p);//不写逗号
								n = 0;//把n更新
							}
						}
					}
					/*if (strcmp(p, id) == 0 && q == ',')
					{
						fputc('\n', fi);//应该是什么也不用干
					}*/
					if (strcmp(p, id) == 0 && q == '0')//如果自己的名字出现在最前面标记
					{
						n = 1;
					}
					q = fgetc(fpp);

				}
				fputc('\n', fi);
			}
			else
			{
				char r[2000];
				fscanf(fpp, "%s\n", r);
				fprintf(fi, "%s\n", r);
			}
		}
		else if (flag == 0)//后面就一个名字
		{
			fseek(fpp, -(h + 1), 1);
			if (strcmp(m, trueid) == 0)//如果退的就是这门课看看后面有没有我的名字
			{
				char p[20];//存每一个助教名字
				char q = '0';
				while (q != '\n' && fscanf(fpp, "%[^,\n]", p) != EOF)
				{
					q = fgetc(fpp);
					if (strcmp(p, id) != 0)//不是自己的名字要把课程id也写上 是自己的名字就啥也不写了因为后面就一个自己
					{
						fprintf(fi, "%s\t%s",trueid, p);
						fputc(q, fi);
					}
				}
			}
			else//如果退的不是这门课
			{
				fprintf(fi, "%s\t", m);//先把课程id填上
				char r[2000];
				fscanf(fpp, "%s\n", r);//再把后面的助教全写上就可了
				fprintf(fi, "%s\n", r);
			}
		}
	}
	fclose(fpp);
	fclose(fi);
	remove("assistant.txt");
	rename("tem3.txt", "assistant.txt");
	cout << "退课成功！\n";
	lookmy(id);
	studentoperate(id);
}
void lookwhochoose(char id[20])//看看谁选我当助教
{
	FILE* f = fopen("student.txt", "a+");
	if (f == NULL)
	{
		cout << "打开学生文件失败";
		exit(-1);
	}
	student a[100];
	char stuid[20];//学生信息表里的学生id
	char pass[20];//学生密码
	int i = 0;
	while (fscanf(f, "%[^,],%s\n", stuid, pass) != EOF)
	{
		strcpy(a[i].student_id, stuid);
		i++;
	}
	fclose(f);
	int flag = 0;
	for (int j = 0; j < i; j++)
	{
		char str1[25];
		strcpy(str1,a[j].student_id);
		const char* file = ".txt";//打开个人课表文件
		strcat(str1, file);
		FILE* fp = fopen(str1, "r");
		if (fp == NULL)
		{
			cout << "学生个人课表文件打开失败";
			exit(-1);
		}
		char m[4];//课程id
		char n[20];//助教id
		while (fscanf(fp, "%s\t%s\n", m, n) != EOF)
		{
			if (strcmp(n, id) == 0)//这个学生的助教id和我名字一样
			{
				flag = 1;
				cout << "学生id为" << a[j].student_id << "的同学选你为课程id为" <<m<<"的助教\n" ;
			}
		}
		fclose(fp);
	}
	if (flag == 0)
		cout << "抱歉，没人选你当助教！\n";
	studentoperate(id);
}
void giveup(char id[20])
{
	cout << "您确定要退学？请输入：(1. 手滑了 2.退学！)：";
	int num;
	cin >> num;
	if (num == 1)
		studentoperate(id);
	else if (num == 2)
	{
		char str1[25];
		strcpy(str1,id);
		const char* file = ".txt";//先把个人课表里的每门课都退掉再删除这个文件才行
		strcat(str1, file);
		FILE* f2 = fopen(str1, "r");
		if (f2 == NULL)
		{
			cout << "打开个人课表失败！";
			exit(-1);
		}
		char ke[4], zhujiao[20];
		while (fscanf(f2, "%s\t%s", ke, zhujiao) != EOF)
		{
			FILE* fp = fopen("current_course.txt", "r");//同样修改课程信息文件也是建立临时文件
			if (fp == NULL)
			{
				cout << "打开课程信息文件失败！";
				exit(-1);
			}
			FILE* fn = fopen("tem2.txt", "w");
			if (fn == NULL)
			{
				cout << "打开临时文件失败！";
				exit(-1);
			}
			course c;
			while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id, c.course_name, c.teacher_name,
				&c.total, &c.current, c.kind) != EOF)
			{
				if (strcmp(c.course_id, ke) == 0)//如过id对了将这门课的已选人数减一
					fprintf(fn, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id, c.course_name, c.teacher_name,
						c.total, c.current - 1, c.kind);
				else
					fprintf(fn, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id, c.course_name, c.teacher_name,
						c.total, c.current, c.kind);
			}
			fclose(fp);
			fclose(fn);
			remove("current_course.txt");
			rename("tem2.txt", "current_course.txt");
			FILE* fpp = fopen("assistant.txt", "r");
			if (fpp == NULL)
			{
				cout << "打开助教文件失败！";
				exit(-1);
			}
			FILE* fi = fopen("tem3.txt", "w");
			if (fi == NULL)
			{
				cout << "打开临时文件失败！";
				exit(-1);
			}
			int flag = 0;
			char m[4];//存助教文件里的课程id
			char n[2000];//存助教文件里的助教序列带逗号
			while (fscanf(fpp, "%s\t", m) != EOF)
			{
				flag = 0;
				int h = 0;
				char tem = '\0';
				while (tem != '\n')
				{
					h++;//记录文件指针向后走了多少个字符
					tem = fgetc(fpp);
					if (tem == ',')
					{
						flag = 1;//表示后面有逗号，不会出现删除后助教姓名为空的情况
						break;
					}
				}
				if (flag == 1)
				{
					fseek(fpp, -h, 1);//把文件指针移到原位
					fprintf(fi, "%s\t", m);
					if (strcmp(m, ke) == 0)//如果在助教文件里找到了要退的id找到自己并删除
					{
						int n = 0;
						char p[20];//存每一个助教名字
						char q = '0';
						while (q != '\n' && fscanf(fpp, "%[^,\n]", p) != EOF)
						{
							if (strcmp(p, id) != 0 && (q == '0' || q == ','))//不是自己的名字并且在最前面或者中间
							{
								if (q == '0')//在最前面
									fprintf(fi, "%s", p);
								else if (q == ',')//在中间
								{
									if (n == 0)//如果前面不是要删除的名字
									{
										fputc(q, fi);//要把逗号写上
										fprintf(fi, "%s", p);
									}

									else if (n == 1)//如果前面是要删除的名字
									{
										fprintf(fi, "%s", p);//不写逗号
										n = 0;//把n更新
									}
								}
							}
							/*if (strcmp(p, id) == 0 && q == ',')
							{
								fputc('\n', fi);//应该是什么也不用干
							}*/
							if (strcmp(p, id) == 0 && q == '0')//如果自己的名字出现在最前面标记
							{
								n = 1;
							}
							q = fgetc(fpp);

						}
						fputc('\n', fi);
					}
					else
					{
						char r[2000];
						fscanf(fpp, "%s\n", r);
						fprintf(fi, "%s\n", r);
					}
				}
				else if (flag == 0)//后面就一个名字
				{
					fseek(fpp, -(h + 1), 1);
					if (strcmp(m, ke) == 0)//如果退的就是这门课看看后面有没有我的名字
					{
						char p[20];//存每一个助教名字
						char q = '0';
						while (q != '\n' && fscanf(fpp, "%[^,\n]", p) != EOF)
						{
							q = fgetc(fpp);
							if (strcmp(p, id) != 0)//不是自己的名字要把课程id也写上 是自己的名字就啥也不写了因为后面就一个自己
							{
								fprintf(fi, "%s\t%s", ke, p);
								fputc(q, fi);
							}
						}
					}
					else//如果退的不是这门课
					{
						fprintf(fi, "%s\t", m);//先把课程id填上
						char r[2000];
						fscanf(fpp, "%s\n", r);//再把后面的助教全写上就可了
						fprintf(fi, "%s\n", r);
					}
				}
			}
			fclose(fpp);
			fclose(fi);
			remove("assistant.txt");
			rename("tem3.txt", "assistant.txt");
		}
		fclose(f2);
		remove(str1);//删除个人课表文件
		FILE* f = fopen("student.txt", "r");
		if (f == NULL)
		{
			cout << "打开学生信息文件失败!\n";
			exit(-1);
		}
		char m[20];//学生id
		char n[20];//学生密码
		FILE* fin = fopen("ttem.txt", "w");
		if (fin == NULL)
		{
			cout << "打开临时文件失败！";
			exit(-1);
		}
		while (fscanf(f, "%[^,],%s\n", m, n) != EOF)
		{
			if (strcmp(m, id) != 0)
				fprintf(fin, "%s,%s\n", m, n);
		}
		fclose(f);
		fclose(fin);
		remove("student.txt");
		rename("ttem.txt", "student.txt");

		cout << " 退学成功，祝您生活愉快！\n";
	}
	tobegin();// 返回原始界面
}