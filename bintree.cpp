#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>

/*данный код реализует бинарное дерево поиска с функцией вставки
и вывода дерева на экран*/

struct binTree {
    int value;
    binTree *left, *right;
    int balance;
    binTree(int key) : value(key), balance(1), left(nullptr), right(nullptr) {} 
};


binTree* insert (binTree* root, int value) {
    if (root == nullptr) return root = new binTree(value);
    if (value < root->value) root->left = insert(root->left, value);
    else if (value > root->value) root->right = insert(root->right, value);
    root->balance = 1 + std::max((root->left ? root->left->balance : 0), (root->right ? root->right->balance : 0));
    return root; 
}


void print_tree_util(binTree* root, const std::string &indent = "", bool isLeft = true) {
    if(root == nullptr) return;
    if(root->right) print_tree_util(root->right, indent + (isLeft ? "|   " : "    "), false);
    std::cout << indent;
    if(isLeft) std::cout << "\\---";
    else std::cout << "/---";
    std::cout << root->value << " (Balance: " << ((root->left ? root->left->balance : 0) - (root->right ? root->right->balance : 0)) << ") " << std::endl;
    if(root->left) print_tree_util(root->left, indent + (isLeft ? "    " : "|   "), true);
}


void print_tree(binTree* root) {
    print_tree_util(root, "", false);
}


int main() {
    std::srand(time(nullptr));
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
    for (auto i = 0; i < depth; i++) std::cout << keys[i] << " ";
    std::cout << "]" << std::endl;
    std::cout << "Your binary tree for serach:" << std::endl;
    print_tree(root);
    delete[] keys;
    return 0;
}