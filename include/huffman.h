#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <map>
#include <queue>
#include <fstream>
#include <string>

#include "node.h"
#include "compare.h"

using namespace std;

class Huffman {
  map<unsigned char, int> frequency;
  /* A helper functoin that rebuilds the symbol table from the compressed data */
  void rebuild_symbol_table(ifstream& inStream);
  /* A helper functoin that rebuilds the Huffman tree from the compressed data */
  void rebuild_huffman_tree();
  /* A helper functoin that writes the data to a file */
  void write_to_file(ifstream& inStream, ofstream& outStream);

  public:
  priority_queue<Node*, vector<Node*>, Compare> pq;
  Node* root;
  map<unsigned char, vector<char>> symbolTable;
  vector<char> bitVector;


    /* A function that counts the frequency of bytes */
    int count_frequency(string inputFile);

    /* A function to populate the pq */
    void populate_pq ();

    /* A function that builds a Huffman tree*/
    void build_huffman_tree();

    /* A function to print the content of the pq */
    void print_pq();

    /* A functoin that prints the tree */
    void print_huffman_tree(Node* node, int depth);

    /* A function that builds the symbolTable table */
    void build_symbol_table(Node* node, vector<char> &vec);

    /* A function that prints the symbolTable table */
    void print_symbol_table(map<unsigned char, vector<char>> &map);

    /* A function to compress the file */
    void compress(string fileToEncode, string compressedFile);

   void build_huffman_tree_decompress(map<unsigned char, vector<char>> symbolTable);

    /* A function to decompress the file */
    void decompress(string compressedFile, string outputFile);

};

#endif