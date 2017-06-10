#pragma once
#include <string>
#include <Windows.h>
using namespace std;

class Profile
{
public:
	Profile(string name);
	~Profile();

private:
	FILETIME t;
	string name;
	LARGE_INTEGER m_liPerfStart;
	static thread_local byte depth;
};



#define PROFILE_BEGIN(name) \
	Profile* profile##name = new Profile(#name);

#define PROFILE_END(name) \
	profile##name->~Profile();

