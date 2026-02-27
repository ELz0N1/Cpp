#include <gtest/gtest.h>

#include "avl_tree.hpp"

class AVLTreeTest : public ::testing::Test {
 protected:
  AVLTree tree;

  void SetUp() override {
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
  }
};

TEST_F(AVLTreeTest, InsertAndSearch) {
  EXPECT_TRUE(tree.search(10));
  EXPECT_TRUE(tree.search(20));
  EXPECT_TRUE(tree.search(30));
  EXPECT_FALSE(tree.search(40));
}

TEST_F(AVLTreeTest, Remove) {
  tree.remove(20);

  EXPECT_TRUE(tree.search(10));
  EXPECT_FALSE(tree.search(20));
  EXPECT_TRUE(tree.search(30));

  tree.remove(10);
  EXPECT_FALSE(tree.search(10));
}

TEST_F(AVLTreeTest, RemoveRoot) {
  EXPECT_TRUE(tree.search(20));
  tree.remove(20);
  EXPECT_FALSE(tree.search(20));
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

TEST_F(AVLTreeTest, CopyConstructorDeepCopy) {
  AVLTree copyTree(tree);

  EXPECT_TRUE(copyTree.search(10));
  EXPECT_TRUE(copyTree.search(20));
  EXPECT_TRUE(copyTree.search(30));

  tree.insert(40);
  EXPECT_TRUE(tree.search(40));
  EXPECT_FALSE(copyTree.search(40));
}

TEST_F(AVLTreeTest, CopyAssignmentOperator) {
  AVLTree otherTree;
  otherTree.insert(100);

  otherTree = tree;

  EXPECT_FALSE(otherTree.search(100));
  EXPECT_TRUE(otherTree.search(10));
  EXPECT_TRUE(otherTree.search(20));

  otherTree.remove(10);
  EXPECT_FALSE(otherTree.search(10));
  EXPECT_TRUE(tree.search(10));
}

TEST_F(AVLTreeTest, SelfAssignment) {
  ASSERT_NO_THROW({ tree = tree; });
  EXPECT_TRUE(tree.search(10));
  EXPECT_TRUE(tree.search(20));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}