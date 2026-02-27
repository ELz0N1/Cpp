#include <gtest/gtest.h>

#include "avl_tree.hpp"

class AVLTreeTest : public ::testing::Test {
 protected:
  AVLTree tree;
};

TEST_F(AVLTreeTest, InsertAndSearch) {
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);

  EXPECT_TRUE(tree.search(10));
  EXPECT_TRUE(tree.search(20));
  EXPECT_TRUE(tree.search(30));
  EXPECT_FALSE(tree.search(40));  
}

TEST_F(AVLTreeTest, Remove) {
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.remove(20);  

  EXPECT_TRUE(tree.search(10));
  EXPECT_FALSE(tree.search(20));  
  EXPECT_TRUE(tree.search(30));

  tree.remove(10);
  EXPECT_FALSE(tree.search(10));  
}

TEST_F(AVLTreeTest, RemoveRoot) {
  tree.insert(50);
  tree.insert(30);
  tree.insert(70);

  EXPECT_TRUE(tree.search(50));   
  tree.remove(50);                
  EXPECT_FALSE(tree.search(50));  
}

TEST_F(AVLTreeTest, SequentialInsertAndRemove) {
  for (int i = 1; i <= 10; ++i) {
    tree.insert(i);
  }

  for (int i = 1; i <= 10; ++i) {
    EXPECT_TRUE(tree.search(i));  
    tree.remove(i);
    EXPECT_FALSE(tree.search(i));  
  }
}
