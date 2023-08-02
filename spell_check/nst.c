#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nst.h"
#include "cs136-trace.h"

// === N-Search Tree Node =====================================================

// LETTERS represents the number of children in a nst_node
const int LETTERS = 26;

// nst_node represents a node in a n-search tree
struct nst_node {
  bool end;                   // indicates if a node can be the end of a word
  struct nst_node **children; // pointer to the node's children
};

// your implementation goes here

// === N-Search Tree ==========================================================

// nst represents a n-search tree
struct nst {
  struct nst_node *root;
};

// See nst.h for documentation
struct nst *nst_create() {
  struct nst *n = malloc(sizeof(struct nst));
  n->root = NULL;
  return n;
}


// node_destroy(node) releases all resources used by node
// effects: invalidates node
// time: O(n), where n is the number of nodes in node
void node_destroy(struct nst_node *node) {
  if (node) {
    for (int i = 0; i < LETTERS; ++i) {
      node_destroy(node->children[i]);
    }
    free(node->children);
    free(node);
  }
}

// See nst.h for documentation
void nst_destroy(struct nst *tree) {
  assert(tree);
  node_destroy(tree->root);
  free(tree);
}

// convert_lowercase(word) converts word to lowercase
// effects: allocates heap memory [client must call nst_spellcheck or nst_insert]
// time: O(n) where n is the length of *word
char *convert_lowercase(const char *word) {
  assert(word);
  int i = 0;
  char *lo_word = malloc(strlen(word) * sizeof(char) + 1);
  strcpy(lo_word, word); 
  while (lo_word[i]) {
    if (lo_word[i] >= 'A' && lo_word[i] <= 'Z') {
      lo_word[i] += 32;
    }
    ++i;
  }
  return lo_word;
}

// new_leaf(word) creates a new leaf containing word in a tree
// requires: *word must contain letters only
// time: O(1)
struct nst_node *node_create() {
  struct nst_node *node = malloc(sizeof(struct nst_node));
  node->children = malloc(LETTERS * sizeof(struct nst_node *));
  for (int i = 0; i < LETTERS; ++i) {
    node->children[i] = NULL;
  }
  node->end = false;
  return node;
}

// node_insert(node, word, i) inserts a new word in node
// effects: mutates *node
// requires: *word must contain letters only
// time: O(n), where n is the length of *word
void node_insert(struct nst_node *node, char *word, int i) {
  assert(node);
  assert(word);
  if (word[i] == 0) {
    trace_int(word[i - 1] - 97);
    trace_ptr(node->children[word[i - 1] - 97]);
    free(word);
    return;
  }
  if (node->children[word[i] - 97]) {
    trace_msg(node exists);
    if (word[i + 1] == 0) {
      node->children[word[i] - 97]->end = true;
    }
    node_insert(node->children[word[i] - 97], word, i + 1);
  } else {
    trace_msg(new node);
    trace_int(word[i] - 97);
    node->children[word[i] - 97] = node_create();
    trace_ptr(node->children[word[i] - 97]);
    if (word[i + 1] == 0) {
      trace_int(word[i] - 97);
      node->children[word[i] - 97]->end = true;
    }
    node_insert(node->children[word[i] - 97], word, i + 1);
  }
}

// See nst.h for documentation
void nst_insert(struct nst *tree, const char *word) {
  assert(tree);
  assert(word);
  char *lo_word = convert_lowercase(word);
  if (!(tree->root)) {
    tree->root = node_create();
  }
  node_insert(tree->root, lo_word, 0);
}

// node_check(node, word, i) checks if *word is in *node.
// requires: *word must contain letters only
// time:     O(n), where n is the length of *word
bool node_check(struct nst_node *node, char *word, int i) {
  assert(node);
  assert(word);
  if (node->children[word[i] - 97]) {
    trace_msg(exists);
    if (word[i + 1] == 0) {
      trace_msg(i + 1);
      trace_ptr(node->children[word[i] - 97]);
      int num = word[i] - 97;
      free(word);
      return node->children[num]->end;
    }
    trace_int(word[i] - 97);
    return node_check(node->children[word[i] - 97], word, i + 1);
  } else {
    trace_msg(not exists);
    free(word);
    return false;
  }
}

// See nst.h for documentation
bool nst_spellcheck(const struct nst *tree, const char *word) {
  assert(tree);
  assert(word);
  char *lo_word = convert_lowercase(word);
  if (tree->root) {
    return node_check(tree->root, lo_word, 0);
  }
  return false;
}

// node_memory(node) returns the amount of memory that *node is using.
// time: O(n), where n is the number of nodes in node
void node_memory(const struct nst_node *node, int *mem) {
  const int mem_node = 224;
  if (node) {
    for (int i = 0; i < LETTERS; ++i) {
      if (node->children[i]) {
        *mem += mem_node;
        node_memory(node->children[i], mem);
      }
    }
  }
}

// See nst.h for documentation
int nst_memory(const struct nst *tree) {
  assert(tree);
  int i = 232;
  int *mem = &i;
  if (tree->root) {
    node_memory(tree->root, mem);
    return *mem;
  }
  return 0;
}