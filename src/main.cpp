#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include "huffman.h"

using namespace std;

int main(int argc, char* argv[]) {

  Huffman huffman;

  string inputFile = "test_files/test.txt";
  string compressFile = "test_files/compre_test.txt";
  string outputFile = "test_files/output_test.txt";




  huffman.count_frequency(inputFile);

  huffman.populate_pq();
  // huffman.print_pq();

  huffman.build_huffman_tree();
  // huffman.print_huffman_tree(huffman.root, 0);

  huffman.build_symbol_table(huffman.root, huffman.byteVector);
  // huffman.print_symbol_table(huffman.symbolTable);

  huffman.compress(inputFile, compressFile);
  cout << "compresed sucseffulty" << endl;

  huffman.decompress(compressFile, outputFile);

  cout << "decompressed sucseffulty" << endl;


  return 0;
}

