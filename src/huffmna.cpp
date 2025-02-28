#include "huffman.h"
#include <iostream>
#include <cassert>
using namespace std;

// A function that counts the frequency of bytes
int Huffman::count_frequency(string fileName){
  ifstream stream(fileName, ios::in | ios::binary);

  if (!stream) {
    cout << "file cant be read" << endl;
    return 1;
  }

  unsigned char byte;

  while (stream.read(reinterpret_cast<char*>(&byte), 1)) {
    if (frequency.count(byte)) {
      frequency[byte] += 1;
    } else {
      frequency[byte] = 1;
    }
  }
  stream.close();
  return 0;
}

// A function to populate the pq
void Huffman::populate_pq (){
  for (auto iter = frequency.begin(); iter != frequency.end(); iter++) {
    unsigned char elm = iter->first;
    int freq = iter->second;
    Node* new_node = new Node();
    new_node->byte = elm;
    new_node->weight = freq;
    pq.push(new_node);
  }
}



// A function that builds the huffman tree
void Huffman::build_huffman_tree() {
  while (pq.size() > 1) {
    Node* new_node = new Node();
    Node* item1 = pq.top();
    pq.pop();
    Node* item2 = pq.top();
    pq.pop();

    if (item1->weight > item2->weight ||
      (item1->weight == item2->weight && item1->byte > item2->byte)) {
      swap(item1, item2);
    }

    new_node->left = item1;
    new_node->right = item2;
    new_node->weight = item1->weight + item2->weight;

    if (pq.empty()) {
      root = new_node;
      break;
    }

    pq.push(new_node);
  }
}

// A function that builds the symbol table
void Huffman::build_symbol_table(Node* node, vector<char>& vec) {
  // Base case: if it's a leaf node, store the code in the symbol table
  if (node->isLeaf()) {
    symbol[node->byte] = vec;
    return;
  }

  // Traverse left: append '0' for left child
  vec.push_back('0');
  build_symbol_table(node->left, vec);
  vec.pop_back(); // Backtrack after traversing left

  // Traverse right: append '1' for right child
  vec.push_back('1');
  build_symbol_table(node->right, vec);
  vec.pop_back(); // Backtrack after traversing right
}

void Huffman::compress(string fileToEncode, string compressedFile) {
  ifstream originStream(fileToEncode, ios::in | ios::binary);
  ofstream encodeStream(compressedFile, ios::out | ios::binary);

  if (!originStream) {
    cout << "Error opening input file for reading!" << endl;
    return;
  }

  if (!encodeStream) {
    cout << "Error opening output file for writing!" << endl;
    return;
  }

  // add symbol table to map
  for (const auto& entry : symbol ){
    unsigned char key = entry.first;
    const vector<char>& value = entry.second;

    // add the key to the output file
    encodeStream.write(reinterpret_cast<const char*>(&key), sizeof(key));

    // add the vector to the output file
    int size_of_value = value.size();
    encodeStream.write(reinterpret_cast<const char*>(&value), sizeof(size_of_value));

    encodeStream.write(value.data(), size_of_value);
  }

  unsigned char byte;
  while (originStream.read(reinterpret_cast<char*>(&byte), 1)) {
    auto entry = symbol.find(byte);

    if (entry != symbol.end()) {
      const vector<char>& bitValue = entry->second;
      int size_of_value = bitValue.size();
      encodeStream.write(reinterpret_cast<const char*>(&bitValue), sizeof(size_of_value));;
    }
  }

  originStream.close();
  encodeStream.close();
}