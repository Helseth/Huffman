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

void listFiles(std::string, bool, std::vector<std::string>*);
void usage();

int main(int argc, char* argv[]){
	
	bool title, sing, verbose, combine,	help, graph;
	title = sing = verbose = combine = help = graph = false;
	std::string inDir;
	std::string tmpStr = "";
	std::string testString = "";
	std::vector<std::string> *inFiles = new std::vector<std::string>();
	std::vector<HuffmanTree*> *trees = new std::vector<HuffmanTree*>();
	std::vector<std::string> *args = new std::vector<std::string>(argv + 1, argv + argc);
	if(std::find(args->begin(), args->end(), "-i") != args->begin())
		usage();
	else
		inDir = args->at(1);
	title = (std::find(args->begin(), args->end(), "-t") != args->end());
	sing = (std::find(args->begin(), args->end(), "-s") != args->end());
	combine = (std::find(args->begin(), args->end(), "-c") != args->end());
	verbose = (std::find(args->begin(), args->end(), "-v") != args->end());
	help = (std::find(args->begin(), args->end(), "-h") != args->end());
	graph = (std::find(args->begin(), args->end(), "-g") != args->end());
	if((!title && !combine) || (title && combine))
		usage();
	if(help)
		usage();
	if(graph)
		graphSet = true;

	std::streambuf *cinbuf = std::cin.rdbuf();
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	listFiles(inDir, false, inFiles);
	std::ifstream testFile;
	system("rmdir /s /q output");
	system("mkdir output");
	std::ofstream outFile;
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

			trees->push_back(new HuffmanTree(testString));		
			trees->at(i)->buildWords();
			trees->at(i)->initSubTrees();
			trees->at(i)->buildSubtree();
			trees->at(i)->buildBitmap();
			trees->at(i)->findCompression(testString);
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
			trees->push_back(new HuffmanTree(testString));
			trees->at(0)->buildWords();
			trees->at(0)->initSubTrees();
			trees->at(0)->buildSubtree();
			trees->at(0)->buildBitmap();

		if(!graph)
			trees->at(0)->findCompression(testString);
		
		if(sing == false){
			outFile.close();
			std::cout.rdbuf(coutbuf); //reset to standard output again
		}
	}
	if(sing == true){
		if(graph){
			for(int i = 0; i < inFiles->size(); i++){
				double compr = 0;
				testFile.open(inFiles->at(i));
				std::getline(testFile, tmpStr);
				compr = trees->at(0)->findCompression(tmpStr);
				//if(compr / (tmpStr.length() * 8) <= .65){
				if(verboseG)
					std::cout << inFiles->at(i) << ": ";
				std::cout << compr / (tmpStr.length() * 8) << ",";
				if(verboseG)
					std::cout << std::endl;
				//}
				testFile.close();
			}
		}
		outFile.close();
		std::cout.rdbuf(coutbuf); //reset to standard output again
	}

	return 0;
}

bool isDir(std::string dir){
	struct stat fileInfo;
	stat(dir.c_str(), &fileInfo);
	if (S_ISDIR(fileInfo.st_mode)) {
		return true;
	} else {
		return false;
	}
}

void listFiles(std::string baseDir, bool recursive, std::vector<std::string> *input){
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(baseDir.c_str())) == NULL) {
		std::cout << "[ERROR: " << errno << " ] Couldn't open " << baseDir << "." << std::endl;
		return;
	} else {
		while ((dirp = readdir(dp)) != NULL) {
			if (dirp->d_name != std::string(".") && dirp->d_name != std::string("..")) {
				if (isDir(baseDir + dirp->d_name) == true && recursive == true) {
					std::cout << "[DIR]\t" << baseDir << dirp->d_name << "/" << std::endl;
					listFiles(baseDir + dirp->d_name + "/", true, input);
				} else {
					std::cout << "[FILE]\t" /*<< baseDir */<< dirp->d_name << std::endl;
					input->push_back(baseDir + "/" + dirp->d_name);
				}
			}
		}
		closedir(dp);
	}
}

void usage(){
	std::cout << "Usage: Huffman.exe -i <input directory> [-s] [-t/-c] [-g] [-v]" << std::endl;
	std::cout << "-i: input" << std::endl;
	std::cout << "-s: single file mode, all output is placed into a single file"<< std::endl;
	std::cout << "-t: individual mode, each input file builds a unique tree" << std::endl;
	std::cout << "-c: combined mode, all input files are concatenated to form 1 tree" << std::endl;
	std::cout << "-g: builds compression data for graphing from each input, based on all input files" << std::endl;
	std::cout << "-v: verbose output, displays word-to-bitstring mappings, total input bit count, and compressed bit count" << std::endl;
	std::cout << "Note: combine mode only works in single file mode" << std::endl;
	exit(0);
}
