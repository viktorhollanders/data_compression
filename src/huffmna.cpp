#include "huffman.h"
#include <iostream>
#include <cassert>
using namespace std;

// A function that counts the frequency of bytes
int Huffman::count_frequency(string inputFile){
  ifstream stream(inputFile, ios::in | ios::binary);

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

// A function that builds the symbolTable table
void Huffman::build_symbol_table(Node* node, vector<char>& vec) {
  // Base case: if it's a leaf node, store the code in the symbolTable table
  if (node->isLeaf()) {
    symbolTable[node->byte] = vec;
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

// A function that compresses the data
void Huffman::compress(string fileToEncode, string compressedFile) {
  ofstream encodeStream(compressedFile, ios::out | ios::binary);

  if (!encodeStream) {
      cout << "Error opening output file for writing!" << endl;
      return;
  }

  int symbolTableSize = symbolTable.size();
  encodeStream.write(reinterpret_cast<const char*>(&symbolTableSize), sizeof(symbolTableSize));

  for (const auto& entry : symbolTable) {
      unsigned char key = entry.first;
      const vector<char>& value = entry.second;

      // Write symbol (byte)
      encodeStream.write(reinterpret_cast<const char*>(&key), sizeof(key));

      // Write code length
      int size_of_value = value.size();
      encodeStream.write(reinterpret_cast<const char*>(&size_of_value), sizeof(size_of_value));

      // Write code as a sequence of characters
      encodeStream.write(value.data(), value.size());
  }

  ifstream originStream(fileToEncode, ios::in | ios::binary);

  if (!originStream) {
    cout << "Error opening input file for reading!" << endl;
    return;
  }

  unsigned char byte;

  while (originStream.read(reinterpret_cast<char*>(&byte), 1)) {
    auto keyToFind = symbolTable.find(byte);
    const vector<char>& value = keyToFind->second;

    // For debugging
    // cout << "Symbol: "  << keyToFind->first << ", Huffman Code: ";
    // for (int i = 0; i < value.size(); i++) {
    //   cout << value[i] << " ";
    // }
    // cout << endl;

    // Write Huffman code length
    int size_of_value = value.size();
    encodeStream.write(reinterpret_cast<const char*>(&size_of_value), sizeof(size_of_value));

    // Write Huffman code as a sequence of characters
    encodeStream.write(value.data(), value.size());
  }

  originStream.close();
  encodeStream.close();
}


void Huffman::decompress(string compressedFile, string outputFile) {
  ifstream compressedStream(compressedFile, ios::in | ios::binary);

  if (!compressedStream) {
    cout << "Error opening input file for reading!" << endl;
    return;
  }

  int symbolTableSize;
  compressedStream.read(reinterpret_cast<char*>(&symbolTableSize), sizeof(symbolTableSize));


  for (int i = 0; i < symbolTableSize; i++) {
    unsigned char key;
    int sizeOfValue;
    vector<char> value;

    compressedStream.read(reinterpret_cast<char*>(&key), sizeof(key));
    compressedStream.read(reinterpret_cast<char*>(&sizeOfValue), sizeof(sizeOfValue));

    value.resize(sizeOfValue);
    compressedStream.read(value.data(), sizeOfValue);

    symbolTable[key] = value;

    // std::cout << "Symbol: " << key << ", Huffman Code: ";
    // for (char c : value) {
    // cout << c;
    // }
    // cout << std::endl;
  }

  
}