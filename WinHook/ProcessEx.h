#pragma once
//�������� 
class CProcessEx
{
public:
	CProcessEx();
	~CProcessEx();
	//������ǰ����Ȩ��
	static BOOL  AdjustProcessTokenPrivilege();
	static HANDLE GetProcessHandle(DWORD pID, DWORD dwDesiredAccess);
	static HANDLE GetProcessHandle(DWORD pID);
	static DWORD GetProcessPid(LPCTSTR lpProcessName);
	static BOOL IsProcess(DWORD pID, LPCTSTR lpProcessName);
};

