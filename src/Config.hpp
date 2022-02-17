#pragma once

#ifdef DEBUG
	#define LM_IGNORE_IN_RELEASE(x) x
#else
	#define LM_IGNORE_IN_RELEASE(x)
#endif

#define LM_LEXER_BUFFER_ENABLE 0
#define LM_LEXER_BUFFER_SIZE 1024
