#pragma once

#include "List.h"

void initLLL(LLLPtr* manager)
{
	(*manager)->next = NULL;

	return;
}

void insertAfter(LLLPtr ptrAddAfter)
{
	LLLPtr temp = ptrAddAfter->next;
	LLLPtr newLLL = (LLLPtr)malloc(sizeof(LLL));
	ptrAddAfter->next = newLLL;
	newLLL->next = temp;

	return;
}

void deleteAfter(LLLPtr ptrDeleteAfter)
{
	LLLPtr temp = ptrDeleteAfter->next->next;
	free(ptrDeleteAfter->next);
	ptrDeleteAfter->next = temp;

	return;
}

void popLLLChar(LLLPtr* manager)
{
	LLLPtr* saveManager = *manager;
	LLLPtr newManager = (*manager)->next;
	free(saveManager);

	return;
}

void pushLLLChar(LLLPtr* manager)
{
	LLLPtr oldManager = (LLLPtr)malloc(sizeof(LLL));
	oldManager = *manager;
	(*manager)->next = oldManager;

	return;
}