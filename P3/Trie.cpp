#include "Trie.h"
#include "illegal_exception.h"

Trie::Trie()
{
    children = new Trie *[MAX_SLOTS];
    isEnd = false;
    for (int i = 0; i < MAX_SLOTS; i++)
    {
        children[i] = nullptr;
    }
    count = 0;
}

Trie::~Trie()
{
    delete[] children;
}

/// @brief Wrapper function to recursively insert string s into the trie.
/// @param s The string to insert into the trie.
/// @return True if the string was inserted, false otherwise.
bool Trie::Insert(std::string s)
{
    // Wrapper function is needed to meet illegal_exception criteria without having O(n^2) runtime (recursive function).
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] < ASCII_FACTOR || s[i] > ASCII_UPPER)
        {
            throw illegal_exception();
        }
    }
    return PerformInsert(s);
}

/// @brief Recursive function to insert string s into the trie.
/// @param s The string to insert into the trie.
/// @return True if the string was inserted successfully, false otherwise.
bool Trie::PerformInsert(std::string s)
{
    if (s.length() > 0) // Add until there are no more characters.
    {
        char c = s.at(0);
        // Create the new trie if it does not exist. This condition will never be true if the word cannot be inserted.
        if (children[c - ASCII_FACTOR] == nullptr)
            children[c - ASCII_FACTOR] = new Trie(); 

        // Recursively insert, checking if the previous insertion was successful (if so, increment count).
        if (children[c - ASCII_FACTOR]->PerformInsert(s.substr(1)))
        {
            count++;
            return true;
        }
    }
    // If there are no characters and we have not reached a word end then the word is not already added.
    else if (!this->isEnd) 
    {
        this->isEnd = true;
        count++;
        return true;
    }
    return false; // If the word is already in the trie, return false.
}

/// @brief Wrapper function to remove an element from the trie. 
/// @param s The string to remove from the trie.
/// @return True if the element was removed successfully, false otherwise.
bool Trie::Remove(std::string s)
{
    // Achieve O(n) runtime using wrapper function.
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] < ASCII_FACTOR || s[i] > ASCII_UPPER)
        {
            throw illegal_exception();
        }
    }
    return PerformRemove(s);
}

/// @brief Recursively remove string s from the trie.
/// @param s The string to remove from the trie.
/// @return True if the string was removed, false otherwise.
bool Trie::PerformRemove(std::string s)
{
    if (s.length() > 0) // Remove until there are no more characters to remove.
    {
        // If we have reached a trie that does not have the correct child, we cannot remove the word.
        char c = s.at(0);
        if (children[c - ASCII_FACTOR] == nullptr)
            return false;

        // Recursively remove the remaining bit of the word. Subtracting from the count if successful.
        if (children[c - ASCII_FACTOR]->PerformRemove(s.substr(1)))
        {
            count--;

            // Free any child tries that have a count of 0. These are guaranteed to have no children.
            for (int i = 0; i < MAX_SLOTS; i++) 
            {
                if (children[i] != nullptr && children[i]->IsEmpty())
                {
                    delete children[i];
                    children[i] = nullptr;
                }
            }

            return true; // If previous removes were successful, this remove is also successful.
        }
    }
    // If we have reached the end of the word, we can succesfully remove it from the trie.
    else if (this->isEnd)
    {
        this->isEnd = false;
        count--;
        return true;
    }

    return false; // When we are out of characters, but did not find a word end, cannot remove.
}

/// @brief Determine if the trie is empty.
/// @return True if the trie is empty, false otherwise.
bool Trie::IsEmpty()
{
    return count == 0;
}

/// @brief Empty the trie.
void Trie::Clear()
{
    // We do not need to worry about dangling pointers, since everything is being deleted in order.
    for (int i = 0; i < MAX_SLOTS; i++)
    {
        if (children[i] != nullptr)
            children[i]->Clear(); // Recursively delete any non-null pointer children.
    }

    delete this;
}

/// @brief Perform a depth first search on the trie for string s, outputting the result by performing in place modification of the vector out.
/// @param out 
/// @param s 
void Trie::DepthFirstSearch(std::vector<std::string> *out, std::string s)
{
    if (isEnd)
        out->push_back(s); // If we have reached the end, put the word into the output

    // Recursively search children nodes, in order from A-Z.
    for (int i = 0; i < MAX_SLOTS; i++)
    {
        if (children[i] != nullptr)
            children[i]->DepthFirstSearch(out, s + (char)(i + ASCII_FACTOR));
    }
}

/// @brief Get the number of words in the trie.
/// @return An integer of the number of words in the trie.
int Trie::Size()
{
    return count;
}

/// @brief Wrapper function to count the number of suffixes for a given string s.
/// @param s 
/// @return 
int Trie::CountSuffixes(std::string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] < ASCII_FACTOR || s[i] > ASCII_UPPER)
        {
            throw illegal_exception();
        }
    }
    return PerformCountSuffixes(s);
}


int Trie::PerformCountSuffixes(std::string s)
{
    if (s.empty())
        return count;

    char c = s.at(0);
    int index = c - ASCII_FACTOR;

    if (children[index] != nullptr)
        return children[index]->PerformCountSuffixes(s.substr(1));
    else
        return 0; 
}

bool Trie::SpellCheck(std::vector<std::string> *out, std::string check, std::string s)
{
    if (check.empty() && isEnd)
        return true;
    else if (check.empty())
        return false;

    char c = check.at(0);
    int index = c - ASCII_FACTOR;
;
    if (children[index] != nullptr)
    {
        if (children[index]->SpellCheck(out, check.substr(1), s + c))
        {
            return true;
        }
        else
        {
            children[index]->DepthFirstSearch(out, s + c);
            return true;
        }
    }
    return false;
}
