#include"define.h"
void studentoperate(char id[20])
{
	cout << "*****************��������ѧ�����***************\n";
	cout << "================================================\n";
	cout << "                * 1.ע����¼         *\n"
		    "                * 2.�鿴�γ���Ϣ     *\n"
		    "                * 3.ѡ��             *\n"
		    "                * 4.�鿴���˿α�     *\n"
		    "                * 5.�˿�             *\n"
		    "                * 6.���ֱ�������     *\n"
		    "                * 7.ѡ���������     *\n"
		    "                * 8.��������         *\n"
		    "                * 9.����˭ѡ�ҵ����� *\n"
		    "                *10.��Ҫ��ѧ         *\n"
		    "                **********************\n";
	cout << "================================================\n";
	cout << "��������ѡ��Ĺ���:";
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
void lookallcourse2(char id[20])//�鿴ȫ���γ���Ϣ
{
	system("cls");
	FILE* fp = fopen("current_course.txt", "a+");
	if (fp == NULL)
	{
		cout << "��ȫ���γ���Ϣ�ļ�ʧ��!\n";
		exit(-1);
	}
	cout << "ȫ���γ���Ϣ����:\n";
	cout << "�γ�ID\t" << "�γ�����\t" << "            �ο���ʦ\t" << "                 �������� " << "��ѡ����\t" << "�γ�����\n";
	course a;//һ��һ�ж�¼��a��
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id
		, a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)
	{
		printf("%s\t%-30s%-30s%-10d%-10d%-10s\n", a.course_id
			, a.course_name, a.teacher_name, a.total, a.current, a.kind);
	}
	fclose(fp);
	studentoperate(id);
}
void choosemy(char id[20])//��Ҫ��current_course�ļ�ҲҪ��ѧ�����˿α��ļ�
{
	cout << "��������Ҫѡ��Ŀγ�id(ע���ǿγ�idŶ)��";
	char chooseid[4];
	M:gets_s(chooseid);
	if (ifinmycourse(id, chooseid) == true)
	{
		cout << "���Ѿ�ѡ�����ſ��ˣ�����������Ŷ��";
		goto M;
	}
	FILE* fp = fopen("current_course.txt", "r");//Ҫ��ȡ�ж��Ƿ��Ѵ����޲�������Ӧ�޸�
	if (fp == NULL)
	{
		cout << "�򿪿γ���Ϣ�ļ�ʧ��!";
		exit(-1);
	}
	FILE* fin = fopen("tem.txt", "w");//���ǽ�����ʱ�ļ�д�����
	if (fin == NULL)
	{
		cout << "����ʱ�ļ�ʧ�ܣ�\n";
		exit(-1);
	}
	course a;
	bool flag = 1;//�жϿγ��Ƿ��Ѿ�����1��ʾ�Ѿ�����
	bool flag1 = 0;//�жϿγ��ļ����Ƿ������ſ�0��ʾû��
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
		,a.course_name, a.teacher_name, &a.total, &a.current, a.kind) != EOF)//����ԭ�γ��ļ�����ʱ�ļ���д
	{
		if (strcmp(chooseid, a.course_id) == 0)//�ڿγ��ļ����ҵ������������ʱ�ļ���д�Ķ��������
		{
			flag1 = 1;
			if (a.current == a.total)//�γ������Ѵ����޲��ø�дԭ����
			{
				flag = 1;//���flag��ʾ���ſ��Ѿ�����
				fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
					, a.course_name, a.teacher_name, a.total, a.current, a.kind);
			}
			if (a.current < a.total)//����ѡ��Ҫ�ı��ļ���ѡ������
			{
				flag = 0;//��ʾû����
				fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
					, a.course_name, a.teacher_name, a.total, a.current + 1, a.kind);//����ѡ������һ
			}
				
		}
		else//������ſβ���Ҫ�Ķ���ֱ������ʱ�ļ���д
		{
			fprintf(fin, "%s\t%s\t%s\t%d\t%d\t%s\n", a.course_id
				, a.course_name, a.teacher_name, a.total, a.current, a.kind);
		}
	}
	fclose(fp);//�γ��ļ��޸����
	fclose(fin);
	remove("current_course.txt");
	rename("tem.txt", "current_course.txt");
	if (flag1 == 0)
	{
		cout << "��Ǹû�����ſε�idŶ��\n";
		cout << "�Ƿ��������룿1.�� 2.����ѧ�����ܽ��棺";
		int m;
		cin >> m;
		getchar();//���ջس�
		if (m == 1)choosemy(id);
		else if (m == 2)studentoperate(id);
	}
	//�޸�ѧ���ĸ��˿α��ļ�(�γ�\t����)
	//
	char str1[30];
	strcpy(str1, id);
	const char* file = ".txt";
	strcat(str1, file);
	FILE* fpp = fopen(str1, "r+");
	if (fpp == NULL)
	{
		cout << "ѧ�����˿α��ļ���ʧ��++--";
		exit(-1);
	}
	//ע��ѧ���α��ļ�ʼ�հ��տγ�id��������
	mycourse *newchoose=new mycourse;
	strcpy(newchoose->mycourseid, chooseid);//����ѡ��Ŀγ̴浽mycourse��������
	strcpy(newchoose->theassistant, "null");
	newchoose->next = NULL;
	int newidcount = 100 * (newchoose->mycourseid[0] - '0') + 10 * (newchoose->mycourseid[1] - '0') 
		+ (newchoose->mycourseid[2]-'0');
	if (flag == 0 && flag1==1)//�������ѡ���ſξ���Ҫ�Ķ����˿α��ļ�
	{
		int num = 0, eachidcount=0;
		mycourse* head = NULL;//�������˿γ����������
		mycourse* tail = NULL;//������β�巨��
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
		if (num == 0)//������˿α��ļ����Ǹ����ļ�
		{
			//ֱ��д�����˿α��ļ���
			fprintf(fpp, "%s\t%s\n", newchoose->mycourseid, newchoose->theassistant);
			fclose(fpp);
			cout << "ѡ�γɹ��ˣ�\n";
			studentoperate(id);
		}
		if (num == 10)
		{
			cout << "����ѡ��Ŀγ��Ѿ��ﵽ10�����޲���ѡ��!";
			studentoperate(id);//����ѧ����������
		}
		else//����Ѿ��������γ�����Ƚ�
		{
			mycourse* pre = head;
			mycourse* tem = head;
			while (tem)//����ѡ�Ŀγ̲��뵽������
			{
				eachidcount = 100 * (tem->mycourseid[0] - '0') + 10 * (tem->mycourseid[1] - '0')
					+ (tem->mycourseid[2] - '0');
				if (newidcount < eachidcount)//�ҵ���ѡ�Ŀγ�idС���б��еĿγ�id
				{
					if (pre == tem)//�嵽ͷ��
					{
						newchoose->next = tem;
						head = newchoose;
					}
					else//�嵽�м�
					{
						newchoose->next = pre->next;
						pre->next = newchoose;
					}
					break;//����˾�����ѭ�����ļ���д
				}
				pre = tem;
				tem = tem->next;
			}
			if (tem == NULL)//һֱ�����û�ҵ�˵��Ҫ�嵽�������
			{
				pre->next = newchoose;
			}
		fseek(fpp, 0, 0);//�ļ�ָ���Ƶ���ͷ���¸��ǵ�
		while(head)
		{
			fprintf(fpp, "%s\t%s\n", head->mycourseid, head->theassistant);
			head = head->next;
		}
		fclose(fpp);
		cout << "ѡ��γ̳ɹ�!\n";
		studentoperate(id);
		}
	}
}

