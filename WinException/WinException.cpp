// WinException.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;
//异常分2种   :cpu 抛出异常都为硬件异常   软件异常


// SEH 1、终止处理    2、异常处理
//Seh 终止处理   语句 __try{}   __finally{}     除了在try 块中调用了 ExitPorcess  ExitThread  TerminateProcess TerminateThread 函数 否则 finally 都会执行 就算是主线程里调用return  0
//上面所说情况 还有一例特殊 若是栈空间被耗尽了 finally则有可能没有机会执行
// 挂载调试器 的时候必须调试器处理
//当try 块中存在 return goto continue break（try块提前退出） 时存在局部展开（额外开销） 
void SEHStop()
{
	char *p = NULL;
	__try
	{
		//__leave;    //__leave 将会直接跳到块结尾 不会产生额外开销
		(*p)++;
	}
	__finally
	{
		int code=AbnormalTermination();  //try 块中内存访问 违规 或者越界 会产生全局展开  
		MessageBoxA(NULL, "Exception Occur", "Error", 0);
	}
}
// __try {} __except(filter){}   filter 即为过滤函数   异常才会执行 __except 块中代码
//try块中使用  return goto continue break 不会带来性能开销

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

