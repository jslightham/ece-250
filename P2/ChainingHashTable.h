#ifndef CHAININGHASHTABLE_H
#define CHAININGHASHTABLE_H

#include <vector>
#include "Process.h"
#include "HashTable.h"

class ChainingHashTable : public HashTable
{
public:
    bool Insert(Process *p);
    int Search(unsigned int PID);
    Process *Get(unsigned int PID);
    bool Remove(unsigned int PID);
    void Print(unsigned int m);

    ChainingHashTable(int size);
    ~ChainingHashTable();

private:
    std::vector<Process *> *processList;
};
#endif
