#ifndef VIRTUALMEMORY_H
#define VIRTUALMEMORY_H

#include "Process.h"
#include "HashTable.h"

class VirtualMemory
{
public:
    VirtualMemory(int n, int p, bool chaining);
    ~VirtualMemory();

    bool Insert(unsigned int PID);
    int Search(unsigned int PID);

    bool Write(unsigned int PID, int addr, int x);
    void Read(unsigned int PID, int addr);

    bool Delete(unsigned int PID);
    void Print(int m);

private:
    HashTable *ht;
    int memorySize;
    int pageSize;
    int *memory;
    std::vector<int> freeMemory;
    bool chaining;
};
#endif
