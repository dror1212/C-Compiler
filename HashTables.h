#pragma once

#ifndef _HASH
#define _HASH
#include "graphAlg.h"

#define HASH_TABLE_SIZE 450

typedef struct DataItem {
    void* data;
    void* key;
}DataItem, * DataItemPtr, *** HashTableArray;

typedef DataItemPtr HashTable[HASH_TABLE_SIZE];

DataItemPtr searchHash(DataItemPtr*, void *, int(*)(void*));
void insertHash(DataItemPtr* hashArray, void* key, void* data, int(*)(void*));
DataItemPtr deleteHash(DataItemPtr* hashArray, DataItemPtr item);
void displayHash(DataItemPtr* hashArray);
void initHash(HashTable hashArray);

#endif // !_HASH
