#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include "Process.h"

class HashTable
{
public:
    virtual bool Insert(Process *p) = 0;
    virtual int Search(unsigned int PID) = 0;
    virtual Process *Get(unsigned int PID) = 0;
    virtual bool Remove(unsigned int PID) = 0;
    virtual void Print(unsigned int m) = 0;

protected:
    int maxCount;
    int count;
};
#endif
