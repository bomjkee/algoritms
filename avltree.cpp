#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>

/*Структура реализует avl бинарное дерево поиска с функцией вставки
и функцией удаления (и последующей балансировке), также программа выводит
исходное и конечное дерево*/
class AVL {
    public:
        struct avlTree {
            int value;
            avlTree *left, *right;
            int balance;
    
            avlTree(int value) : value(value), balance(1), left(nullptr), right(nullptr) {} 
        };

        avlTree* insert (avlTree* root, int value) {
            if (root == nullptr) return root = new avlTree(value);
            if (value < root->value) root->left = insert(root->left, value);
            else root->right = insert(root->right, value);
            return root; 
        }

        void print_tree(avlTree* root, int space = 0, int count = 7) {
            if (root == nullptr) return;
            space += count;
            print_tree(root->right, space);
            std::cout << std::endl;
            for (auto i = count; i < space; i++) std::cout << ' ';
            std::cout << root->value << "(Balance: " << root->balance << ')' << std::endl;
            print_tree(root->left, space);
        }

        avlTree* remove (avlTree* root, int key) {
            if (root == nullptr) return nullptr;
            if (key < root->value) root->left = remove(root->left, key);
            else if (key > root->value) root->right = remove(root->right, key);
            else {
                if (root->left == nullptr || root->right == nullptr) {
                    avlTree* temp = (root->left != nullptr) ? root->left : root->right;
                    if (temp == nullptr) {temp = root; root = nullptr;}
                    else *root = *temp;
                    delete temp;
                } else {
                    avlTree* temp = find_min(root->right);
                    root->value = temp->value;
                    root->right = remove(root->right, temp->value); 
                }
            }
            if (root == nullptr) return nullptr;
            return balance(root);
        }

    private:
    
        int balanced(avlTree* root) {
            if (root == nullptr) return 0;
            return root->balance;
        }


        int balance_factor(avlTree* root) {
            if (root == nullptr) return 0;
            return balanced(root->left) - balanced(root->right);
        }


        void fix_balance(avlTree* root) {
            root->balance = 1 + std::max(balanced(root->left), balanced(root->right));
        }


        avlTree* rotate_left(avlTree* root) {
            avlTree* temp = root->right;
            root->right = temp->left;
            temp->left = root;
            fix_balance(root);
            fix_balance(temp);
            return temp;
        }


        avlTree* rotate_right(avlTree* root) {
            avlTree* temp = root->left;
            root->left = temp->right;
            temp->right = root;
            fix_balance(root);
            fix_balance(temp);
            return temp;
        }


        avlTree* balance(avlTree* root) {
            fix_balance(root);
            if (balance_factor(root) == 2) {
                if (balance_factor(root->right) < 0) root->right = rotate_right(root->right);
                return rotate_left(root);
            } 
            if (balance_factor(root) == -2) {
                if (balance_factor(root->left) > 0) root->left = rotate_left(root->left);
                return rotate_right(root);
            }
            return root;
        }


        avlTree* find_min (avlTree* root) {
            for (;root->left != nullptr;) root = root->left;
            return root;
        }
};


int main() {
    AVL Tree;
    std::srand(time(nullptr));
    AVL::avlTree* root = nullptr;
    int depth, key;
    std::cout << "Enter the depth: ";
    std::cin >> depth;
    int *keys = new int[depth];
    for (auto i = 0; i < depth; i++) { keys[i] = 1 + rand() % 100; root = Tree.insert(root, keys[i]);}
    std::cout << "Generate: [";
    for (auto i = 0; i < depth; i++) std::cout << keys[i] << " ";
    std::cout << "]" << std::endl;
    std::cout << "AVL structure:" << std::endl;
    Tree.print_tree(root);
    std::cout << "Enter key to remove: ";
    std::cin >> key;
    root = Tree.remove(root, key);
    std::cout << "Running..." << std::endl;
    Tree.print_tree(root);
    delete[] keys;
    return 0;
}