#include "stdio.h"
#include "windows.h"
#include "tlhelp32.h"
#include "string.h"

//利用进程快照枚举当前Windows运行进程的信息 
int main()
{
	PROCESSENTRY32 pe;
	//设置结构体pe的大小
	pe.dwSize = sizeof(pe);
	//获取系统内进程的快照
	while(1)
	{
		int flag=0;
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
		if (hProcessSnap == INVALID_HANDLE_VALUE) 
		{
			printf("CreateToolhelp32Snapshot error.\n");
			return -1;
		}
		//遍历进程快照，显示每个进程的信息
		BOOL bMore = ::Process32First(hProcessSnap,&pe);
		while (bMore)  
		{
			bMore = ::Process32Next(hProcessSnap,&pe);
			if(strcmp(pe.szExeFile,"数据处理软件.exe")==0)
			{
				flag=1;
			}
		}
		if(flag==1)
		{
			printf("程序运行正常!\n");
		}
		else if(flag==0)
		{
			printf("程序已被关闭!\n");
			printf("重启该软件!\n");
			ShellExecute(NULL,"open","数据处理软件.exe","数据处理软件.exe","", SW_SHOW);
		}
		//释放snapshot对象
		::CloseHandle(hProcessSnap);
	} 
	return 0;
}