#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    unsigned int getPid();
    int getStartingIndex();

    Process(unsigned int PID, int startingIndex);

private:
    unsigned int PID;
    int startingIndex;
};
#endif
