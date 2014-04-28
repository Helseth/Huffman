#include <string>
#include <vector>
#include <map>
#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(){
	this->root = NULL;
	this->bitmap = new std::map<std::string, std::string>();
	this->words = new std::map<std::string, int>();
	this->subTrees = new std::vector<HuffmanNode*>();
}