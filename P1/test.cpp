#include <iostream>
#include "Calculator.h"

using namespace std;

int main ()
{
    string cmd;
    Calculator *calc = nullptr; 

    while (cin >> cmd)
    {
        if (cmd == "CRT")
        {
            int N;
            cin >> N;

            if (calc != nullptr)
                delete calc;
            calc = new Calculator(N);

            cout << "success" << endl;
        }
        else if (cmd == "DEF")
        {
            string name;
            double val;

            cin >> name;
            cin >> val;

            if (calc->define(name, val))
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        else if (cmd == "ADD" || cmd == "SUB")
        {
            string v1;
            string v2;
            string out;

            cin >> v1;
            cin >> v2;
            cin >> out;

            function<double(double, double)> operation;
            if (cmd == "ADD")
                operation = [](double d1, double d2) {return d1 + d2;};
            else
                operation = [](double d1, double d2) {return d1 - d2;};

            if (calc->performOperation(v1, v2, out, operation))
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        else if (cmd == "REM")
        {
            string name;

            cin >> name;

            if (calc->remove(name))
                cout << "success" << endl;
            else
                cout << "failure" << endl;
        }
        else if (cmd == "PRT")
        {
            string name;

            cin >> name;

            calc->print(name);
        }
        else if (cmd == "END")
        {
            break;
        }
    }

    delete calc;
}