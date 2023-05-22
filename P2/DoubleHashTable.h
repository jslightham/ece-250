#ifndef DOUBLEHASHTABLE_H
#define DOUBLEHASHTABLE_H

#include <vector>
#include "Process.h"
#include "HashTable.h"

class DoubleHashTable : public HashTable
{
public:
    bool Insert(Process *p);
    int Search(unsigned int PID);
    Process *Get(unsigned int PID);
    bool Remove(unsigned int PID);
    void Print(unsigned int m);

    DoubleHashTable(int size);
    ~DoubleHashTable();

private:
    Process **processList;
    int HashIndex(unsigned int k, int i);
};
#endif
