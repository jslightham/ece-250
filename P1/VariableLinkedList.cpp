#include "VariableLinkedList.h"

using namespace std;

VariableLinkedList::VariableLinkedList(int cap)
{
    this->maxCount = cap;
    this->count = 0;
    this->head = nullptr;
}

VariableLinkedList::~VariableLinkedList()
{
    if (head != nullptr)
        head->DestroyAll();
}

/// @brief Insert a variable into the head of the linked list
/// @param name The name of the variable to insert
/// @param value The double value to initialize the variable with
/// @return True if the variable was added, false otherwise
bool VariableLinkedList::insert(string name, double value)
{
    // Ensure there is space
    if (count == maxCount)
        return false;

    // Ensure the variable does not exist
    VariableNode *s = this->search(name);
    if (s != nullptr)
        return false;

    // Insert a new VariableNode into the head.
    head = new VariableNode(name, value, head);
    
    count++;
    return true;
}

/// @brief Remove the variable with name from the linked list
/// @param name The name of the variable to remove
/// @return True if removed, false otherwise
bool VariableLinkedList::remove(string name)
{
    // Root node must be handled in a seperate case
    if (head != nullptr && head->getName() == name)
    {
        VariableNode *temp = head->getNext();
        delete head;
        head = temp;
        count --;
        return true;
    }

    // Search for the node before the one we want to remove.
    VariableNode *currentIndex = this->head;
    while (currentIndex != nullptr && currentIndex->getNext() != nullptr && 
           currentIndex->getNext()->getName() != name)
        currentIndex = currentIndex->getNext();

    // currentIndex will be null if the index does not exist.
    if (currentIndex == nullptr || currentIndex->getNext() == nullptr)
        return false;

    VariableNode *temp = currentIndex->getNext()->getNext();
    delete currentIndex->getNext();
    count--;
    currentIndex->setNext(temp);
    return true;
}

/// @brief Search for the variable with the given name
/// @param name The name of the variable to search for
/// @return A pointer to a valid VariableNode if the node exists, nullptr otherwise
VariableNode *VariableLinkedList::search(string name)
{
    VariableNode *currentIndex = this->head;
    while (currentIndex != nullptr)
    {
        if (currentIndex->getName() == name)
        {
            return currentIndex;
        }
        currentIndex = currentIndex->getNext();
    }

    return nullptr;
}
