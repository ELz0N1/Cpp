#include "avl_tree.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

/* AVL Node Implementation */
AVLTree::AVLNode::AVLNode(int k)
    : key(k), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLNode::AVLNode(const AVLNode& other)
    : key(other.key), height(other.height), left(nullptr), right(nullptr) {}

AVLTree::AVLNode::AVLNode(AVLNode&& other)
    : key(other.key),
      height(other.height),
      left(other.left),
      right(other.right) {
  other.left = nullptr;
  other.right = nullptr;
}

AVLTree::AVLNode& AVLTree::AVLNode::operator=(AVLNode other) {
  std::swap(key, other.key);
  std::swap(height, other.height);
  std::swap(left, other.left);
  std::swap(right, other.right);
  return *this;
}

AVLTree::AVLNode::~AVLNode() {
  delete left;
  delete right;
}

AVLTree::AVLNode* AVLTree::AVLNode::detachSingleChild() {
  AVLNode* child = left ? left : right;
  left = nullptr;
  right = nullptr;
  return child;
}

/* AVL Tree Implementation */
AVLTree::AVLTree() : root_(nullptr) {}

AVLTree::AVLTree(const AVLTree& other) { root_ = copy(other.root_); }

AVLTree::AVLTree(AVLTree&& other) : root_(other.root_) {
  other.root_ = nullptr;
}

AVLTree& AVLTree::operator=(AVLTree other) {
  std::swap(root_, other.root_);
  return *this;
}

AVLTree::~AVLTree() { delete root_; }

int AVLTree::height(AVLTree::AVLNode* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int AVLTree::balanceFactor(AVLTree::AVLNode* node) {
  if (node == nullptr) {
    return 0;
  }
  return height(node->left) - height(node->right);
}

AVLTree::AVLNode* AVLTree::rightRotate(AVLTree::AVLNode* y) {
  AVLNode* x = y->left;
  AVLNode* T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

AVLTree::AVLNode* AVLTree::leftRotate(AVLTree::AVLNode* x) {
  AVLNode* y = x->right;
  AVLNode* T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

AVLTree::AVLNode* AVLTree::insert(AVLTree::AVLNode* node, int key) {
  if (node == nullptr) {
    return new AVLNode(key);
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

AVLTree::AVLNode* AVLTree::minValueNode(AVLTree::AVLNode* node) {
  AVLNode* current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

AVLTree::AVLNode* AVLTree::deleteNode(AVLTree::AVLNode* root_, int key) {
  if (root_ == nullptr) {
    return root_;
  }

  if (key < root_->key) {
    root_->left = deleteNode(root_->left, key);
  } else if (key > root_->key) {
    root_->right = deleteNode(root_->right, key);
  } else {
    if (root_->left == nullptr || root_->right == nullptr) {
      AVLNode* child = root_->detachSingleChild();
      delete root_;
      return child;
    }

    AVLNode* temp = minValueNode(root_->right);
    root_->key = temp->key;
    root_->right = deleteNode(root_->right, temp->key);
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

bool AVLTree::search(AVLTree::AVLNode* root_, int key) {
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

AVLTree::AVLNode* AVLTree::copy(AVLTree::AVLNode* node) {
  if (node == nullptr) {
    return nullptr;
  }

  AVLNode* newNode = new AVLNode(node->key);

  newNode->left = copy(node->left);
  newNode->right = copy(node->right);

  newNode->height = height(newNode);

  return newNode;
}
