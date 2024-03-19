#include <iostream>
#include <iomanip>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
};

void printHelper(Node* root, int space) {
    if (root == nullptr) {
        return;
    }

    space += 5;

    printHelper(root->right, space);

    std::cout << std::endl;
    for (int i = 5; i < space; i++) {
        std::cout << " ";
    }
    if(root->color == RED){
        std::cout << "\033[1;31m" << root->data << "\033[0m" << std::endl;
    }else{
        std::cout << root->data << std::endl;
    }

    printHelper(root->left, space);
}

void print(Node* root) {
    printHelper(root, 0);
}

int countBlackNodes(Node* root) {
    if (root == nullptr) {
        return 1;
    }

    if (root->left == nullptr && root->right == nullptr) {
        return (root->color == BLACK) ? 1 : 0;
    }

    int leftHeight = countBlackNodes(root->left);
    int rightHeight = countBlackNodes(root->right);

    if (leftHeight != rightHeight || leftHeight == -1 || rightHeight == -1 || root->color == RED) {
        return -1;
    }

    return (root->color == BLACK) ? leftHeight + 1 : leftHeight;
}

bool checkRedBlackProperties(Node* root) {
    int blackNodes = countBlackNodes(root);
    if (blackNodes == -1) {
        return false;
    }

    return true;
}

Node* rotateLeft(Node* root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return root;
}

Node* rotateRight(Node* root, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    return root;
}

Node* fixInsertion(Node* root, Node* x) {
    while (x != root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            Node* y = x->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    root = rotateLeft(root, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                root = rotateRight(root, x->parent->parent);
            }
        } else {
            Node* y = x->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    root = rotateRight(root, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                root = rotateLeft(root, x->parent->parent);
            }
        }
    }

    root->color = BLACK;
    return root;
}

Node* insert(Node* root, Node* newNode) {
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (newNode->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    newNode->parent = y;
    if (y == nullptr) {
        root = newNode;
    } else if (newNode->data < y->data) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    newNode->color = RED;
    root = fixInsertion(root, newNode);

    return root;
}

int main() {
    Node* root = nullptr;
    
    root = insert(root, new Node{10, BLACK, nullptr, nullptr, nullptr});
    root = insert(root, new Node{5, RED, nullptr, nullptr, nullptr});
    root = insert(root, new Node{15, RED, nullptr, nullptr, nullptr});
    root = insert(root, new Node{3, BLACK, nullptr, nullptr, nullptr});
    root = insert(root, new Node{7, BLACK, nullptr, nullptr, nullptr});
    
    if (checkRedBlackProperties(root)) std::cout <<  "True" << std::endl;
    else std::cout << "False" << std::endl;
    print(root);
    
    Node* node = nullptr;
    
    node = insert(node, new Node{2, BLACK, nullptr, nullptr, nullptr});
    node = insert(node, new Node{3, RED, nullptr, nullptr, nullptr});
    node = insert(node, new Node{10, BLACK, nullptr, nullptr, nullptr});
    node = insert(node, new Node{11, RED, nullptr, nullptr, nullptr});
    node = insert(node, new Node{1, BLACK, nullptr, nullptr, nullptr});
    
    if (checkRedBlackProperties(node)) std::cout <<  "True" << std::endl;
    else std::cout << "False" << std::endl;
    print(node);

    return 0;
}