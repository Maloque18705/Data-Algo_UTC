#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    string english;
    string vietnamese;
    Node* left;
    Node* right;

    Node(string eng, string viet): english(eng), vietnamese(viet), left(nullptr), right(nullptr) {}
};

class BST{
    private:
    Node* root;

    //Insert a node
    Node* insert(Node* node, string english, string vietnamese){
        if (node == nullptr) return new Node(english, vietnamese);

        if (english < node->english) node->left = insert(node->left, english, vietnamese);
        else if (english > node->english) node->right = insert(node->right, english, vietnamese);

        return node;
    }

    //Finding the minimum node
    Node* findMin(Node* node){
        while (node && node->left != nullptr) node = node->left;
        return node;
    }

    //Delete a node
    Node* remove(Node *node, string english){
        if (node == nullptr) return node;

        if (english < node->english){
            node->left = remove(node->left, english);
        } 
        else if (english > node->english){
            node->right = remove(node->right, english);
        }
        else{
            if (node->left == nullptr){
                Node*temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr){
                Node* temp = node ->left;
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

    //Searching a node
    Node* search(Node* node, string english) {
        if (node == nullptr || node-> english == english){
            return node;
        }
        if (english < node->english){
            return search(node->left, english);
        }
        else {
            return search(node->right, english);
        }
    }

    //In-order traversal
    void inOrder(Node* node, ofstream &outFile){
        if (node != nullptr){
            inOrder(node->left, outFile);
            outFile << node->english << ": " << node->vietnamese << endl;
            inOrder(node->right, outFile);
        }
    }
    
    void clear(Node* node){
        if (node != nullptr){
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

        void insert(string english, string vietnamese){
            root = insert(root, english, vietnamese);
        }

        void remove(string english){
            root = remove(root, english);
        }

        Node* search(string english){
            return search(root, english);
        }

        void update(string english, string newVietnamese){
            Node* node = search(root, english);
            if(node != nullptr){
                node->vietnamese = newVietnamese;
            }
        }

        void inOrder(ofstream &outFile){
            inOrder(root, outFile);
        }
};

class Dictionary{
    private:
        BST bst;
    public:
        void loadFromFile(const string& filename){
            ifstream inFile(filename);
            if (!inFile){
                cout << "Error opening file" << endl;
                return;
            }

            string english, vietnamese;
            while (inFile >> english && getline(inFile, vietnamese)){
                if (!vietnamese.empty() && vietnamese[0] == ' '){
                    vietnamese.erase(0, 1);
                    bst.insert(english, vietnamese);
                }

                inFile.close();
            }
        }

        void saveToFile(const string& filename){
            ofstream outFile(filename);
            if(!outFile){
                cout << "Error opening file!" << endl;
                return;
            }

            bst.inOrder(outFile);
            outFile.close();
        }

        void addWord(const string& english, const string& vietnamese){
            bst.insert(english, vietnamese);
        }

        void removeWord(const string& english){
            bst.remove(english);
        }

        void updateWord(const string& english, const string& newVietnamese){
            bst.update(english, newVietnamese);
        }

        void findWord(const string& english){
            Node* result = bst.search(english);
            if (result){
                cout << "Found: " << result->english << " - " << result->vietnamese << endl;
            }
            else {
                cout << "Word not found!" << endl;
            }
        }
};

int main(){
    Dictionary dictionary;
    string filename = "dictionary.txt";

    // Load dictionary from file
    dictionary.loadFromFile(filename);

    // Add, remove, update, find words
    dictionary.addWord("hello", "xin chào");
    dictionary.addWord("book", "sách");
    dictionary.removeWord("hello");
    dictionary.updateWord("book", "quyển sách");
    dictionary.findWord("book");
    dictionary.addWord("England", "Anh Quốc");

    // Save dictionary to file
    dictionary.saveToFile(filename);

    return 0;
}