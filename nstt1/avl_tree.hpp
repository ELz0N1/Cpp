#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>

using namespace std;

struct AVLNode {
  AVLNode(int k);
  AVLNode(const AVLNode& other);
  AVLNode(AVLNode&& other);
  AVLNode& operator=(AVLNode other);
  ~AVLNode();

  int key;
  AVLNode* left;
  AVLNode* right;
  int height;
};

class AVLTree {
 public:
  AVLTree();
  AVLTree(const AVLTree& other);
  AVLTree(AVLTree&& other);
  AVLTree& operator=(AVLTree other);
  ~AVLTree();

  void insert(int key) { root_ = insert(root_, key); }

  void remove(int key) { root_ = deleteNode(root_, key); }

  bool search(int key) { return search(root_, key); }

 private:
  AVLNode* root_;

  int height(AVLNode* node);

  int balanceFactor(AVLNode* node);

  AVLNode* rightRotate(AVLNode* y);

  AVLNode* leftRotate(AVLNode* x);

  AVLNode* insert(AVLNode* node, int key);

  AVLNode* minValueNode(AVLNode* node);

  AVLNode* deleteNode(AVLNode* root_, int key);

  bool search(AVLNode* root_, int key);

  void destroyTree(AVLNode* root_);

  AVLNode* copy(AVLNode* node);
};

#endif