#ifndef HUFFMAN_NODE
#define HUFFMAN_NODE

#include <string>

class HuffmanNode{

public:

	HuffmanNode(std::string key);
	HuffmanNode(std::string key, int freq);

	HuffmanNode* getLeft();
	HuffmanNode* getRight();
	void setLeft(HuffmanNode *left);
	void setRight(HuffmanNode *right);
	std::string getKey();
	void setKey(std::string key);
	int  getFreq();
	void setFreq(int freq);
	bool isLeaf();

private:

	HuffmanNode *left;
	HuffmanNode *right;
	std::string key;
	int freq;
};

#endif