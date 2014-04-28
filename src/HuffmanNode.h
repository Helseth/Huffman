#ifndef HUFFMAN_NODE
#define HUFFMAN_NODE

class HuffmanNode{

public:

	HuffmanNode(char *key);
	HuffmanNode(char *key, int freq);

	HuffmanNode* getLeft();
	HuffmanNode* getRight();
	void setLeft(HuffmanNode *left);
	void setRight(HuffmanNode *right);
	char* getKey();
	void setKey(char *key);
	int  getFreq();
	void setFreq(int freq);
	bool isLeaf();

private:

	HuffmanNode *left;
	HuffmanNode *right;
	char *key;
	int freq;
};

#endif