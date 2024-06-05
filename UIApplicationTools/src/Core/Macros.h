#pragma once

#include <iostream>
#include <memory>

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