#include <iostream>
#include <cstdlib> 
#include <ctime>   

class SplayTree {
public:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };
    
    SplayTree() : root(nullptr) {}

    ~SplayTree() {
        deleteTree(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    void print_tree() {
        print_tree_util(root, 0, 7);
    }

private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        node = splay(node, key);
        if (node->key == key) return node; 
        Node* newNode = new Node(key);
        if (key < node->key) {
            newNode->left = node->left;
            newNode->right = node;
            node->left = nullptr;
        } else {
            newNode->right = node->right;
            newNode->left = node;
            node->right = nullptr;
        }
        return newNode;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) return nullptr; 
        node = splay(node, key);
        if (node->key != key) return node; 
        Node* toDelete = node;
        if (node->left == nullptr) node = node->right;
        else {
            Node* leftSubtree = splay(node->left, key); 
            leftSubtree->right = node->right;
            node = leftSubtree;
        }
        delete toDelete; 
        return node;
    }

    Node* splay(Node* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->key) {
            if (node->left == nullptr) return node; 
            if (key < node->left->key) {
                node->left->left = splay(node->left->left, key);
                node = rotateRight(node);
            } else if (key > node->left->key) {
                node->left->right = splay(node->left->right, key);
                if (node->left->right != nullptr) {
                    node->left = rotateLeft(node->left);
                }
            }
            return (node->left == nullptr) ? node : rotateRight(node);
        } else if (key > node->key) {
            if (node->right == nullptr) return node; 
            if (key > node->right->key) {
                node->right->right = splay(node->right->right, key);
                node = rotateLeft(node);
            } else if (key < node->right->key) {
                node->right->left = splay(node->right->left, key);
                if (node->right->left != nullptr) {
                    node->right = rotateRight(node->right);
                }
            }
            return (node->right == nullptr) ? node : rotateLeft(node);
        }
        return node;
    }

    Node* rotateRight(Node* node) {
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }

    Node* rotateLeft(Node* node) {
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }

    Node* findMax(Node* node) {
        Node* current = node;
        while (current != nullptr && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    void print_tree_util(Node* node, int space, int count) {
        if (node == nullptr) return;
        space += count;
        print_tree_util(node->right, space, count);
        std::cout << std::endl;
        for (int i = count; i < space; i++) std::cout << ' ';
        std::cout << node->key << "\n";
        print_tree_util(node->left, space, count);
    }

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

int main() {
    SplayTree tree;
    std::srand(std::time(nullptr));
    int depth, key;
    std::cout << "Enter the depth: ";
    std::cin >> depth;
    for (int i = 0; i < depth; ++i) tree.insert(std::rand() % 100);
    std::cout << "Splay Tree after inserts: " << std::endl;
    tree.print_tree();
    std::cout << "Enter key to remove: ";
    std::cin >> key;
    tree.remove(key);
    std::cout << "Splay Tree after removal:" << std::endl;
    tree.print_tree();
    return 0;
}