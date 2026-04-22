#include <gtest/gtest.h>

#include <utility>

#include "avl_tree.cpp"
#include "avl_tree.hpp"

class AVLTreeTest : public ::testing::Test {
 protected:
  AVLTree<int> tree;

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
  AVLTree<int> otherTree;
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
  AVLTree<int> targetTree;
  targetTree.insert(100);
  targetTree = std::move(tree);

  EXPECT_TRUE(targetTree.search(20));
  EXPECT_FALSE(targetTree.search(100));

  EXPECT_FALSE(tree.search(30));
}

TEST_F(AVLTreeTest, ChainMoveAssignments) {
  AVLTree<int> treeA;
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

TEST_F(AVLTreeTest, IteratorTest) {
  int result = 0;
  for (auto&& node : tree) {
    result += node;
  }
  EXPECT_EQ(result, 60);
}

TEST_F(AVLTreeTest, IteratorTest2) {
  auto it = tree.begin();

  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(it, tree.end());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}