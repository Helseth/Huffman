#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <algorithm>
#include "HuffmanNode.h"
#include "HuffmanTree.h"

using namespace std;

void listFiles(string, bool, vector<string>*);
void usage();

int main(int argc, char* argv[]){
	string inDir;
	bool title = false;
	bool sing = false;
	bool verbose = false;
	bool combine = false;
	string tmpStr = "";
	std::string testString = "";
	vector<string> *inFiles = new vector<string>();
	vector<HuffmanTree> *trees = new vector<HuffmanTree>();
	vector<string> *args = new vector<string>(argv + 1, argv + argc);
	if(std::find(args->begin(), args->end(), "-i") != args->begin())
		usage();
	else
		inDir = argv[2];
	title = (std::find(args->begin(), args->end(), "-t") != args->end());
	sing = (std::find(args->begin(), args->end(), "-s") != args->end());
	combine = (std::find(args->begin(), args->end(), "-c") != args->end());
	verbose = (std::find(args->begin(), args->end(), "-v") != args->end());

	std::streambuf *cinbuf = std::cin.rdbuf();
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	listFiles(inDir, false, inFiles);
	std::ifstream testFile;
	system("rmdir /s /q output");
	system("mkdir output");
	ofstream outFile;
	verboseG = verbose;

	if(sing == true){
		outFile.open("output/compr.txt",std::ofstream::out);
		std::cout.rdbuf(outFile.rdbuf());
	}
	if(!combine){
		for(int i = 0; i < inFiles->size(); i++){


			testFile.open(inFiles->at(i));
			std::cin.rdbuf(testFile.rdbuf());
			std::getline(testFile, testString);
			inFiles->at(i).replace(0, inDir.length() + 1, "");
			if(sing == false){
				outFile.open("output/" + inFiles->at(i),std::ofstream::out);
				std::cout.rdbuf(outFile.rdbuf());
			}
			HuffmanTree *huffTree = new HuffmanTree(testString);
			huffTree->buildWords();
			huffTree->initSubTrees();
			huffTree->buildSubtree();
			huffTree->buildBitmap();
			huffTree->findCompression(testString);
			testString = "";
			testFile.close();
			std::cin.rdbuf(cinbuf);   //reset to standard input again
			if(sing == false){
				outFile.close();
				std::cout.rdbuf(coutbuf); //reset to standard output again
			}

		}
	}
	if(combine){
		for(int i = 0; i < inFiles->size(); i++){
			testFile.open(inFiles->at(i));
			std::cin.rdbuf(testFile.rdbuf());
			std::getline(testFile, tmpStr);
			testString += tmpStr;
			tmpStr = "";
			testFile.close();
			std::cin.rdbuf(cinbuf);   //reset to standard input again
		}
		HuffmanTree *huffTree = new HuffmanTree(testString);
		huffTree->buildWords();
		huffTree->initSubTrees();
		huffTree->buildSubtree();
		huffTree->buildBitmap();
		huffTree->findCompression(testString);
		if(sing == false){
			outFile.close();
			std::cout.rdbuf(coutbuf); //reset to standard output again
		}
	}
	if(sing == true){
		outFile.close();
		std::cout.rdbuf(coutbuf); //reset to standard output again
	}

	return 0;
}

bool isDir(string dir){
	struct stat fileInfo;
	stat(dir.c_str(), &fileInfo);
	if (S_ISDIR(fileInfo.st_mode)) {
		return true;
	} else {
		return false;
	}
}

void listFiles(std::string baseDir, bool recursive, vector<string> *input){
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

void usage(){
	cout << "Usage: Huffman.exe -i <input directory> [-s] [-t/-c] [-v]" << endl;
	cout << "-i: input" <<endl;
	cout << "-s: single file mode, all output is placed into a single file"<< endl;
	cout << "-t: individual mode, each input file builds a unique tree" <<endl;
	cout << "-c: combined mode, all input files are concatenated" <<endl;
	cout << "-v: verbose output, displays word-to-bitstring mappings, total input bit count, and compressed bit count" <<endl;
	cout << "Note: combine mode only works in single file mode" << endl;
	exit(0);
}
