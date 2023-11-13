#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::nanoseconds;
using std::chrono::system_clock;


struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;
    int color;
};

typedef Node* NodePtr;
struct QueueNode
{
    Node* trans;
    QueueNode* next;
};

class Queue
{
private:
    QueueNode* Head;

public:
    Queue()
    {
        Head = NULL;
    }

    int isEmpty()
    {
        if (Head == NULL)
            return 1;
        else
            return 0;
    }

    void addToQueue(Node* tmp)
    {
        QueueNode* Ptr = new QueueNode;
        Ptr->trans = tmp;

        if (Head == NULL)
        {
            Head = Ptr;
            Ptr->next = NULL;
        }
        else
        {
            QueueNode* tmp_c = Head;

            while (tmp_c->next != NULL)
                tmp_c = tmp_c->next;

            tmp_c->next = Ptr;
            Ptr->next = NULL;
        }
    }

    Node* delQueue()
    {
        QueueNode* cur = Head->next;
        Node* tmp_c = Head->trans;

        if (Head != NULL)
        {
            delete Head;
            Head = cur;
            return tmp_c;
        }
        else
            return NULL;
    }
};
class RedBlackTree {
private:
    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    void preOrderHelper(NodePtr node) {
        if (node != TNULL) {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(NodePtr node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(NodePtr node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    

    void deleteFix(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteFix(x);
        }
    }

    void insertFix(NodePtr k) {
        uint64_t s;
        uint64_t ms = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
        NodePtr u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
        s = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
        //cout << ms - s << endl;
    }

    void printHelper(NodePtr root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

   

public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void preorder() {
        preOrderHelper(this->root);
    }

    void inorder() {
        inOrderHelper(this->root);
    }

    void postorder() {
        postOrderHelper(this->root);
    }
    void Width()                   
    {
        Queue Universal;
        Universal.addToQueue(root);

        Node* tmp;

        while (!Universal.isEmpty())
        {
            tmp = Universal.delQueue();
            cout << tmp->data << " ";

            if (tmp->left != NULL)
                Universal.addToQueue(tmp->left);
            if (tmp->right != NULL)
                Universal.addToQueue(tmp->right);
        }
    }

    NodePtr searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }

    NodePtr minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insert(int key) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->data < y->data) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    NodePtr getRoot() {
        return this->root;
    }

    void deleteNode(int data) {
        deleteNodeHelper(this->root, data);
    }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
    int heightHelper(Node* n) const {
        if (n == NULL) {
            return -1;
        }
        else {
            return max(heightHelper(n->left), heightHelper(n->right)) + 1;
        }
    }

    int max(int x, int y) const {
        if (x >= y) {
            return x;
        }
        else {
            return y;
        }
    }
    void InsertFile() {
        fstream f; int tmp;
        f.open("Text11.txt", ios::in);
        while (!f.eof()) {
            f >> tmp;
            insert(tmp);
        }
    }
};

int main() {
    RedBlackTree t;
    char c; int tmp;
    bool exit = 0;
    //t.InsertFile();
    while (exit == 0) {
        cout << "Please choose function:\n1) Insert;\n2) Delete;\n3) Output;\n4) Height of tree;\n5) Find;\n0) Exit.\n";
        cin >> c;
        switch (c) {
        case'1':
            cout << "Enter number to insert: ";
            cin >> tmp;
            t.insert(tmp);
            break;
        case'2':
            cout << "Enter number to delete: ";
            cin >> tmp;
            t.deleteNode(tmp);
            break;
        case'3':
            
            cout << "Please choose output method:\n1) Inorder\n2) Preorder\n3) Postorder\n4) By width\n";
            cin >> c;
            switch (c) {
            case'1':
                t.inorder();
                break;
            case'2':
                t.preorder();
                break;
            case'3':
                t.postorder();
                break;
            case'4':
                t.postorder();
                break;
            default:
                cout << "Wrong input.\n";
                break;

            }

            cout << endl;
            break;
        case'4':
            tmp=t.heightHelper(t.getRoot());
            cout << "Height of tree is " << tmp << endl;
            break;
        case'5':
            cout << "Enter number to find: ";
            cin >> tmp;
            if (t.searchTree(tmp)->data==tmp )cout << tmp << " found.\n";
            else cout << tmp << " not found.\n";
            break;
        case'0':
            exit = 1;
            cout << "Bye!\n";
            break;
        default:
            break;

        }
    }
}