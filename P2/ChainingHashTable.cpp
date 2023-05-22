#include <iostream>

#include "ChainingHashTable.h"
#include "Process.h"

ChainingHashTable::ChainingHashTable(int size)
{
    processList = new std::vector<Process *>[size];
    maxCount = size;
    count = 0;
}

ChainingHashTable::~ChainingHashTable()
{
    for (int i = 0; i < maxCount; i++)
    {
        for (int j = 0; j < processList[i].size(); j++)
        {
            delete processList[i][j];
        }
    }

    delete[] processList;
}

/// @brief Insert a process into the hash table
/// @param p the process to insert
/// @return true if insertion was successful, false otherwise
bool ChainingHashTable::Insert(Process *p)
{
    if (count >= maxCount)
    {
        return false;
    }

    int hashedIndex = p->getPid() % maxCount;

    int indexSize = processList[hashedIndex].size();

    if (indexSize == 0)
    {
        processList[hashedIndex].emplace_back(p);
        count++;
        return true;
    }

    // attempt to insert in the middle of the vector
    for (int i = 0; i < indexSize; i++)
    {
        if (processList[hashedIndex][i]->getPid() == p->getPid())
        {
            return false;
        }
        // store in descending order (9, 8, 7,...)
        if (processList[hashedIndex][i]->getPid() < p->getPid())
        {
            processList[hashedIndex].insert(processList[hashedIndex].begin() + i, p);
            count++;
            return true;
        }
    }

    // insert at the end of the vector if we have to
    processList[hashedIndex].emplace_back(p);
    return true;
}

/// @brief Search the hash table for the PID
/// @param PID the PID to search the hash table for
/// @return the index if in the hash table, or -1 otherwise
int ChainingHashTable::Search(unsigned int PID)
{
    int hashedIndex = PID % maxCount;

    int indexSize = processList[hashedIndex].size();

    for (int i = 0; i < indexSize; i++)
    {
        if (processList[hashedIndex][i]->getPid() == PID)
        {
            return hashedIndex;
        }
    }

    return -1;
}

/// @brief Get a pointer to the process with PID
/// @param PID the PID to look for
/// @return a pointer to the process, or nullptr if the process does not exist
Process *ChainingHashTable::Get(unsigned int PID)
{
    int hashedIndex = PID % maxCount;

    int indexSize = processList[hashedIndex].size();

    for (int i = 0; i < indexSize; i++)
    {
        if (processList[hashedIndex][i]->getPid() == PID)
        {
            return processList[hashedIndex][i];
        }
    }

    return nullptr;
}

/// @brief Remove a process from the hash table with a given PID
/// @param PID the PID of the process to remove
/// @return true if the process was removed, false otherwise
bool ChainingHashTable::Remove(unsigned int PID)
{
    int hashedIndex = PID % maxCount;

    int indexSize = processList[hashedIndex].size();

    for (int i = 0; i < indexSize; i++)
    {
        if (processList[hashedIndex][i]->getPid() == PID)
        {
            delete processList[hashedIndex][i];
            processList[hashedIndex].erase(processList[hashedIndex].begin() + i);
            count--;
            return true;
        }
    }
    return false;
}

/// @brief Print out the value of the chain at index m
/// @param m the index to print the chain of
void ChainingHashTable::Print(unsigned int m)
{
    if (m >= maxCount)
    {
        std::cout << "chain is empty" << std::endl;
        return;
    }

    int indexSize = processList[m].size();

    for (int i = 0; i < indexSize; i++)
    {
        if (i != 0)
            std::cout << " ";

        std::cout << processList[m][i]->getPid();
    }

    if (indexSize < 1)
    {
        std::cout << "chain is empty";
    }

    std::cout << std::endl;
}
