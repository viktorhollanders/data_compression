#include "huffman.h"
#include <iostream>
using namespace std;

// A function that counts the frequency of bytes
int Huffman::count_frequency(string fileName){
  ifstream stream(fileName, ios::out | ios::binary);

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

// A function that prints the huffman tree
void Huffman::print_huffman_tree(Node* node, int depth = 0) {
  if (node == nullptr) return; // Base case

  // Indent based on depth to show tree structure
  for (int i = 0; i < depth; i++) cout << "  ";

  // Print node info
  cout << "(" << node->byte << ", " << node->weight << ")" << endl;

  // Recur for left and right children, increasing depth
  print_huffman_tree(node->left, depth + 1);
  print_huffman_tree(node->right, depth + 1);
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