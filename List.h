#pragma once
//AlonLLL.h
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "graphAlg.h"

typedef struct LLL {
	void * info;
	struct LLL* next;
} LLL,* LLLPtr;

void initLLL(LLLPtr* manager);
void insertAfter(LLLPtr ptrAddAfter);
void deleteAfter(LLLPtr ptrDeleteAfter);
void popLLLChar(LLLPtr* manager);
void pushLLLChar(LLLPtr* manager);