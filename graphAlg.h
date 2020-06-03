#define _CRT_SECURE_NO_WARNINGS


#ifndef _GRAPH
#define _GRAPH
#include<time.h>
#include<string.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#include<limits.h>
#ifndef _BOOLEAN
#define _BOOLEAN
typedef enum { FALSE, TRUE }BOOLEAN;
#endif // !_BOOLEAN
#ifndef N
#define N 3000
#endif //!N
#ifndef M
#define M 300
#endif //!M
#ifndef _STRING
#define _STRING
typedef char STRING[M];
typedef char LONG_STRING[N];
#endif // !_STRING

typedef enum {
	SEARCHING, SUCCES, WRONG_PARAMETER_NAME, COMMAND_DOES_NOT_EXIST, FIND_MAIN,
	PROBLEM_OPERAND, NOT_PART_OF_NAME_OPTION, IDENTATION_ERROR, SYNTAX_ERROR, NOT_PART_OF_NUMBER,
	VARIABLES_GRAPH,CHECK_VARIABLES_GRAPH, CONDITION_GRAPH, NUMBERS_GRAPH
} Status;

typedef struct vertex
{
	void * value;
	Status status;
}vertex, * vertexPtr;


typedef struct
{
	vertexPtr * verticesArr;
	BOOLEAN **adjacentMat;
	int size;
}graph, *graphPtr;

void initGraph(graphPtr);
void addVertexToGraph(graphPtr, vertexPtr);
int getOffsetByVertexName(graphPtr, void*, int(*cmp)(void*, void*));
BOOLEAN joinEdgeToGraph(graphPtr g, void* vertexName1, void* vertexName2, BOOLEAN edge, int(*cmp)(void*, void*));
BOOLEAN removeEdgeFromGraph(graphPtr, void*, void*, int(*cmp)(void*, void*));
void freeGraph(graphPtr graph);
#endif
