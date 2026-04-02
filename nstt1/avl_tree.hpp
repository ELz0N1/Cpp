#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
struct AVLNode {
  AVLNode<T>(T k);
  AVLNode<T>(const AVLNode<T>& other);
  AVLNode<T>(AVLNode<T>&& other);
  AVLNode<T>& operator=(AVLNode<T> other);
  ~AVLNode<T>();

  T key;
  AVLNode<T>* left;
  AVLNode<T>* right;
  int height;
};

template <typename T>
class AVLTree {
 public:
  AVLTree<T>();
  AVLTree<T>(const AVLTree<T>& other);
  AVLTree<T>(AVLTree<T>&& other);
  AVLTree<T>& operator=(AVLTree<T> other);
  ~AVLTree<T>();

  void insert(T key) { root_ = insert(root_, key); }

  void remove(T key) { root_ = deleteNode(root_, key); }

  bool search(T key) { return search(root_, key); }

 private:
  AVLNode<T>* root_;

  int height(AVLNode<T>* node);

  int balanceFactor(AVLNode<T>* node);

  AVLNode<T>* rightRotate(AVLNode<T>* y);
  AVLNode<T>* leftRotate(AVLNode<T>* x);

  AVLNode<T>* insert(AVLNode<T>* node, T key);

  AVLNode<T>* minValueNode(AVLNode<T>* node);

  AVLNode<T>* deleteNode(AVLNode<T>* root_, T key);

  bool search(AVLNode<T>* root_, T key);

  void destroyTree(AVLNode<T>* root_);

  AVLNode<T>* copy(AVLNode<T>* node);
};

#endif