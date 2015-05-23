
#include "stdafx.h"
#include <process.h>
#include <windows.h>
class CWork
{
private:
	size_t _num;
public:
	CWork(size_t i):_num(i){}
public:
	unsigned int WINAPI  work()
	{
		printf("number = %d\n",_num);
		return 0;
	}
};
template <typename T>
union u_Proc
{
	unsigned int (WINAPI * ThreadProc)(void*);
	unsigned int  (WINAPI T::*MemberProc)();
};


int _tmain(int argc, _TCHAR* argv[])
{
	CWork obj(2);
	u_Proc<CWork> proc;
	proc.MemberProc = &CWork::work;

	HANDLE h = (HANDLE)(_beginthreadex(NULL,0,proc.ThreadProc,&obj,0,NULL));

	WaitForSingleObject(h,INFINITE);

	CloseHandle(h);
	return 0;
}

