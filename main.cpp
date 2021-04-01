#include <iostream>
#include <string>
#include <unordered_map>
#include "lib/decode.cpp"
#include "lib/huffmanTree.cpp"
#include "lib/encode.cpp"

using namespace std;

void encode(string inputFile, string outpFile){
    unordered_map<char, int> *countMap = new unordered_map<char, int>();
    vector<char> *allChars = new vector<char>();
    readUncodedFile(countMap, inputFile, allChars);
    BinaryTree *huffmanTree = new BinaryTree(countMap);
    delete countMap;
    writeBinaryFromTree(huffmanTree, &outpFile, allChars);
    delete allChars;
    delete huffmanTree;
}

void decode(string inputFile, string outpFile){
    unordered_map<string, char> *map = new unordered_map<string, char>();
    vector<char> *allChars = new vector<char>();
    readEncodedFile(map, inputFile, allChars, outpFile);
    delete map;
    delete allChars;
}

int main(int argc, char *argv[]){
    if (argc == 4){

        string inputFile = argv[2];
        string outpFile = argv[3];
        string choice = argv[1];

        if(choice.compare("-c") == 0){
            encode(inputFile, outpFile);

        }
        else if (choice.compare("-u") == 0) {
            decode(inputFile, outpFile);
        }
    }
    
    return 0;
}

