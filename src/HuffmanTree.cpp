#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(){
	this->compression = 0.0;
	this->root = NULL;
	this->bitmap = new std::map<std::string, std::string>();
	this->words = new std::map<std::string, int>();
	this->subTrees = new std::vector<HuffmanNode*>();
}


HuffmanNode* HuffmanTree::buildSubtree(){

	/* This function follows the convention that 2 trees are removed from the vector,
	// then the tree built from them is placed back into the vector
	*/
	HuffmanNode *subTree;
	HuffmanNode *smallest;
	while(true){
		if(this->subTrees->size() == 1)
			break;
		smallest = this->subTrees->at(0);
		HuffmanNode *secondSmall = this->subTrees->at(1);;//this->subTrees->at(1);

		int loc1 = 0;
		int loc2 = 0;
		for (unsigned int i = 1; i < this->subTrees->size(); i++){
			if(this->subTrees->at(i)->getFreq() < smallest->getFreq()){
				secondSmall = smallest;
				smallest = this->subTrees->at(i);
				loc2 = loc1;
				loc1 = i;
			}
		}

		subTree = new HuffmanNode("", smallest->getFreq() + secondSmall->getFreq()); //Build our new sub tree
		subTree->setLeft(smallest);
		subTree->setRight(secondSmall);
		this->subTrees->erase(this->subTrees->begin() + loc1); //Pls don't actually delete, just remove
		this->subTrees->erase(this->subTrees->begin() + loc2); //Gooby pls
		this->subTrees->push_back(subTree); //Let's just put this back in the subTree vector
	}
	this->root = this->subTrees->at(0);
	return subTree;
}

void HuffmanTree::buildBitmap(std::string bitString, HuffmanNode *node){
	if(node->isLeaf()){
		std::pair<std::string, std::string> temp;
		temp = make_pair(node->getKey(), bitString);  //Only leaf nodes should be 'words' and be added to the bit map
		this->bitmap->emplace(temp);
		this->compression += node->getFreq() * bitString.length();
		//std::cout << node->getKey() << "\t\t" << bitString << std::endl; //This prints out the key/bitstring pair
		return;
	}

	//Every sub tree "should" have 2 children, if not, someone has abducted little Timmy...
	if(node->getLeft() != NULL){
		bitString.push_back('0');
		HuffmanTree::buildBitmap(bitString, node->getLeft());
		bitString.pop_back();
	}

	if(node->getRight() != NULL){
		bitString.push_back('1');
		HuffmanTree::buildBitmap(bitString, node->getRight());
		bitString.pop_back();
	}
}

void HuffmanTree::initSubTrees(){
	HuffmanNode *newNode;
	for ( std::map< std::string, int>::const_iterator iter = this->words->begin(); iter != this->words->end(); ++iter ){
		newNode = new HuffmanNode(iter->first, iter->second); 
		this->subTrees->insert(this->subTrees->end(), newNode);
	}
}

void HuffmanTree::buildWords(std::string input){
	std::vector<std::string> tempVec;
	std::map<std::string, int>::iterator iter;
	split(input, tempVec, ' ');
	for(unsigned int i = 0; i < tempVec.size(); i++){
		iter = this->words->find(tempVec.at(i));
		if(iter != this->words->end())
			iter->second++;
		else{
			std::pair<std::string, int> temp;
			temp = make_pair(tempVec.at(i), 1);
			this->words->emplace(temp);
		}	
	}
}

double HuffmanTree::findCompression(std::string  input){
	double compressionRatio;
	compressionRatio = this->compression / (input.length() * 8);
	std::cout << "Bitstring:" << std::endl;
	std::cout << this->compression << " bits" << std::endl << std::endl;
	std::cout << "Compression Rate: " << compressionRatio << std::endl; 
	return compressionRatio;
}

/* This function was grabbed from http://stackoverflow.com/questions/5888022/split-string-by-single-spaces
// Was going to use Boost library "boost\algorithm\string\split.hpp"
// C++ does not have a similar function for strings like Java's string.split()
*/
unsigned int HuffmanTree::split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    unsigned int pos = txt.find( ch );
    unsigned int initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos + 1 ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}