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
	char course_id[4];//课程id 
	char course_name[30];//课程名称
	char teacher_name[30];//任课教师
	int total;//人数上限
	int current;//已选人数
	char kind[10];//课程类型
};
struct student
{
	char student_id[20];//学生id
	char password[20];//学生密码
};
struct mycourse//学生课表文件里的数据结构
{
	char mycourseid[4];//课程id
	char mycoursename[30];//课程名称
	char myteacher[30];//任课教师
	char mykind[10];//课程类型
	char theassistant[20];//助教姓名
	mycourse* next;
};
//登入登出功能部分
void logout();
void adminlog();
void studentlog();
void studentcreate();
void tobegin();
//
//管理员功能部分
void adminoperate();
void inputcourse();
void lookallcourse1();
void addcourse();
void deletecourse();
void changecourse();
void lookone();
//
//学生功能部分
void lookallcourse2(char id[20]);
void studentoperate(char id[20]);
void choosemy(char id[20]);//需要参数学生的id 
void lookmy(char id[20]);
void deletemy(char id[20]);
void tobe_assistant(char id[20]);
void choose_assistant(char id[20]);
void change_password(char id[20]);//*****************新增修改密码功能
void lookwhochoose(char id[20]);//************新增看看谁选我当助教
void giveup(char id[20]);//**************新增退学功能
//
//实用工具部分
//**************************void createfile();
bool ifinmycourse(char id[20],char str[30]);//***************也算新增的功能吧，主要是针对选择助教和报名助教功能，判断输入的
                                   //课程名称或者id是否存在于我的个人课表中
void toknowid(char name[30],char tobe[4] );//************也算个新增功能吧，知道课程名称求得课程id
void toknowname(char id[4] ,char tobe[30]);//************同上面，知道课程id求得课程名称
void changemyassistant(char id[20], char mycourseid[30],char mychoose[20]);
bool ifinthestudent(char id[20]);//看看这个id是否存在于学生信息文件中，用于学生注册时判断id是否有人用过
bool ifinallcourse(char coursename[30]);//看看这个课程名称是否存在于课程文件中，用于管理员添加课程时判断课程是否已经存在
bool ifassconnect(char id[20]);//当学生登陆时看看个人课表里的助教是否对应在助教文件里依然存在如果*发生改变*的话就该个人课表并标记输出提醒