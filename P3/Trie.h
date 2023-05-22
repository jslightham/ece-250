#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>

class Trie
{
public:
    Trie();
    ~Trie();
    bool Insert(std::string s);
    bool Remove(std::string s);
    void DepthFirstSearch(std::vector<std::string> *out, std::string s);
    bool IsEmpty();
    void Clear();
    int Size();
    int CountSuffixes(std::string s);
    bool SpellCheck(std::vector<std::string> *out, std::string check, std::string s);

private:
    const int MAX_SLOTS = 26;
    const int ASCII_FACTOR = 65;
    const int ASCII_UPPER = 90;
    int count;
    bool isEnd;
    Trie **children;

    bool PerformInsert(std::string s);
    bool PerformRemove(std::string s);
    int PerformCountSuffixes(std::string s);
};
#endif