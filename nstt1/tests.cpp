#include <gtest/gtest.h>

#include <utility>

#include "avl_tree.hpp"

class AVLNodeTest : public ::testing::Test, public AVLTree {};

TEST_F(AVLNodeTest, MoveConstructorNullifiesSourcePointers) {
  AVLNode* child = new AVLNode(5);
  AVLNode parent(10);
  parent.left = child;

  AVLNode moved(std::move(parent));

  EXPECT_EQ(moved.key, 10);
  EXPECT_EQ(moved.left, child);
  EXPECT_EQ(moved.right, nullptr);
  EXPECT_EQ(parent.left, nullptr);
  EXPECT_EQ(parent.right, nullptr);
}

TEST_F(AVLNodeTest, MoveConstructorTransfersOwnedSubtree) {
  AVLNode* left = new AVLNode(5);
  AVLNode parent(10);
  parent.left = left;

  AVLNode moved(std::move(parent));

  EXPECT_EQ(moved.left, left);
  EXPECT_EQ(parent.left, nullptr);
}

TEST_F(AVLNodeTest, CopyConstructorDoesNotAliasChildren) {
  AVLNode* left = new AVLNode(5);
  AVLNode parent(10);
  parent.left = left;

  AVLNode copied(parent);

  EXPECT_EQ(copied.key, parent.key);
  EXPECT_EQ(copied.height, parent.height);
  EXPECT_EQ(copied.left, nullptr);
  EXPECT_EQ(copied.right, nullptr);
}

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

TEST_F(AVLTreeTest, MoveConstructor) {
  AVLTree movedTree(std::move(tree));

  EXPECT_TRUE(movedTree.search(10));
  EXPECT_TRUE(movedTree.search(20));
  EXPECT_TRUE(movedTree.search(30));

  EXPECT_FALSE(tree.search(10));
  EXPECT_FALSE(tree.search(30));
}

TEST_F(AVLTreeTest, MoveAssignmentOperator) {
  AVLTree targetTree;
  targetTree.insert(100);
  targetTree = std::move(tree);

  EXPECT_TRUE(targetTree.search(20));
  EXPECT_FALSE(targetTree.search(100));

  EXPECT_FALSE(tree.search(30));
}

TEST_F(AVLTreeTest, ChainMoveAssignments) {
  AVLTree treeA;
  treeA.insert(1);

  AVLTree treeB = std::move(treeA);
  AVLTree treeC = std::move(treeB);

  EXPECT_TRUE(treeC.search(1));
  EXPECT_FALSE(treeB.search(1));
  EXPECT_FALSE(treeA.search(1));
}

TEST_F(AVLTreeTest, SelfMoveAssignment) {
  ASSERT_NO_THROW({ tree = std::move(tree); });

  EXPECT_TRUE(tree.search(30));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}