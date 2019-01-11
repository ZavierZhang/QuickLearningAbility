#pragma once
//此类用来远程线程方式注入进程dll
class CRemoteThreadDll
{
public:
	CRemoteThreadDll();
	~CRemoteThreadDll();
	BOOL RemoteInjection(LPCTSTR lpProcessName, LPCTSTR lpDllPath);
};

