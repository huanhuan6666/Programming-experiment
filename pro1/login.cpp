#include"define.h"
void tobegin()//��ԭʼ�Ĳ�������
{
	cout<<"**********************��ӭ����ѡ��ϵͳ!************************\n";
	cout<<"--------------------��ѡ������Ҫ�Ĳ���----------------------\n";
	cout<<"======================================================\n";
	cout << "                  *  0.�˳�����   *\n"
		    "                  *  1.ѧ����¼   *\n"
	   	    "                  *  2.ѧ��ע��   *\n"
		    "                  *  3.����Ա��¼ *\n"
		    "                  *****************\n";
	cout<<"======================================================\n";
	int num;
	cin >> num;
	getchar();
	switch (num)
	{
	case 0:
	{
		cout << "��л����ʹ�ã��ټ���";
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
	cout << "���������Աid��";
	char inputid[10],inputpass[10];
	gets_s(inputid);
	if (strcmp(inputid, "Admin") == 0)
	{
		int i = 0;
		B:cout << "���������Ա���룺";
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
			printf("���Թ���Ա��ݳɹ���¼!\n");
			system("cls");
			adminoperate();
			return;
		}
		else printf("�������!\n");
		goto B;
	}
	else printf("����Աid����!\n");
	adminlog();
}
//
//Ϊʲ��ע������֮��ע���û��ٵ�¼һֱ��ʾ����û��ע���������ѧ���ļ���ȷʵ�������ݰ�
//Ӧ����ѧ����¼�����������⣬�о��͸���û�ж�ѧ���ļ������������
void studentcreate()//ע��ע���ʱ����Ҫ��½�ɹ�
{
	student* newboy = new student;
	cout << "����������ѧ��id(��Сд��ĸ�����ֹ���,��Ҫ����20λ):";
	A:gets_s(newboy->student_id);
	if(ifinthestudent(newboy->student_id) == true)//������id����ע���
	{
		cout << "��Ǹ���id�Ѿ�����ע����ˣ������ٴ�����һ����";
		goto A;
	}
	for (int i = 0; i < strlen(newboy->student_id); i++)//�ж�һ������id�ĺϷ���
	{
		char a = newboy->student_id[i];
		if (!(islower(a) || (a >= '0' && a <= '9')))
		{
			i = -1;
			cout << "��⵽�������id���Ϸ���ע��ֻ�ܰ���Сд��ĸ������Ŷ\n�����ٴ����룺";
			goto A;
		}
	}
	cout << "��������������(��Сд��ĸ�����ֹ���,��Ҫ����20λ)��";
	gets_s(newboy->password);
	for (int i = 0; i < strlen(newboy->password); i++)//�ж�һ����������ĺϷ���
	{
		char a = newboy->password[i];
		if (!(islower(a) || (a >= '0' && a <= '9')))
		{
			i = -1;
			cout << "��⵽����������벻�Ϸ���ע��ֻ�ܰ���Сд��ĸ������Ŷ\n�����ٴ����룺";
			gets_s(newboy->password);
		}
	}
	FILE* fp = fopen("student.txt", "a+");//ע��ѧ��Ҫ�Ѹ�ѧ��¼��ѧ���ļ���
	if (fp == NULL)
	{
		printf("��ѧ���ļ�����!\n");
		exit(-1);
	}
	fprintf(fp, "%s,%s\n", newboy->student_id, newboy->password);
	fclose(fp);
	const char *file = ".txt";//����Ҫ��Ӧ�Ĵ������ѧ���Ŀα��ļ�
	char tem[20];
	strcpy(tem, newboy->student_id);
	strcat(tem, file);
	FILE* fpp = fopen(tem, "w");//������ѧ��id��Ϊ�ļ�����ѧ���α��ļ�
	fclose(fpp);
	cout << "ѧ����Ϣע��ɹ�!�����Լ������в���\n";
	fclose(fp);
	studentoperate(newboy->student_id);
}
void studentlog()
{

	char id[20];
	char password[20];
	cout << "����������id:";
	gets_s(id);//����ѧ����id
	FILE* fp = fopen("student.txt", "a+");
	if (fp == NULL)
	{
		cout << "ѧ����Ϣ�ļ���ʧ��!\n";
		exit(-1);
	}
	student a;
	//�ȿ�����û�����id��
	bool exist=0;
	while (fscanf(fp, "%[^,],%s\n", a.student_id, a.password)!=EOF) //��Ϊ���ö��ŷָ��ģ���������ʽ��ϴ����
	{
		if (strcmp(id, a.student_id) == 0)//�еĻ����
		{
			exist = 1;
			break;
		}
		else continue;
	}
	if (exist==0)//���û�����id��
	{
		cout << "��Ǹ���id��û�б�ע��,��ѡ���������Ĳ���:(1.��Ҫע��  2.���ص�¼������������)\n";
		int a;
		cin >> a;
		getchar();//ͬ��������ϴ�س�
		if (a == 1)
		{ 
			fclose(fp);
			studentcreate();//����ע�ắ��
		}
		else if (a == 2)
		{
			fclose(fp);
			studentlog();
		}
	}
	else//������id���ڵĻ�����ʱa�д�����ݾ��Ѿ���Ŀ�������ˣ������ظ���������
	{
	cout << "��������������:";
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
				cout << "\n**************��½�ɹ�!**************\n";
				fclose(fp);
				ifassconnect(id);//**************************�����ҵ������Ƿ���
				studentoperate(id);//��½�ɹ������������
			}
			else//������Ĳ���
			{
				int count = 3;//���λ���
				while (strcmp(password, a.password) != 0&&count>1)//������һֱ��ƥ��ʱ
				{
					
					count--;
					cout << "������������д�������������!\n"<<"������"<<count<<"�λ���\n";
					cout << "��������������:\n";
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
				if (strcmp(password, a.password) == 0)//��������������ѭ��
				{
					cout << "\n**************��½�ɹ�!*************\n";
					fclose(fp);
					ifassconnect(id);//**************************�����ҵ������Ƿ���
					studentoperate(id);//��½�ɹ������������
				}
				else 
				{
					cout << "����3�λ����Ѿ�ʹ������!\n"<<"�����Կ�����������(1.�� 2.��)������:";
					int tem = 0;
					fclose(fp);
					cin >> tem;
					getchar();//��ϴ�س���Ϊ���������õĺ�����ͷ��ֱ����gets�����յ�
					if (tem == 1)//�ǵĻ��͵����������뺯�� 
					  change_password(id);
					else if (tem == 2)//�����þͷ��ؿ�ʼ����
					{
						system("cls");
						tobegin();
						return;
					}
				}
			}
		}
}
void change_password(char id[20])//�������빦��
{
	char newpass[20];
	char again[20];
	A:cout << "����������������:";
	gets_s(newpass);
	cout << "���ٴ���������������:";
	gets_s(again);
	if (strcmp(newpass, again) != 0)//�������벢��һ��
	{
		cout << "��������������벻һ��!\n�������ٴ���������\n";
		goto A;
	}
	else 
	{
		FILE* fp = fopen("student.txt", "r+");
		student a;
		while (fscanf(fp, "%[^,],%s\n", a.student_id, a.password))
		{
			if (strcmp(a.student_id, id)==0)//�ҵ���id
			{
				fseek(fp, -((int)strlen(a.password)+2), 1);//���ļ�ָ���Ƶ���һ�п�ͷ
				fprintf(fp, "%s\n",newpass);//��ԭ����id���µ����븲�ǵ���һ��
				fclose(fp);
				cout << "���������Ѿ�����!\n";
				studentoperate(id);//������ɺ�ֱ�ӽ����������
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