#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename K, typename V>
void print_map2(unordered_map<K,V> const &m)
{
    for (auto const& pair: m) {
        std::cout << "{" << pair.second << ": " << pair.first << "}\n";
    }
}

void readEncodedFile(unordered_map<string,char> *map, string inpFileName, vector<char> *outputVector, string outpFilename){
    ifstream f;
    f.open(inpFileName, ios::binary);
    char tempFint;
    unsigned int fLoop = 0;
    unsigned char firstBit = 128;
    // Count of all bits used by the compression algorithm
    f.get(tempFint);
    fLoop = (fLoop |((int) (unsigned char) tempFint)<<24);
    f.get(tempFint);
    fLoop = (fLoop |((int) (unsigned char) tempFint)<<16);
    f.get(tempFint);
    fLoop = (fLoop |((int) (unsigned char) tempFint)<<8);
    f.get(tempFint);
    fLoop = (fLoop |((int) (unsigned char) tempFint));

    char size;
    f.get(size);

    // This forloop reads in the huffman table
    for (int i = 0; i < (unsigned int)(unsigned char)size; i++){
        char redChar;
        char tempchar;
        f.get(redChar);     // reading in char (this char will be added to the ecoding table)
        f.get(tempchar);    // reading in size of bits that this char represents
        int sizeOfBits = (unsigned int)(unsigned char) tempchar;
        string path;
        int remainder = ((int)sizeOfBits % 8);
        int charCount = ((int)sizeOfBits / 8);
        f.get(tempchar);
        for (int j = 0; j<charCount; j++){
            for( int x = 0; x<8; x++){
                path += (tempchar & firstBit) ? "1" : "0";
                tempchar = tempchar << 1;
            }
            f.get(tempchar);
        }
        for( int x = 0; x<remainder; x++){
            path += (tempchar & firstBit) ? "1" : "0";
            tempchar = tempchar << 1;
        }
        map->insert(pair<string, char>(path,redChar));
    }

    cout << "huffman map read from file" << endl;
    print_map2(*map);

    int quotient = ((int)fLoop / 8)-1;

    char tempCharOne = 0;
    char tempCharTwo = 0;

    ofstream outpFile;
    outpFile.open(outpFilename);
    string path;

    for(int i = 0; i < quotient; i++){

        f.get(tempCharOne);
        tempCharTwo = tempCharOne;

        for(int j = 0; j < 8; j++){

            path += (tempCharTwo & firstBit) ? "1" : "0";
            tempCharTwo = tempCharTwo << 1;

            if (!(map->find(path) == map->end())){

                outpFile << map->at(path);
                path.clear();
            }
        }
    }


    outpFile.close();
    f.close();
}
 
