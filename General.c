#pragma once

#include "General.h"

//----------------------------------------------------------------------
//                            cmpNameVrx
//                          -------------
//
// General      : This function compares between two vertexes.
//
// Parameters   : 
//			val1 - The first vertex
//			val2 - The second vertex
//
// Return Value : Are they equals
//
//----------------------------------------------------------------------
int cmpNameVrx(void* val1, void* val2)
{
	return (char)((vertexPtr)val1)->value - (char)((vertexPtr)val2)->value;
}

//----------------------------------------------------------------------
//                            cmpCharVrx
//                          -------------
//
// General      : This function compares between two vertexes.
//
// Parameters   : 
//			val1 - The first vertex
//			val2 - The second vertex
//
// Return Value : Are they equals
//
//----------------------------------------------------------------------
int cmpCharVrx(void* val1, void* val2)
{
	return ((char)val1 - (char)((vertexPtr)val2)->value);
}

//----------------------------------------------------------------------
//                            cmpStatus
//                          -------------
//
// General      : This function compares between two vertexes.
//
// Parameters   : 
//			val1 - The first vertex
//			val2 - The second vertex
//
// Return Value : Are they equals
//
//----------------------------------------------------------------------
int cmpStatus(void* val1, void* val2)
{
	return ((int)val1 - ((vertexPtr)val2)->status);
}

//----------------------------------------------------------------------
//                            hashCode
//                          ------------
//
// General      : This function do hash for simple values.
//
// Parameters   : 
//			key - The value for the hash
//
// Return Value : The hash key.
//
//----------------------------------------------------------------------
int hashCode(void* key)
{
	return (Status)key % HASH_TABLE_SIZE;
}

//----------------------------------------------------------------------
//                            stringHashCode
//                          ------------------
//
// General      : This function do hash for strings.
//
// Parameters   : 
//			str - The string
//
// Return Value : The hash key.
//
//----------------------------------------------------------------------
int stringHashCode(char* str)
{
	unsigned char hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % HASH_TABLE_SIZE;
}

//----------------------------------------------------------------------
//                            initMyGraph
//                          ----------------
//
// General      : Creates a graph.
//
// Parameters   : 
//			graph - The graph
//			statuses - The statuses 
//			vertexes - The vertexex values
//			graphs - Temp value
//			err - The errors for this graph
//
// Return Value : void
//
//----------------------------------------------------------------------
void initMyGraph(graphPtr graph, int* statuses, char* vertexes, char* graphs, Status err)
{
	vertexPtr vert;
	int firstOffset;
	int secondOffset;
	int counter = 0;
	int arr[260];

	for (int i = 0; i < 260; i++)
	{
		vert = (vertexPtr)malloc(sizeof(vertex));
		vert->value = i;
		vert->status = err;
		addVertexToGraph(graph, vert);
		arr[i] = i;
	}

	while (*vertexes != '\0')
	{
		firstOffset = arr[*vertexes];
		if (graph->verticesArr[firstOffset]->status == err)
		{
			if (statuses[counter] >= VARIABLES_GRAPH && statuses[counter] <= CONDITION_GRAPH)
			{
				graph->verticesArr[256 + statuses[counter] - VARIABLES_GRAPH]->status = statuses[counter];
				graph->verticesArr[256 + statuses[counter] - VARIABLES_GRAPH]->value = statuses[counter];
				firstOffset = 256 + statuses[counter] - VARIABLES_GRAPH;
				arr[*vertexes] = 256 + statuses[counter] - VARIABLES_GRAPH;
			}
			else
			{
				graph->verticesArr[firstOffset]->status = statuses[counter];
			}
			counter++;
		}
		vertexes++;
		secondOffset = arr[*vertexes];
		if (graph->verticesArr[secondOffset]->status == err)
		{
			if (statuses[counter] >= VARIABLES_GRAPH && statuses[counter] <= CONDITION_GRAPH)
			{
				graph->verticesArr[256 + statuses[counter] - VARIABLES_GRAPH]->status = statuses[counter];
				graph->verticesArr[256 + statuses[counter] - VARIABLES_GRAPH]->value = statuses[counter];
				secondOffset = 256 + statuses[counter] - VARIABLES_GRAPH;
				arr[*vertexes] = 256 + statuses[counter] - VARIABLES_GRAPH;
			}
			else
			{
				graph->verticesArr[secondOffset]->status = statuses[counter];
			}
			counter++;
		}
		vertexes++;

		graph->adjacentMat[firstOffset][secondOffset] = TRUE;
	}

	vert = (vertexPtr)malloc(sizeof(vertex));
	vert->value = NULL;
	vert->status = err;
	addVertexToGraph(graph, vert);
}

