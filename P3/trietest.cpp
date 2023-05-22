#include <iostream>
#include <fstream>
#include "Trie.h"
#include <vector>
#include "illegal_exception.h"

using namespace std;

const string FILE_NAME = "corpus.txt";

void PrintVector(vector<string> *out)
{
    for (int i = 0; i < out->size(); i++)
    {
        cout << (*out)[i];
        if (i < out->size() - 1)
            cout << " ";
    }
}

int main()
{
    string cmd;
    string addWord;
    ifstream fin(FILE_NAME);
    Trie *trie = new Trie();

    while (cin >> cmd)
    {
        if (cmd == "load")
        {
            if (!fin.is_open())
                fin.open(FILE_NAME);

            while (fin >> addWord)
            {
                trie->Insert(addWord);
            }

            fin.close();
            cout << "success" << endl;
        }
        else if (cmd == "i")
        {
            string word;
            cin >> word;
            try
            {
                if (trie->Insert(word))
                    cout << "success" << endl;
                else
                    cout << "failure" << endl;
            }
            catch (illegal_exception e)
            {
                cout << "illegal argument" << endl;
            }
        }
        else if (cmd == "e")
        {
            string word;
            cin >> word;

            try
            {
                if (trie->Remove(word))
                    cout << "success" << endl;
                else
                    cout << "failure" << endl;
            }
            catch (illegal_exception e)
            {
                cout << "illegal argument" << endl;
            }
        }
        else if (cmd == "clear")
        {
            trie->Clear();
            trie = new Trie();
            cout << "success" << endl;
        }
        else if (cmd == "size")
        {
            cout << "number of words is " << trie->Size() << endl;
        }
        else if (cmd == "empty")
        {
            if (trie->IsEmpty())
                cout << "empty 1" << endl;
            else
                cout << "empty 0" << endl;
        }
        else if (cmd == "spellcheck")
        {
            string word;
            cin >> word;

            vector<string> out;

            bool result = trie->SpellCheck(&out, word, "");

            if (out.empty() && result)
            {
                cout << "correct" << endl;
            }
            else if (!result)
            {
                cout << endl;
            }
            else
            {
                PrintVector(&out);
                cout << endl;
            }
        }
        else if (cmd == "p")
        {
            vector<string> out;
            trie->DepthFirstSearch(&out, "");

            PrintVector(&out);

            if (out.size() > 0)
                cout << endl;
            
        }

        else if (cmd == "c")
        {
            string prefix;
            cin >> prefix;

            try
            {
                int count = trie->CountSuffixes(prefix);

                if (count != -1 && count != 0)
                    cout << "count is " << count << endl;
                else
                    cout << "not found" << endl;
            }
            catch (illegal_exception e)
            {
                cout << "illegal argument" << endl;
            }
        }
        else if (cmd == "exit")
        {
            break;
        }
    }
    trie->Clear();
}
