#include"define.h"
void compare(char *file1,char *file2)//比较文件函数*无参数
{
	struct stat st1;
        stat(file1,&st1);
        if(S_ISDIR(st1.st_mode))
        {
                printf("cmp: %s: 是一个目录\n",file1);
                return ;
        }
	struct stat st2;
	stat(file2,&st2);
	if(S_ISDIR(st2.st_mode))
	{
		printf("cmp: %s: 是一个目录\n",file2);
		return ;
	}
	FILE*fp1=fopen(file1,"r");
	FILE*fp2=fopen(file2,"r");
	if(fp1==NULL)
	{
		printf("cmp: %s: 没有那个文件或目录\n",file1);
		return ;
	}
	if(fp2==NULL)
	{
		printf("cmp: %s: 没有那个文件或目录\n",file2);
		return ;
	}
	char ch1,ch2;
	int lines=1;
	int bytes=0;
	do
	{
		
		ch1=fgetc(fp1);
		ch2=fgetc(fp2);
		if(feof(fp1)&&ch2=='\n')
		{
			cout<<"cmp: "<<file1<<" 已结束\n";
			break;
		}
		if(feof(fp2)&&ch1=='\n')
		{
			cout<<"cmp: "<<file2<<" 已结束\n";
			break;
		}
		bytes++;//每读一个字节字节数就加一
		if(ch1=='\n'||ch2=='\n')
			lines++;//读到回车行数增加
		if(ch1!=ch2)
		{
			cout<<file1<<' '<<file2<<" 不同: "<<"第 "<<bytes<<" 字节，"<<"第 "<<lines<<" 行\n";
			break;
		}
		
	}while(1);
	//一模一样就什么也不输出
	fclose(fp1);
	fclose(fp2);
	return ;//这里return可以吗？
}
bool ifdir(char *path)
{
	struct stat st;
	stat(path,&st);
	if(S_ISDIR(st.st_mode))
		return 1;
	else 
		return 0;
}
bool whatend(char *str,char c)
{
	if(str[strlen(str)-1]==c)
		return 1;
	else 
		return 0;
}
bool iffile(char *path)
{
	struct stat st;
	stat(path,&st);
	if(S_ISREG(st.st_mode))
		return 1;
	else 
		return 0;
}
void copydir(char *dir1,char *dir2)
{
	if(iffile(dir1)&&!opendir(dir2))//如果源是个文件且目标还不是个目录
		{
			copyfile(dir1,dir2);//就当文件的复制
			return ;
		}
	else if(iffile(dir1)&&opendir(dir2))//如果源是个文件且目标是个目录
	{
		char* the=new char[1024];
		memset(the,0,sizeof(the));
		if(whatend(dir2,'/'))
		{	
			the=strcat(the,dir2);
			the=strcat(the,dir1);	
		}
		else
		{
			the=strcat(the,dir2);
			the=strcat(the,"/");
			the=strcat(the,dir1);
		}
		copyfile(dir1,the);
		return ;
	}
	else if(ifdir(dir1)&&iffile(dir2))//如果源是个目录而目标是个文件
	{
		printf("cp: 无法以目录'%s' 来覆盖非目录'%s'\n",dir1,dir2);
		return ;
	}
	DIR *dp=opendir(dir1);
        if(dp==NULL)
        {
                printf("cp: 无法获取'%s' 的文件状态(stat): 没有那个文件或目录\n",dir1);
                return ;
        }
	if(!opendir(dir2))//如果目标目录不存在就先创建
        {
                if(mkdir(dir2,0777))//创建成功返回0失败返回-1
                {
                cout<<"创建目标目录失败\n";
                }
	struct dirent* filename;
	while(filename=readdir(dp))//一个个读源目录里的文件错误或读完返回NULL
	{
		char* path1=new char[1024];
      		char* path2=new char[1024];
		memset(path1,0,sizeof(path1));
		memset(path2,0,sizeof(path2));
		if(whatend(dir1,'/'))//源目录路径结尾是/ 直接连接即可
			path1=strcat(path1,dir1);
		else//结尾不是/则需要添加
		{
			path1=strcat(path1,dir1);
			path1=strcat(path1,"/");
		}
		if(whatend(dir2,'/'))//目标目录路径结尾是/直接连接
			path2=strcat(path2,dir2);
		else//结尾不是/则需要添加
		{
			path2=strcat(path2,dir2);
			path2=strcat(path2,"/");
		}
		path1=strcat(path1,filename->d_name);//在dirent结构中的文件名称
		path2=strcat(path2,filename->d_name);
	
        //如果目录里的这个文件还是个目录递归调用
	//！注意源目录里开头有. ..默认目录！表示同级目录和上级目录！不能递归
		if(ifdir(path1))
		{
               		if(!whatend(path1,'.'))//是目录而且不是默认的目录
			copydir(path1,path2);
		}
		else//不是目录就是文件了
			copyfile(path1,path2);	
	}
	return ;
	}
	else if(opendir(dir2))//如果目标目录已经存在
	{
		char *path=new char[1024];
		memset(path,0,sizeof(path));
		if(whatend(dir2,'/'))
		{
			path=strcat(path,dir2);
			path=strcat(path,dir1);
		}
		else
		{
			path=strcat(path,dir2);
			path=strcat(path,"/");
			path=strcat(path,dir1);
		}
		copydir(dir1,path);
		return ;
	}
}
void copyfile(char *file1,char *file2)//复制文件
{
	int read_count=0;//成功读取的字节数
	int last_location=0;//上次位置
	int now_location=0;//这次位置
	FILE*fp1=fopen(file1,"r");
	FILE*fp2=fopen(file2,"w");
	if(fp1==NULL)
	{
		printf("cp: 无法获取'%s' 的文件状态(stat): 没有那个文件或目录\n"
,file1);
		return ;
	}
	while(1)
	{
		last_location=ftell(fp1);//读取上次位置
		char content[1000]={0};
		read_count=fread(content,sizeof(content),1,fp1);
		now_location=ftell(fp1);//读取这次位置
		if(read_count<1)//出现错误或者到了文件末尾了
		{
			if(feof(fp1))//如果到了文件末尾
			{
				int gap=now_location-last_location;
				fwrite(content,gap,1,fp2);//写到目标文件里
				fclose(fp1);
				fclose(fp2);
				return ;
			}
			else
			{
				cout<<"read resource file error!\n";
				exit(-1);
			}
		}
		else//正常读取
			fwrite(content,sizeof(content),1,fp2);

	}
	fclose(fp1);
	fclose(fp2);
	return ;
}
int wcl(char *file)//统计file的行数并返回
{
	struct stat st;
        stat(file,&st);
        if(S_ISDIR(st.st_mode))
     		return 0;
	FILE*fp=fopen(file,"r");
	if(fp==NULL) return 0;
	int lines=0;
	char ch;
	while((ch=fgetc(fp))!=EOF)
		if(ch=='\n')
		lines++;
	fclose(fp);
	return lines;
}
int wcw(char *file)//统计单词数并返回
{
	struct stat st;
        stat(file,&st);
        if(S_ISDIR(st.st_mode))
                return 0;
        FILE*fp=fopen(file,"r");
        if(fp==NULL) return 0;
	int words=0;
	bool flag=0;
	char ch;
	while((ch=fgetc(fp))!=EOF)
        {
                if(ch!='\t'&&ch!='\n'&&ch!=' ')
                {
                        flag=1;
                        continue;
                }
                if((ch=='\t'||ch=='\n'||ch==' ')&&flag==1)//记录到字母或者汉字了
                {
                        words++;
                        flag=0;
                }
        }
        if(flag==1)//最后的单词顶到最后了
                words++;
	fclose(fp);
	return words;
}
int wcc(char *file)//统计字节数并返回
{
	struct stat st;
        stat(file,&st);
        if(S_ISDIR(st.st_mode))
                return 0;
        FILE*fp=fopen(file,"r");
        if(fp==NULL) return 0;
        int chars=0;
	char ch;
	while((ch=fgetc(fp))!=EOF)
		chars++;
	fclose(fp);
	return chars;
}
void wc(char *file,char *mode)//统计字数函数*有参数
{
	struct stat st;
        stat(file,&st);
        if(S_ISDIR(st.st_mode))
        {
                printf("wc: %s: 是一个目录\n",file);
                return ;
        }

	int chars=0,lines=0,words=0;
	FILE *fp=fopen(file,"r");
	if(fp==NULL)
	{
		printf("wc: %s: 没有那个文件或目录\n",file);
		return ;
	}
	char ch;
	bool flag=0;//统计单词数时做标记
	while((ch=fgetc(fp))!=EOF)
	{
		chars++;
		if(ch=='\n')
			lines++;
		if(ch!='\t'&&ch!='\n'&&ch!=' ')
		{
			flag=1;
			continue;
		}
		if((ch=='\t'||ch=='\n'||ch==' ')&&flag==1)//记录到字母或者汉字了
		{
			words++;
			flag=0;
		}
	}
	if(flag==1)//最后的单词顶到最后了
		words++;
	if(strcmp(mode,"-c")==0)
		cout<<chars<<" "<<file<<endl;
	else if(strcmp(mode,"-l")==0)
		cout<<lines<<" "<<file<<endl;
	else if(strcmp(mode,"-w")==0)//单参数
		cout<<words<<" "<<file<<endl;
	else if(strcmp(mode,"lw")==0)
		cout<<" "<<lines<<"  "<<words<<" "<<file<<endl;
	else if(strcmp(mode,"lc")==0)
		cout<<" "<<lines<<" "<<chars<<" "<<file<<endl;
	else if(strcmp(mode,"wc")==0)//双参数
		cout<<" "<<words<<" "<<chars<<" "<<file<<endl;
	else if(strcmp(mode,"all")==0)//无参数和三参数
		printf(" %d  %d %d %s\n",lines,words,chars,file);
}
void cat(char *file)//读取文件函数*无参数
{
	struct stat st;
	stat(file,&st);
	if(S_ISDIR(st.st_mode))
	{
		printf("cat: %s: 是一个目录\n",file);
		return ;
	}
	FILE*fp=fopen(file,"r");
	if(fp==NULL)
	{
		printf("cat: %s: 没有那个文件或目录\n",file);
		return ;
	}
	char ch;
	while((ch=fgetc(fp))!=EOF)
		cout<<ch;
	//cout<<endl;
}
void man(char *mode)//显示功能函数*无参数
{
	//纠错函数 void correct(char* input)对于输入的一个功能，判断其最多差一位字母的话，就把input字符串改为对应的正确功能字符串，如果相差太多就屏幕显示输入错误了没有这个功能退出函数即可
	if(strcmp(mode,"sh")==0)
	{
		cout<<"NAME\n       dash — command interpreter (shell)\n";
		cout<<"SYNOPSIS\n       sh [FILE]\n";
		cout<<"DESCRIPTION\n       Execute script file line by line\n";
		return ;
	}
	char modetem[100];
	strcpy(modetem,mode);
	for(int i=0;i<strlen(modetem);i++)// man函数可以忽略大小写
	{
		if(isupper(modetem[i]))
			modetem[i]=tolower(modetem[i]);
	}
	strcpy(modetem,correct(modetem));
	const char*file=".txt";
	char str[100];
	strcpy(str,modetem);
	strcat(str,file);
	//输出对应的文件
	FILE*fp=fopen(str,"r");
        if(fp==NULL)
        {
                printf("没有 %s 的手册页条目\n",mode);
                return ;
        }
        char ch;
        while((ch=fgetc(fp))!=EOF)
                cout<<ch;

}
char* correct(char *old)//修正原来输入的功能*纠错函数
{
	if(strncmp(old,"cp",2)==0)
	{
		strcpy(old,"cp");
		return old;
	}
	else if(strncmp(old,"cmp",3)==0)
	{
		strcpy(old,"cmp");
		return old;
	}
	else if(strncmp(old,"wc",2)==0)
	{
		strcpy(old,"wc");
		return old;
	}
	else if(strncmp(old,"cat",3)==0)
	{
		strcpy(old,"cat");
		return old;
	}
	else if(strncmp(old,"man",3)==0)
	{
		strcpy(old,"man");
		return old;
	}
	else if(strncmp(old,"sh",2)==0)
	{
		strcpy(old,"sh");
		return old;
	}
	else return old;
}
void shellit(char *file)
{
	char command[1024]={0};
	char ch=0;
	FILE*fp=fopen(file,"r");
	if(fp==NULL)//没有这个文件
	{
		cout<<"sh: 0: Can't open "<<file<<endl;
		return ;
	}
	int lines=0;
	while(fgets(command,1024,fp))
	{
		if(command[0]=='\n') continue;
		char *find=strchr(command,'\n');
		if(find) *find='\0';
		lines++;
		char *fun;
		char *func;
		char tem[1024];
		strcpy(tem,command);
		fun=strtok(tem,"\t ");
		func=correct(fun);
		if(strcmp(func,"man")!=0&&strcmp(func,"cp")!=0&&strcmp(func,"cmp")!=0&&strcmp(func,"wc")!=0&&strcmp(func,"cat")!=0&&strcmp(func,"sh")!=0)
		cout<<file<<": "<< lines<<": "<<file<<": "<<fun<<": "<<"not found"<<endl;
		else
		operate(command);
	}
	fclose(fp);
	return ;
}
void operate(char *str)//对输入的字符串进行对应的操作
{
        char *func  = strtok(str,"\t ");//获取要进行的功能名
	strcpy(func,correct(func));
        if(strcmp(func , "cmp")==0)
        {
                char *file1=strtok(NULL,"\t ");
                char *file2=strtok(NULL,"\t ");
		char *th=strtok(NULL,"\t ");
		if(th!=NULL)//如果参数过多
		{
			printf("cmp: invalid --ignore-initial value '%s'\n",th);
			cout<<"cmp: Try 'man cmp' for more information.\n";
			return ;//直接结束
		}
                compare(file1,file2);
        }
	else if(strcmp(func,"sh")==0)
	{
		char *file=strtok(NULL,"\t ");
		shellit(file);
	}
        else if(strcmp(func , "wc")==0)
        {
		int filecount=0;//记录被视为文件的参数个数
		char *files[100]={0};//记录文件名
		bool ifl=0,ifw=0,ifc=0;
                char *one=strtok(NULL,"\t ");
		while(one)
		{
			if(one[0]=='-')//串开头为-则观察后面的一个或多个参数
			{
				for(int i=1;i<strlen(one);i++)
				{
				if(one[i]=='l')
				ifl=1;
				else if(one[i]=='w')								ifw=1;
				else if(one[i]=='c')
				ifc=1;
				else
				{
				cout<<"wc: 无效选项 -- "<<one[i]<<endl;
				cout<<"Try 'man wc' for more information.\n";
				return;//这里直接结束该函数不会输出文件信息	
				}	
				}
			}
			else//不是参数就当作文件名记录
			{
				files[filecount]=one;
				filecount++;
			}
		one=strtok(NULL,"\t ");
		}
		if(ifl==0&&ifw==0&&ifc==0||ifl==1&&ifw==1&&ifc==1)//满参数
		{
			int alll=0,allw=0,allc=0;
			char m[4]="all";
			for(int i=0;i<filecount;i++)
			{
				wc(files[i],m);
				alll+=wcl(files[i]);
				allw+=wcw(files[i]);
				allc+=wcc(files[i]);
			}
			if(filecount>1)
			printf(" %d  %d %d 总用量\n",alll,allw,allc);
		}
		else if(ifl==1&&ifw==0&&ifc==0)//一个参数
                {
			int alll=0;
			char m[3]="-l";
			for(int i=0;i<filecount;i++)
			{
				wc(files[i],m);	
				alll+=wcl(files[i]);
			}
			if(filecount>1)
			printf(" %d 总用量\n",alll);
		}
                else if(ifl==0&&ifw==1&&ifc==0)
		{
			int allw=0;
			char m[3]="-w";
			for(int i=0;i<filecount;i++)
			{
				wc(files[i],m);
				allw+=wcw(files[i]);
			}
			if(filecount>1)
			printf(" %d 总用量\n",allw);
		}
		else if(ifl==0&&ifw==0&&ifc==1)
		{
			int allc=0;
			char m[3]="-c";
			for(int i=0;i<filecount;i++)
			{
				wc(files[i],m);
				allc+=wcc(files[i]);	
			}
			if(filecount>1)
                        printf(" %d 总用量\n",allc);

		}
		else if(ifl==1&&ifw==1&&ifc==0)
		{
			char m[3]="lw";
			int alll=0,allw=0;
			for(int i=0;i<filecount;i++)
			{
				wc(files[i],m);
				alll+=wcl(files[i]);
				allw+=wcw(files[i]);
			}
			if(filecount>1)
			printf(" %d %d 总用量\n",alll,allw);
		}
		else if(ifl==1&&ifw==0&&ifc==1)
		{
			char m[3]="lc";
			int alll=0,allc=0;
			for(int i=0;i<filecount;i++)
			{
				wc(files[i],m);
				alll+=wcl(files[i]);
				allc+=wcc(files[i]);
			}
			if(filecount>1)
			printf(" %d %d 总用量\n",alll,allc);
		}
		else if(ifl==0&&ifw==1&&ifc==1)
		{
			char m[3]="wc";
			int allw=0,allc=0;
			for(int i=0;i<filecount;i++)
			{
				wc(files[i],m);
				allw+=wcw(files[i]);
				allc+=wcc(files[i]);
			}
			if(filecount>1)
			printf(" %d %d 总用量\n",allw,allc);
		}
        }
        else if(strcmp(func , "cat")==0)
        {
		char *file=strtok(NULL,"\t ");
		while(file)
		{
               		cat(file);
			file=strtok(NULL,"\t ");
		}
        }
        else if(strcmp(func , "man")==0)
        {
                char *mode=strtok(NULL,"\t ");
                man(mode);
        }
        else if(strcmp(func ,"cp")==0)//这里暂时只实现了文件复制功能
        {
                char *one =strtok(NULL,"\t ");
		char *two =strtok(NULL,"\t ");
		char *thr =strtok(NULL,"\t ");
		if(one==NULL&&two==NULL&&thr==NULL)//cp后面什么也没有
		{
			cout<<"cp: 缺少了文件操作数\n";
			cout<<"Try 'man cp' for more information.\n";
		}
		else if(two==NULL&&thr==NULL)//cp后面只有一个参数
		{
			if(one[0]=='-')//后面这个是参数
			{
			for(int i=1;i<strlen(one);i++) 
			  if(one[i]!='r')
			  {
                            cout<<"cp：无效选项 -- "<<one[i]<<endl;
                            cout<<"Try 'cp --help' for more information."<<endl;
                            return ;
                          }
			cout<<"cp: 缺少了文件操作数\n";
			cout<<"Try 'cp --help' for more information."<<endl;
			}
			else
			{
			cout<<"cp: 在'"<<one<<"'  后缺少了要操作的目标文件\n";
			cout<<"Try 'cp --help' for more information."<<endl;
			}
		}
		else if(thr==NULL)//只有两个参数其中可能包括-r项
		{
			//先判断参数是否合理
			if(one[0]=='-')//有参数-×项
			for(int i=1;i<strlen(one);i++)
			  if(one[i]!='r')//参数只能有r
			  {
			    cout<<"cp：无效选项 -- "<<one[i]<<endl;
			    cout<<"Try 'cp --help' for more information."<<endl;
			    return ;
			  }
			if(two[0]=='-')//有参数-×项
                        for(int i=1;i<strlen(two);i++)
                          if(two[i]!='r')//参数只能有r
                          {
                            cout<<"cp：无效选项 -- "<<two[i]<<endl;
                            cout<<"Try 'cp --help' for more information."<<endl;
                            return ;
			  }
			if(one[0]=='-'&&two[0]=='-')
			{
			  cout<<"cp: 缺少了文件操作数\n";
			  cout<<"Try 'man cp' for more information.\n";
			}
			else if(one[0]=='-'||two[0]=='-')
			{
			  if(one[0]=='-')
			  {
				cout<<"cp: 在'"<<two<<"' 后缺少了要操作的目标文件\n";
				cout<<"Try 'man cp' for more information.\n";
			  }
			  else if(two[0]=='-')
                          {
                                cout<<"cp: 在'"<<one<<"' 后缺少了要操作的目标文>件\n";
                                cout<<"Try 'man cp' for more information.\n";
                          }
			}
		else//没有参数后面都是文件或者目录
		{
		  struct stat st1;
		  if(stat(one,&st1)==-1)//源文件或目录不存在
		  {
			cout<<"cp: 无法获取'"<<one<<"' 的文件状态(stat): 没有那个文件或目录\n";
			return ;
		  }
		  if(S_ISDIR(st1.st_mode))//源文件是个目录
       		  {
        	     	printf("cp: 略过目录'%s'\n",one);
        	      	return ;
       		  }
		  else if(iffile(one))//如果源是个文件不管第二个什么都用copydir
			copydir(one,two);
		}
		}
		else//有三个参数
		{
		 	if(strcmp(one,"-r")==0)
		 	copydir(two,thr);
			else if(strcmp(two,"-r")==0)
		        copydir(one,thr);
			else if(strcmp(thr,"-r")==0)
			copydir(one,two);
			else cout<<"cp: 输入错误 请检查您的参数是否正确\nTry 'man cp' for more information.\n";	
		}
	}			
                
	else
	{
		cout<<"未找到 '"<<func<<"' 相关命令，请您从(cp,cmp,wc,cat,man,sh,exit)中选择\n";
		return;
	}
}
