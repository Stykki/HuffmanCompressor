-------------------- Compiling ----------------------
g++ -std=c++11 main.cpp -o compressor
(This has been tested on 2 windows 10 machines and on a rpi4 running ubuntu 20.4)

-------------------- Compressing --------------------

./compressor -c {Filename to compress} {output file name}


-------------------- Decompressing ------------------

./compressor -u {Compressed file} {output file name}


-------------------- How it works -------------------

When compressing a file, first the file to be compressed is read in char by char.
Each char is added to a map that counts the apperance of that char.

Then a huffman tree is created using a priority queue ordered by how often a char appeared in the input file.

When writing the binary a hashmap is created from the huffman tree, with chars as keys and their paths as values.
That hashmap is then written to the output binary file.
All chars that appeared in the original file are written as their binary path.

When decompressing, the previously written map is read from the binary and all subsiquent binary is tested with the created map.
when a match is found that character gets written to the output file.

We tested this on the bible and it worked like a charm, included in bible.txt is the whole bible for you to compress and decompress.