void tobe_assistant(char id[20])//���ֱ������̲��޸�assistant�ļ�
{
	FILE* f = fopen("assistant.txt", "r+");//�������ļ��������id�Ƿ������2��********************ע�������ļ���һ������!
	if (f == NULL)
	{
		cout << "�������ļ�ʧ��!\n";
		exit(-1);
	}
	int count = 0;
	char gap='0';
	char temid[4];
	char myid[20];//���������������ļ������ö��Ÿ�����
	while (fscanf(f, "%s\t",temid) != EOF)//������������ȡÿһ�п�ͷ�Ŀγ�id
	{
		gap = '0';
		//���꿪ͷ�Ŀγ�id�������ľ�������������
		while (gap!='\n'&&fscanf(f, "%[^,\n]", myid) != EOF)//�����س���ʾ��һ�н�������Ҫ��������һ��
		{
			gap=fgetc(f);//��һ�����ţ����Ż��߻س�
			if (strcmp(myid, id) == 0)//����ҵ����ҵ�id������һ
				count++;
		}
	}
	if (count == 2)
	{
		fclose(f);
		cout << "�����������̸����Ѵ����ޣ��޷�����!\n";
		studentoperate(id);//����ѧ�����ܽ���
	}
	
	cout << "��������Ҫ�������̵Ŀγ����ƻ��߿γ�id:";
	char str[30];
	gets_s(str);
	char trueid[4];
	if (strlen(str) > 3)//������ȹ����͵�֪������
		toknowid(str, trueid);//�õ����ƶ�Ӧ��id
	
	if( ifinmycourse(id,str) )//����д������ļ������Լ�������
		{
		//�ж�һ���Լ��Ƿ��Ѿ��������ſε�������
		fseek(f, 0, 0);
		char a[4];
		char b[20];
		char c='\0';
		while (fscanf(f, "%s\t", a) != EOF)//�ȶ�ѧ��
		{
			if (strcmp(a, str) == 0 || strlen(str) > 3 && strcmp(a, trueid) == 0)//�ҵ����ſ�
				while (c != '\n' && fscanf(f, "%[^,\n]", b) != EOF)
				{
					c = fgetc(f);
					if (strcmp(b, id) == 0)//���ſε����������ҵ�������
					{
						fclose(f);
						cout << "���Ѿ������ſε�������Ŷ������ѡ������Ĳ���(1.��Ҫ����������� 2.����ѧ�����ܽ���)��";
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
				fscanf(f, "%s\n", alllist);//����������ſξͶ�һ����
			}
		}	
		fseek(f, 0, 0);//�������ļ�ָ���Ƶ���ͷ
		FILE* fin = fopen("temass.txt", "w");
		if (fin == NULL)
		{
			cout << "����ʱ�����ļ�ʧ�ܣ�";
			exit(-1);
		}
		int flag = 0;//�ж������ļ����Ƿ��������0��ʾû��
		char assid[4];//�����ļ���γ�id
		char allass[2000];//����γ�id�����е�����һ����������
		while (fscanf(f, "%s\t%s\n", assid,allass) != EOF)//�������ļ�����û�����id�еĻ��������û�еĻ��½�һ��
		{
			
			if (strcmp(assid, str) == 0||strlen(str)>3&&strcmp(assid,trueid)==0)//�����ļ��������ſ�,ע�������ļ����ҵ��ǿγ�id�����ǿγ�����
			{
				flag = 1;
				fprintf(fin, "%s\t%s,%s\n",assid, allass, id);//����һ��ȫд����ʱ�ļ����������Լ�������
			}
			else//����������ſ�Ҫ�����־�ֱ������ʱ�ļ���д
			{
				fprintf(fin, "%s\t%s\n", assid, allass);
			}
		}
		if (flag == 0)//��������ļ�ԭ�Ⱦ�û���˱��������
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
		cout << "�����γ����̳ɹ��ˣ�\n";
		studentoperate(id);
	}
	
	else //����β������ҵĸ��˿α���
	{
		fclose(f);
		cout << "����û��ѡ���ſ�!\n";
		cout << "�Ƿ����ѡ�ν���?(1. ��  2.�񣬷���ѧ�����ܽ���)\n";
		int a;
		cin >> a;
		getchar();//���ջس�
		if (a == 1) choosemy(id);
		else if (a == 2)
			studentoperate(id);
	}
}	
void lookmy(char id[20])//�鿴���˿α�
{
	char str1[25];
	strcpy(str1, id);
	const char* file = ".txt";//�򿪸��˿α��ļ�
	strcat(str1, file);
	FILE* fp = fopen(str1, "r");
	if (fp == NULL)
	{
		cout << "ѧ�����˿α��ļ���ʧ��";
		exit(-1);
	}
	mycourse* head = NULL;//�������˿γ����������
	mycourse* tail = NULL;//������β�巨��
	char tem1[4];
	char tem2[20];
	while (fscanf(fp, "%s\t%s\n",tem1,tem2) != EOF)//�Ѹ��˿α���Ŀγ�id������
		                                                            //�ȶ������������ڿγ��ļ���������
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
		cout << "�򿪿γ��ļ�ʧ��!\n";
		exit(-1);
	}
	mycourse* head1 = head;
	while (head1)
	{
		//fseek(fpp, 0, 0);//*******************************?�Ƿ��б�Ҫ��Ϊ���ǰ���˳�����е�
		int tem1, tem2;
		course a;
		while (fscanf(fpp, "%s\t%s\t%s\t%d\t%d\t%s", a.course_id, a.course_name, a.teacher_name,
			&a.total, &a.current, a.kind) != EOF)//�ѿγ��ļ����һ�ж���a�����ж�
		{
			if (strcmp(a.course_id, head1->mycourseid) == 0)
			{
				strcpy(head1->mycoursename, a.course_name);//�ҵ�ƥ���id�Ͱѿγ��ļ������Ϣ��Ӧд���ڵ���
				strcpy(head1->myteacher, a.teacher_name);
				strcpy(head1->mykind, a.kind);
				break;//д���˾�����ѭ��
			}
		}
		head1 = head1->next;
	}
	fclose(fpp);
	cout << "��Ŀǰ��ѡ�Ŀγ���:\n";
	cout << "******************************************\n";
	cout << "�γ�id\t�γ�����\t�ڿν�ʦ\t�γ�����\t��������\n";
	int count1 = 0, count2 = 0;
	while (head)
	{
		cout << head->mycourseid << '\t' << head->mycoursename << '\t' << head->myteacher << '\t' 
			<< head->mykind << '\t'<< head->theassistant << '\n';
		if (strcmp(head->mykind, "רҵ��") == 0) count1++;
		else if (strcmp(head->mykind, "��רҵ��") == 0) count2++;
		head = head->next;
	}
	cout << "*******************************************\n";
	if (count1 < MAJ || count2 < UMA)
		cout << "����ѧԺҪ��:Ŀǰ��ѡ�Ŀγ��������!�Բ�" << MAJ - count1 << "��רҵ�Σ�"
		<< "�Լ�" << UMA - count2 << "�ŷ�רҵ��!�뼰ʱѡ��!\n";
	else cout << "��Ŀǰ��ѡ�Ŀγ����Ѵ��!\n";
	studentoperate(id);
}
void choose_assistant(char id[20])//Ϊ�Լ�ĳ�ſ�ѡ������,Ҫ�ı���˿α��ļ�
{
	//�����Լ��α�����û������κ�֮ǰ������������֮�����ɸ���ճ��
	cout << "��������Ҫѡ�����̵Ŀγ����ƻ��߿γ�id:";
	char str[30];
	gets_s(str);
	char trueid[4];
	if (strlen(str) > 3)//������ȹ����͵�֪������
		toknowid(str, trueid);//�õ����ƶ�Ӧ��id
	if (ifinmycourse(id, str))//����ҵĿα��������ſ�
	{
		//��������ļ���ӡ��������
		
			FILE* f = fopen("assistant.txt", "r");
			if (f == NULL)
			{
				cout << "�����̽��ļ�ʧ��!\n";
				exit(-1);
			}
			//��ӡ�����ſε�ǰ����������
			//���ܻ�û���˱�����Ҳ�������˱�����
			bool have = 0;
			char assid[4], ass[20];//�����ļ���γ�id�Ͷ�Ӧ�����ĵ�����
			while (fscanf( f, "%s\t", assid) != EOF)//�������ļ�����û�����id�еĻ���ӡ����û�еĻ���ʾû��
			{
				if (strcmp(assid, str) == 0||strlen(str)>3&&strcmp(assid,trueid)==0)//�����ļ��������ſ�,ע�������ļ����ҵ��ǿγ�id�����ǿγ�����
				{
					have = 1;//have��ֵ��1��ʾ���˱�������ε�����
					char theall[2000];
					cout << "��ǰ�������ſ����̵�ͬѧ��:";
					fscanf(f, "%s\n", theall);//��ӡһ�󴮼���
					cout << theall;
					fclose(f);//��ӡ���������ļ�ָ��Ϳ��Թ���
					cout << "\n���������������У�ѡ����ĸ�������:";
					//
					//
					//��Ҫ�Ķ����˿α��ļ�
					char ichooseass[20];
					gets_s(ichooseass);
					char  str1[25];
					strcpy(str1, id);
					const char* file = ".txt";//�򿪸��˿α��ļ�
					strcat(str1, file);
					FILE* fp = fopen(str1, "r+");
					if (fp == NULL)
					{
						cout << "ѧ�����˿α��ļ���ʧ��";
						exit(-1);
					}
					mycourse my;
					while (fscanf(fp, "%s\t%s", my.mycourseid, my.theassistant) != EOF)
					{
						//�ڸ��˿α���������γ̣�ע��ƥ����ǿγ�id
						if (strcmp(my.mycourseid, str) == 0 || strlen(str) != 3 && strcmp(my.mycourseid, trueid) == 0)
						{
							if (strcmp(my.theassistant, "null") != 0)
							{
								cout << "���ſ����Ѿ�ѡ��������!\n�Ƿ���ѡһ��(1.�� 2.�񣬷���ѧ�����ܽ���)";
								int cho;
								cin >> cho;
								getchar();
								fclose(fp);
								if (cho == 1 && strlen(str) == 3) changemyassistant(id, str, ichooseass);//����д����������ѡ������̵������滻ԭ����null���߾�����               ; 
								else if (cho == 1 && strlen(str) != 3) changemyassistant(id, trueid, ichooseass);
								
							}
							else//��ʾ���ſ����̴�����null����ԸĶ�
							{
								//���������ᵽ���Ǹ�����
								fclose(fp);
								if (strlen(str) == 3) changemyassistant(id, str, ichooseass);//����д����������ѡ������̵������滻ԭ����null���߾�����               ; 
								else if (strlen(str) != 3) changemyassistant(id, trueid, ichooseass);
								
							}
							cout << "�����ɹ�\n";
							studentoperate(id);
						}
					}
					fclose(fp);
				}
				else //�����ʱ���������ſε�id��
				{
					char alllist[2000];
					fscanf(f, "%s\n", alllist);
				}
			}
			fclose(f);
		if (have == 0)
		{
			cout << "��Ǹ���ſλ�û���˱�������!\n�Ƿ�������(1.�� 2.�񣬷���ѧ�����ܽ���)";
			int num;
			cin >> num;
			getchar();
			if (num == 1) tobe_assistant(id);
			else if (num == 2) studentoperate(id);
		}
	}
	else 
	{
		cout << "����û��ѡ���ſ�!\n";
		cout << "�Ƿ����ѡ�ν���?(1. ��  2.�񣬷���ѧ�����ܽ���)\n";
		int a;
		cin >> a;
		getchar();
		if (a == 1) choosemy(id);
		else if (a == 2)
			studentoperate(id);
	}
}
void deletemy(char id[20])//ѧ���˿Σ�Ҫ�Ķ����˿α��ļ����Ķ��γ��ļ����ѡ������
{
	cout << "������γ����ƻ��߿γ�id��";
	char str[30];
	gets_s(str);
	if (ifinmycourse(id, str) == false)
	{
		cout << "��Ǹ��û��ѡ���ſΣ�";
		studentoperate(id);
	}
	char trueid[4];
	if (strlen(str) > 3)
		toknowid(str, trueid);
	else if (strlen(str) == 3)
		strcpy(trueid, str);
	char  str1[25];
	strcpy(str1, id);
	const char* file = ".txt";//�򿪸��˿α��ļ�
	strcat(str1, file);
	FILE* f = fopen(str1, "r");//�޸Ŀα�����ʱ�ļ�
	if (f == NULL)
	{
		cout << "��ѧ�����˿α��ļ�ʧ�ܣ�";
		exit(-1);
	}
	FILE* fin = fopen("tem.txt", "w");
	if (fin == NULL)
	{
		cout << "����ʱ�ļ�ʧ�ܣ�";
		exit(-1);
	}
	char a[4];//��Ϊɾ��ʱ���ÿ����������������ֱ������������洢
	char b[20];
	while (fscanf(f, "%s\t%s\n", a, b) != EOF)
	{
		if (strcmp(a, trueid) != 0)//�������ſξ�д
		{
			fprintf(fin, "%s\t%s\n", a, b);

		}
	}
	fclose(f);
	fclose(fin);
	remove(str1);
	rename("tem.txt", str1);//д����ɾ����������
	FILE* fp = fopen("current_course.txt", "r");//ͬ���޸Ŀγ���Ϣ�ļ�Ҳ�ǽ�����ʱ�ļ�
	if (fp == NULL)
	{
		cout << "�򿪿γ���Ϣ�ļ�ʧ�ܣ�";
		exit(-1);
	}
	FILE* fn = fopen("tem2.txt", "w");
	if (fn == NULL)
	{
		cout << "����ʱ�ļ�ʧ�ܣ�";
		exit(-1);
	}
	course c;
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id, c.course_name, c.teacher_name,
		&c.total, &c.current, c.kind) != EOF)
	{
		if (strcmp(c.course_id, trueid) == 0)//���id���˽����ſε���ѡ������һ
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
		cout << "�������ļ�ʧ�ܣ�";
		exit(-1);
	}
	FILE* fi = fopen("tem3.txt", "w");
	if (fi == NULL)
	{
		cout << "����ʱ�ļ�ʧ�ܣ�";
		exit(-1);
	}
	int flag = 0;
	char m[4];//�������ļ���Ŀγ�id
	char n[2000];//�������ļ�����������д�����
	while (fscanf(fpp, "%s\t", m) != EOF)
	{
		flag = 0;
		int h = 0;
		char tem = '\0';
		while (tem != '\n')
		{
			h++;//��¼�ļ�ָ��������˶��ٸ��ַ�
			tem = fgetc(fpp);
			if (tem == ',')
			{
				flag = 1;//��ʾ�����ж��ţ��������ɾ������������Ϊ�յ����
				break;
			}
		}
		if (flag == 1)
		{
			fseek(fpp, -h, 1);//���ļ�ָ���Ƶ�ԭλ
			fprintf(fi, "%s\t", m);
			if (strcmp(m, trueid) == 0)//����������ļ����ҵ���Ҫ�˵�id�ҵ��Լ���ɾ��
			{
				int n = 0;
				char p[20];//��ÿһ����������
				char q = '0';
				while (q != '\n' && fscanf(fpp, "%[^,\n]", p) != EOF)
				{
					if (strcmp(p, id) != 0&&(q=='0'||q==','))//�����Լ������ֲ�������ǰ������м�
					{
						if(q=='0')//����ǰ��
						fprintf(fi, "%s", p);
						else if (q == ',')//���м�
						{
							if (n == 0)//���ǰ�治��Ҫɾ��������
							{
								fputc(q, fi);//Ҫ�Ѷ���д��
								fprintf(fi, "%s", p);
							}
							
							else if(n==1)//���ǰ����Ҫɾ��������
							{
								fprintf(fi, "%s", p);//��д����
								n = 0;//��n����
							}
						}
					}
					/*if (strcmp(p, id) == 0 && q == ',')
					{
						fputc('\n', fi);//Ӧ����ʲôҲ���ø�
					}*/
					if (strcmp(p, id) == 0 && q == '0')//����Լ������ֳ�������ǰ����
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
		else if (flag == 0)//�����һ������
		{
			fseek(fpp, -(h + 1), 1);
			if (strcmp(m, trueid) == 0)//����˵ľ������ſο���������û���ҵ�����
			{
				char p[20];//��ÿһ����������
				char q = '0';
				while (q != '\n' && fscanf(fpp, "%[^,\n]", p) != EOF)
				{
					q = fgetc(fpp);
					if (strcmp(p, id) != 0)//�����Լ�������Ҫ�ѿγ�idҲд�� ���Լ������־�ɶҲ��д����Ϊ�����һ���Լ�
					{
						fprintf(fi, "%s\t%s",trueid, p);
						fputc(q, fi);
					}
				}
			}
			else//����˵Ĳ������ſ�
			{
				fprintf(fi, "%s\t", m);//�Ȱѿγ�id����
				char r[2000];
				fscanf(fpp, "%s\n", r);//�ٰѺ��������ȫд�ϾͿ���
				fprintf(fi, "%s\n", r);
			}
		}
	}
	fclose(fpp);
	fclose(fi);
	remove("assistant.txt");
	rename("tem3.txt", "assistant.txt");
	cout << "�˿γɹ���\n";
	lookmy(id);
	studentoperate(id);
}
void lookwhochoose(char id[20])//����˭ѡ�ҵ�����
{
	FILE* f = fopen("student.txt", "a+");
	if (f == NULL)
	{
		cout << "��ѧ���ļ�ʧ��";
		exit(-1);
	}
	student a[100];
	char stuid[20];//ѧ����Ϣ�����ѧ��id
	char pass[20];//ѧ������
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
		const char* file = ".txt";//�򿪸��˿α��ļ�
		strcat(str1, file);
		FILE* fp = fopen(str1, "r");
		if (fp == NULL)
		{
			cout << "ѧ�����˿α��ļ���ʧ��";
			exit(-1);
		}
		char m[4];//�γ�id
		char n[20];//����id
		while (fscanf(fp, "%s\t%s\n", m, n) != EOF)
		{
			if (strcmp(n, id) == 0)//���ѧ��������id��������һ��
			{
				flag = 1;
				cout << "ѧ��idΪ" << a[j].student_id << "��ͬѧѡ��Ϊ�γ�idΪ" <<m<<"������\n" ;
			}
		}
		fclose(fp);
	}
	if (flag == 0)
		cout << "��Ǹ��û��ѡ�㵱���̣�\n";
	studentoperate(id);
}
void giveup(char id[20])
{
	cout << "��ȷ��Ҫ��ѧ�������룺(1. �ֻ��� 2.��ѧ��)��";
	int num;
	cin >> num;
	if (num == 1)
		studentoperate(id);
	else if (num == 2)
	{
		char str1[25];
		strcpy(str1,id);
		const char* file = ".txt";//�ȰѸ��˿α����ÿ�ſζ��˵���ɾ������ļ�����
		strcat(str1, file);
		FILE* f2 = fopen(str1, "r");
		if (f2 == NULL)
		{
			cout << "�򿪸��˿α�ʧ�ܣ�";
			exit(-1);
		}
		char ke[4], zhujiao[20];
		while (fscanf(f2, "%s\t%s", ke, zhujiao) != EOF)
		{
			FILE* fp = fopen("current_course.txt", "r");//ͬ���޸Ŀγ���Ϣ�ļ�Ҳ�ǽ�����ʱ�ļ�
			if (fp == NULL)
			{
				cout << "�򿪿γ���Ϣ�ļ�ʧ�ܣ�";
				exit(-1);
			}
			FILE* fn = fopen("tem2.txt", "w");
			if (fn == NULL)
			{
				cout << "����ʱ�ļ�ʧ�ܣ�";
				exit(-1);
			}
			course c;
			while (fscanf(fp, "%s\t%s\t%s\t%d\t%d\t%s\n", c.course_id, c.course_name, c.teacher_name,
				&c.total, &c.current, c.kind) != EOF)
			{
				if (strcmp(c.course_id, ke) == 0)//���id���˽����ſε���ѡ������һ
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
				cout << "�������ļ�ʧ�ܣ�";
				exit(-1);
			}
			FILE* fi = fopen("tem3.txt", "w");
			if (fi == NULL)
			{
				cout << "����ʱ�ļ�ʧ�ܣ�";
				exit(-1);
			}
			int flag = 0;
			char m[4];//�������ļ���Ŀγ�id
			char n[2000];//�������ļ�����������д�����
			while (fscanf(fpp, "%s\t", m) != EOF)
			{
				flag = 0;
				int h = 0;
				char tem = '\0';
				while (tem != '\n')
				{
					h++;//��¼�ļ�ָ��������˶��ٸ��ַ�
					tem = fgetc(fpp);
					if (tem == ',')
					{
						flag = 1;//��ʾ�����ж��ţ��������ɾ������������Ϊ�յ����
						break;
					}
				}
				if (flag == 1)
				{
					fseek(fpp, -h, 1);//���ļ�ָ���Ƶ�ԭλ
					fprintf(fi, "%s\t", m);
					if (strcmp(m, ke) == 0)//����������ļ����ҵ���Ҫ�˵�id�ҵ��Լ���ɾ��
					{
						int n = 0;
						char p[20];//��ÿһ����������
						char q = '0';
						while (q != '\n' && fscanf(fpp, "%[^,\n]", p) != EOF)
						{
							if (strcmp(p, id) != 0 && (q == '0' || q == ','))//�����Լ������ֲ�������ǰ������м�
							{
								if (q == '0')//����ǰ��
									fprintf(fi, "%s", p);
								else if (q == ',')//���м�
								{
									if (n == 0)//���ǰ�治��Ҫɾ��������
									{
										fputc(q, fi);//Ҫ�Ѷ���д��
										fprintf(fi, "%s", p);
									}

									else if (n == 1)//���ǰ����Ҫɾ��������
									{
										fprintf(fi, "%s", p);//��д����
										n = 0;//��n����
									}
								}
							}
							/*if (strcmp(p, id) == 0 && q == ',')
							{
								fputc('\n', fi);//Ӧ����ʲôҲ���ø�
							}*/
							if (strcmp(p, id) == 0 && q == '0')//����Լ������ֳ�������ǰ����
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
				else if (flag == 0)//�����һ������
				{
					fseek(fpp, -(h + 1), 1);
					if (strcmp(m, ke) == 0)//����˵ľ������ſο���������û���ҵ�����
					{
						char p[20];//��ÿһ����������
						char q = '0';
						while (q != '\n' && fscanf(fpp, "%[^,\n]", p) != EOF)
						{
							q = fgetc(fpp);
							if (strcmp(p, id) != 0)//�����Լ�������Ҫ�ѿγ�idҲд�� ���Լ������־�ɶҲ��д����Ϊ�����һ���Լ�
							{
								fprintf(fi, "%s\t%s", ke, p);
								fputc(q, fi);
							}
						}
					}
					else//����˵Ĳ������ſ�
					{
						fprintf(fi, "%s\t", m);//�Ȱѿγ�id����
						char r[2000];
						fscanf(fpp, "%s\n", r);//�ٰѺ��������ȫд�ϾͿ���
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
		remove(str1);//ɾ�����˿α��ļ�
		FILE* f = fopen("student.txt", "r");
		if (f == NULL)
		{
			cout << "��ѧ����Ϣ�ļ�ʧ��!\n";
			exit(-1);
		}
		char m[20];//ѧ��id
		char n[20];//ѧ������
		FILE* fin = fopen("ttem.txt", "w");
		if (fin == NULL)
		{
			cout << "����ʱ�ļ�ʧ�ܣ�";
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

		cout << " ��ѧ�ɹ���ף��������죡\n";
	}
	tobegin();// ����ԭʼ����
}