#include <iostream>
#include <fstream>
#include "Graph.h"
#include "illegal_exception.h"

using namespace std;

const int MAX_NODE_COUNT = 50001;

int main()
{
    string cmd;
    Graph *graph = new Graph(MAX_NODE_COUNT, false);
    bool mstModified = true;
    int prevCost = 0;
    std::vector<std::tuple<int, int, int>> prevOutput;

    while (cin >> cmd)
    {
        if (cmd == "LOAD")
        {
            mstModified = true;
            string filename;
            cin >> filename;

            ifstream fin(filename.c_str());

            int count;
            fin >> count;

            int n1;
            while (fin >> n1)
            {
                int n2;
                fin >> n2;
                int w;
                fin >> w;

                graph->Insert(n1, n2, w);
            }

            fin.close();
            cout << "success" << endl;
        }
        else if (cmd == "INSERT")
        {
            int a;
            int b;
            int w;

            cin >> a;
            cin >> b;
            cin >> w;

            try
            {
                if (graph->Insert(a, b, w))
                {
                    mstModified = true;
                    std::cout << "success" << std::endl;
                }
                    
                else
                {
                    std::cout << "failure" << std::endl;
                }
            }
            catch (illegal_exception)
            {
                std::cout << "illegal argument" << std::endl;
            }
        }
        else if (cmd == "DELETE")
        {
            int a;
            cin >> a;

            try
            {
                if (graph->Delete(a))
                {
                    mstModified = true;
                    std::cout << "success" << std::endl;
                }
                else
                {
                    std::cout << "failure" << std::endl;
                }
            }
            catch (illegal_exception)
            {
                std::cout << "illegal argument" << std::endl;
            }
        }
        else if (cmd == "PRINT")
        {
            int a;
            cin >> a;

            try
            {
                std::vector<std::tuple<int, int>> *out = graph->GetAdjacent(a);
                for (int i = 0; i < out->size(); i++)
                {
                    std::cout << get<0>(out->at(i)) << " ";
                }

                if (out->size() < 1)
                {
                    std::cout << "failure";
                }
                std::cout << endl;
            }
            catch (illegal_exception)
            {
                std::cout << "illegal argument" << std::endl;
            }
        }
        else if (cmd == "MST")
        {
            // Prevent useless regeneration of MST.
            if (!mstModified)
            {
                if (prevOutput.size() < 1)
                    std::cout << "failure";

                for (int i = 0; i < prevOutput.size(); i++)
                {
                    std::cout << std::get<0>(prevOutput[i]) << " " << std::get<1>(prevOutput[i]) << " " << std::get<2>(prevOutput[i]) << " ";
                }

                std::cout << std::endl;
            }
            else
            {
                std::vector<std::tuple<int, int, int>> out;
                out.reserve(graph->GetVertexCount());
                prevCost = graph->MST(&out);
                prevOutput = out;

                for (int i = 0; i < out.size(); i++)
                {
                    std::cout << std::get<0>(out[i]) << " " << std::get<1>(out[i]) << " " << std::get<2>(out[i]) << " ";
                }

                if (out.size() < 1)
                    std::cout << "failure";

                std::cout << std::endl;
                mstModified = false;
            }
        }
        else if (cmd == "COST")
        {
            // Prevent useless regeneration of MST.
            if (!mstModified)
            {
                std::cout << "cost is " << prevCost << std::endl;
            }
            else
            {
                std::vector<std::tuple<int, int, int>> out;
                out.reserve(graph->GetVertexCount());
                int cost = graph->MST(&out);
                prevOutput = out;
                prevCost = cost;

                std::cout << "cost is " << cost << std::endl;
                mstModified = false;
            }
        }

        else if (cmd == "END")
        {
            break;
        }
    }

    delete graph;
}
