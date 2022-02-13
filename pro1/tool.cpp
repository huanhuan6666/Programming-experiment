#include"define.h"
bool ifinallcourse(char coursename[30])
{
	FILE* fp = fopen("current_course.txt", "r");
	if (fp == NULL)
	{
		cout << "打开课程信息文件失败！";
		exit(-1);
	}
	course c;
	while ( fscanf( fp, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id,c.course_name,c.teacher_name
	,&c.total,&c.current,c.kind) != EOF)
	{
		if (strlen(coursename)>3&&strcmp(coursename,c.course_name) == 0)//对比课程名称得知已经存在于课程文件里了
		{
			fclose(fp);
			return true;
		}
		else if (strlen(coursename) == 3 && strcmp(coursename, c.course_id) == 0)//对比课程id得知已经存在于课程文件里了
		{
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}
bool ifinthestudent(char id[20])
{
	//打开学生信息文件
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL)
	{
		cout << "打开学生信息文件失败！\n";
		exit(-1);
	}
	student a;
	while (fscanf(fp, "%[^,],%s\n", a.student_id, a.password) != EOF)
	{
		if (strcmp(a.student_id, id) == 0)//找见一样的id了
		{
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}
bool ifinmycourse(char id[20], char str[30])//个人课表里有这个课返回true没有返回false
{
	//打开个人课表文件
	char tem[20];
	strcpy(tem, id);
	const char* file = ".txt";
	strcat(tem, file);
	FILE* fp = fopen(tem, "r");
	if (fp == NULL)
	{
		cout << "学生个人课表文件打开失败*******";
		exit(-1);
	}
	//同样把学生个人课表文件读到链表里面
	//课表文件只有课程id和助教姓名，至少要添加课程名称
	mycourse* head = NULL;//创建个人课程链表方便插入
	mycourse* tail = NULL;//这里用尾插法存
	int num = 0, eachidcount = 0;
	char tem1[4];
	char tem2[20];
	while (fscanf(fp, "%s\t%s\n",tem1,tem2) != EOF)//把个人课表里的课程id先读到链表里再在课程文件里找名称
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
	fclose(fp);
	FILE* fpp = fopen("current_course.txt", "r");
	if (fpp == NULL)
	{
		cout << "课程文件打开失败!\n";
		exit(-1);
	}
	course m;
	mycourse* head1 = head;
	while (head1)//完善链表的节点把课程名称填进去
	{
		//fseek(fpp, 0, 0);//************************有必要?每次都把指针移到最前面
		while (fscanf(fpp, "%s\t%s\t%s\t%d\t%d\t%s", m.course_id, m.course_name,m.teacher_name,
			&m.total,&m.current,m.kind) != EOF)
			if (strcmp(head1->mycourseid, m.course_id) == 0)//找到对应id了
			{
				strcpy(head1->mycoursename, m.course_name);//把课程名称写到节点里
				break;//写好了就跳出来
			}
			else continue;
		head1 = head1->next;
	}
	fclose(fpp);
	while (head)//看看个人课表里有没有这个课
	{
		if (strcmp(str, head->mycourseid) == 0 || strcmp(str, head->mycoursename) == 0)//如果有打开助教文件加上自己的名字
			return true;//有个人这门课的id或者名称
		head = head->next;
	}
	if (head == NULL) return false;//一直到最后也没有找见
}
void toknowid(char name[30],char tobe[4])
{
	FILE* fp = fopen("current_course.txt", "r");
	course a;
	while (fscanf(fp, "%s\t%s\t%s\%d\t%d\t%s", a.course_id, a.course_name,a.teacher_name,
	&a.total,&a.current,a.kind) != EOF)//读取课程文件里得信息比对
	{
		if (strcmp(a.course_name, name) == 0)
		{
			strcpy(tobe, a.course_id);
			fclose(fp);
		}
	}
	tobe[0] = {'\0'};//课程文件里没有这个名称就赋值为空
}
void toknowname(char id[4],char tobe[30])
{
	FILE* fp = fopen("current_course.txt", "r");
	course a;
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id, a.course_name,a.teacher_name,
		&a.total,&a.current,a.kind) != EOF)
	{
		if (strcmp(a.course_id, id) == 0)
		{
			strcpy(tobe, a.course_name);
			fclose(fp);
		}
	}
	tobe[0] = { '\0' };//没有这个id就赋值为空
}
void changemyassistant(char id[20],char mycourse[30],char mychoose[20])//修改个人课表里的助教姓名
{
	char str1[25];
	strcpy(str1, id);
	const char* file = ".txt";//打开个人课表文件
	strcat(str1, file);
	const char* thename = str1;
	FILE* fp = fopen(str1, "r");
	if (fp == NULL)
	{
		cout << "学生个人课表文件打开失败";
		exit(-1);
	}
	char temid[5],temname[20];
	FILE* fpp = fopen("tem1.txt", "w");
	if (fpp == NULL)
	{
		cout << "打开临时文件失败\n";
		exit(-1);
	}
	//这里修改学生个人课表里的助教信息还是采用的新建文件重命名的方式
	while (fscanf(fp, "%s\t%s\n", temid,temname) != EOF)
	{
		if (strcmp(temid, mycourse) == 0)
			fprintf(fpp, "%s\t%s\n", temid, mychoose);
		else
			fprintf(fpp, "%s\t%s\n", temid, temname);
	}
	fclose(fp);
	fclose(fpp);
	remove(str1);
	rename("tem1.txt", str1);
}
bool ifassconnect(char id[20])
{
	char str1[25];
	strcpy(str1, id);
	const char* file = ".txt";//打开个人课表文件
	strcat(str1, file);
	FILE* fp = fopen(str1, "r");
	if (fp == NULL)
	{
		cout << "打开学生个人课表失败！";
		exit(-1);
	}
	FILE* f = fopen("assistant.txt", "a+");
	if (f == NULL)
	{
		cout << "打开助教文件失败！";
		exit(-1);
	}
	FILE* fin = fopen("tem.txt", "w");
	if (fin == NULL)
	{
		cout << "打开临时文件失败！";
		exit(-1);
	}
	int flag = 0;//判断助教在不在1表示在
	char a[4];//存课程id
	char b[20];//存个人课表里的那个助教名字
	while (fscanf(fp, "%s\t%s\n", a, b) != EOF)
	{
		if (strcmp(b, "null") == 0)//如果这门课的助教还没有就不用判断了
		{
			fprintf(fin, "%s\t%s\n", a, b);//直接写到临时文件里
			continue;
		}
		flag = 0;
		fseek(f, 0, 0);
		char m[4];//存助教文件里的课程id
		char listall[2020];//存一大行
		while (fscanf(f, "%s\t", m) != EOF)
		{
			if (strcmp(a, m) == 0)//找到了这门课看看助教还在不在
			{
				char p[20];//存每一个助教名字
				char q = '0';
				while (q != '\n' && fscanf(f, "%[^,\n]", p) != EOF)
				{
					q = fgetc(f);
					if (strcmp(p, b) == 0)//说明助教还在
					{
						flag = 1;//标记说明这门课识别完毕可以跳出了
						break;
					}
				}
			}
			else//不是这门课就读完这一行进入下一行
			{
				fscanf(f, "%s\n", listall);
			}
			
		}
		if (flag == 0)
		{
			cout << "请注意！您的课程id为"<<a<<"的助教退课了！\n";
			//再把个人课表里的这门课的助教改成null
			fprintf(fin, "%s\t%s\n", a, "null");//在临时文件里把助教写成null
		}
		if (flag == 1)
		{
			fprintf(fin, "%s\t%s\n", a, b);//助教还在的话就直接写
		}
	}
	fclose(f);
	fclose(fp);
	fclose(fin);
	remove(str1);
	rename("tem.txt", str1);
}