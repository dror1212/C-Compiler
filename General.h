#pragma once

#ifndef _GENERAL
#define _GENERAL

#include "HashTables.h"

typedef struct map {
	graphPtr graph;
	DataItemPtr * hashArray;
}map, * mapPtr;

void initMainGraph(graphPtr graph);
void initMyGraph(graphPtr graph, Status* statuses, char* vertexes, char* graphs);
void initNewVarNameGraph(graphPtr graph);
void initifAndElseGraph(graphPtr graph);
void initCreateVariablesGraph(graphPtr graph);
int cmpNameVrx(void* val1, void* val2);
int cmpCharVrx(void* val1, void* val2);
int stringHashCode(char* str);
void initErrorsHashTable(HashTable hashArray);
int hashCode(void* key);
void initNewVarNameHashTable(HashTable hashArray);
void initGraphsToUse(HashTable hashArray, graphPtr newGraph, HashTable newTable, int graphName);
void initStartsCreatingVars(HashTable hashArray);
Status explore(graphPtr gra, int vertexIndex, FILE* source, int expectedLength, HashTable graphsToUse, HashTable variables);
Status exploreAndCreateVars(graphPtr gra, int vertexIndex, FILE* source, char* newVar);
void initStartsIfAndElse(HashTable hashArray);
void initNumbersGraph(graphPtr graph);
void initNumbersHash(HashTable hashArray);
void initConditionGraph(graphPtr graph);
void initStartsCondition(HashTable hashArray);
#endif // !_GENERAL