#include "Calculator.h"
#include "VariableNode.h"

using namespace std;

Calculator::Calculator(int cap)
{
    this->data = new VariableLinkedList(cap);
}

Calculator::~Calculator()
{
    delete this->data;
}

/// @brief Define a new variable
/// @param name The name of the new variable
/// @param value The initial value to store in the variable
/// @return True if the variable was added, false otherwise
bool Calculator::define(string name, double value)
{
    return this->data->insert(name, value);
}

/// @brief Perform an operation on two variables, and store the result in a thrid
/// @param v1 The first variable to perform the operation on
/// @param v2 The second variable to perform the opetation on
/// @param v3 The variable to store the output result in
/// @param operation A lambda function to apply on the two variables
/// @return True if successful, false otherwise
bool Calculator::performOperation(string v1, string v2, string out, function<double(double, double)> operation)
{
    VariableNode *vn1 = this->data->search(v1);
    VariableNode *vn2 = this->data->search(v2);
    VariableNode *output = this->data->search(out);

    // If a single one of the variables is not found, we cannot continue.
    if (vn1 == nullptr || vn2 == nullptr || output == nullptr)
        return false;

    output->setValue(operation(vn1->getValue(), vn2->getValue()));
    return true;
}

/// @brief Remove the given variable from storage
/// @param name The name of the variable to remove
/// @return True if the variable was successfully removed, false otherwise
bool Calculator::remove(string name)
{
    return this->data->remove(name);
}

/// @brief Print out the value of the given variable
/// @param name The name of the variable to print out
void Calculator::print(string name)
{
    VariableNode *temp = this->data->search(name);
    if (temp == nullptr)
        cout << "variable " << name << " not found" << endl;
    else
        cout << temp->getValue() << endl;
}
