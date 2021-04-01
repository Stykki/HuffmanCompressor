#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename K, typename V>
void print_map(unordered_map<K,V> const &m)
{
    for (auto const& pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}
void writeBinaryFromTree(BinaryTree *bTree, string * outpFilename, vector<char>* allChars){

    ofstream outputStream;
    outputStream.open(*outpFilename, ios::binary);

    unordered_map<char, string> *map = bTree->getHash();

    // Creating space for total bit count
    for (int i = 0; i < 4; i++){
        outputStream.put(0x00);
    }

    // total chars in map
    outputStream.put((char)map->size());

    cout << "total characters in map: " << (int)(char)map->size() << endl;
    cout << "huffman map" << endl;
    print_map(*map);

    long tempOne;
    int writeArr[4] = {24, 16, 8, 0};
    for (auto const& pair: *map){
        outputStream.put((char)pair.first);
        outputStream.put((char)pair.second.size());

        int charCount = (pair.second.size() / 8)+1;

        char tempChar = 0;

        
        // converting our string binary representation into actual binary
        tempOne = strtol(pair.second.c_str(), NULL,2);

        tempOne = tempOne << (32-pair.second.size());

        unsigned long outpL = tempOne;

        char outp = 0xff;
        for(int i = 0; i < charCount; i++){
            outputStream.put(outp &(char)(outpL >> writeArr[i]));
        }
    
    }

    char tempPathChar = 0;
    int largeCount = 0;
    int count = 0;
    for(int i = 0; i < allChars->size()-1; i++){
        string path = map->at(allChars->at(i)); 

        for( int k = 0; k < path.size(); k++){

            if(count < 8){
                tempPathChar |= (path[k] == '1') ? 1:0;
                count++;
                largeCount++;
            }

            if (count == 8){
                outputStream.put(tempPathChar);
                tempPathChar = 0;
                count = 0;
            }
            tempPathChar = tempPathChar << 1;
        }

    }
    if ( count > 0 && count < 8){
        tempPathChar = tempPathChar << (8-count);
        outputStream.put(tempPathChar);
        largeCount+= (8-count);
    }

    cout << "Total bit count : " << (largeCount) << endl;

    outputStream.seekp(outputStream.beg);

    outputStream.put((largeCount & 0xff000000)>>24);

    outputStream.put((largeCount & 0x00ff0000)>>16);

    outputStream.put((largeCount & 0x0000ff00)>>8);

    outputStream.put((largeCount & 0x000000ff));

    outputStream.close();
}

void readUncodedFile(unordered_map<char, int>* hasmap, string filename, vector<char>* allChars){
    char *character;
    ifstream f;
    f.open(filename, ios::binary);
    

    while(!f.eof()){
        // creates a hashmap counting how often they appear in the file
        f.read(character, sizeof(char));
        if (*character != '\r'){ // frick windows line endings
            if (hasmap->find(*character) == hasmap->end()){
                    hasmap->insert(pair<char, int>{*character,1});
                }
            else{

                int count = hasmap->at(*character);
                hasmap->at(*character) = count + 1;
            }
            allChars->push_back(*character);
        }

    }
}

