#include"define.h"
void adminoperate()
{
	cout << "***************�������ǹ���Ա���*****************\n";
	cout << "==================================================\n";
	cout << "              * 1.ע����¼          *\n"
		    "              * 2.¼��γ���Ϣ      *\n"
		    "              * 3.�鿴ȫ���γ���Ϣ  *\n"
		    "              * 4.���ӿγ�          *\n"
		    "              * 5.ɾ���γ�          *\n"
		    "              * 6.�޸Ŀγ�          *\n"
		    "              * 7.�鿴����γ�      *\n";
	cout << "==================================================\n";
	cout << "��������ѡ��Ĺ���:";
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
void inputcourse()//¼��γ���Ϣ
{
	system("cls");
	cout << "����������Ҫ����Ŀγ���Ϣ�ļ�����:\n";
	char filename[30];
	gets_s(filename);
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		cout << "�򿪿γ���Ϣ�ļ�ʧ��!\n";
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
	cout << "******����γ���Ϣ�ɹ���!********\n";
	fclose(fp);
	fclose(fpp);
	adminoperate();
}
void lookallcourse1()//�鿴ȫ���γ���Ϣ(����Ա��ѧ����ͬ���ĺ���)
{
	system("cls");
	FILE* fp = fopen("current_course.txt", "a+");
	if (fp == NULL)
	{
		cout << "��ȫ���γ���Ϣ�ļ�ʧ��!\n";
		exit(-1);
	}
	cout << "ȫ���γ���Ϣ����:\n";
	cout << "�γ�ID\t" << "�γ�����\t" << "          �ο���ʦ\t" << "                 �������� " << "��ѡ����\t" << "�γ�����\n";
	course a;//һ��һ�ж�¼��a��
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
//���������Ӻ�����û�м��γ��Ѿ����ڵĹ���
//Ҫע��!
void addcourse()//����Ա����һ�ſγ�������չʾ���пγ�
{
	char newname[30],newteacher[30],newkind[10];//�����ǰ��¿γ̵ĸ�����Ϣһ����¼���±�����
	int all, cur;
	cout << "������Ҫ����γ̵ľ�����Ϣ(�γ�id���Զ�����,����¼��)\n";
	cout << "������γ�����:";
	C:gets_s(newname);
	if (ifinallcourse(newname)==true)
	{
		cout << "��Ǹ���ſ��Ѿ������ˣ�\n���������������ƣ�";
		goto C;
	}
	cout << "�������ڿν�ʦ����:";
	gets_s(newteacher);
	cout << "������γ�����(רҵ�� �� ��רҵ��):";
	gets_s(newkind);
	cout << "������γ���������:";
	cin >> all;
	cout << "������Ŀǰ��ѡ����:";
	cin >> cur;
	FILE* fp = fopen("current_course.txt", "a+");//�Զ�д��ʽ���ļ�
	//�����һ�еĿγ�id
	course a;
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF);//һֱ�������
	int count = 0;
	char c1,c2,c3;
	//��ʱa�д�ľ������һ�е�����
	c1 = a.course_id[0];
	c2 = a.course_id[1];
	c3 = a.course_id[2];
	count = (c1-'0') * 100 + (c2-'0') * 10 + (c3-'0') + 1;
	char newcount[4];
	for (int i = 0; i < 3; i++)//���µı�Ŵ���newcount������
	{
		newcount[2 - i] = (count % 10)+'0';
		count /= 10;
	}
	newcount[3] = '\0';
	fseek(fp, 0, 2);//��ȡ��ź��ļ�ָ���Ƶ��ļ����ʼд�µ�һ�пγ���Ϣ
	fprintf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", newcount, 
		newname, newteacher, all, cur, newkind);//��ʽ�������ļ�ĩβ
	fclose(fp);//�Ȱ����ָ��ص�����һ��
	lookallcourse1();//���ò鿴ȫ���γ̺������鿴��Ϣ
}
void deletecourse()//ָ���γ�id��ɾ������γ̵�û��ѡ�ÿγ̵������
{
	char delid[4];
	cout << "������Ҫɾ���Ŀγ�id:";
	gets_s(delid);
	FILE* fp = fopen("current_course.txt", "r");
	if (fp == NULL)
	{
		cout << "��ȫ���γ���Ϣ�ļ�ʧ��!\n";
		exit(-1);
	}
	course a;
	bool flag = 0;
	//
	//����һ����ʱ�ļ�������д��Ϣ��ȷ��������Ҫɾ���Ŀγ���Ϣ���ɾ��ԭ�γ��ļ�������ʱ�ļ�������
	FILE* fin = fopen("tmp.txt", "w");
	if (fin == NULL)
	{
		cout << "�����γ���ʱ�ļ�ʧ��!";
		exit(-1);
	}
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)
	{
		flag = 0;
		if (strcmp(delid, a.course_id) == 0)//�γ�idһ������Ҫɾ
			flag = 1;
		if (!flag)//����Ҫɾ���Ŀγ�
			fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
				, a.course_name, a.teacher_name, a.total, a.current, a.kind);//�Ѷ���������д����ʱ�ļ���
		else//��Ҫɾ�Ŀγ̵Ļ����ÿ����Ƿ�����ѡ��
		{
			if (a.current > 0)//�������ѡ�˻���¼����ʱ�ļ���
			{
				cout << "��Ǹ,���ſ��Ѿ���ͬѧѡ��,�޷�ɾ��!\n";
				fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
					, a.course_name, a.teacher_name, a.total, a.current, a.kind);
			}
			else cout << "ɾ���γ���Ϣ�ɹ��ˣ�\n";
		}
	}
	fclose(fp);
	fclose(fin);
	remove("current_course.txt");//ɾ��ԭ�ļ�
	rename("tmp.txt", "current_course.txt");//����ʱ�ļ�����Ϊԭ�ļ���
	adminoperate();
}
void changecourse()//�޸Ŀγ���Ϣͬ��Ҳ�ǽ���һ����ʱ�ļ�����
{
	cout << "������Ҫ�޸ĵĿγ�ID:";
	char changeid[4];
	gets_s(changeid);
	cout << "��Ҫ�޸ĵľ����ֶ�Ϊ(1.�ον�ʦ  2.��������):";
	int num;
	cin >> num;
	char newteacher[30];
	int newall;
	cout << "�����޸�Ϊ:";
	getchar();
	if (num == 1)
		gets_s(newteacher);
	else if (num == 2)
		cin >> newall;
	//��ʼ��ԭ�ļ���д����ʱ�ļ�
	FILE* fp = fopen("current_course.txt", "r");
	if(fp==NULL)
	{
		cout << "��ȫ���γ���Ϣ�ļ�ʧ��!\n";
		exit(-1);
	}
	course a;
	bool flag = 0;
	//
	//����һ����ʱ�ļ�������д��Ϣ���޸Ķ�Ӧid�Ŀγ���Ϣ
	FILE* fin = fopen("tmp.txt", "w");
	if (fin == NULL)
	{
		cout << "�����γ���ʱ�ļ�ʧ��!";
		exit(-1);
	}
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)
	{
		flag = 0;
		if (strcmp(changeid, a.course_id) == 0)//�γ�idһ���˾���Ҫ�޸���
			flag = 1;
		if (!flag)//����Ҫɾ���Ŀγ�
			fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
				, a.course_name, a.teacher_name, a.total, a.current, a.kind);//�Ѷ���������д����ʱ�ļ���
		else //��Ҫ�޸ĵĿγ̻�Ҫ�ж��޸ĺ����������ѡ�����Ĵ�С��ϵ
		{
			if(num==1)//�ĵ�����ʦ����
			{
				fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
					, a.course_name, newteacher, a.total, a.current, a.kind);//¼��������
				cout << "�޸ĳɹ���!\n";
			}
			else if (num == 2)//�ĵ�����������
			{
				if (newall < a.current)//�ĺ�������С
				{
					cout << "�ĺ�����С�ڵ�ǰ�γ���ѡ����,�޷��޸�!\n";
					fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
						, a.course_name, a.teacher_name, a.total, a.current, a.kind);//¼��ԭ��Ϣ
				}
				else //�ĺ�����������ѡ����
					fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
						, a.course_name, a.teacher_name, newall, a.current, a.kind);//¼���µ���������
			}
		}
	}
	fclose(fp);
	fclose(fin);
	remove("current_course.txt");//ɾ��ԭ�ļ�
	rename("tmp.txt", "current_course.txt");//����ʱ�ļ�����Ϊԭ�ļ���
	adminoperate();
}
void lookone()//�鿴ĳһ�ſγ̵ľ�����Ϣ
{
	cout << "��������Ҫ�鿴�γ̵�id�������ƣ�";//ע�������ƺ�id��Ҫ
	char str[30];
	gets_s(str);
	int allhave=0;//������γ��������ޣ���������������ѻ������������
	if (ifinallcourse(str) != true)//�����������id���ǿγ����ƺ�������ȶԵ�
	{
		cout << "��Ǹ�γ��ļ���û�����ſΣ�\n";
		adminoperate();
	}
	FILE* fp = fopen("current_course.txt", "r");
	if (fp == NULL)
	{
		cout << "�򿪿γ���Ϣ�ʼ�ʧ�ܣ�";
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
	cout << "������Ҫ�鿴�����������ݣ�1.�鿴ѡ��ѧ������ 2.�鿴�γ̱�����������\n";
	int num;
	cout << "�����������ţ�";
	cin >> num;
	if (num == 2)
	{
		FILE* f = fopen("assistant.txt", "r");
		if (f == NULL)
		{
			cout << "�������ļ�ʧ�ܣ�";
			exit(-1);
		}
		char tema[4];
		char list[1000];
		bool have = 0;
		while (fscanf(f, "%s\t%s\n", tema, list) != EOF)
		{
			if (strcmp(tema, theid) == 0)//�ҵ��˶�Ӧid��ӡ�������������
			{
				have = 1;
				cout << "Ŀǰ���ſα����������У�" << list;
			}
		}
		if (have == 0)
			cout << "Ŀǰ��û���˱������ſε�����Ŷ��\n";
		fclose(f);
	}
	else if (num == 1)
	{
		//��student�ļ���ѧ��id��һ�����򿪱���
		FILE* fpp = fopen("student.txt", "r");
		if (fpp == NULL)
		{
			cout << "��ѧ����Ϣ�ļ�ʧ�ܣ�";
			exit(-1);
		}
		student a[100];
		int count = 0;
		while (fscanf(fpp, "%[^,]%s\n", a[count].student_id, a[count].password) != EOF)
		{
			count++;
		}
		int havechoose = 0;
		cout << "Ŀǰѡ����ſε�ѧ���У�";
		for (int i = 0; i < count; i++)
		{
			//������˳��һ�����򿪶�Ӧ�ĸ����ļ����Ƿ��ж�Ӧ�Ŀγ�id�оʹ�ӡѧ����idû�м�����
			char str1[30];
			strcpy(str1,a[i].student_id);
			const char* file = ".txt";
			strcat(str1, file);
			FILE* fpp = fopen(str1, "r");
			if (fpp == NULL)
			{
				cout << "ѧ�����˿α��ļ���ʧ��";
				exit(-1);
			}
			char m[4];//����˿α���Ŀγ�id
			char n[20];//���˿α������������
			
			while (fscanf(fpp, "%s\t%s\n", m, n) != EOF)
			{
				if (strcmp(m, theid) == 0)
				{
					havechoose++;
					cout << a[i].student_id <<',';//Ҫ�������ѧ����id
					break;
				}

			}
		}
		fclose(fpp);
		cout << "����" << havechoose << "��ͬѧ," << "�������λ���" << allhave - havechoose << "��ͬѧ��\n";
	}
	adminoperate();
}