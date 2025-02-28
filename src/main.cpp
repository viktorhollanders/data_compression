


// steps

// 1. read in a file if stream in binary nodes
// 2. go throught the binary string
// 3. store in a map
// 4. remove the two minimum values
// 5. run the hufman algorithm
// 6. add the tree first and then the look up table

// 7. the three pices
  // - look up table
  // - count table
  // - tree

// write the data as binary?
// a shell script / command line tool


#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include "huffman.h"

using namespace std;

int main(int argc, char* argv[]) {

  Huffman huffman;

  string fileName = "test_files/test.txt";


  huffman.count_frequency(fileName);
  
  huffman.populate_pq();
  huffman.print_pq();

  huffman.build_huffman_tree();
  huffman.print_huffman_tree(huffman.root, 0);

  huffman.build_symbol_table(huffman.root, huffman.byteVector);
  huffman.print_symbol_table(huffman.symbol);



  return 0;
}