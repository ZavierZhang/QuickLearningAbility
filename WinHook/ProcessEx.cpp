#include "stdafx.h"
#include "ProcessEx.h"
#include <psapi.h>
#pragma comment(lib, "psapi.lib ")

CProcessEx::CProcessEx()
{
}


CProcessEx::~CProcessEx()
{

}
BOOL CProcessEx::AdjustProcessTokenPrivilege()
{
	HANDLE hToken = NULL;
	if (FALSE == OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;
	//�жϵ�ǰ�����Ƿ����SE_DEBUG_NAME Ȩ�ޣ��Խ��̽���
	LUID luidTmp;  //�ֲ�ȫ��Ψһ��������ϵͳ������ȫ��Ψһ
	if (FALSE == LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luidTmp))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = luidTmp;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	BOOL bSuc=AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL);
	int Code = GetLastError();
	CloseHandle(hToken);
	return bSuc;
}
HANDLE CProcessEx::GetProcessHandle(DWORD pID, DWORD dwDesiredAccess)
{
	return OpenProcess(dwDesiredAccess, FALSE, pID);
}
HANDLE CProcessEx::GetProcessHandle(DWORD pID)
{
	return OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pID);
}
BOOL CProcessEx::IsProcess(DWORD pID, LPCTSTR lpProcessName)
{
	BOOL bSuc = FALSE;
	HANDLE hProcess = GetProcessHandle(pID);
	if (NULL == hProcess)
	{
		return bSuc;
	}
	TCHAR szProcessName[MAX_PATH] = { 0 };
	if (0 == GetModuleBaseName(hProcess, NULL, szProcessName, sizeof(szProcessName)))
	{
		CloseHandle(hProcess);
		return bSuc;
	}
	if (0 == _tcscmp(szProcessName, lpProcessName))
	{
		bSuc = TRUE;
	}
	CloseHandle(hProcess);
	return bSuc;
}
DWORD CProcessEx::GetProcessPid(LPCTSTR lpProcessName)
{
	DWORD  dwProcess[1024] = { 0 };
	DWORD dwRealSize = 0;
	DWORD PID = NULL;
	if (!EnumProcesses(dwProcess, sizeof(dwProcess), &dwRealSize))
	{
		return 0;
	}
	int dwProcessCount = dwRealSize / sizeof(DWORD);
	for (int i = 0; i < dwProcessCount; i++)
	{
		DWORD pid = dwProcess[i];
		if (0 != pid)
		{   //����Զ�˽��̱������PROCESS_VM_READ ��PROCESS_QUERY_INFORMATION Ȩ��
			if (IsProcess(pid, lpProcessName))
				return pid;
		}
	}
	return 0;
}
