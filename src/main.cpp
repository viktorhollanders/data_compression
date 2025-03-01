#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "huffman.h"

using namespace std;

void checkAndCreateFile(const std::string& filePath) {
  std::ifstream infile(filePath);
  if (infile.good()) {
    return;
  } else {
      std::ofstream outfile(filePath);
      if (outfile.is_open()) {
          return;
      } else {
          std::cout << "Failed to create the file: " << filePath << std::endl;
      }
  }
}

int main(int argc, char* argv[]) {

  Huffman huffman;

  if (argc == 1) {
    cout << "No comand line arguments provided running demo" << endl;

    string inputFile = "demo/test.txt";
    string compressFile = "demo/compress.txt";
    string outputFile = "demo/output.txt";

    huffman.count_frequency(inputFile);
    huffman.populate_pq();
    huffman.build_huffman_tree();
    huffman.build_symbol_table(huffman.root, huffman.bitVector);
    huffman.compress(inputFile, compressFile);
    huffman.decompress(compressFile, outputFile);

    cout << "Demo ran successfully 🚀" << endl;
  } else {
    if (strcmp(argv[1], "-e") == 0) {
      string inputFile = argv[2];
      string outputFile = argv[3];

      // checkAndCreateFile(outputFile);

      huffman.count_frequency(inputFile);
      huffman.populate_pq();
      huffman.build_huffman_tree();
      huffman.build_symbol_table(huffman.root, huffman.bitVector);


      huffman.compress(inputFile, outputFile);

      cout << "file sucseffuly compressed" << endl;
    } else if (strcmp(argv[1], "-d") == 0) {
      string inputFile = argv[2];
      string outputFile = argv[3];

      // checkAndCreateFile(outputFile);

      huffman.decompress(inputFile, outputFile);
      cout << "file sucseffuly decompressed take a look in the output directory to see the resault 🚀" << endl;
    }
  }

  return 0;
}

