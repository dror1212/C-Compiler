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
	graph graphArray[2];
	DataItemPtr * hashArray[2];
	Status status;

	initGraph(&mainGraph);
	initGraph(&createVarsGraph);
	initGraph(&ifAndElseGraph);
	initGraph(&variablesNamesGraph);
	initGraph(&numbersGraph);
	initGraph(&conditionGraph);

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

	initStartsIfAndElse(ifAndElseStarts);
	initStartsCreatingVars(creatingVarsStarts);
	initErrorsHashTable(errorsHashArray);
	initNewVarNameHashTable(newVariables);
	initNumbersHash(numbersStarts);
	initStartsCondition(conditionStarts);

	initGraphsToUse(graphsToUse, &variablesNamesGraph, newVariables,VARIABLES_GRAPH);
	initGraphsToUse(graphsToUse, &numbersGraph, numbersStarts, NUMBERS_GRAPH);
	initGraphsToUse(graphsToUse, &conditionGraph, conditionStarts, CONDITION_GRAPH);

	identationHelp[1] = 1;
	graphArray[0] = createVarsGraph;
	hashArray[0] = creatingVarsStarts;
	graphArray[1] = ifAndElseGraph;
	hashArray[1] = ifAndElseStarts;

	status = explore(&mainGraph, getOffsetByVertexName(&mainGraph, getc(file), cmpCharVrx),
					file, 15, graphsToUse,vars);

	while (status == SUCCES && identation >= 0 && (c = getc(file)) != EOF)
	{
		while (c == '\n' || c == ' ' || c == '	')
		{
			c = getc(file);
		}
		if (c == '}')
		{
			identation--;
		}
		else
		{
			Status statusTemp = SEARCHING;
			for (graphsCounter = 0; graphsCounter < length && statusTemp != SUCCES; graphsCounter++)
			{
				DataItemPtr data = searchHash(hashArray[graphsCounter], c, hashCode);
				if (data)
				{
					place = ftell(file);
					statusTemp = status = explore(&graphArray[graphsCounter], data->data, file, -1, graphsToUse,vars);
					status == SUCCES ? NULL : fseek(file, place, SEEK_SET);
					identation += status == SUCCES ? identationHelp[graphsCounter] : 0;
				}
				else
				{
					statusTemp = status = SYNTAX_ERROR;
				}
			}
		}
	}

	if ((status == SUCCES && identation >= 0))
	{
		status = IDENTATION_ERROR;
	}

	errorCode = status;
	fclose(file);
	printf("%s", (char *)searchHash(errorsHashArray, errorCode,hashCode)->data);

	freeGraph(&mainGraph);
	freeGraph(&ifAndElseGraph);
	freeGraph(&createVarsGraph);
	freeGraph(&variablesNamesGraph);
}