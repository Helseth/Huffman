#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "HuffmanNode.h"
#include "HuffmanTree.h"

int main(){
	std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
	std::string testString = "the sun is the star at the center of the solar system it is seen in the sky and gives light to the earth when the sun is in the sky it is day when the sun is not in the sky it is night the planets including earth go around it";
	//std::string testString = "the quick brown fox jumped over the lazy dog";
		
	HuffmanTree *huffTree = new HuffmanTree(testString);
	huffTree->buildWords();
	huffTree->initSubTrees();
	huffTree->buildSubtree();
	huffTree->buildBitmap();
	huffTree->findCompression(testString);

	return 0;
}

