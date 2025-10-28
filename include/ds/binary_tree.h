/**
 * @file binary_tree.h
 * @brief Binary tree veri yapısı ve tree traversals implementasyonu
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */

#pragma once
#include <iostream>
#include <functional>
#include <stack>
#include <queue>

namespace ds {

/**
 * @brief Binary tree düğüm yapısı
 * @tparam T Değer türü
 */
template <typename T>
struct TreeNode {
    T value;                  ///< Düğüm değeri
    TreeNode* left;           ///< Sol çocuk pointer'ı
    TreeNode* right;          ///< Sağ çocuk pointer'ı
    
    /**
     * @brief Düğüm oluşturur
     * @param v Düğümde saklanacak değer
     */
    explicit TreeNode(const T& v) : value(v), left(nullptr), right(nullptr) {}
};

/**
 * @brief Binary tree veri yapısı
 * @tparam T Değer türü
 * 
 * Bu sınıf, binary tree veri yapısını implement eder.
 * Tree traversals (inorder, preorder, postorder) ve
 * level-order traversal desteği sağlar.
 */
template <typename T>
class BinaryTree {
    TreeNode<T>* root_;    ///< Kök düğüm pointer'ı
    
    /**
     * @brief Ağacı temizler (recursive)
     * @param node Temizlenecek düğüm
     */
    void destroy(TreeNode<T>* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    
    /**
     * @brief Ağacın yüksekliğini hesaplar (recursive)
     * @param node Hesaplanacak düğüm
     * @return Ağaç yüksekliği
     */
    int height(TreeNode<T>* node) const {
        if (!node) return -1;
        return 1 + std::max(height(node->left), height(node->right));
    }
    
    /**
     * @brief Ağaçtaki düğüm sayısını hesaplar (recursive)
     * @param node Sayılacak düğüm
     * @return Düğüm sayısı
     */
    int countNodes(TreeNode<T>* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    
    /**
     * @brief Inorder traversal (recursive)
     * @param node Gezilecek düğüm
     * @param visit Ziyaret fonksiyonu
     */
    void inorderTraversal(TreeNode<T>* node, std::function<void(const T&)> visit) const {
        if (node) {
            inorderTraversal(node->left, visit);
            visit(node->value);
            inorderTraversal(node->right, visit);
        }
    }
    
    /**
     * @brief Preorder traversal (recursive)
     * @param node Gezilecek düğüm
     * @param visit Ziyaret fonksiyonu
     */
    void preorderTraversal(TreeNode<T>* node, std::function<void(const T&)> visit) const {
        if (node) {
            visit(node->value);
            preorderTraversal(node->left, visit);
            preorderTraversal(node->right, visit);
        }
    }
    
    /**
     * @brief Postorder traversal (recursive)
     * @param node Gezilecek düğüm
     * @param visit Ziyaret fonksiyonu
     */
    void postorderTraversal(TreeNode<T>* node, std::function<void(const T&)> visit) const {
        if (node) {
            postorderTraversal(node->left, visit);
            postorderTraversal(node->right, visit);
            visit(node->value);
        }
    }
    
public:
    /**
     * @brief Varsayılan constructor
     */
    BinaryTree() : root_(nullptr) {}
    
    /**
     * @brief Destructor - Tüm düğümleri serbest bırakır
     */
    ~BinaryTree() { destroy(root_); }
    
    /**
     * @brief Copy constructor (silinmiş)
     */
    BinaryTree(const BinaryTree&) = delete;
    
    /**
     * @brief Copy assignment operator (silinmiş)
     */
    BinaryTree& operator=(const BinaryTree&) = delete;
    
    /**
     * @brief Kök düğüm pointer'ını döndürür
     * @return Kök düğüm pointer'ı
     */
    TreeNode<T>* root() const { return root_; }
    
    /**
     * @brief Ağacın boş olup olmadığını kontrol eder
     * @return true eğer ağaç boşsa
     */
    bool empty() const { return root_ == nullptr; }
    
    /**
     * @brief Ağaçtaki düğüm sayısını döndürür
     * @return Düğüm sayısı
     */
    int size() const { return countNodes(root_); }
    
    /**
     * @brief Ağacın yüksekliğini döndürür
     * @return Ağaç yüksekliği
     */
    int height() const { return height(root_); }
    
    /**
     * @brief Kök düğümü ayarlar
     * @param node Kök düğüm pointer'ı
     */
    void setRoot(TreeNode<T>* node) { root_ = node; }
    
    /**
     * @brief Yeni kök düğümü oluşturur ve ayarlar
     * @param value Kök düğümün değeri
     * @return Oluşturulan kök düğüm pointer'ı
     */
    TreeNode<T>* createRoot(const T& value) {
        root_ = new TreeNode<T>(value);
        return root_;
    }
    
    /**
     * @brief Inorder traversal (LNR: Left, Node, Right)
     * @param visit Her düğümü ziyaret ederken çağrılacak fonksiyon
     * 
     * Inorder traversal, düğümleri sol alt ağaç, kök, sağ alt ağaç
     * sırasında gezer. Binary search tree'lerde sıralı çıktı verir.
     */
    void inorder(std::function<void(const T&)> visit) const {
        inorderTraversal(root_, visit);
    }
    
    /**
     * @brief Preorder traversal (NLR: Node, Left, Right)
     * @param visit Her düğümü ziyaret ederken çağrılacak fonksiyon
     * 
     * Preorder traversal, düğümleri kök, sol alt ağaç, sağ alt ağaç
     * sırasında gezer. Tree'yi copy etmek için kullanılabilir.
     */
    void preorder(std::function<void(const T&)> visit) const {
        preorderTraversal(root_, visit);
    }
    
    /**
     * @brief Postorder traversal (LRN: Left, Right, Node)
     * @param visit Her düğümü ziyaret ederken çağrılacak fonksiyon
     * 
     * Postorder traversal, düğümleri sol alt ağaç, sağ alt ağaç, kök
     * sırasında gezer. Tree'yi silmek için kullanılabilir.
     */
    void postorder(std::function<void(const T&)> visit) const {
        postorderTraversal(root_, visit);
    }
    
    /**
     * @brief Level-order traversal (breadth-first)
     * @param visit Her düğümü ziyaret ederken çağrılacak fonksiyon
     * 
     * Level-order traversal, düğümleri seviye seviye gezer.
     * Queue kullanarak breadth-first search yapar.
     */
    void levelOrder(std::function<void(const T&)> visit) const {
        if (!root_) return;
        
        std::queue<TreeNode<T>*> q;
        q.push(root_);
        
        while (!q.empty()) {
            TreeNode<T>* node = q.front();
            q.pop();
            visit(node->value);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    /**
     * @brief Inorder traversal (iterative)
     * @param visit Her düğümü ziyaret ederken çağrılacak fonksiyon
     */
    void inorderIterative(std::function<void(const T&)> visit) const {
        if (!root_) return;
        
        std::stack<TreeNode<T>*> stk;
        TreeNode<T>* current = root_;
        
        while (!stk.empty() || current) {
            while (current) {
                stk.push(current);
                current = current->left;
            }
            current = stk.top();
            stk.pop();
            visit(current->value);
            current = current->right;
        }
    }
    
    /**
     * @brief Preorder traversal (iterative)
     * @param visit Her düğümü ziyaret ederken çağrılacak fonksiyon
     */
    void preorderIterative(std::function<void(const T&)> visit) const {
        if (!root_) return;
        
        std::stack<TreeNode<T>*> stk;
        stk.push(root_);
        
        while (!stk.empty()) {
            TreeNode<T>* node = stk.top();
            stk.pop();
            visit(node->value);
            
            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
        }
    }
};

} // namespace ds
