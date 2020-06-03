#include"graphAlg.h"
//----------------------------------------------------------------------------------------------
//                                        Graphs
//                                        ------
//
//
// General  :  This file consts of te basc meod for the graph inteeface
//
// Input  : no input
//
// Process  :  
//
// Output  :  depends on the method
//
//----------------------------------------------------------------------------------------------
// Programmer: Jonathan Roll
// Student's ID number: 322999343 
// Date : 2.1.2020
//----------------------------------------------------------------------------------------------
void initGraph(graphPtr g)
{
	g->adjacentMat = NULL;
	g->verticesArr = NULL;
	g->size = 0;
}


void addVertexToGraph(graphPtr g,vertexPtr vertex)
{
	int i;
	//adding vertex to arr
	g->verticesArr = (vertexPtr *)realloc(g->verticesArr, sizeof(void*)*(++(g->size)));
	g->verticesArr[g->size - 1] = vertex;

	//buliding the extra frame unit for the adjacent mat
	g->adjacentMat = (BOOLEAN **)realloc(g->adjacentMat,g->size *sizeof(void**));

	for ( i = 0; i < g->size-1; i++)
	{
		//adding the extra cell for each row in the adjacent mat and update them to False
		g->adjacentMat[i] = (BOOLEAN**)realloc(g->adjacentMat[i], sizeof(void*)*(g->size));
		g->adjacentMat[i][g->size - 1] = FALSE;
	}

	//by signle allocation adding the last row to the adjacent mat
	g->adjacentMat[g->size - 1] = (BOOLEAN**)calloc(g->size, sizeof(void*));
}


int getOffsetByVertexName(graphPtr g, void* name, int(*cmp)(void*, void*))
{
	int i;
	for (i = 0; i < g->size&&cmp(name, g->verticesArr[i]); i++);
	return (i < g->size) ? i : -1;
}


BOOLEAN joinEdgeToGraph(graphPtr g, void* vertexName1, void* vertexName2, BOOLEAN edge, int(*cmp)(void*, void*))
{
	BOOLEAN isOk=FALSE;
	int index1 = getOffsetByVertexName(g, vertexName1, cmp);
	int index2= getOffsetByVertexName(g, vertexName2, cmp);
	isOk = (BOOLEAN)((index1 != -1) && (index2 != -1) && (!g->adjacentMat[index1][index2]));
	if (isOk)
	{
		g->adjacentMat[index1][index2] = edge;
	}
	return isOk;
}


BOOLEAN removeEdgeFromGraph(graphPtr g, void*vertexName1, void*vertexName2,  int(*cmp)(void*, void*))
{
	BOOLEAN temp = FALSE;
	int index1 = getOffsetByVertexName(g, vertexName1, cmp);
	int index2 = getOffsetByVertexName(g, vertexName2, cmp);
	if (index1!=-1&&index2!=-1)
	{
		temp = g->adjacentMat[index1][index2];
		g->adjacentMat[index1][index2] = FALSE;
	}
	return temp;
}

void freeGraph(graphPtr graph)
{
	free(graph->adjacentMat);
	free(graph->verticesArr);
}