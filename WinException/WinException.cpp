// WinException.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;
//�쳣��2��   :cpu �׳��쳣��ΪӲ���쳣   ����쳣


// SEH 1����ֹ����    2���쳣����
//Seh ��ֹ����   ��� __try{}   __finally{}     ������try ���е����� ExitPorcess  ExitThread  TerminateProcess TerminateThread ���� ���� finally ����ִ�� ���������߳������return  0
//������˵��� ����һ������ ����ջ�ռ䱻�ľ��� finally���п���û�л���ִ��
// ���ص����� ��ʱ��������������
//��try ���д��� return goto continue break��try����ǰ�˳��� ʱ���ھֲ�չ�������⿪���� 
void SEHStop()
{
	char *p = NULL;
	__try
	{
		//__leave;    //__leave ����ֱ���������β ����������⿪��
		(*p)++;
	}
	__finally
	{
		int code=AbnormalTermination();  //try �����ڴ���� Υ�� ����Խ�� �����ȫ��չ��  
		MessageBoxA(NULL, "Exception Occur", "Error", 0);
	}
}
// __try {} __except(filter){}   filter ��Ϊ���˺���   �쳣�Ż�ִ�� __except ���д���
//try����ʹ��  return goto continue break ����������ܿ���

LONG filter(int code)
{
	if (code == EXCEPTION_BREAKPOINT)
	{
		MessageBoxA(NULL, "EXCEPTION_BREAKPOINT", "Error", 0);
		return EXCEPTION_EXECUTE_HANDLER;
	}	
	else
	{
		MessageBoxA(NULL, "EXCEPTION_CONTINUE_EXECUTION", "Error", 0);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
		
}
void SEHFilter()
{
	__try
	{
		char *p = NULL;
		(*p)++;
	}
	__except(filter(GetExceptionCode()))
	{
		MessageBoxA(NULL, "Exception Occur", "Error", 0);
	}
}


int main()
{
	cout << "sssss";
	//SEHStop();
	SEHFilter();
    return 0;
}

