#pragma once
#include<iostream>
#include<cstring>
#include<conio.h>
#include<Windows.h>
const int MAJ = 4;
const int UMA = 2;
using namespace std;
struct course
{
	char course_id[4];//�γ�id 
	char course_name[30];//�γ�����
	char teacher_name[30];//�ον�ʦ
	int total;//��������
	int current;//��ѡ����
	char kind[10];//�γ�����
};
struct student
{
	char student_id[20];//ѧ��id
	char password[20];//ѧ������
};
struct mycourse//ѧ���α��ļ�������ݽṹ
{
	char mycourseid[4];//�γ�id
	char mycoursename[30];//�γ�����
	char myteacher[30];//�ον�ʦ
	char mykind[10];//�γ�����
	char theassistant[20];//��������
	mycourse* next;
};
//����ǳ����ܲ���
void logout();
void adminlog();
void studentlog();
void studentcreate();
void tobegin();
//
//����Ա���ܲ���
void adminoperate();
void inputcourse();
void lookallcourse1();
void addcourse();
void deletecourse();
void changecourse();
void lookone();
//
//ѧ�����ܲ���
void lookallcourse2(char id[20]);
void studentoperate(char id[20]);
void choosemy(char id[20]);//��Ҫ����ѧ����id 
void lookmy(char id[20]);
void deletemy(char id[20]);
void tobe_assistant(char id[20]);
void choose_assistant(char id[20]);
void change_password(char id[20]);//*****************�����޸����빦��
void lookwhochoose(char id[20]);//************��������˭ѡ�ҵ�����
void giveup(char id[20]);//**************������ѧ����
//
//ʵ�ù��߲���
//**************************void createfile();
bool ifinmycourse(char id[20],char str[30]);//***************Ҳ�������Ĺ��ܰɣ���Ҫ�����ѡ�����̺ͱ������̹��ܣ��ж������
                                   //�γ����ƻ���id�Ƿ�������ҵĸ��˿α���
void toknowid(char name[30],char tobe[4] );//************Ҳ����������ܰɣ�֪���γ�������ÿγ�id
void toknowname(char id[4] ,char tobe[30]);//************ͬ���棬֪���γ�id��ÿγ�����
void changemyassistant(char id[20], char mycourseid[30],char mychoose[20]);
bool ifinthestudent(char id[20]);//�������id�Ƿ������ѧ����Ϣ�ļ��У�����ѧ��ע��ʱ�ж�id�Ƿ������ù�
bool ifinallcourse(char coursename[30]);//��������γ������Ƿ�����ڿγ��ļ��У����ڹ���Ա��ӿγ�ʱ�жϿγ��Ƿ��Ѿ�����
bool ifassconnect(char id[20]);//��ѧ����½ʱ�������˿α���������Ƿ��Ӧ�������ļ�����Ȼ�������*�����ı�*�Ļ��͸ø��˿α�����������