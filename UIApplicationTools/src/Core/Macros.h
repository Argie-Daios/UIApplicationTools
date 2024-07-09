#pragma once

#include <iostream>
#include <memory>

#include "Tools/Random.h"

#ifdef UIDEBUG
	#define UIASSERT(x, y) { if(!(x)) { std::cout << y << std::endl; __debugbreak(); } }
	#define UIERROR(x) { std::cout << "Error: " << x << std::endl; }
#else
	#define UIASSERT(x, y) { if(!(x)) {} }
	#define UIERROR(x) { }
#endif

#define TAB(x) {for(int i = 0; i < x; i++) std::cout << "\t";}
#define STAB(x, stream) {for(int i = 0; i < x; i++) stream << "\t";}

#define SPACE(x) {for(int i = 0; i < x; i++) std::cout << " ";}
#define SSPACE(x, stream) {for(int i = 0; i < x; i++) stream << " ";}
	
template<typename TCasted, typename T>
TCasted Cast(T object)
{
	return dynamic_cast<TCasted>(object);
}

inline std::string randomStringGenerator(int size = 0)
{
	UIASSERT(size <= 50, "Overflow");

	std::string str;

	for (int i = 0; i < size; i++)
	{
		if (Random::Randrange(1))
		{
			str += '9' - Random::Randrange(9);
		}
		else
		{
			str += 'z' - Random::Randrange(25);
		}
	}

	return str;
}