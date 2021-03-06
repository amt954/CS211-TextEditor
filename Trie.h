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
		int index = 0;
		while (_root != NULL) {
			TrieNode* deleteMe = _root;
			_root = _root->getChild(index);
			delete deleteMe;
		}
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
		string temp = word;
		TrieNode* searcher = _root;
		
		vector<string> matches;

		for (auto character : word)
		{
			if (searcher->hasChild(character) == true)
			{
				searcher = searcher->getChildren()[character];
			}
			else
			{
				return matches;
			}
		}

		/*searchHelper(matches, temp)*/

		for (auto child : searcher->getChildren())
		{
			if (child.first != '$')
			{
				temp = temp + child.first;
				searchHelper(matches, word + child.first);
			}
			else
			{
				matches.push_back(temp);
			}
		}

		//search through for beginning then return suggested words

        return matches;
    }

	void searchHelper(vector<string>& vect, const string& word)
	{
		string temp = word;
		TrieNode* searcher = _root;

		for (int i = 0; i < temp.length(); i++)
		{
			if (searcher->hasChild(temp[i]) == true)
			{
				searcher = searcher->getChild(temp[i]);
			}
			else
			{
				return;
			}
		}

		/*searchHelper(matches, temp)*/

		for (auto child : searcher->getChildren())
		{
			if (child.first != '$')
			{
				temp = temp + child.first;
				searchHelper(vect, word + child.first);
			}
			else
			{
				vect.push_back(temp);
			}
		}

	}
};

#endif // !TRIE_H
