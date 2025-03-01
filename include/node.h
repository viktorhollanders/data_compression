#ifndef NODE_H
#define NODE_H

struct Node
{
  struct Node *parent;
  struct Node *left;
  struct Node *right;
  int weight;
  unsigned char byte;
  Node(): parent(nullptr), left(nullptr), right(nullptr){}
  bool isLeaf() {
    return left == nullptr && right == nullptr;
  };
};

#endif