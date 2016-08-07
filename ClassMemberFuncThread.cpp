
#include <stdio.h>
#include <process.h>
#include <windows.h>
class CWork
{
	size_t _num;
public:
	CWork(size_t i):_num(i){}

	unsigned int WINAPI  work()
	{
		printf("number = %d\n",_num);
		return 0;
	}
};


struct work_t
{
    unsigned int  num_;

    work_t():num_(0){}

    unsigned int WINAPI work()
    {
        printf("number = %d\n",num_);
        return num_;
    }
};


template <typename T>
union proc_u
{
	unsigned int (WINAPI * ThreadProc)(void*);
	unsigned int  (WINAPI T::*MemberProc)();
};


int main(int argc, char * argv[])
{
    work_t workobj;
    workobj.num_ = 5;

    proc_u<work_t> proc;
	proc.MemberProc = &work_t::work;

	HANDLE h = (HANDLE)(_beginthreadex(NULL,0,proc.ThreadProc,&workobj,0,NULL));
	WaitForSingleObject(h,INFINITE);
	CloseHandle(h);

    return 0;
}