//----------------------------------------------------------------------
//                            initMainGraph
//                          ----------------
//
// General      : Creates the main graph.
//
// Parameters   : 
//			graph - The graph
//
// Return Value : void
//
//----------------------------------------------------------------------
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
	initMyGraph(graph, statuses, "vooiidd    mmaaiinn(n  ((vd)){","", FIND_MAIN);
}

//----------------------------------------------------------------------
//                            initifAndElseGraph
//                          ----------------------
//
// General      : Creates the if and else graph.
//
// Parameters   : 
//			graph - The graph
//
// Return Value : void
//
//----------------------------------------------------------------------
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
	initMyGraph(graph, statuses, "iff f( (ellssee  i(!!)e{){ {)   }e}  i e", "!", PROBLEM_OPERAND);
}

//----------------------------------------------------------------------
//                            initConditionGraph
//                          ----------------------
//
// General      : Creates the condition graph.
//
// Parameters   : 
//			graph - The graph
//
// Return Value : void
//
//----------------------------------------------------------------------
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
	initMyGraph(graph, statuses, "{)}){ }    ) + - * / % < > = | &<=>===&&||+{-{*{/{%{={|{&{+}-}*}/}%}=}|}&}(?{){+{-{*{/{%{<{>{={|{&})}+}-}*}/}%}<}>}=}|}&", "{}?", PROBLEM_OPERAND);
}

//----------------------------------------------------------------------
//                            initNewVarNameGraph
//                          ----------------------
//
// General      : Creates the new vars graph.
//
// Parameters   : 
//			graph - The graph
//
// Return Value : void
//
//----------------------------------------------------------------------
void initNewVarNameGraph(graphPtr graph)
{
	Status statuses[37] = { SEARCHING };
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
	initMyGraph(graph, statuses, vertexes,"", WRONG_PARAMETER_NAME);
}

//----------------------------------------------------------------------
//                            initNumbersGraph
//                          --------------------
//
// General      : Creates the numbers graph.
//
// Parameters   : 
//			graph - The graph
//
// Return Value : void
//
//----------------------------------------------------------------------
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
	initMyGraph(graph, statuses, vertexes, "", NOT_PART_OF_NUMBER);
}

//----------------------------------------------------------------------
//                            initEqualsGraph
//                          -------------------
//
// General      : Creates the equals graph.
//
// Parameters   : 
//			graph - The graph
//
// Return Value : void
//
//----------------------------------------------------------------------
void initEqualsGraph(graphPtr graph)
{
	Status statuses[6] = { SEARCHING,CHECK_VARIABLES_GRAPH,SEARCHING, SUCCES,NUMBERS_GRAPH, SYNTAX_ERROR};
	// edges:

	initMyGraph(graph, statuses, "   }}==}}; == =? ?? ?;} =}", "}?", PROBLEM_IN_PLACEMENT);
}

//----------------------------------------------------------------------
//                        initCreateVariablesGraph
//                          -------------------
//
// General      : Creates the create variables graph.
//
// Parameters   : 
//			graph - The graph
//
// Return Value : void
//
//----------------------------------------------------------------------
void initCreateVariablesGraph(graphPtr graph)
{
	Status statuses[18] = { SEARCHING };
	statuses[17] = WRONG_PARAMETER_NAME;
	statuses[16] = SUCCES;
	statuses[15] = VARIABLES_GRAPH;
	initMyGraph(graph, statuses, "unnssiiggnneedd    iinnt ffllooaatt  sshhoorrt }};", "}", WRONG_PARAMETER_NAME);
}

