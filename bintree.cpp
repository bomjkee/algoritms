#include <iostream>
#include <ctime>
#include <string>


struct binTree {
    int value;
    binTree *left, *right;
    int balance;
    binTree(int key) : value(key), left(nullptr), right(nullptr) {} 
};

binTree* insert (binTree* root, int value) {
    if (root == nullptr) return root = new binTree(value);
    if (value < root->value) root->left = insert(root->left, value);
    else if (value > root->value) root->right = insert(root->right, value);
    root->balance = std::max((root->left ? root->left->balance : 0), (root->right ? root->right->balance : 0));
    return root; 
}

void print_tree(binTree* root, const std::string paste = "", bool isRight = false) {
    if (root == nullptr) return;
    print_tree(root->left, paste + (isRight ? "    " : "|   "), false);
    if (isRight) std::cout << paste << "`---";
    else std::cout << paste << "|---";
    std::cout << root->value << "Balance: " << ((root->left ? root->left->balance : 0) - (root->right ? root->right->balance : 0)) << std::endl;
    print_tree(root->right, paste + (isRight ? "    " : "|   "), true);
}

int main() {
    binTree* root = nullptr;
    int depth;
    std::cout << "Enter the depth: ";
    std::cin >> depth;
    int *keys = new int[depth];
    for (auto i = 0; i < depth; i++) {
        keys[i] = rand() % 10;
        root = insert(root, keys[i]);
    }
    std::cout << "Generate: [";
    for (auto i = 0; i < depth; i++) std::cout << keys[i];
    std::cout << "]" << std::endl;
    std::cout << "Your binary tree for serach:" << std::endl;
    print_tree(root);
    return 0;
    delete[] keys;
}