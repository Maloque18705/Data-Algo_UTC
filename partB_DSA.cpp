#include <iostream>
#include <fstream>
#include <string>
#include <locale> // Để xử lý Unicode
using namespace std;

struct Node {
    string english;
    string vietnamese;
    Node* left;
    Node* right;

    Node(string eng, string viet) : english(eng), vietnamese(viet), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, const string& english, const string& vietnamese) {
        if (node == nullptr) return new Node(english, vietnamese);

        if (english < node->english) node->left = insert(node->left, english, vietnamese);
        else if (english > node->english) node->right = insert(node->right, english, vietnamese);

        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) node = node->left;
        return node;
    }

    Node* remove(Node* node, const string& english) {
        if (node == nullptr) return node;

        if (english < node->english) node->left = remove(node->left, english);
        else if (english > node->english) node->right = remove(node->right, english);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->english = temp->english;
            node->vietnamese = temp->vietnamese;
            node->right = remove(node->right, temp->english);
        }
        return node;
    }

    Node* search(Node* node, const string& english) {
        if (node == nullptr || node->english == english) return node;

        if (english < node->english) return search(node->left, english);
        else return search(node->right, english);
    }

    void inOrder(Node* node, ofstream &outFile) {
        if (node != nullptr) {
            inOrder(node->left, outFile);
            outFile << node->english << ": " << node->vietnamese << endl;
            inOrder(node->right, outFile);
        }
    }

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const string& english, const string& vietnamese) {
        root = insert(root, english, vietnamese);
    }

    void remove(const string& english) {
        root = remove(root, english);
    }

    Node* search(const string& english) {
        return search(root, english);
    }

    void update(const string& english, const string& newVietnamese) {
        Node* node = search(root, english);
        if (node != nullptr) {
            node->vietnamese = newVietnamese;
        }
    }

    void inOrder(ofstream &outFile) {
        inOrder(root, outFile);
    }
};

class Dictionary {
private:
    BST bst;

public:
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error opening file!" << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            size_t pos = line.find(": ");
            if (pos != string::npos) {
                string english = line.substr(0, pos);
                string vietnamese = line.substr(pos + 2); // Bỏ qua dấu ": " ở giữa
                bst.insert(english, vietnamese);
            }
        }

        inFile.close();
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file!" << endl;
            return;
        }

        bst.inOrder(outFile);
        outFile.close();
    }

    void addWord(const string& english, const string& vietnamese) {
        bst.insert(english, vietnamese);
    }

    void removeWord(const string& english) {
        bst.remove(english);
    }

    void updateWord(const string& english, const string& newVietnamese) {
        bst.update(english, newVietnamese);
    }

    void findWord(const string& english) {
        Node* result = bst.search(english);
        if (result) {
            cout << "Found: " << result->english << " - " << result->vietnamese << endl;
        } else {
            cout << "Word not found!" << endl;
        }
    }
};

void menu(Dictionary &dictionary) {
    int choice;
    string english, vietnamese, filename = "dictionary.txt";

    while (true) {
        cout << "\n===== Dictionary Menu =====\n";
        cout << "1. Load dictionary from file\n";
        cout << "2. Save dictionary to file\n";
        cout << "3. Add a new word\n";
        cout << "4. Remove a word\n";
        cout << "5. Update a word's translation\n";
        cout << "6. Find a word\n";
        cout << "7. Display all words\n";
        cout << "8. Exit\n";
        cout << "Choose an option (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1:
                dictionary.loadFromFile(filename);
                cout << "Dictionary loaded from file.\n";
                break;
            case 2:
                dictionary.saveToFile(filename);
                cout << "Dictionary saved to file.\n";
                break;
            case 3:
                cout << "Enter English word: ";
                cin >> english;
                cout << "Enter Vietnamese translation: ";
                cin.ignore(); // Ignore newline left by cin
                getline(cin, vietnamese);
                dictionary.addWord(english, vietnamese);
                cout << "Word added.\n";
                break;
            case 4:
                cout << "Enter English word to remove: ";
                cin >> english;
                dictionary.removeWord(english);
                cout << "Word removed if it existed.\n";
                break;
            case 5:
                cout << "Enter English word to update: ";
                cin >> english;
                cout << "Enter new Vietnamese translation: ";
                cin.ignore(); // Ignore newline left by cin
                getline(cin, vietnamese);
                dictionary.updateWord(english, vietnamese);
                cout << "Word updated.\n";
                break;
            case 6:
                cout << "Enter English word to find: ";
                cin >> english;
                dictionary.findWord(english);
                break;
            case 7:
                cout << "All words in the dictionary:\n";
                dictionary.saveToFile("temp.txt"); // Save to a temporary file
                {
                    ifstream tempFile("temp.txt"); // Open temporary file
                    if (tempFile.is_open()) {
                        cout << tempFile.rdbuf(); // Display content of temp file
                        tempFile.close();
                    } else {
                        cerr << "Error opening temporary file for display." << endl;
                    }
                }
                remove("temp.txt"); // Delete temporary file after use
                break;
            case 8:
                cout << "Exiting program.\n";
                return; // Exit the menu loop
            default:
                cout << "Invalid choice. Please select a number from 1 to 8.\n";
                break;
        }
    }
}


int main() {
    Dictionary dictionary;
    menu(dictionary);
    return 0;
}



