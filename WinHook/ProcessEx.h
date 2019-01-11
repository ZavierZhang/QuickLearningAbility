#pragma once
//操作进程 
class CProcessEx
{
public:
	CProcessEx();
	~CProcessEx();
	//提升当前进程权限
	static BOOL  AdjustProcessTokenPrivilege();
	static HANDLE GetProcessHandle(DWORD pID, DWORD dwDesiredAccess);
	static HANDLE GetProcessHandle(DWORD pID);
	static DWORD GetProcessPid(LPCTSTR lpProcessName);
	static BOOL IsProcess(DWORD pID, LPCTSTR lpProcessName);
};

