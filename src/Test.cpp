#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include "HuffmanNode.h"
#include "HuffmanTree.h"

using namespace std;

void listFiles(string, bool, vector<string>*);

int main(int argc, char* argv[]){
	string inDir;
	vector<string> *inFiles = new vector<string>();
	vector<HuffmanTree> *trees = new vector<HuffmanTree>();
	if(argc > 1){
		if(strcmp(argv[1], "-i") == 0)
			inDir = argv[2];
	}

	std::streambuf *cinbuf = std::cin.rdbuf();
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	listFiles(inDir, false, inFiles);
	std::ifstream testFile;
	system("mkdir output");
	for(int i = 0; i < inFiles->size(); i++){

		std::string testString = "";
		testFile.open(inFiles->at(i));
		std::cin.rdbuf(testFile.rdbuf());
		std::getline(testFile, testString);
		inFiles->at(i).replace(0, inDir.length(), "");
		std::ofstream out("output/" + inFiles->at(i));
		std::cout.rdbuf(out.rdbuf());

		HuffmanTree *huffTree = new HuffmanTree(testString);
		huffTree->buildWords();
		huffTree->initSubTrees();
		huffTree->buildSubtree();
		huffTree->buildBitmap();
		huffTree->findCompression(testString);

		testFile.close();
		std::cin.rdbuf(cinbuf);   //reset to standard input again
		std::cout.rdbuf(coutbuf); //reset to standard output again
		
	}	

	//std::cin.rdbuf(cinbuf);   //reset to standard input again
	//std::cout.rdbuf(coutbuf); //reset to standard output again

	return 0;
}

bool isDir(string dir)
{
    struct stat fileInfo;
    stat(dir.c_str(), &fileInfo);
    if (S_ISDIR(fileInfo.st_mode)) {
        return true;
    } else {
        return false;
    }
}

void listFiles(std::string baseDir, bool recursive, vector<string> *input)
{
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(baseDir.c_str())) == NULL) {
        cout << "[ERROR: " << errno << " ] Couldn't open " << baseDir << "." << endl;
        return;
    } else {
        while ((dirp = readdir(dp)) != NULL) {
            if (dirp->d_name != string(".") && dirp->d_name != string("..")) {
                if (isDir(baseDir + dirp->d_name) == true && recursive == true) {
                    cout << "[DIR]\t" << baseDir << dirp->d_name << "/" << endl;
                    listFiles(baseDir + dirp->d_name + "/", true, input);
                } else {
                    cout << "[FILE]\t" /*<< baseDir */<< dirp->d_name << endl;
					input->push_back(baseDir + "/" + dirp->d_name);
                }
            }
        }
        closedir(dp);
    }
}
