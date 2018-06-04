// procc.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
HANDLE mutex=NULL;

typedef struct
{
	int i;
	int k;
	int count;
}parampampam;

unsigned __stdcall FunThread(void* pvParam){
	DWORD ret;
	int temp;
	SYSTEM_INFO sys;
	GetSystemInfo(&sys);
	parampampam* p= (parampampam*) (pvParam);
	temp=p->count/sys.dwNumberOfProcessors;
	int start=p->i;
	int stop=p->k;
	p->i=p->k;
	p->k=p->k+temp;	
	printf("start: %d, stop: %d\n",start,stop);
ret=WaitForSingleObject(mutex,INFINITE);
			if(ret==WAIT_OBJECT_0){
		for(register int k=start; k<stop;++k)
		{	
			
				printf("Number: %d\n",k);
			
			}			//Sleep(100);
		ReleaseMutex(mutex);
	}
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"Russian");
	SYSTEM_INFO sys;
	GetSystemInfo(&sys);
	parampampam p;
	int x=103;//размерность массива
	p.i=0;
	p.k=x/sys.dwNumberOfProcessors+x%sys.dwNumberOfProcessors;
	p.count=x;
	HANDLE *hTread=(HANDLE*) malloc(sys.dwNumberOfProcessors*sizeof(HANDLE));
	printf(" оличество €дер: %d\n",sys.dwNumberOfProcessors);
	mutex=CreateMutex(NULL,FALSE,NULL);

	for( register int i=0; i<sys.dwNumberOfProcessors;++i)
	{
		hTread[i]=(HANDLE)_beginthreadex(NULL,NULL,&FunThread,(PVOID)&p,0,NULL);
	}

	for( register int f=0; f<sys.dwNumberOfProcessors;++f)
	{
		WaitForSingleObject(hTread[f], INFINITE);
		
	}

	for( register int f=0; f<sys.dwNumberOfProcessors;++f)
	{
		CloseHandle(hTread[f]);
		
	}
	return 0;
}

