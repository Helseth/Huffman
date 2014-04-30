#include <iostream>
#include <string>
#include <fstream>
#include "HuffmanNode.h"
#include "HuffmanTree.h"

int main(){
	//double compression;
	std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
	//std::string testString = "the sun is the star at the center of the solar system it is seen in the sky and gives light to the earth when the sun is in the sky it is day when the sun is not in the sky it is night the planets including earth go around it";
	std::string testString = "the quick brown fox jumped over the lazy dog";
	std::cout << "String:\n";
	std::cout << testString << std::endl << testString.length() * 8 << " bits" << std::endl << std::endl;
	std::cout << "key\t\tbitstring\n";
	std::cout << "----------------------------------\n";
	HuffmanTree *huffTree = new HuffmanTree();
	huffTree->buildWords(testString);
	huffTree->initSubTrees();
	huffTree->buildSubtree();
	huffTree->buildBitmap("", huffTree->root);
	huffTree->findCompression(testString);

	//std::cout << std::endl << "Compression Rate: " << compression << std::endl; 
	//system("pause");

	return 0;
}