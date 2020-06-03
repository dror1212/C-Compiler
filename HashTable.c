#pragma once
#include "HashTables.h"

DataItemPtr searchHash(DataItemPtr* hashArray, void* key, int(*hashCode)(void*))
{
    //get the hash 
    int hashOffset = hashCode(key);
    DataItemPtr temp = NULL;

    // check if the key exists
    if (hashArray[hashOffset] != NULL) 
    {
        temp = hashArray[hashOffset];
    }

    return temp;
}

void initHash(HashTable hashArray)
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hashArray[i] = NULL;
    }
}

void insertHash(DataItemPtr* hashArray, void* key, void* data, int(*hashCode)(void*))
{
    DataItemPtr item = (DataItemPtr)malloc(sizeof(DataItem));
    item->data = data;
    item->key = key;

    //get the hash 
    int hashIndex = hashCode(key);
    hashArray[hashIndex] = item;
}

DataItemPtr deleteHash(DataItemPtr* hashArray, DataItemPtr item)
{
    int key = item->key;

    //get the hash 
    int hashIndex = hashCode(key);

    if ((*hashArray + hashIndex)->key == key)
    {
        DataItemPtr temp = (hashArray + hashIndex);

        //assign a dummy item at deleted position
        hashArray[hashIndex] = NULL;
        return temp;
    }
    return NULL;
}

void displayHash(DataItemPtr* hashArray)
{
    int i = 0;

    for (i = 0; i < HASH_TABLE_SIZE; i++) {

        if (hashArray[i] != NULL)
            printf(" (%s)", (char *)hashArray[i]->data);
        else
            printf(" ~~ ");
    }

    printf("\n");
}