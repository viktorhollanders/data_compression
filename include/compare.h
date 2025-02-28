#ifndef COMPARE
#define COMPARE

#include "node.h"

struct Compare {
  bool operator()(const Node* a, const Node* b) const {
    if (a->weight == b->weight) {
      return a->byte > b->byte;
    }
    return a->weight > b->weight;
  }
};

#endif