#include <iostream>
#include <string>

struct Node {
    std::string name;
    std::string phone;
    Node* left;
    Node* right;
};

Node* insert(Node* root, std::string name, std::string phone) {
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->name = name;
        newNode->phone = phone;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (name < root->name) {
        root->left = insert(root->left, name, phone);
    } else if (name > root->name) {
        root->right = insert(root->right, name, phone);
    } else if (name == root->name) {
        root->phone += ", " + phone;
    }  
    return root;
}

Node* min_node(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* name_search(Node* root, std::string name) {
    if (root == nullptr || root->name == name) {
        return root;
    }
    if (name < root->name) {
        return name_search(root->left, name);
    } 
    else if (name > root->name) {
        return name_search(root->right, name); 
    }
}

Node* phone_search(Node* root, std::string phone) {
    if (root == nullptr || root->phone == phone) {
        return root;
    }
    Node* left_search = phone_search(root->left, phone);
    Node* right_search = phone_search(root->right, phone);

    return left_search ? left_search : right_search;
}

Node* remove(Node* root, std::string name) {
    if (root == nullptr) {
        return root;
    }
    if (name < root->name) {
        root->left = remove(root->left, name);
    } else if (name > root->name) {
        root->right = remove(root->right, name);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        } 
        Node* temp = min_node(root->right);
        root->name = temp->name;
        root->phone = temp->phone;
        root->right = remove(root->right, temp->name);
    }
    return root;
}

void Print(Node* root) {
    if (root == NULL) {
        return;
    }
    Print(root->left);
    std::cout << root->name << ": " << root->phone << std::endl;
    Print(root->right);
}

int main() {
    Node* root = nullptr;
    char choice;
    do {
        std::cout << "Phonebook" << std::endl;
        std::cout << "1. Add a new contact" << std::endl;
        std::cout << "2. Search contact to name" << std::endl;
        std::cout << "3. Search contact to phone" << std::endl;
        std::cout << "4. Remove a contact" << std::endl;
        std::cout << "5. Show contact" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "_______________________" << std::endl;
        
        switch(choice) {
            case '1': {
                std::string name, phone;
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter phone number: ";
                std::cin >> phone;
                root = insert(root, name, phone);
                std::cout << "Done" << std::endl;
                std::cout << "_______________________" << std::endl;
                break;
            }
            case '2': {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin >> name;
                root = name_search(root, name);
                if (root == nullptr) std::cout << "Try again" << std::endl;
                else std::cout << "Phone: " << root->phone << std::endl;
                std::cout << "_______________________" << std::endl;
                break;
            }
            case '3': {
                std::string phone;
                std::cout << "Enter phone to search: ";
                std::cin >> phone;
                root = name_search(root, phone);
                if (root == nullptr) std::cout << "Try again" << std::endl;
                else std::cout << "Name: " << root->phone << std::endl;
                std::cout << "_______________________" << std::endl;
                break;
            }
            case '4': {
                std::string name;
                std::cout << "Enter name to remove: ";
                std::cin >> name;
                root = remove(root, name);
                std::cout << "Done" << std::endl;
                std::cout << "_______________________" << std::endl;
                break;
            }
            case '5': {
                std::cout << "Contacts:" << std::endl;
                Print(root);
                std::cout << "_______________________" << std::endl;
                break;
            }
            case '6':
                std::cout << "Exiting..." << std::endl;
                std::cout << "Have a nice day";
                break;
            default:
                std::cout << "Ivalid choice. Retry please" << std::endl;
        }
    } while (choice != '6');
    return 0;
}