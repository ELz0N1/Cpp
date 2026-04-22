#include "avl_tree.hpp"

#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

/* AVL Node Implementation */

template <typename T>
AVLNode<T>::AVLNode(T k) : key(k), left(nullptr), right(nullptr), height(1) {}

template <typename T>
AVLNode<T>::AVLNode(const AVLNode& other)
    : key(other.key),
      height(other.height),
      left(other.left),
      right(other.right) {}

template <typename T>
AVLNode<T>::AVLNode(AVLNode&& other)
    : key(other.key),
      height(other.height),
      left(std::move(other.left)),
      right(std::move(other.right)) {}

template <typename T>
AVLNode<T>& AVLNode<T>::operator=(AVLNode other) {
  std::swap(key, other.key);
  std::swap(height, other.height);
  std::swap(left, other.left);
  std::swap(right, other.right);
  return *this;
}

template <typename T>
AVLNode<T>::~AVLNode() = default;

/* AVL Tree Implementation */
template <typename T>
AVLTree<T>::AVLTree() : root_(nullptr) {}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree& other) {
  root_ = copy(other.root_);
}

template <typename T>
AVLTree<T>::AVLTree(AVLTree&& other) : root_(other.root_) {
  other.root_ = nullptr;
}

template <typename T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree other) {
  std::swap(root_, other.root_);
  return *this;
}

template <typename T>
AVLTree<T>::~AVLTree() {
  destroyTree(root_);
}

template <typename T>
int AVLTree<T>::height(AVLNode<T>* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

template <typename T>
int AVLTree<T>::balanceFactor(AVLNode<T>* node) {
  if (node == nullptr) {
    return 0;
  }
  return height(node->left) - height(node->right);
}

template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y) {
  AVLNode<T>* x = y->left;
  AVLNode<T>* T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x) {
  AVLNode<T>* y = x->right;
  AVLNode<T>* T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T key) {
  if (node == nullptr) {
    return new AVLNode<T>(key);
  }

  if (key < node->key) {
    node->left = insert(node->left, key);
  } else if (key > node->key) {
    node->right = insert(node->right, key);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));

  int balance = balanceFactor(node);

  // Left Left Case
  if (balance > 1 && key < node->left->key) {
    return rightRotate(node);
  }

  // Right Right Case
  if (balance < -1 && key > node->right->key) {
    return leftRotate(node);
  }

  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
  AVLNode<T>* current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

template <typename T>
AVLNode<T>* AVLTree<T>::deleteNode(AVLNode<T>* root_, T key) {
  if (root_ == nullptr) {
    return root_;
  }

  if (key < root_->key) {
    root_->left = deleteNode(root_->left, key);
  } else if (key > root_->key) {
    root_->right = deleteNode(root_->right, key);
  } else {
    if ((root_->left == nullptr) || (root_->right == nullptr)) {
      AVLNode<T>* temp = root_->left ? root_->left : root_->right;
      if (temp == nullptr) {
        temp = root_;
        root_ = nullptr;
      } else {
        *root_ = *temp;
      }
      delete temp;
    } else {
      AVLNode<T>* temp = minValueNode(root_->right);
      root_->key = temp->key;
      root_->right = deleteNode(root_->right, temp->key);
    }
  }

  if (root_ == nullptr) {
    return root_;
  }
  root_->height = 1 + max(height(root_->left), height(root_->right));
  int balance = balanceFactor(root_);

  // Left Left Case
  if (balance > 1 && balanceFactor(root_->left) >= 0) {
    return rightRotate(root_);
  }

  // Left Right Case
  if (balance > 1 && balanceFactor(root_->left) < 0) {
    root_->left = leftRotate(root_->left);
    return rightRotate(root_);
  }

  // Right Right Case
  if (balance < -1 && balanceFactor(root_->right) <= 0) {
    return leftRotate(root_);
  }

  // Right Left Case
  if (balance < -1 && balanceFactor(root_->right) > 0) {
    root_->right = rightRotate(root_->right);
    return leftRotate(root_);
  }

  return root_;
}

template <typename T>
bool AVLTree<T>::search(AVLNode<T>* root_, T key) {
  if (root_ == nullptr) {
    return false;
  }
  if (root_->key == key) {
    return true;
  }
  if (key < root_->key) {
    return search(root_->left, key);
  } else {
    return search(root_->right, key);
  }
}

template <typename T>
void AVLTree<T>::destroyTree(AVLNode<T>* node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
  }
}

template <typename T>
AVLNode<T>* AVLTree<T>::copy(AVLNode<T>* node) {
  if (node == nullptr) {
    return nullptr;
  }

  AVLNode<T>* newNode = new AVLNode<T>(node->key);

  newNode->left = copy(node->left);
  newNode->right = copy(node->right);

  newNode->height = height(newNode);

  return newNode;
}

template <typename T>
class AVLTree<T>::iterator {
 public:
  iterator(AVLNode<T>* root) { pushLeftSubtree(root); }
  iterator() = default;

  const T& operator*() const { return node_stack.top()->key; }

  iterator& operator++() {
    AVLNode<T>* node = node_stack.top();
    node_stack.pop();

    if (node->right) {
      pushLeftSubtree(node->right);
    }
    return *this;
  }

  iterator& operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  bool operator==(const iterator& other) const {
    if (node_stack.empty() || other.node_stack.empty()) {
      return node_stack.empty() == other.node_stack.empty();
    }
    return node_stack.top() == other.node_stack.top();
  }

  bool operator!=(const iterator& other) const { return !(*this == other); }

 private:
  std::stack<AVLNode<T>*> node_stack;

  void pushLeftSubtree(AVLNode<T>* node) {
    while (node != nullptr) {
      node_stack.push(node);
      node = node->left;
    }
  }
};