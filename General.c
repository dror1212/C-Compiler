#pragma once

#include "General.h"

int cmpNameVrx(void* val1, void* val2)
{
	return (char)((vertexPtr)val1)->value - (char)((vertexPtr)val2)->value;
}

int cmpCharVrx(void* val1, void* val2)
{
	return ((char)val1 - (char)((vertexPtr)val2)->value);
}

int cmpStatus(void* val1, void* val2)
{
	return ((int)val1 - ((vertexPtr)val2)->status);
}


int hashCode(void* key)
{
	return (Status)key % HASH_TABLE_SIZE;
}

int stringHashCode(char* str)
{
	unsigned char hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % HASH_TABLE_SIZE;
}

void initMyGraph(graphPtr graph, Status * statuses, char * vertexes, char * graphs)
{
	vertexPtr vert;
	int firstOffset;
	int secondOffset;
	int counter = 0;
	while (*vertexes != '\0')
	{
		firstOffset = getOffsetByVertexName(graph, *vertexes, cmpCharVrx);
		if(firstOffset == -1)
		{
			vert = (vertexPtr)malloc(sizeof(vertex));
			vert->value = *vertexes;
			vert->status = statuses[counter];
			addVertexToGraph(graph, vert);
			firstOffset = getOffsetByVertexName(graph, *vertexes, cmpCharVrx);
			counter++;
		}
		if (firstOffset == -1)
		{
			printf(*vertexes);
		}
		vertexes++;
		secondOffset = getOffsetByVertexName(graph, *vertexes, cmpCharVrx);
		if (secondOffset == -1)
		{
			vert = (vertexPtr)malloc(sizeof(vertex));
			vert->value = *vertexes;
			vert->status = statuses[counter];
			addVertexToGraph(graph, vert);
			secondOffset = getOffsetByVertexName(graph, *vertexes, cmpCharVrx);
			counter++;
		}
		vertexes++;

		graph->adjacentMat[firstOffset][secondOffset] = TRUE;
	}
	vert = (vertexPtr)malloc(sizeof(vertex));
	vert->value = NULL;
	vert->status = statuses[counter];
	addVertexToGraph(graph, vert);

	/*
	// will be removed
	for (int i = 0; i < graph->size - 1; i++)
	{
		for(char * ch = graphs; *ch != '\0';ch++)
		{
			graph->verticesArr[i]->value == *ch ? graph->verticesArr[i]->value = NULL : NULL;
		}
		graph->adjacentMat[i][graph->size - 1] = TRUE;
	}



	for (int i = 0; i < graph->size; i++)
	{
		printf("%c", graph->verticesArr[i]->value);
		printf("%d\n", graph->verticesArr[i]->status);
		for (int j = 0; j < graph->size; j++)
		{
			printf("%d", graph->adjacentMat[i][j]);
		}
		printf("\n");
	}
	*/
}

void initMainGraph(graphPtr graph)
{
	Status statuses[12] = { SEARCHING,SEARCHING,SEARCHING,SEARCHING,SEARCHING,SEARCHING,
							SEARCHING,SEARCHING,SEARCHING,SEARCHING,SUCCES,FIND_MAIN };
	// edges:
	// v --> o
	// o --> i
	// i --> d
	// d --> " "
	// " " --> " "
	// " " --> m
	// m --> a
	// a --> i
	// i --> n
	// n --> (
	// ( --> v
	// d --> )
	// ) --> {
	initMyGraph(graph, statuses, "vooiidd    mmaaiinn(n  ((vd)){","");
}

void initifAndElseGraph(graphPtr graph)
{
	Status statuses[12] = { SEARCHING,SEARCHING,SEARCHING,SEARCHING,SEARCHING,SEARCHING,
							SEARCHING,CONDITION_GRAPH,SEARCHING,SUCCES,SEARCHING,PROBLEM_OPERAND };
	// edges:
	// i --> f
	// f --> " "
	// f --> (
	// " " --> (
	// ( --> condition
	// condition --> )
	// ) --> {
	// e --> l
	// l --> s
	// s --> e
	// e --> " "
	// e --> {
	// " " --> i
	// " " --> " "
	initMyGraph(graph, statuses, "iff f( (ellssee  i(??)e{){ {)   }e}  i", "?");
}

