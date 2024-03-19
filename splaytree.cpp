#include <iostream>


class SplayTree {
public:
    struct Node {
            int key;
            Node* left;
            Node* right;
            Node(int k) : key(k), left(nullptr), right(nullptr) {}
        };
        
    SplayTree() : root(nullptr) {}

    void insert(int key) {
        if (root == nullptr) {
            root = new Node(key);
            return;
        }
        root = splay(root, key);
        if (key < root->key) {
            Node* newNode = new Node(key);
            newNode->left = root->left;
            newNode->right = root;
            root->left = nullptr;
            root = newNode;
        } else if (key > root->key) {
            Node* newNode = new Node(key);
            newNode->right = root->right;
            newNode->left = root;
            root->right = nullptr;
            root = newNode;
        }
    }

    void remove(int key) {
        if (root == nullptr) {
            return;
        }
        root = splay(root, key);
        if (root->key != key) {
            return;
        }
        Node* leftSubtree = root->left;
        Node* rightSubtree = root->right;
        delete root;
        if (leftSubtree == nullptr) {
            root = rightSubtree;
        } else {
            Node* maxNode = findMax(leftSubtree);
            root = splay(leftSubtree, maxNode->key);
            root->right = rightSubtree;
        }
    }
private:
    Node* root;

    Node* splay(Node* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }
        if (key < node->key) {
            if (node->left == nullptr) {
                return node;
            }
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
        } else {
            if (node->right == nullptr) {
                return node;
            }
            if (key < node->right->key) {
                node->right->left = splay(node->right->left, key);
                if (node->right->left != nullptr) {
                    node->right = rotateRight(node->right);
                }
            } else if (key > node->right->key) {
                node->right->right = splay(node->right->right, key);
                node = rotateLeft(node);
            }
            return (node->right == nullptr) ? node : rotateLeft(node);
        }
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

    Node* merge(Node* left, Node* right) {
        Node* maxNode = findMax(left);
        return splay(left, maxNode->key)->right = right;
    }
};

int main() {
    SplayTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    tree.remove(4);

    return 0;
}