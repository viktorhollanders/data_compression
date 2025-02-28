#include "huffman.h"
#include <iostream>
using namespace std;

// A function to print the pq
void Huffman::print_pq() {
  priority_queue<Node*, vector<Node*>, Compare> print_q = pq;
  while (!print_q.empty()) {
    // get the
    Node* topItem = print_q.top();
    unsigned char key = topItem->byte;
    int value = topItem->weight;

    // remove the item
    print_q.pop();

    cout << key << ": " << value << endl;
  }
}

// A function that prints the huffman tree
void Huffman::print_huffman_tree(Node* node, int depth = 0) {
  if (node == nullptr) return; // Base case

  for (int i = 0; i < depth; i++) cout << "  ";

  cout << "(" << node->byte << ", " << node->weight << ")" << endl;

  print_huffman_tree(node->left, depth + 1);
  print_huffman_tree(node->right, depth + 1);
}

// A function that prints the symbol table
void Huffman::print_symbol_table(map<unsigned char, vector<char>> &map){
  for(auto iter = map.begin(); iter != map.end(); iter++ ) {
    string byteString = "";

    for (int i = 0; i < iter->second.size(); i++) {
      byteString += iter->second[i];
    }

    cout << iter->first << " " << byteString << endl;
  }
}
