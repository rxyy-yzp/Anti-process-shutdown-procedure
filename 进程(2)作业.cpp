#include "stdio.h"
#include "windows.h"
#include "tlhelp32.h"
#include "string.h"

//���ý��̿���ö�ٵ�ǰWindows���н��̵���Ϣ 
int main()
{
	PROCESSENTRY32 pe;
	//���ýṹ��pe�Ĵ�С
	pe.dwSize = sizeof(pe);
	//��ȡϵͳ�ڽ��̵Ŀ���
	while(1)
	{
		int flag=0;
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
		if (hProcessSnap == INVALID_HANDLE_VALUE) 
		{
			printf("CreateToolhelp32Snapshot error.\n");
			return -1;
		}
		//�������̿��գ���ʾÿ�����̵���Ϣ
		BOOL bMore = ::Process32First(hProcessSnap,&pe);
		while (bMore)  
		{
			bMore = ::Process32Next(hProcessSnap,&pe);
			if(strcmp(pe.szExeFile,"���ݴ������.exe")==0)
			{
				flag=1;
			}
		}
		if(flag==1)
		{
			printf("������������!\n");
		}
		else if(flag==0)
		{
			printf("�����ѱ��ر�!\n");
			printf("���������!\n");
			ShellExecute(NULL,"open","���ݴ������.exe","���ݴ������.exe","", SW_SHOW);
		}
		//�ͷ�snapshot����
		::CloseHandle(hProcessSnap);
	} 
	return 0;
}