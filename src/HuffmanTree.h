#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <string>
#include <vector>
#include <map>
#include "HuffmanNode.h"

extern bool verboseG;
extern bool graphSet;

class HuffmanTree{

public:
	//bool verbose;
	double compression;
	std::string inString;
	HuffmanNode *root;
	std::map<std::string, int> *words; //word to frequency mapping, this gets built first, use to build tree
	std::map<std::string, std::string> *bitmap; //word to bit-string mapping, this is built last from tree
	std::vector<HuffmanNode*> *subTrees; //List of all sub trees, yes a single node is a subtree

	HuffmanTree();
	HuffmanTree(std::string input); //Use this contructor
	void buildWords();
	std::map<std::string, int>* buildWords(std::vector<std::string>); //Old used for testing, kept for test reasons
	void initSubTrees(); //Build all of our nodes from "words" mapping
	void buildBitmap();
	void buildBitmap(std::string bitString, HuffmanNode *node);
	HuffmanNode* buildSubtree(); //return a sub tree built from smallest 2 nodes in subTrees vector, return is pointer to subtree
	double findCompression(std::string input);
	std::string wrap(const char *text);
	int traverse(std::pair<std::string, int> word);

private:
	unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch);
};

#endif