void initConditionGraph(graphPtr graph)
{
	Status statuses[17] = { SEARCHING };
	statuses[16] = PROBLEM_OPERAND;
	statuses[15] = CONDITION_GRAPH;
	statuses[0] = CHECK_VARIABLES_GRAPH;
	statuses[1] = SUCCES;
	statuses[2] = NUMBERS_GRAPH;

	// edges:
	// varNames --> )
	// numbers --> )
	// varNames --> " "
	// numbers --> " "
	// " " --> )
	// " " --> +
	// " " --> -
	// " " --> *
	// " " --> /
	// " " --> %
	// " " --> <
	// " " --> >
	// " " --> =
	// " " --> |
	// " " --> &
	// < --> =
	// > --> =
	// = --> =
	// & --> &
	// | --> |
	// + --> varName
	// - --> varName
	// * --> varName
	// / --> varName
	// % --> varName
	// = --> varName
	// | --> varName
	// & --> varName
	// + --> numbers
	// - --> numbers
	// * --> numbers
	// / --> numbers
	// % --> numbers
	// = --> numbers
	// | --> numbers
	// & --> numbers
	// ( --> operands ?
	// varName --> )
	// varName --> +
	// varName --> -
	// varName --> *
	// varName --> /
	// varName --> %
	// varName --> <
	// varName --> >
	// varName --> =
	// varName --> |
	// varName --> &
	// numbers --> )
	// numbers --> +
	// numbers --> -
	// numbers --> *
	// numbers --> /
	// numbers --> %
	// numbers --> <
	// numbers --> >
	// numbers --> =
	// numbers --> |
	// numbers --> &
	initMyGraph(graph, statuses, "{)}){ }    ) + - * / % < > = | &<=>===&&||+{-{*{/{%{={|{&{+}-}*}/}%}=}|}&}(?{){+{-{*{/{%{<{>{={|{&})}+}-}*}/}%}<}>}=}|}&", "{}?");
}

void initNewVarNameGraph(graphPtr graph)
{
	Status statuses[37] = { SUCCES };
	statuses[36] = WRONG_PARAMETER_NAME;
	// a --> a
	// a --> b
	// a --> c
	// a --> d
	// .....
	// .....
	// a --> 0
	// a --> 1
	// .....
	// .....
	// 0 --> a
	// 1 --> a
	// .....

	LONG_STRING vertexes = "";
	int counter = 0;
	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		for (char ca = 'a'; ca <= 'z'; ca++)
		{
			vertexes[counter++] = ch;
			vertexes[counter++] = ca;
		}
		for (char ca = '0'; ca <= '9'; ca++)
		{
			vertexes[counter++] = ch;
			vertexes[counter++] = ca;
			vertexes[counter++] = ca;
			vertexes[counter++] = ch;
		}
	}
	for (char ch = '0'; ch <= '9'; ch++)
	{
		for (char ca = '0'; ca <= '9'; ca++)
		{
			vertexes[counter++] = ch;
			vertexes[counter++] = ca;
		}
	}
	vertexes[counter] = '\0';
	initMyGraph(graph, statuses, vertexes,"");
}

void initNumbersGraph(graphPtr graph)
{
	Status statuses[11] = { SEARCHING };
	statuses[10] = NOT_PART_OF_NUMBER;

	// connect all the numbers to eachother

	LONG_STRING vertexes = "";
	int counter = 0;
	for (char ch = '0'; ch <= '9'; ch++)
	{
		for (char ca = '0'; ca <= '9'; ca++)
		{
			vertexes[counter++] = ch;
			vertexes[counter++] = ca;
		}
	}
	vertexes[counter] = '\0';
	initMyGraph(graph, statuses, vertexes, "");
}


void initCreateVariablesGraph(graphPtr graph)
{
	Status statuses[20] = { SEARCHING };
	statuses[19] = WRONG_PARAMETER_NAME;
	statuses[18] = CONDITION_GRAPH;
	statuses[16] = SUCCES;
	statuses[15] = VARIABLES_GRAPH;

	initMyGraph(graph, statuses, "unnssiiggnneedd    iinnt ffllooaatt  sshhoorrt }};}=={{;","{}");
}

void initErrorsHashTable(HashTable hashArray)
{
	insertHash(hashArray, IDENTATION_ERROR, "There was an error in the identation", hashCode);
	insertHash(hashArray, FIND_MAIN, "Could not find a main", hashCode);
	insertHash(hashArray, SUCCES, "The code compiled succesfully", hashCode);
	insertHash(hashArray, SYNTAX_ERROR, "There was an error", hashCode);
	insertHash(hashArray, PROBLEM_OPERAND, "You had a problem in the condition", hashCode);
	insertHash(hashArray, WRONG_PARAMETER_NAME, "Could not create the variable", hashCode);
}

void initGraphsToUse(HashTable hashArray, graphPtr newGraph,HashTable newTable, int graphName)
{
	mapPtr map = (mapPtr)malloc(sizeof(map));
	map->graph = newGraph;
	map->hashArray = newTable;
	insertHash(hashArray, graphName, map, hashCode);
}

