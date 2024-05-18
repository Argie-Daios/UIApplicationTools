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