#include "Process.h"

Process::Process(unsigned int PID, int startingIndex)
{
    this->PID = PID;
    this->startingIndex = startingIndex;
}

unsigned int Process::getPid()
{
    return this->PID;
}

int Process::getStartingIndex()
{
    return this->startingIndex;
}