void initStartsCreatingVars(HashTable hashArray)
{
	insertHash(hashArray, 'i', 3, hashCode);
	insertHash(hashArray, 's', 2, hashCode);
	insertHash(hashArray, 'f', 9, hashCode);
	insertHash(hashArray, 'u', 0, hashCode);
}

void initStartsCondition(HashTable hashArray)
{
	insertHash(hashArray, '(', 3, hashCode);
	insertHash(hashArray, 's', 2, hashCode);
	insertHash(hashArray, 'f', 9, hashCode);
	insertHash(hashArray, 'u', 0, hashCode);
}


void initNumbersHash(HashTable hashArray)
{
	insertHash(hashArray, '0', '0', hashCode);
	insertHash(hashArray, '1', '1', hashCode);
	insertHash(hashArray, '2', '2', hashCode);
	insertHash(hashArray, '3', '3', hashCode);
	insertHash(hashArray, '4', '4', hashCode);
	insertHash(hashArray, '5', '5', hashCode);
	insertHash(hashArray, '6', '6', hashCode);
	insertHash(hashArray, '7', '7', hashCode);
	insertHash(hashArray, '8', '8', hashCode);
	insertHash(hashArray, '9', '9', hashCode);
}

void initStartsIfAndElse(HashTable hashArray)
{
	insertHash(hashArray, 'i', 0, hashCode);
	insertHash(hashArray, '}', 10, hashCode);
}

void initNewVarNameHashTable(HashTable hashArray)
{
	STRING starts = "abcdefghijknlmopqrstuvwxyz";
	char* ch = starts;
	for (; *ch != '\0'; ch++)
	{
		insertHash(hashArray, *ch, *ch, hashCode);
	}
}

Status variableGraphFunction(graphPtr gra, int *vertexIndex, FILE* source, HashTable graphsToUse, HashTable variables, Status status, char * newVar, char c)
{
	while (c == '\n' || c == ' ' || c == '	')
	{
		c = getc(source);
	}
	int index = getOffsetByVertexName(gra, VARIABLES_GRAPH, cmpStatus);
	if (*vertexIndex != -1 && index != -1 && gra->adjacentMat[*vertexIndex][index])
	{
		*vertexIndex = index;
		map* data = (map*)searchHash(graphsToUse, VARIABLES_GRAPH, hashCode)->data;
		index = getOffsetByVertexName(data->graph, searchHash(data->hashArray, c, hashCode)->data, cmpCharVrx);
		status = exploreAndCreateVars(data->graph, index, source, newVar);
		insertHash(variables, newVar, newVar, stringHashCode);
	}
	else
	{
		status = gra->verticesArr[gra->size - 1]->status;
	}

	return status;
}

Status numbersGraphFunction(graphPtr gra, int* vertexIndex, FILE* source, HashTable graphsToUse, HashTable variables, Status status, char* newVar, char c)
{
	while (c == '\n' || c == ' ' || c == '	')
	{
		c = getc(source);
	}
	int index = getOffsetByVertexName(gra, NUMBERS_GRAPH, cmpStatus);
	if (*vertexIndex != -1 && index != -1 && gra->adjacentMat[*vertexIndex][index])
	{
		*vertexIndex = index;
		map* data = (map*)searchHash(graphsToUse, NUMBERS_GRAPH, hashCode)->data;
		if (searchHash(data->hashArray, c, hashCode))
		{
			index = getOffsetByVertexName(data->graph, searchHash(data->hashArray, c, hashCode)->data, cmpCharVrx);
			status = exploreAndCreateVars(data->graph, index, source, newVar);
		}
	}
	else
	{
		status = gra->verticesArr[gra->size - 1]->status;
	}

	return status;
}

Status checkVariablesGraphFunction(graphPtr gra, int *vertexIndex, FILE* source, HashTable graphsToUse, HashTable variables, Status status, char* newVar, char c)
{
	fseek(source, -2L, SEEK_CUR);
	c = getc(source);
	while (c == '\n' || c == ' ' || c == '	')
	{
		c = getc(source);
	}
	int index = getOffsetByVertexName(gra, CHECK_VARIABLES_GRAPH, cmpStatus);
	if (*vertexIndex != -1 && index != -1 && gra->adjacentMat[*vertexIndex][index])
	{
		*vertexIndex = index;
		map* data = (map*)searchHash(graphsToUse, VARIABLES_GRAPH, hashCode)->data;
		DataItemPtr p = searchHash(data->hashArray, c, hashCode);
		if (p)
		{
			index = getOffsetByVertexName(data->graph, searchHash(data->hashArray, c, hashCode)->data, cmpCharVrx);
			status = exploreAndCreateVars(data->graph, index, source, newVar);
			if (!searchHash(variables, newVar, stringHashCode))
			{
				status = WRONG_PARAMETER_NAME;
			}
		}
		else
		{
			status = gra->verticesArr[gra->size - 1]->status;
		}
	}
	else
	{
		status = gra->verticesArr[gra->size - 1]->status;
	}

	return status;
}

