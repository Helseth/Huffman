#include "HuffmanNode.h"
#include <string>

using namespace std;

#ifndef NULL
#define NULL 0
#endif

HuffmanNode::HuffmanNode(string key){
	this->key = key;
	this->freq = 0;
	this->left = NULL;
	this->right = NULL;
}

HuffmanNode::HuffmanNode(string key, int freq){
	this->key = key;
	this->freq = freq;
	this->left = NULL;
	this->right = NULL;
}

HuffmanNode* HuffmanNode::getLeft(){
	return this->left;
}

HuffmanNode* HuffmanNode::getRight(){
	return this->right;
}

string HuffmanNode::getKey(){
	return this->key;
}

int HuffmanNode::getFreq(){
	return this->freq;
}

void HuffmanNode::setLeft(HuffmanNode *left){
	this->left = left;
}

void HuffmanNode::setRight(HuffmanNode *right){
	this->right = right;
}

void HuffmanNode::setKey(string key){
	this->key = key;
}

void HuffmanNode::setFreq(int freq){
	this->freq = freq;
}

bool HuffmanNode::isLeaf(){
	if(this->left == NULL && this->right == NULL)
		return true;
	return false;
}