/*структура бинарного дерево отрезков, которая генерирует
дерево после ввода начала и конца отрезка, а также исчет 
количество вхождений заданного элемента и считает сумму на 
определенном интервале*/

#include <iostream>
#include <string>

struct Tree {
    int min_key, max_key;
    int sum;
    Tree *left, *right;
    Tree(int s, int l) : min_key(s), max_key(l), sum(0), left(nullptr), right(nullptr) {}
};

Tree* build_tree(int min_key, int max_key) {
    if (min_key > max_key) return nullptr;
    Tree* node = new Tree(min_key, max_key); 
    if (min_key == max_key) node->sum = node->min_key;
    else if (max_key - min_key == 1) {
        node->left = new Tree(min_key, min_key);
        node->left->sum = node->min_key;
        node->right = new Tree(max_key, max_key);
        node->right->sum = node->max_key;
        } else {
            int past = min_key + (max_key - min_key) / 2;
            node->left = build_tree(min_key, past);
            node->right = build_tree(past + 1, max_key);
            node->sum = (node->left ? node->left->sum : 0) + (node->right ? node->right->sum : 0);
        }
    return node;
}

void print_tree_util(Tree* node, const std::string &indent = "", bool isLeft = true) {
    if(node == nullptr) return;
    if(node->right) print_tree_util(node->right, indent + (isLeft ? "|   " : "    "), false);
    std::cout << indent;
    if(isLeft) std::cout << "\\---";
    else std::cout << "/---";
    std::cout << "[" << node->min_key << "," << node->max_key << "]" << std::endl;
    if(node->left) print_tree_util(node->left, indent + (isLeft ? "    " : "|   "), true);
}

void print_tree(Tree* root) {
    print_tree_util(root, "", false);
}

int search_util(Tree* root, int value, int& count) {
    if (root == nullptr) return count;
    if (root->min_key > value) return count;
    if (root->max_key < value) return count;
    if (root->min_key <= value && root->max_key >= value) count++;
    search_util(root->left, value, count);
    search_util(root->right, value, count);
    return count;
}

int search(Tree* root, int value) {
    int count = 0;
    search_util(root, value, count);
    return count;
}

int tree_summ(Tree* node, int L, int R) {
    if (node == nullptr || L > node->max_key || R < node->min_key) return 0;
    if (node->min_key == node->max_key) return node->min_key;
    if (L <= node->min_key && R >= node->max_key) {
        return (node->max_key - node->min_key + 1) * (node->min_key + node->max_key) / 2;
    }
    return tree_summ(node->left, L, R) + tree_summ(node->right, L, R);
}


int main() {
    int value, first, last;
    int f, l;
    std::cout << "Set a segment of the tree: ";
    std::cin >> f >> l;
    std::cout << "Running..." << std::endl;
    Tree* root = build_tree(f, l);
    print_tree(root);
    std::cout << "____________________________________________" << std::endl;
    std::cout << "Enter the value: ";
    std::cin >> value;
    std::cout << "Count value in range: " << search(root, value) << std::endl;
    std::cout << "____________________________________________" << std::endl;
    std::cout << "Please enter the beginning and end of the segment: ";
    std::cin >> first >> last;
    std::cout << "The summ of the segment " << '[' << first << ", " << last << ']' << ": " <<tree_summ(root, first, last) << std::endl;
    std::cout << "___________________________________________";
    return 0;
}