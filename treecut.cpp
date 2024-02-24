/*структура бинарного дерево отрезков, которая генерирует
дерево после ввода начала и конца отрезка, а также исчет 
количество вхождений заданного элемента и считает сумму на 
определенном интервале*/

#include <iostream>

struct Node {
    int min_key, max_key;
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* new_node(int min_key, int max_key) {
    Node* newNode = new Node;
    newNode->min_key = min_key;
    newNode->max_key = max_key;
    newNode->left = newNode->right = nullptr;
    if (newNode->min_key == newNode->max_key) newNode->value = 0;
    return newNode;
}

Node* build_tree(Node* node, int min_key, int max_key) {
    if (node == nullptr) {
        node = new_node(min_key, max_key);
        build_tree(node, min_key, max_key);
    }
    else {
        if (node->max_key - node->min_key == 1) {
            node->value = node->max_key; 
            return node;
        }
        else {
            int past = (min_key + max_key) / 2;
            if (past == min_key) return nullptr;
            else node->left = build_tree(new_node(min_key, past), min_key, past);
            if (past == max_key)  return nullptr;
            else node->right = build_tree(new_node(past, max_key), past, max_key);
            node->value = (node->left ? node->left->value : 0) + (node->right ? node->right->value : 0);
        }
    }
    return node;
}

void print_tree_util (Node* root, int space) {
    int count_space = 7;
    if (root == nullptr) return;
    space += count_space;
    print_tree_util(root->right, space);
    std::cout << std::endl;
    for(int i = count_space; i < space; i++) std::cout << ' ';
    std::cout << '[' << root->min_key << ", " << root->max_key << ']' << std::endl;
    print_tree_util(root->left, space);
}

void print_tree(Node* root) {    
    print_tree_util(root, 0);
}

int search_util(Node* root, int value, int &count) {
    if (root == nullptr) return count;
    if (root->min_key > value) return count;
    if (root->max_key < value) return count;
    if (root->min_key <= value && root->max_key >= value) count++;
    search_util(root->left, value, count);
    search_util(root->right, value, count);
    return count;
    }

int search(Node* root, int value) {
    int count = 0;
    search_util(root, value, count);
    return count;
}

int summ (Node* root, int first, int last) {
    if (root == nullptr) return 0;
    if (first > root->max_key || last < root->min_key) return 0;
    if (first <= root->min_key && last >= root->max_key) return root->value;
    return summ(root->left, first, last) + summ(root->right, first, last);
}

int main() {
    Node* root = nullptr;
    int value, first, last;
    int f, l;
    std::cout << "Set a segment of the tree: ";
    std::cin >> f >> l; 
    std::cout << "Running..." << std::endl;
    std::cout << "___________________________________________";
    root = build_tree(root, f, l);
    print_tree(root);
    std::cout << "____________________________________________" << std::endl;
    std::cout << "Enter the value: ";
    std::cin >> value;
    std::cout << "Count value in range: " << search(root, value) << std::endl;
    std::cout << "____________________________________________" << std::endl;
    std::cout << "Please enter the beginning and end of the segment: ";
    std::cin >> first >> last;
    std::cout << "The summ of the segment: " << summ(root, first, last) + first << std::endl;
    std::cout << "___________________________________________";
    return 0;
}