Status conditionGraphFunction(graphPtr gra, int * vertexIndex, FILE* source, HashTable graphsToUse, HashTable variables, Status status, char* newVar, char c)
{
	while (c == '\n' || c == ' ' || c == '	')
	{
		c = getc(source);
	}
	int index = getOffsetByVertexName(gra, CONDITION_GRAPH, cmpStatus);
	if (*vertexIndex != -1 && index != -1 && gra->adjacentMat[*vertexIndex][index])
	{
		*vertexIndex = index;
		map* data = (map*)searchHash(graphsToUse, CONDITION_GRAPH, hashCode)->data;
		if (searchHash(data->hashArray, c, hashCode))
		{
			index = getOffsetByVertexName(data->graph, searchHash(data->hashArray, c, hashCode)->data, cmpCharVrx);
		}
		if (index == -1)
		{
			index = getOffsetByVertexName(data->graph, CONDITION_GRAPH, cmpStatus);
		}
		if (index == -1)
		{
			index = getOffsetByVertexName(data->graph, CHECK_VARIABLES_GRAPH, cmpStatus);
		}
		status = explore(data->graph, index, source, -1, graphsToUse, variables);
		fseek(source, -1L, SEEK_CUR);
	}
	else
	{
		status = gra->verticesArr[gra->size - 1]->status;
	}
}


Status explore(graphPtr gra, int vertexIndex, FILE* source, int expectedLength, HashTable graphsToUse, HashTable variables)
{
	Status status = SEARCHING;
	int length = 1;
	char c;
	STRING newVar = "";
	Status(*functions[NUMBERS_GRAPH - VARIABLES_GRAPH + 1])();
	functions[VARIABLES_GRAPH - VARIABLES_GRAPH] = variableGraphFunction;
	functions[CHECK_VARIABLES_GRAPH - VARIABLES_GRAPH] = checkVariablesGraphFunction;
	functions[CONDITION_GRAPH - VARIABLES_GRAPH] = conditionGraphFunction;
	functions[NUMBERS_GRAPH - VARIABLES_GRAPH] = numbersGraphFunction;

	while (status == SEARCHING && (c = getc(source)) != EOF)
	{
		while (c == '\n' || c == '	')
		{
			c = getc(source);
		}
		int index = getOffsetByVertexName(gra, c, cmpCharVrx);
		if (vertexIndex != -1 && index != -1 && gra->adjacentMat[vertexIndex][index])
		{
			vertexIndex = index;
			status = gra->verticesArr[index]->status;
		}
		else 
		{
			Status temp = PROBLEM_OPERAND;
			for (int i = VARIABLES_GRAPH; i <= NUMBERS_GRAPH && temp != SEARCHING && temp != SUCCES; i++)
			{
				int vert = vertexIndex;
				long place = ftell(source);
				temp = functions[i - VARIABLES_GRAPH](gra, &vertexIndex, source, graphsToUse, variables, status, newVar, c);
				status = temp == SUCCES ? SEARCHING : temp;
				status == SEARCHING || status == SUCCES ? NULL : fseek(source, place, SEEK_SET);
				vertexIndex = status == SEARCHING || status == SUCCES ? vertexIndex : vert;
			}
		}
		length += c == ' ' || c == '	' || c == '\n' ? 0 : 1;
	}
	
	if (length != expectedLength && expectedLength != -1)
	{
		status = gra->verticesArr[gra->size - 1]->status;
	}
	
	return status;
}

Status exploreAndCreateVars(graphPtr gra, int vertexIndex, FILE* source, char * newVar)
{
	Status status = SEARCHING;
	char c;
	int counter = 0;
	newVar[counter++] = (char)gra->verticesArr[vertexIndex]->value;
	while (status == SEARCHING && (c = getc(source)) != EOF)
	{
		int index = getOffsetByVertexName(gra, c, cmpCharVrx);
		if (vertexIndex != -1 && index != -1 && gra->adjacentMat[vertexIndex][index])
		{
			vertexIndex = index;
			status = gra->verticesArr[index]->status;
			newVar[counter++] = c;
		}
		else
		{
			status = gra->verticesArr[gra->size - 1]->status;
		}
	}

	fseek(source, -1L, SEEK_CUR);
	return SEARCHING;
}