//----------------------------------------------------------------------
//							initErrorsHashTable
//                          -------------------
//
// General      : Creates the errors hash table.
//
// Parameters   : 
//			hashArray - The hash table
//
// Return Value : void
//
//----------------------------------------------------------------------
void initErrorsHashTable(HashTable hashArray)
{
	insertHash(hashArray, IDENTATION_ERROR, "There was an error in the identation", hashCode);
	insertHash(hashArray, FIND_MAIN, "Could not find a main", hashCode);
	insertHash(hashArray, SUCCES, "The code compiled succesfully", hashCode);
	insertHash(hashArray, SYNTAX_ERROR, "There was an error", hashCode);
	insertHash(hashArray, PROBLEM_OPERAND, "You had a problem in the condition", hashCode);
	insertHash(hashArray, WRONG_PARAMETER_NAME, "Could not create the variable", hashCode);
	insertHash(hashArray, CODE_AFTER_MAIN, "There is unreadable code outside the main", hashCode);
	insertHash(hashArray, PROBLEM_IN_PLACEMENT, "There was an error while trying to place a new value to var", hashCode);
}

//----------------------------------------------------------------------
//							initGraphsToUse
//                          ----------------
//
// General      : Add value to the graphs to use hash table.
//
// Parameters   : 
//			hashArray - The hash table
//			newGraph - The graph to add
//			newTable - the graph's hash table
//			graphName - The value that represents the graph
//
// Return Value : void
//
//----------------------------------------------------------------------
void initGraphsToUse(HashTable hashArray, graphPtr newGraph,HashTable newTable, int graphName)
{
	mapPtr map = (mapPtr)malloc(sizeof(map));
	map->graph = newGraph;
	map->hashArray = newTable;
	insertHash(hashArray, graphName, map, hashCode);
}

//----------------------------------------------------------------------
//							initStartsCreatingVars
//                          ----------------------
//
// General      : Creates the creating vars hash table.
//
// Parameters   : 
//			hashArray - The hash table
//
// Return Value : void
//
//----------------------------------------------------------------------
void initStartsCreatingVars(HashTable hashArray)
{
	insertHash(hashArray, 'i', 3, hashCode);
	insertHash(hashArray, 's', 2, hashCode);
	insertHash(hashArray, 'f', 9, hashCode);
	insertHash(hashArray, 'u', 0, hashCode);
}

//----------------------------------------------------------------------
//							initStartsCondition
//                          --------------------
//
// General      : Creates the condition hash table.
//
// Parameters   : 
//			hashArray - The hash table
//
// Return Value : void
//
//----------------------------------------------------------------------
void initStartsCondition(HashTable hashArray)
{
	insertHash(hashArray, '(', 3, hashCode);
}

//----------------------------------------------------------------------
//							initNumbersHash
//                          ----------------
//
// General      : Creates the numbers hash table.
//
// Parameters   : 
//			hashArray - The hash table
//
// Return Value : void
//
//----------------------------------------------------------------------
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

//----------------------------------------------------------------------
//							initStartsIfAndElse
//                          -------------------
//
// General      : Creates the if and else hash table.
//
// Parameters   : 
//			hashArray - The hash table
//
// Return Value : void
//
//----------------------------------------------------------------------
void initStartsIfAndElse(HashTable hashArray)
{
	insertHash(hashArray, 'i', 0, hashCode);
	insertHash(hashArray, '}', 10, hashCode);
}

//----------------------------------------------------------------------
//							initNewVarNameHashTable
//                          -----------------------
//
// General      : Creates the new var names hash table.
//
// Parameters   : 
//			hashArray - The hash table
//
// Return Value : void
//
//----------------------------------------------------------------------
void initNewVarNameHashTable(HashTable hashArray)
{
	STRING starts = "abcdefghijknlmopqrstuvwxyz";
	char* ch = starts;
	for (; *ch != '\0'; ch++)
	{
		insertHash(hashArray, *ch, *ch, hashCode);
	}
}

