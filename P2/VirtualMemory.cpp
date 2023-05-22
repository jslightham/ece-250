#include <iostream>

#include "VirtualMemory.h"
#include "ChainingHashTable.h"
#include "DoubleHashTable.h"

VirtualMemory::VirtualMemory(int n, int p, bool chaining)
{
    if (chaining)
    {
        ht = new ChainingHashTable(n / p);
    }
    else
    {
        ht = new DoubleHashTable(n / p);
    }

    this->chaining = chaining;
    this->memorySize = n;
    this->pageSize = p;
    this->memory = new int[n];

    // push the indices onto the free memory
    for (int i = 0; i < n / p; i++)
    {
        freeMemory.push_back(i);
    }
}

VirtualMemory::~VirtualMemory()
{
    if (chaining)
    {
        delete (ChainingHashTable *)ht;
    }
    else
    {
        delete (DoubleHashTable *)ht;
    }

    delete[] memory;
}

/// @brief Allocate memory for process PID
/// @param PID the PID to allocate memory for
/// @return true if successful, false otherwise
bool VirtualMemory::Insert(unsigned int PID)
{
    if (freeMemory.size() <= 0)
        return false;

    int memoryIndex = freeMemory.back();
    freeMemory.pop_back();

    Process *p = new Process(PID, memoryIndex);
    if (!ht->Insert(p))
    {
        delete p;
        freeMemory.push_back(memoryIndex);
        return false;
    }

    return true;
}

/// @brief Search the hash table for the index of PID
/// @param PID the PID of the process to search for
/// @return the index of the process object, -1 if the object does not exist
int VirtualMemory::Search(unsigned int PID)
{
    return ht->Search(PID);
}

/// @brief Write to a process's memory
/// @param PID The PID of the memory to write to
/// @param addr The virtual address of the memory to write to
/// @param x The value to write into memory
/// @return true if successful, false otherwise
bool VirtualMemory::Write(unsigned int PID, int addr, int x)
{
    if (addr >= pageSize || addr < 0)
        return false;

    Process *p = ht->Get(PID);

    // if we do not have any memory allocated to PID
    if (p == nullptr)
        return false;

    memory[p->getStartingIndex() * pageSize + addr] = x;
    return true;
}

/// @brief Read the memory
/// @param PID The PID of the process to read memory of
/// @param addr The virtual address of memory to read from
void VirtualMemory::Read(unsigned int PID, int addr)
{
    if (addr >= pageSize)
    {
        std::cout << "failure" << std::endl;
        return;
    }

    Process *p = ht->Get(PID);
    // if we do not have any memory allocated to PID
    if (p == nullptr)
    {
        std::cout << "failure" << std::endl;
        return;
    }

    std::cout << addr << " " << memory[p->getStartingIndex() * pageSize + addr] << std::endl;
}

/// @brief Deallocate memory from process PID.
/// @param PID The PID of the process to dealocate memory from
/// @return true if successful, false otherwise
bool VirtualMemory::Delete(unsigned int PID)
{
    Process *p = ht->Get(PID);

    if (p == nullptr)
        return false;

    freeMemory.push_back(p->getStartingIndex());

    return ht->Remove(PID);
}

/// @brief Print the chain of the hash table at index m
/// @param m the index of the chain to print
void VirtualMemory::Print(int m)
{
    ht->Print(m);
}
