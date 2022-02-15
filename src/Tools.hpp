#pragma once

#include "Logger.hpp"

#ifdef DEBUG
	#define LM_IGNORE_IN_RELEASE(x) x
#else
	#define LM_IGNORE_IN_RELEASE(x)
#endif