//----------------------------------------------------------------------
//							variableGraphFunction
//                          ----------------------
//
// General      : Exploring the var names graph.
//
// Parameters   : 
//
// Return Value : status
//
//----------------------------------------------------------------------
Status variableGraphFunction(graphPtr gra, int *vertexIndex, FILE* source, HashTable graphsToUse, HashTable variables, Status status, char * newVar, char c, int * line)
{
	strip(source, &c, line);

	int index = 256 + VARIABLES_GRAPH - VARIABLES_GRAPH;
	if (gra->adjacentMat[*vertexIndex][index])
	{
		*vertexIndex = index;
		map* data = (map*)searchHash(graphsToUse, VARIABLES_GRAPH, hashCode)->data;
		if (data && searchHash(data->hashArray, c, hashCode))
		{
			status = exploreAndCreateVars(data->graph, c, source, newVar);
			insertHash(variables, newVar, newVar, stringHashCode);
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

//----------------------------------------------------------------------
//							numbersGraphFunction
//                          ----------------------
//
// General      : Exploring the numbers graph.
//
// Parameters   : 
//
// Return Value : status
//
//----------------------------------------------------------------------
Status numbersGraphFunction(graphPtr gra, int* vertexIndex, FILE* source, HashTable graphsToUse, HashTable variables, Status status, char* newVar, char c, int * line)
{
	strip(source, &c,line);

	int index = 256 + NUMBERS_GRAPH - VARIABLES_GRAPH;
	if (index != -1 && gra->adjacentMat[*vertexIndex][index])
	{
		*vertexIndex = index;
		map* data = (map*)searchHash(graphsToUse, NUMBERS_GRAPH, hashCode)->data;
		if (searchHash(data->hashArray, c, hashCode))
		{
			status = exploreAndCreateVars(data->graph, index, source, newVar);
		}
	}
	else
	{
		status = gra->verticesArr[gra->size - 1]->status;
	}

	return status;
}


//----------------------------------------------------------------------
//						  checkVariablesGraphFunction
//                          ----------------------
//
// General      : Exploring the check variables graph.
//
// Parameters   : 
//
// Return Value : status
//
//----------------------------------------------------------------------
Status checkVariablesGraphFunction(graphPtr gra, int *vertexIndex, FILE* source, HashTable graphsToUse, HashTable variables, Status status, char* newVar, char c, int * line)
{
	strip(source, &c, line);
	if (c >= 'a' && c <= 'z')
	{
		fseek(source, -2L, SEEK_CUR);
		c = getc(source);
		while (c == '\n' || c == ' ' || c == '	' || (c > 'z' || c < 'a'))
		{
			*line += c == '\n';
			c = getc(source);
		}
		int index = getOffsetByVertexName(gra, CHECK_VARIABLES_GRAPH, cmpStatus);
		if (*vertexIndex != -1 && index != -1)
		{
			*vertexIndex = index;
			map* data = (map*)searchHash(graphsToUse, VARIABLES_GRAPH, hashCode)->data;
			DataItemPtr p = searchHash(data->hashArray, c, hashCode);
			if (p)
			{
				index = getOffsetByVertexName(data->graph, searchHash(data->hashArray, c, hashCode)->data, cmpCharVrx);
				status = exploreAndCreateVars(data->graph, index, source, newVar);

				status = !searchHash(variables, newVar, stringHashCode) ? WRONG_PARAMETER_NAME : status;
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
	}
	else
	{
		status = gra->verticesArr[gra->size - 1]->status;
	}
	return status;
}

//----------------------------------------------------------------------
//							conditionGraphFunction
//                          ----------------------
//
// General      : Exploring the condition graph.
//
// Parameters   : 
//
// Return Value : status
//
//----------------------------------------------------------------------
Status conditionGraphFunction(graphPtr gra, int * vertexIndex, FILE* source, HashTable graphsToUse, HashTable variables, Status status, char* newVar, char c, int * line)
{
	strip(source, &c, line);
	int index = 256 + CONDITION_GRAPH - VARIABLES_GRAPH;
	if (gra->adjacentMat[*vertexIndex][index])
	{
		*vertexIndex = index;
		map* data = (map*)searchHash(graphsToUse, CONDITION_GRAPH, hashCode)->data;
		status = explore(data->graph, index, source, -1, graphsToUse, variables, line);
		fseek(source, -1L, SEEK_CUR);
	}
	else
	{
		status = gra->verticesArr[c]->status;
	}

	return status;
}

//----------------------------------------------------------------------
//								explore
//							   ---------
//
// General      : Exploring the graphs to find the code meanings.
//
// Parameters   : 
//
// Return Value : status
//
//----------------------------------------------------------------------
Status explore(graphPtr gra, int vertexIndex, FILE* source, int expectedLength, HashTable graphsToUse, HashTable variables, int * line)
{
	Status status = SEARCHING;
	int length = 1;
	char c;
	STRING newVar = "";
	Status(*functions[CONDITION_GRAPH - VARIABLES_GRAPH + 1])();
	functions[VARIABLES_GRAPH - VARIABLES_GRAPH] = variableGraphFunction;
	functions[CHECK_VARIABLES_GRAPH - VARIABLES_GRAPH] = checkVariablesGraphFunction;
	functions[CONDITION_GRAPH - VARIABLES_GRAPH] = conditionGraphFunction;
	functions[NUMBERS_GRAPH - VARIABLES_GRAPH] = numbersGraphFunction;
	while (status == SEARCHING && (c = getc(source)) != EOF)
	{
		partStrip(source, &c, line);
		if (gra->adjacentMat[vertexIndex][c])
		{
			vertexIndex = c;
			status = gra->verticesArr[c]->status;
		}
		else
		{
			Status temp = PROBLEM_OPERAND;
			for (int i = VARIABLES_GRAPH; i <= CONDITION_GRAPH && temp != SEARCHING && temp != SUCCES; i++)
			{
				int vert = vertexIndex;
				long place = ftell(source);
				temp = functions[i - VARIABLES_GRAPH](gra, &vertexIndex, source, graphsToUse, variables, status, newVar, c, line);
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

//----------------------------------------------------------------------
//								exploreAndCreateVars
//							   ----------------------
//
// General      : Exploring the graphs to find the code meanings to create var.
//
// Parameters   : 
//
// Return Value : status
//
//----------------------------------------------------------------------
Status exploreAndCreateVars(graphPtr gra, int vertexIndex, FILE* source, char * newVar)
{
	Status status = SEARCHING;
	char c;
	int counter = 0;
	newVar[counter++] = (char)gra->verticesArr[vertexIndex]->value;
	while (status == SEARCHING && (c = getc(source)) != EOF)
	{
		vertexIndex = c;
		status = gra->verticesArr[c]->status;
		newVar[counter++] = c;
	}
	newVar[--counter] = '\0';
	fseek(source, -1L, SEEK_CUR);
	return SEARCHING;
}

void strip(FILE* file, char* c, int * line)
{
	while (*c == '\n' || *c == ' ' || *c == '	')
	{
		*line += *c == '\n';
		*c = getc(file);
	}
}

void partStrip(FILE* file, char* c, int * line)
{
	while (*c == '\n' || *c == '	')
	{
		*line += *c == '\n';
		*c = getc(file);
	}
}

//----------------------------------------------------------------------
//								findNextPartOfCode
//							   --------------------
//
// General      : Find the next part of code after an error
//
// Parameters   : 
//
// Return Value : status
//
//----------------------------------------------------------------------
void findNextPartOfCode(FILE* file, char* c, int* line, int * identation)
{
	while (*c != ';')
	{
		*line += *c == '\n';
		*identation -= *c == '}';
		*identation += *c == '{';
		if ((*c = getc(file)) == EOF)
		{
			break;
		}
	}
}

//----------------------------------------------------------------------
//								showAllErrors
//							   ---------------
//
// General      : Show all the errors from the list
//
// Parameters   : 
//
// Return Value : status
//
//----------------------------------------------------------------------
void showAllErrors(LLLPtr list, HashTable errorsHashArray)
{
	if (list != NULL)
	{
		if (list->next != NULL)
		{
			showAllErrors(list->next, errorsHashArray);
		}
		printf("\n%s on line %d.", (char*)searchHash(errorsHashArray, ((errorPtr)(list->info))->status, hashCode)->data, ((errorPtr)(list->info))->line);
	}
	else
	{
		printf("\n%s", (char*)searchHash(errorsHashArray, SUCCES, hashCode)->data);
	}
}

void checkError(int* status, LLLPtr first, int* lines, int err, FILE* file, char* c, int* identation)
{
	if (*status > SUCCES)
	{
		insertAfter(first);
		errorPtr errPtr = malloc(sizeof(error));
		errPtr->line = *lines;
		errPtr->status = err;
		first->next->info = errPtr;
		findNextPartOfCode(file, c, lines, identation);
		*status = SUCCES;
	}
}