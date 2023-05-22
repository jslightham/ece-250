#ifndef VARIABLELINKEDLIST_H
#define VARIABLELINKEDLIST_H

#include <iostream>
#include <functional>
#include "VariableNode.h"

class VariableLinkedList
{
public:
    bool insert(std::string name, double value);
    VariableNode *search(std::string name);
    bool remove(std::string name);
    VariableLinkedList(int cap);
    ~VariableLinkedList();

private:
    VariableNode *head;
    int count;
    int maxCount;
};
#endif
