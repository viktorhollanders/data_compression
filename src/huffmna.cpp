#include "huffman.h"
#include <iostream>
#include <cassert>
using namespace std;

// A function that counts the frequency of bytes
int Huffman::count_frequency(string inputFile){
  ifstream stream(inputFile, ios::in | ios::binary);

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
  vec.pop_back();

  // Traverse right: append '1' for right child
  vec.push_back('1');
  build_symbol_table(node->right, vec);
  vec.pop_back();
}

// A function that compresses the data
void Huffman::compress(string fileToEncode, string compressedFile) {
  ofstream encodeStream(compressedFile, ios::out | ios::binary);

  if (!encodeStream) {
      cout << "Error opening output file to encode for writing!" << endl;
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
    cout << "Error opening encoded file for reading!" << endl;
    return;
  }

  unsigned char byte;

  while (originStream.read(reinterpret_cast<char*>(&byte), 1)) {
    auto keyToFind = symbolTable.find(byte);
    const vector<char>& value = keyToFind->second;


    // Write Huffman code length
    int size_of_value = value.size();
    encodeStream.write(reinterpret_cast<const char*>(&size_of_value), sizeof(size_of_value));

    // Write Huffman code as a sequence of characters
    encodeStream.write(value.data(), value.size());
  }

  originStream.close();
  encodeStream.close();
}

// A function that reconstructs the Huffman tree from the decompressed file
void reconstruct_huffman_tree(Node* root, map<unsigned char, vector<char>> table, vector<char> bitString) {
  root = new Node();
  for(auto iter = table.begin(); iter != table.end(); iter++ ) {
    bitString = iter->second;

    Node* current_node = root;

    for (auto bit : bitString ) {
      if (bit == '1') {
        if (!current_node->right) {
          current_node->right = new Node();
        }
        current_node = current_node->right;
      } else {
        if (!current_node->left) {
          current_node->left = new Node();
        }
        current_node = current_node->left;
      }
    }
    current_node->byte = iter->first;
  }
}

// A helper function that rebuild the symbol table
void Huffman::rebuild_symbol_table(ifstream& inStream) {
  int symbolTableSize;
  inStream.read(reinterpret_cast<char*>(&symbolTableSize), sizeof(symbolTableSize));


  for (int i = 0; i < symbolTableSize; i++) {
    unsigned char key;
    int sizeOfValue;
    vector<char> value;

    inStream.read(reinterpret_cast<char*>(&key), sizeof(key));
    inStream.read(reinterpret_cast<char*>(&sizeOfValue), sizeof(sizeOfValue));

    value.resize(sizeOfValue);
    inStream.read(value.data(), sizeOfValue);

    symbolTable[key] = value;
  }
}

// A functoin that rebuilds the Huffman tree from the compressed data
void Huffman::rebuild_huffman_tree() {
  root = new Node();
  for(auto iter = symbolTable.begin(); iter != symbolTable.end(); iter++ ) {
    bitVector = iter->second;

    Node* current_node = root;

    for (auto bit : bitVector ) {
      if (bit == '1') {
        if (!current_node->right) {
          current_node->right = new Node();
        }
        current_node = current_node->right;
      } else {
        if (!current_node->left) {
          current_node->left = new Node();
        }
        current_node = current_node->left;
      }
    }
    current_node->byte = iter->first;
  }
}

// A helper functoin that writes to the file
void Huffman::write_to_file(ifstream& inStream, ofstream& outStream) {
  Node* walk_node = root;

  unsigned char byte;

  while(inStream.read(reinterpret_cast<char*>(&byte), 1)) {
    if (byte == '1') {
      walk_node = walk_node->right;
    } else if (byte == '0') {
      walk_node = walk_node->left;
    }

    if (walk_node->isLeaf()) {
      outStream << walk_node->byte;
      walk_node = root;
    }
  }
}

//A function that decompresses the file
void Huffman::decompress(string compressedFile, string outputFile) {
  ifstream compressedStream(compressedFile, ios::in | ios::binary);

  if (!compressedStream) {
    cout << "Error opening input file for reading!" << endl;
    return;
  }

  Huffman::rebuild_symbol_table(compressedStream);
  Huffman::rebuild_huffman_tree();

  ofstream outStream(outputFile);

  Huffman::write_to_file(compressedStream, outStream);
  cout << "writing to file" << endl;

  compressedStream.close();
  outStream.close();
}