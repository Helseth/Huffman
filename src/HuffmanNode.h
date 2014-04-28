#ifndef HUFFMAN_NODE
#define HUFFMAN_NODE

#include <string>
using namespace std;

class HuffmanNode{

public:

	HuffmanNode(string key);
	HuffmanNode(string key, int freq);

	HuffmanNode* getLeft();
	HuffmanNode* getRight();
	void setLeft(HuffmanNode *left);
	void setRight(HuffmanNode *right);
	string getKey();
	void setKey(string key);
	int  getFreq();
	void setFreq(int freq);
	bool isLeaf();

private:

	HuffmanNode *left;
	HuffmanNode *right;
	string key;
	int freq;
};

#endif