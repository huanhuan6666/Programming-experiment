#include"define.h"
bool ifinallcourse(char coursename[30])
{
	FILE* fp = fopen("current_course.txt", "r");
	if (fp == NULL)
	{
		cout << "�򿪿γ���Ϣ�ļ�ʧ�ܣ�";
		exit(-1);
	}
	course c;
	while ( fscanf( fp, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id,c.course_name,c.teacher_name
	,&c.total,&c.current,c.kind) != EOF)
	{
		if (strlen(coursename)>3&&strcmp(coursename,c.course_name) == 0)//�Աȿγ����Ƶ�֪�Ѿ������ڿγ��ļ�����
		{
			fclose(fp);
			return true;
		}
		else if (strlen(coursename) == 3 && strcmp(coursename, c.course_id) == 0)//�Աȿγ�id��֪�Ѿ������ڿγ��ļ�����
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
	//��ѧ����Ϣ�ļ�
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL)
	{
		cout << "��ѧ����Ϣ�ļ�ʧ�ܣ�\n";
		exit(-1);
	}
	student a;
	while (fscanf(fp, "%[^,],%s\n", a.student_id, a.password) != EOF)
	{
		if (strcmp(a.student_id, id) == 0)//�Ҽ�һ����id��
		{
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}
bool ifinmycourse(char id[20], char str[30])//���˿α���������η���trueû�з���false
{
	//�򿪸��˿α��ļ�
	char tem[20];
	strcpy(tem, id);
	const char* file = ".txt";
	strcat(tem, file);
	FILE* fp = fopen(tem, "r");
	if (fp == NULL)
	{
		cout << "ѧ�����˿α��ļ���ʧ��*******";
		exit(-1);
	}
	//ͬ����ѧ�����˿α��ļ�������������
	//�α��ļ�ֻ�пγ�id����������������Ҫ��ӿγ�����
	mycourse* head = NULL;//�������˿γ����������
	mycourse* tail = NULL;//������β�巨��
	int num = 0, eachidcount = 0;
	char tem1[4];
	char tem2[20];
	while (fscanf(fp, "%s\t%s\n",tem1,tem2) != EOF)//�Ѹ��˿α���Ŀγ�id�ȶ������������ڿγ��ļ���������
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
		cout << "�γ��ļ���ʧ��!\n";
		exit(-1);
	}
	course m;
	mycourse* head1 = head;
	while (head1)//��������Ľڵ�ѿγ��������ȥ
	{
		//fseek(fpp, 0, 0);//************************�б�Ҫ?ÿ�ζ���ָ���Ƶ���ǰ��
		while (fscanf(fpp, "%s\t%s\t%s\t%d\t%d\t%s", m.course_id, m.course_name,m.teacher_name,
			&m.total,&m.current,m.kind) != EOF)
			if (strcmp(head1->mycourseid, m.course_id) == 0)//�ҵ���Ӧid��
			{
				strcpy(head1->mycoursename, m.course_name);//�ѿγ�����д���ڵ���
				break;//д���˾�������
			}
			else continue;
		head1 = head1->next;
	}
	fclose(fpp);
	while (head)//�������˿α�����û�������
	{
		if (strcmp(str, head->mycourseid) == 0 || strcmp(str, head->mycoursename) == 0)//����д������ļ������Լ�������
			return true;//�и������ſε�id��������
		head = head->next;
	}
	if (head == NULL) return false;//һֱ�����Ҳû���Ҽ�
}
void toknowid(char name[30],char tobe[4])
{
	FILE* fp = fopen("current_course.txt", "r");
	course a;
	while (fscanf(fp, "%s\t%s\t%s\%d\t%d\t%s", a.course_id, a.course_name,a.teacher_name,
	&a.total,&a.current,a.kind) != EOF)//��ȡ�γ��ļ������Ϣ�ȶ�
	{
		if (strcmp(a.course_name, name) == 0)
		{
			strcpy(tobe, a.course_id);
			fclose(fp);
		}
	}
	tobe[0] = {'\0'};//�γ��ļ���û��������ƾ͸�ֵΪ��
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
	tobe[0] = { '\0' };//û�����id�͸�ֵΪ��
}
void changemyassistant(char id[20],char mycourse[30],char mychoose[20])//�޸ĸ��˿α������������
{
	char str1[25];
	strcpy(str1, id);
	const char* file = ".txt";//�򿪸��˿α��ļ�
	strcat(str1, file);
	const char* thename = str1;
	FILE* fp = fopen(str1, "r");
	if (fp == NULL)
	{
		cout << "ѧ�����˿α��ļ���ʧ��";
		exit(-1);
	}
	char temid[5],temname[20];
	FILE* fpp = fopen("tem1.txt", "w");
	if (fpp == NULL)
	{
		cout << "����ʱ�ļ�ʧ��\n";
		exit(-1);
	}
	//�����޸�ѧ�����˿α����������Ϣ���ǲ��õ��½��ļ��������ķ�ʽ
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
	const char* file = ".txt";//�򿪸��˿α��ļ�
	strcat(str1, file);
	FILE* fp = fopen(str1, "r");
	if (fp == NULL)
	{
		cout << "��ѧ�����˿α�ʧ�ܣ�";
		exit(-1);
	}
	FILE* f = fopen("assistant.txt", "a+");
	if (f == NULL)
	{
		cout << "�������ļ�ʧ�ܣ�";
		exit(-1);
	}
	FILE* fin = fopen("tem.txt", "w");
	if (fin == NULL)
	{
		cout << "����ʱ�ļ�ʧ�ܣ�";
		exit(-1);
	}
	int flag = 0;//�ж������ڲ���1��ʾ��
	char a[4];//��γ�id
	char b[20];//����˿α�����Ǹ���������
	while (fscanf(fp, "%s\t%s\n", a, b) != EOF)
	{
		if (strcmp(b, "null") == 0)//������ſε����̻�û�оͲ����ж���
		{
			fprintf(fin, "%s\t%s\n", a, b);//ֱ��д����ʱ�ļ���
			continue;
		}
		flag = 0;
		fseek(f, 0, 0);
		char m[4];//�������ļ���Ŀγ�id
		char listall[2020];//��һ����
		while (fscanf(f, "%s\t", m) != EOF)
		{
			if (strcmp(a, m) == 0)//�ҵ������ſο������̻��ڲ���
			{
				char p[20];//��ÿһ����������
				char q = '0';
				while (q != '\n' && fscanf(f, "%[^,\n]", p) != EOF)
				{
					q = fgetc(f);
					if (strcmp(p, b) == 0)//˵�����̻���
					{
						flag = 1;//���˵�����ſ�ʶ����Ͽ���������
						break;
					}
				}
			}
			else//�������ſξͶ�����һ�н�����һ��
			{
				fscanf(f, "%s\n", listall);
			}
			
		}
		if (flag == 0)
		{
			cout << "��ע�⣡���Ŀγ�idΪ"<<a<<"�������˿��ˣ�\n";
			//�ٰѸ��˿α�������ſε����̸ĳ�null
			fprintf(fin, "%s\t%s\n", a, "null");//����ʱ�ļ��������д��null
		}
		if (flag == 1)
		{
			fprintf(fin, "%s\t%s\n", a, b);//���̻��ڵĻ���ֱ��д
		}
	}
	fclose(f);
	fclose(fp);
	fclose(fin);
	remove(str1);
	rename("tem.txt", str1);
}