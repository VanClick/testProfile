#include <stdio.h>
#include "Profile.h"

thread_local byte Profile::depth = 0;

LARGE_INTEGER sgLiPerfFreq;
class __ProfileData
{
public:
	__ProfileData()
	{
		QueryPerformanceFrequency(&sgLiPerfFreq);
	}
};

__ProfileData sgProfileData;

Profile::Profile(string name)
{
	this->name = name;
	//GetSystemTimeAsFileTime(&t);

	QueryPerformanceCounter(&m_liPerfStart);

	depth++;
}

Profile::~Profile()
{
	depth--;
	//FILETIME endT;
	//GetSystemTimeAsFileTime(&endT);

	//printf("F %*s%s %ul\n", depth * 4, "", name.c_str(), (endT.dwLowDateTime - t.dwLowDateTime));

	LARGE_INTEGER liPerfNow;
	QueryPerformanceCounter(&liPerfNow);
	int time = (((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000000ll) / sgLiPerfFreq.QuadPart);

	printf("C %*s%s %d %lld\n", depth * 4, "", name.c_str(), time, sgLiPerfFreq.QuadPart);
}