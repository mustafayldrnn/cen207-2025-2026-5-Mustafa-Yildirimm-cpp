#include <gtest/gtest.h>
#include <vector>
#include "ds/binary_tree.h"

using namespace ds;

TEST(BinaryTree, ConstructionAndDestruction){
    BinaryTree<int> tree;
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.height(), -1);
}

TEST(BinaryTree, CreateRoot){
    BinaryTree<int> tree;
    auto* root = tree.createRoot(10);
    EXPECT_EQ(root->value, 10);
    EXPECT_FALSE(tree.empty());
    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree.height(), 0);
}

TEST(BinaryTree, BuildTree){
    BinaryTree<int> tree;
    
    // Build tree:
    //       10
    //      /  \
    //     5   15
    //    / \
    //   3   7
    
    auto* root = tree.createRoot(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    
    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.height(), 2);
}

TEST(BinaryTree, InorderTraversal){
    BinaryTree<int> tree;
    
    // Build tree:
    //       10
    //      /  \
    //     5   15
    //    / \
    //   3   7
    
    auto* root = tree.createRoot(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    
    std::vector<int> result;
    tree.inorder([&result](const int& val) {
        result.push_back(val);
    });
    
    // Inorder: 3, 5, 7, 10, 15
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 7);
    EXPECT_EQ(result[3], 10);
    EXPECT_EQ(result[4], 15);
}

TEST(BinaryTree, PreorderTraversal){
    BinaryTree<int> tree;
    
    // Build tree:
    //       10
    //      /  \
    //     5   15
    //    / \
    //   3   7
    
    auto* root = tree.createRoot(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    
    std::vector<int> result;
    tree.preorder([&result](const int& val) {
        result.push_back(val);
    });
    
    // Preorder: 10, 5, 3, 7, 15
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 7);
    EXPECT_EQ(result[4], 15);
}

TEST(BinaryTree, PostorderTraversal){
    BinaryTree<int> tree;
    
    // Build tree:
    //       10
    //      /  \
    //     5   15
    //    / \
    //   3   7
    
    auto* root = tree.createRoot(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    
    std::vector<int> result;
    tree.postorder([&result](const int& val) {
        result.push_back(val);
    });
    
    // Postorder: 3, 7, 5, 15, 10
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 5);
    EXPECT_EQ(result[3], 15);
    EXPECT_EQ(result[4], 10);
}

TEST(BinaryTree, LevelOrderTraversal){
    BinaryTree<int> tree;
    
    // Build tree:
    //       10
    //      /  \
    //     5   15
    //    / \
    //   3   7
    
    auto* root = tree.createRoot(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    
    std::vector<int> result;
    tree.levelOrder([&result](const int& val) {
        result.push_back(val);
    });
    
    // Level-order: 10, 5, 15, 3, 7
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 15);
    EXPECT_EQ(result[3], 3);
    EXPECT_EQ(result[4], 7);
}

TEST(BinaryTree, InorderIterative){
    BinaryTree<int> tree;
    
    auto* root = tree.createRoot(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    
    std::vector<int> result;
    tree.inorderIterative([&result](const int& val) {
        result.push_back(val);
    });
    
    // Should match recursive inorder: 3, 5, 7, 10, 15
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 7);
    EXPECT_EQ(result[3], 10);
    EXPECT_EQ(result[4], 15);
}

TEST(BinaryTree, PreorderIterative){
    BinaryTree<int> tree;
    
    auto* root = tree.createRoot(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    
    std::vector<int> result;
    tree.preorderIterative([&result](const int& val) {
        result.push_back(val);
    });
    
    // Should match recursive preorder: 10, 5, 3, 7, 15
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 7);
    EXPECT_EQ(result[4], 15);
}

TEST(BinaryTree, HeightCalculation){
    BinaryTree<int> tree;
    
    // Empty tree
    EXPECT_EQ(tree.height(), -1);
    
    // Single node
    tree.createRoot(10);
    EXPECT_EQ(tree.height(), 0);
    
    // Add left child
    auto* root = tree.root();
    root->left = new TreeNode<int>(5);
    EXPECT_EQ(tree.height(), 1);
    
    // Add right child (height stays 1)
    root->right = new TreeNode<int>(15);
    EXPECT_EQ(tree.height(), 1);
    
    // Add grandchild
    root->left->left = new TreeNode<int>(3);
    EXPECT_EQ(tree.height(), 2);
}

TEST(BinaryTree, SizeCalculation){
    BinaryTree<int> tree;
    
    EXPECT_EQ(tree.size(), 0);
    
    tree.createRoot(10);
    EXPECT_EQ(tree.size(), 1);
    
    auto* root = tree.root();
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    EXPECT_EQ(tree.size(), 3);
    
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    EXPECT_EQ(tree.size(), 5);
}

TEST(BinaryTree, ComplexTree){
    BinaryTree<std::string> tree;
    
    // Build a more complex tree
    //            "A"
    //           /   \
    //         "B"   "C"
    //        /   \     \
    //      "D"   "E"   "F"
    //             \
    //             "G"
    
    auto* root = tree.createRoot("A");
    root->left = new TreeNode<std::string>("B");
    root->right = new TreeNode<std::string>("C");
    root->left->left = new TreeNode<std::string>("D");
    root->left->right = new TreeNode<std::string>("E");
    root->right->right = new TreeNode<std::string>("F");
    root->left->right->right = new TreeNode<std::string>("G");
    
    EXPECT_EQ(tree.size(), 7);
    EXPECT_EQ(tree.height(), 3);
    
    std::vector<std::string> inorder;
    tree.inorder([&inorder](const std::string& val) {
        inorder.push_back(val);
    });
    
    ASSERT_EQ(inorder.size(), 7u);
    // Inorder: D, B, E, G, A, C, F
    EXPECT_EQ(inorder[0], "D");
    EXPECT_EQ(inorder[1], "B");
    EXPECT_EQ(inorder[2], "E");
    EXPECT_EQ(inorder[3], "G");
    EXPECT_EQ(inorder[4], "A");
    EXPECT_EQ(inorder[5], "C");
    EXPECT_EQ(inorder[6], "F");
}
