#include "stdafx.h"
#include "RemoteThreadDll.h"
#include "ProcessEx.h"

CRemoteThreadDll::CRemoteThreadDll()
{
}

typedef struct _REMOTE_PARAMETER
 {
	    CHAR m_printMsgBox[MAX_PATH];
	    CHAR m_printDbgStr[MAX_PATH];
	     CHAR m_strDllPath[MAX_PATH];
	    DWORD m_dwLoadLibraryAddr;
	   DWORD m_dwFreeLibraryAddr;
	   DWORD m_dwGetProcAddrAddr;

 }RemotePara, *PRemotePara;
//Զ���̺߳���
DWORD WINAPI  RemoteThreadProc(PRemotePara pRemotePara)
{
	

}

CRemoteThreadDll::~CRemoteThreadDll()
{
}
BOOL CRemoteThreadDll::RemoteInjection(LPCTSTR lpProcessName, LPCTSTR lpDllPath)
{
	if (NULL == lpProcessName || NULL == lpDllPath)
		return FALSE;
	if (!PathFileExists(lpDllPath))
		return FALSE;
	//Step1   ��Ȩ
	CProcessEx::AdjustProcessTokenPrivilege();
	//Step2  �ҵ���ӳ����
	DWORD dwPid=CProcessEx::GetProcessPid(lpProcessName);
	if (0 == dwPid)
		return FALSE;
	HANDLE hProcess=CProcessEx::GetProcessHandle(dwPid, PROCESS_ALL_ACCESS);
	if (NULL == hProcess)
		return FALSE;
	//step3  ��Զ�̽����Ϸ���һ���ڴ����� ���ڴ洢dll��·��  ע��򿪽���ʱ��Ȩ�޲���
	char szLibPath[_MAX_PATH] = "D:\\QuickLearningAbility\\HookDll\\Debug\\HookDll.dll";
	//int len=1+lstrlen(lpDllPath);
	//int size = len * sizeof(TCHAR);
	LPVOID  pAdressDllPath=VirtualAllocEx(hProcess, NULL, sizeof(szLibPath), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (NULL == pAdressDllPath)
	{
		CloseHandle(hProcess);
		return FALSE;
	}
		
	//Step4 ��dllpath д�뵽Զ�˽����ڴ�
	if (FALSE == WriteProcessMemory(hProcess, pAdressDllPath, szLibPath, sizeof(szLibPath), NULL))
	{
		CloseHandle(hProcess);
		return FALSE;
	}

	//Step5  ��ȡԶ����Ҫ���ݸ�Զ���̵߳� �̺߳��� ��ʵ����loadlabrary ��Ϊ �����̵߳��̺߳���
	HMODULE modHandle = GetModuleHandle(_T("Kernel32"));
	LPTHREAD_START_ROUTINE pAddrLoad = (LPTHREAD_START_ROUTINE)GetProcAddress(modHandle,"LoadLibraryA");
	LPTHREAD_START_ROUTINE pAddrFree = (LPTHREAD_START_ROUTINE)GetProcAddress(modHandle, "FreeLibraryA");
	if (pAddrLoad == NULL)
	{
		CloseHandle(hProcess);
		return FALSE;
	}
	//Step6 ����Զ���߳� �߳�����������dll �ȴ��߳��˳�
	DWORD dwRemoteThreadid = 0;
	HANDLE hThreadHandle=CreateRemoteThread(hProcess, NULL, 0, pAddrLoad, pAdressDllPath, 0, &dwRemoteThreadid);
	if (NULL == hThreadHandle)
	{
		CloseHandle(hProcess);
		return FALSE;
	}
	WaitForSingleObject(hThreadHandle, INFINITE);
	CloseHandle(hThreadHandle);

	//Step7   �ͷ�������Դ
	if (FALSE == VirtualFreeEx(hProcess, pAdressDllPath, 0, MEM_RELEASE))
	{
		MessageBox(NULL,L"error release remote memory",L"error",MB_OK);
	}
	//Step8 ж��dll 

}
