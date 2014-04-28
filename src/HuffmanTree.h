#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <string>
#include "HuffmanNode.h"

class HuffmanTree{

public:
	HuffmanNode *root;
	map<std::string, int> words; //word to frequency mapping, this gets built first, use to build tree
	map<std::string, std::string> bitmap; //word to bit-string mapping, this is built last from tree
	void buildBitmap();
	HuffmanNode* buildSubtree(HuffmanNode* left, HuffmanNode* right); //return a sub tree built from 2 nodes, return is pointer to subtree

private:

}

#endif