#include <iostream>

#include "VirtualMemory.h"

using namespace std;

int main()
{
    string cmd;
    VirtualMemory *vm = nullptr;
    bool chaining = true;

    while (cin >> cmd)
    {
        if (cmd == "OPEN")
        {
            chaining = false;
        }
        else if (cmd == "ORDERED")
        {
            chaining = true;
        }
        if (cmd == "M")
        {
            int N;
            int P;
            cin >> N;
            cin >> P;

            vm = new VirtualMemory(N, P, chaining);

            cout << "success" << endl;
        }
        else if (cmd == "INSERT")
        {
            unsigned int PID;
            cin >> PID;

            if (vm->Insert(PID))
                cout << "success" << endl;
            else
                cout << "failure" << endl;
        }
        else if (cmd == "SEARCH")
        {
            unsigned int PID;
            cin >> PID;

            int ret = vm->Search(PID);
            if (ret == -1)
                cout << "not found" << endl;
            else
                cout << "found " << PID << " in " << ret << endl;
        }
        else if (cmd == "WRITE")
        {
            unsigned int PID;
            int ADDR;
            int x;

            cin >> PID;
            cin >> ADDR;
            cin >> x;

            if (vm->Write(PID, ADDR, x))
                cout << "success" << endl;
            else
                cout << "failure" << endl;
        }
        else if (cmd == "READ")
        {
            unsigned int PID;
            int ADDR;

            cin >> PID;
            cin >> ADDR;

            vm->Read(PID, ADDR);
        }
        else if (cmd == "DELETE")
        {
            unsigned int PID;
            cin >> PID;

            if (vm->Delete(PID))
                cout << "success" << endl;
            else
                cout << "failure" << endl;
        }
        else if (cmd == "PRINT")
        {
            int m;
            cin >> m;

            vm->Print(m);
        }
        else if (cmd == "END")
        {
            break;
        }
    }
    delete vm;
}
