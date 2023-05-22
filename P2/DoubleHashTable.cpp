
#include <iostream>
#include <cmath>

#include "DoubleHashTable.h"
#include "Process.h"

DoubleHashTable::DoubleHashTable(int size)
{
    processList = new Process *[size];
    maxCount = size;
    count = 0;

    for (int i = 0; i < size; i++)
    {
        processList[i] = nullptr;
    }
}

DoubleHashTable::~DoubleHashTable()
{
    for (int i = 0; i < maxCount; i++)
    {
        if (processList[i] != nullptr)
            delete processList[i];
    }

    delete[] processList;
}

/// @brief Insert a process into the hash table
/// @param p pointer to the process to insert
/// @return true if successful, false otherwise
bool DoubleHashTable::Insert(Process *p)
{
    if (count >= maxCount)
    {
        return false;
    }

    // Continually hash until we have reached a nullpointer, -1, or the end
    int emptyIndex = -1;
    for (int i = 0; i < maxCount; i++)
    {
        unsigned int hashedIndex = HashIndex(p->getPid(), i);

        // If we have reached a nullptr, and have not seen any empty slots before
        if (processList[hashedIndex] == nullptr && emptyIndex == -1)
        {
            // Replace the nullpointer with the process
            processList[hashedIndex] = p;
            return true;
        }
        // If we have reached a nullpointer and have seen an empty slot before
        else if (processList[hashedIndex] == nullptr && emptyIndex != -1)
        {
            // Replace the -1 with the process
            hashedIndex = HashIndex(p->getPid(), emptyIndex);
            delete processList[hashedIndex];
            processList[hashedIndex] = p;
            return true;
        }
        // If we find a process with the same PID already, exit
        else if (processList[hashedIndex]->getPid() == p->getPid())
        {
            return false;
        }
        // If we have found a slot of -1
        else if (processList[hashedIndex]->getStartingIndex() == -1 && emptyIndex == -1)
        {
            // If we can insert in the empty slot (have reached the end)
            emptyIndex = i;
            if (!(i + 1 < maxCount))
            {
                delete processList[hashedIndex];
                processList[hashedIndex] = p;
                return true;
            }
        }
    }

    // Insert into the empty slot - theoretically we do not need the code in the if statement of the last else if clause, but it works...
    if (emptyIndex != -1)
    {
        unsigned int hashedIndex = HashIndex(p->getPid(), emptyIndex);
        delete processList[hashedIndex];
        processList[hashedIndex] = p;
        return true;
    }

    return false;
}

/// @brief Search the hash table for the given PID
/// @param PID the pid to search for
/// @return the index of the process, or -1 if the process does not exist
int DoubleHashTable::Search(unsigned int PID)
{
    for (int i = 0; i < maxCount; i++)
    {
        int hashedIndex = HashIndex(PID, i);

        if (hashedIndex >= maxCount || processList[hashedIndex] == nullptr)
        {
            return -1;
        }
        else if (processList[hashedIndex]->getPid() == PID)
        {
            return hashedIndex;
        }
    }
    return -1;
}

/// @brief Search the hash table for the given PID, and return a pointer to the process object
/// @param PID the pid to search for
/// @return A valid process object if it exists, or a nullpointer otherwise
Process *DoubleHashTable::Get(unsigned int PID)
{
    for (int i = 0; i < maxCount; i++)
    {
        int hashedIndex = HashIndex(PID, i);

        if (hashedIndex >= maxCount || processList[hashedIndex] == nullptr)
        {
            return nullptr;
        }
        else if (processList[hashedIndex]->getPid() == PID)
        {
            return processList[hashedIndex];
        }
    }
    return nullptr;
}

/// @brief Remove a process object from the hash table
/// @param PID the PID of the process to remove
/// @return true if the process was successfully removed, false otherwise
bool DoubleHashTable::Remove(unsigned int PID)
{
    for (int i = 0; i < maxCount; i++)
    {
        int hashedIndex = HashIndex(PID, i);

        if (hashedIndex >= maxCount || processList[hashedIndex] == nullptr)
        {
            return false;
        }
        else if (processList[hashedIndex]->getPid() == PID)
        {
            delete processList[hashedIndex];
            processList[hashedIndex] = new Process(0, -1);
            return true;
        }
    }
    return false;
}

/// @brief Compute the hash of k and i.
/// @param k the k value to hash (PID)
/// @param i the i value to hash (index)
/// @return the hashed value
int DoubleHashTable::HashIndex(unsigned int k, int i)
{
    unsigned int h1 = k % maxCount;
    unsigned int h2 = (int)std::floor(k / maxCount) % maxCount;

    if (h2 % 2 == 0)
        h2++;

    return (h1 + i * h2) % maxCount;
}

void DoubleHashTable::Print(unsigned int m)
{
    // Not implemented
}
