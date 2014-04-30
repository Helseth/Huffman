#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "HuffmanNode.h"
#include "HuffmanTree.h"


#define LINE_LENGTH 72 //Used for nice word wrapping on output

std::string wrap(const char *);

int main(){
	std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
	std::string testString = "the sun is the star at the center of the solar system it is seen in the sky and gives light to the earth when the sun is in the sky it is day when the sun is not in the sky it is night the planets including earth go around it";
	//std::string testString = "the quick brown fox jumped over the lazy dog";
	std::cout << "String:\n";
	std::cout << wrap(testString.c_str()) << std::endl;
	std::cout /*<< testString << std::endl*/ << testString.length() * 8 << " bits" << std::endl << std::endl;
	//std::cout << "key\t\tbitstring\n"; //Header for key/bitstring pairs
	//std::cout << "----------------------------------\n";
	HuffmanTree *huffTree = new HuffmanTree();
	huffTree->buildWords(testString);
	huffTree->initSubTrees();
	huffTree->buildSubtree();
	huffTree->buildBitmap("", huffTree->root);
	huffTree->findCompression(testString);

	return 0;
}

/* Word wrapping function used for cleaner output
// Grabbed from http://rosettacode.org/wiki/Word_wrap#C.2B.2B
*/
std::string wrap(const char *text)
{
    std::istringstream words(text);
    std::ostringstream wrapped;
    std::string word;
 
    if (words >> word) {
        wrapped << word;
        size_t space_left = LINE_LENGTH - word.length();
        while (words >> word) {
            if (space_left < word.length() + 1) {
                wrapped << '\n' << word;
                space_left = LINE_LENGTH - word.length();
            } else {
                wrapped << ' ' << word;
                space_left -= word.length() + 1;
            }
        }
    }
    return wrapped.str();
}