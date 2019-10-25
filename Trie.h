#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <cctype>
using namespace std;

class Trie
{
private:
    TrieNode *_root = nullptr;

protected:

public:
    Trie()
    {
        _root = new TrieNode{};
    }

    virtual ~Trie()
    {
        //TODO: clean up memory
    }

	//TODO: implement
    void addWord(const string &word)
    {
		TrieNode* runner = _root;

		for (int i = 0; i < word.length(); i++)
		{
			if (runner->hasChild(word[i]) == false)
			{
				runner->setChild(word[i], new TrieNode(word[i]));
			}
			runner = runner->getChild(word[i]);
		}
		runner->setChild('$', runner);
    }

	//TODO: implement
    vector<string> search(const string &word)
    {
        vector<string> matches;
        return matches;
    }
};

#endif // !TRIE_H
