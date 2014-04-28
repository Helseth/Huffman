#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <string>
#include <vector>
#include <map>
#include "HuffmanNode.h"

class HuffmanTree{

public:
	HuffmanNode *root;
	std::map<std::string, int> *words; //word to frequency mapping, this gets built first, use to build tree
	std::map<std::string, std::string> *bitmap; //word to bit-string mapping, this is built last from tree
	std::vector<HuffmanNode*> *subTrees; //List of all sub trees, yes a single node is a subtree

	HuffmanTree();
	void initSubTrees(); //Build all of our nodes from "words" mapping
	void buildBitmap(std::string bitString, HuffmanNode *node);
	HuffmanNode* buildSubtree(); //return a sub tree built from smallest 2 nodes in subTrees vector, return is pointer to subtree

private:

}

#endif