#pragma once
//��������Զ���̷߳�ʽע�����dll
class CRemoteThreadDll
{
public:
	CRemoteThreadDll();
	~CRemoteThreadDll();
	BOOL RemoteInjection(LPCTSTR lpProcessName, LPCTSTR lpDllPath);
};

