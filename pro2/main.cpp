#include"define.h"
int main()
{
	
	cout<<"\033[1;32mproject2@zhanghuan-virtual-machine\033[0m"<<':'<<"\033[1;34m~\033[0m"<<"$ ";
	char str[1024];
	fgets(str,1024,stdin);
	if(str[strlen(str)-1]=='\n')
		str[strlen(str)-1]='\0';
	while(strcmp(str,"exit")!=0)
	{
		operate(str);
		cout<<"\033[1;32mproject2@zhanghuan-virtual-machine\033[0m"<<':'<<"\033[1;34m~\033[0m"<<"$ ";
		fgets(str,1024,stdin);
		if(str[strlen(str)-1]=='\n')
                str[strlen(str)-1]='\0';

	}
	return 0;
}
