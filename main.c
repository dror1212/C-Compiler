#include "General.h"

void main()
{
	FILE* file = fopen("code.txt", "r");
	graph mainGraph;
	graph createVarsGraph;
	graph ifAndElseGraph;
	graph variablesNamesGraph;
	graph numbersGraph;
	graph conditionGraph;
	graph equalsGraph;
	HashTable errorsHashArray;
	HashTable newVariables;
	HashTable graphsToUse;
	HashTable creatingVarsStarts;
	HashTable ifAndElseStarts;
	HashTable vars;
	HashTable numbersStarts;
	HashTable conditionStarts;
	int identation = 0;
	char c;
	int length = 2;
	int identationHelp[2] = { 0 };
	int errorCode;
	int graphsCounter;
	long place;
	int lines = 0;
	graph graphArray[2];
	DataItemPtr * hashArray[2];
	Status status;
	LLLPtr first = malloc(sizeof(LLL));
	first->info = SEARCHING;
	LLLPtr* errorsList = &first;
	initLLL(errorsList);

	initGraph(&mainGraph);
	initGraph(&createVarsGraph);
	initGraph(&ifAndElseGraph);
	initGraph(&variablesNamesGraph);
	initGraph(&numbersGraph);
	initGraph(&conditionGraph);
	initGraph(&equalsGraph);

	initHash(creatingVarsStarts);
	initHash(ifAndElseStarts);
	initHash(graphsToUse);
	initHash(errorsHashArray);
	initHash(newVariables);
	initHash(vars);
	initHash(conditionStarts);
	initHash(numbersStarts);

	initMainGraph(&mainGraph);
	initCreateVariablesGraph(&createVarsGraph);
	initifAndElseGraph(&ifAndElseGraph);
	initNewVarNameGraph(&variablesNamesGraph);
	initNumbersGraph(&numbersGraph);
	initConditionGraph(&conditionGraph);
	initEqualsGraph(&equalsGraph);

	initStartsIfAndElse(ifAndElseStarts);
	initStartsCreatingVars(creatingVarsStarts);
	initErrorsHashTable(errorsHashArray);
	initNewVarNameHashTable(newVariables);
	initNumbersHash(numbersStarts);
	initStartsCondition(conditionStarts);

	initGraphsToUse(graphsToUse, &variablesNamesGraph, newVariables,VARIABLES_GRAPH);
	initGraphsToUse(graphsToUse, &numbersGraph, numbersStarts, NUMBERS_GRAPH);
	initGraphsToUse(graphsToUse, &conditionGraph, conditionStarts, CONDITION_GRAPH);

	identationHelp[0] = 1;
	graphArray[1] = createVarsGraph;
	hashArray[1] = creatingVarsStarts;
	graphArray[0] = ifAndElseGraph;
	hashArray[0] = ifAndElseStarts;

	status = explore(&mainGraph, getc(file),
					file, 15, graphsToUse,vars,&lines);
	if (status != SUCCES)
	{
		insertAfter(first);
		errorPtr errPtr = malloc(sizeof(error));
		errPtr->line = lines;
		errPtr->status = status;
		first->next->info = errPtr;
		findNextPartOfCode(file, &c, &lines, &identation);
		status = SUCCES;
	}
	Status err = SYNTAX_ERROR;

	while (identation >= 0 && (c = getc(file)) != EOF)
	{
		strip(file, &c,&lines);
		Status statusTemp = SEARCHING;
		int max = 0;
		err = SYNTAX_ERROR;
		for (graphsCounter = 0; graphsCounter < length && statusTemp != SUCCES; graphsCounter++)
		{
			DataItemPtr data = searchHash(hashArray[graphsCounter], c, hashCode);
			if (data)
			{
				place = ftell(file);
				statusTemp = status = explore(&graphArray[graphsCounter], data->key, file, -1, graphsToUse, vars, &lines);
				if (ftell(file) - place > max && status > SUCCES)
				{
					max = ftell(file) - place;
					err = status;
				}
				status == SUCCES ? NULL : fseek(file, place, SEEK_SET);
				identation += status == SUCCES ? identationHelp[graphsCounter] : 0;
			}
			else
			{
				status = err;
			}
		}
		identation -= (c / '}' == 1) && (c % '}' == 0);
		if (status > SUCCES)
		{
			place = ftell(file);
			c == '}' ? c = getc(file) : fseek(file, -1L, SEEK_CUR);
			place = ftell(file);
			//fseek(file, -1L, SEEK_CUR);
			status = explore(&equalsGraph, 0, file, -1, graphsToUse, vars, &lines);
			if (ftell(file) - place > max && statusTemp != SUCCES)
			{
				max = ftell(file) - place;
				err = status;
			}
			status == SUCCES ? NULL : fseek(file, place, SEEK_SET);
		}
		if (status > SUCCES && max > 0 && identation != -1)
		{
			insertAfter(first);
			errorPtr errPtr = malloc(sizeof(error));
			errPtr->line = lines;
			errPtr->status = err;
			first->next->info = errPtr;
			findNextPartOfCode(file, &c, &lines, &identation);
			status = SUCCES;
		}
		status = SUCCES;
	}
	//identation -= (c / '}' == 1) && (c % '}' == 0);
	status = err = ((status == SUCCES) && (identation != -1)) ? IDENTATION_ERROR : SUCCES;
	if (status != SUCCES)
	{
		insertAfter(first);
		errorPtr errPtr = malloc(sizeof(error));
		errPtr->line = lines;
		errPtr->status = err;
		first->next->info = errPtr;
		findNextPartOfCode(file, &c, &lines, &identation);
		status = SUCCES;
	}
	status = err = ((status == SUCCES) && ((getc(file)) != EOF)) ? CODE_AFTER_MAIN : SUCCES;
	if (status != SUCCES)
	{
		insertAfter(first);
		errorPtr errPtr = malloc(sizeof(error));
		errPtr->line = lines;
		errPtr->status = err;
		first->next->info = errPtr;
		findNextPartOfCode(file, &c, &lines, &identation);
		status = SUCCES;
	}

	c = getc(file);

	strip(file, &c, &lines);

	err = status = ((status == SUCCES) && ((getc(file)) != EOF)) ? CODE_AFTER_MAIN : SUCCES;
	if (status != SUCCES)
	{
		insertAfter(first);
		errorPtr errPtr = malloc(sizeof(error));
		errPtr->line = lines;
		errPtr->status = err;
		first->next->info = errPtr;
		findNextPartOfCode(file, &c, &lines, &identation);
		status = SUCCES;
	}

	errorCode = status;

	fclose(file);
	showAllErrors(first->next, errorsHashArray);


	freeGraph(&mainGraph);
	freeGraph(&ifAndElseGraph);
	freeGraph(&createVarsGraph);
	freeGraph(&variablesNamesGraph);
	freeGraph(&numbersGraph);
	freeGraph(&conditionGraph);
}

void takeSource(FILE* file, char* source)
{
	if (file != NULL) {
		/* Go to the end of the file. */
		if (fseek(file, 0L, SEEK_END) == 0) {
			/* Get the size of the file. */
			long bufsize = ftell(file);
			if (bufsize == -1) { /* Error */ }

			/* Allocate our buffer to that size. */
			source = malloc(sizeof(char) * (bufsize + 1));

			/* Go back to the start of the file. */
			if (fseek(file, 0L, SEEK_SET) != 0) { /* Error */ }

			/* Read the entire file into memory. */
			size_t newLen = fread(source, sizeof(char), bufsize, file);
			if (ferror(file) != 0) {
				fputs("Error reading file", stderr);
			}
			else {
				source[++newLen] = '\0'; /* Just to be safe. */
			}
		}
		//fclose(file);
	}
	fseek(file, 0, SEEK_SET);
}