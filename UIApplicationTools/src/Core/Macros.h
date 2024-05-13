#pragma once

#include <iostream>
#include <memory>

#ifdef UIA_DEBUG
	#define UIA_ASSERT(x, y) { if(!(x)) { std::cout << y << std::endl; __debugbreak(); } }
#else
	#define UIA_ASSERT(x, y) { if(!(x)) {} }
#endif