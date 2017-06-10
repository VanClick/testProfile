#include "Profile.h"

int main()
{

	LARGE_INTEGER sgLiPerfFreq;
	QueryPerformanceFrequency(&sgLiPerfFreq);


	PROFILE_BEGIN(Total);

	PROFILE_BEGIN(Test0);
	long long j = 0;
	for (long long i = 0; i < 5000000; i++)
	{
		FILETIME t1,t2;
		GetSystemTimeAsFileTime(&t1);
		GetSystemTimeAsFileTime(&t2);
		j += t2.dwLowDateTime - t1.dwLowDateTime;
	}
	PROFILE_END(Test0);

	PROFILE_BEGIN(Test1);
	for (long long i = 0; i < 5000000; i++)
	{
		LARGE_INTEGER l1, l2;
		QueryPerformanceCounter(&l1);
		QueryPerformanceCounter(&l2);
		j += (l2.QuadPart - l1.QuadPart);// *1000000ll / sgLiPerfFreq.QuadPart;
	}
	PROFILE_END(Test1);

	PROFILE_BEGIN(Test2);
	for (long long i = 0; i < 200000; i++)
	{
		j += i & 100ll;
	}
	PROFILE_END(Test2);

	PROFILE_BEGIN(Test3);
	for (long long i = 0; i < 400000; i++)
	{
		j += i & 100ll;
	}
	PROFILE_END(Test3);

	PROFILE_END(Total);


	printf("%lld", j);
	char end = getchar();
}
