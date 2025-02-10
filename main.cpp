#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

#define SIZEX 4
#define SIZEY 4

bool containsNonLowercase(string str)
{
    for (char c : str)
    {
        if (!islower(c))
        {
            return true;
        }
    }
    return false;
}
inline char indexToChar(int inx)
{
    return char((int)'a' + inx);
}
inline int charToIndex(char chr)
{
    return (int)chr - (int)'a';
}
const int numOfLetters = 26;
struct trieNode
{
    trieNode *children[numOfLetters];
    bool wordEnd;
    trieNode()
    {
        wordEnd = false;
        for (int i = 0; i < numOfLetters; ++i)
        {
            children[i] = nullptr;
        }
    }
};
class Trie
{
public:
    trieNode root;
    int numberOfWords = 0;
    Trie() {};
    ~Trie()
    {
        for (int i = 0; i < numOfLetters; ++i)
        {
            if (root.children[i] != nullptr)
            {
                delete root.children[i];
            }
        }
    }
    void insertWord(string word)
    {
        trieNode *currNode = &root;
        int i = 0;
        for (; i < word.size(); i++)
        {
            if (currNode->children[charToIndex(word[i])] == nullptr)
            {
                currNode->children[charToIndex(word[i])] = new trieNode();
            }
            currNode = currNode->children[charToIndex(word[i])];
        }
        currNode->wordEnd = true;
    }

    bool areThereWithPrefix(string prefix)
    {
        trieNode *currNode = &root;
        for (int i = 0; i < prefix.size(); i++)
        {
            if (currNode->children[charToIndex(prefix[i])] == nullptr)
            {
                return false;
            }
            currNode = currNode->children[charToIndex(prefix[i])];
        }
        return true;
    }

    bool isThisAWord(string s)
    {
        trieNode *currNode = &root;
        for (int i = 0; i < s.size(); i++)
        {
            if (currNode->children[charToIndex(s[i])] == nullptr)
            {
                return false;
            }
            currNode = currNode->children[charToIndex(s[i])];
        }
        if (currNode->wordEnd)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
Trie words;
vector<string> mozliweSlowa;

void generateStrings(string &pattern, int index = 0)
{
    if (index == (int)pattern.size())
    {
        if (words.isThisAWord(pattern))
        {
            mozliweSlowa.push_back(pattern);

            // cout << pattern << endl;
        }
        return;
    }

    if (pattern[index] == '*')
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            pattern[index] = c;
            if (words.areThereWithPrefix(pattern.substr(0, index + 1)))
            {
                generateStrings(pattern, index + 1);
            }

            pattern[index] = '*';
        }
    }
    else
    {

        generateStrings(pattern, index + 1);
    }
}
int main()
{

    ifstream in("slowa.txt");
    static ofstream mozliweSlowaPlik("wynik.txt");
    string s;
    string s1;
    while (in >> s)
    {
        s1 = "";
        for (int i = 0; i < s.size(); i++)
        {
            s1 += tolower(s[i]);
        }
        if (!containsNonLowercase(s1))
        {
            words.insertWord(s1);
        }
    }

    string slowo = "s*a**z*a"; // szukane slowo * - nieznana literka
    
    
    transform(slowo.begin(), slowo.end(), slowo.begin(), ::tolower);
    vector<int>
        astIndexes;
    for (int i = 0; i < slowo.size(); ++i)
    {
        if (slowo[i] == '*')
        {
            astIndexes.push_back(i);
        }
    }
    generateStrings(slowo);
    mozliweSlowaPlik << "Liczba slow: " << mozliweSlowa.size() << "\n";
    for (int i = 0; i < mozliweSlowa.size(); i++)
    {
        mozliweSlowaPlik << mozliweSlowa[i] << "\n";
    }

    mozliweSlowaPlik.close();
    return 0;
}
