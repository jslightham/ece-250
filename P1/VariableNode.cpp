#include "VariableNode.h"

using namespace std;

VariableNode::VariableNode(std::string name, double value, VariableNode *next) 
{
    this->name = name;
    this->value = value;
    this->next = next;
}

string VariableNode::getName()
{
    return name;
}

double VariableNode::getValue()
{
    return value;
}

void VariableNode::setValue(double value)
{
    this->value = value;
}

void VariableNode::setNext(VariableNode *next)
{
    this->next = next; // Be careful when calling setNext, or we could have a memory leak.
}

VariableNode *VariableNode::getNext()
{
    return next;
}

/// @brief Delete all children nodes of this element
void VariableNode::DestroyAll()
{
    if (this->next != nullptr)
        this->next->DestroyAll();

    delete this;
}
