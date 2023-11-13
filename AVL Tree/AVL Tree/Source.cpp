#include<iostream>
#include <fstream>
#include <chrono>
using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::nanoseconds;
using std::chrono::system_clock;

struct node
{
    int data;
    node* left;
    node* right;
    int height;
};
typedef node* NodePtr;
struct QueueNode
{
    node* trans;
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

    void addToQueue(node* tmp)
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

    node* delQueue()
    {
        QueueNode* cur = Head->next;
        node* tmp_c = Head->trans;

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

class BST
{
    

    node* root;

    void makeEmpty(node* t)
    {
        if (t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    node* insert(int x, node* t)
    {
        if (t == NULL)
        {
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if (x < t->data)
        {
            t->left = insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if (x > t->data)
        {
            t->right = insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    node* singleRightRotate(node*& t)
    {
        uint64_t s;
        uint64_t ms = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
        if (t->left != NULL) {
            node* u = t->left;
            t->left = u->right;
            u->right = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            u->height = max(height(u->left), t->height) + 1;

            s = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
            //cout << ms - s << endl;
            return u;
        }
        s = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
       // cout << ms - s << endl;
        return t;
    }
    node* singleLeftRotate(node*& t)
    {
        uint64_t s;
        uint64_t ms = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
        if (t->right != NULL) {
            node* u = t->right;
            t->right = u->left;
            u->left = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            u->height = max(height(t->right), t->height) + 1;
            s = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
           // cout << ms - s << endl;
            return u;
        }
        s = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
       // cout << ms - s << endl;
        return t;
    }

    node* doubleLeftRotate(node*& t)
    {

        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node*& t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node* findMin(node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t)
    {
        node* temp;

        // Element not found
        if (t == NULL)
            return NULL;

        // Searching for element
        else if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        // With one or zero child
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }
        if (t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right)) + 1;

        // If node is unbalanced
        // If left node is deleted, right case
        if (height(t->left) - height(t->right) == 2)
        {
            // right right case
            if (height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if (height(t->right) - height(t->left) == 2)
        {
            // left left case
            if (height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node* t)
    {
        if (t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(node* t)
    {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
    void preorder(node* t)
    {
        if (t == NULL)
            return;
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);
    }
    void postorder(node* t)
    {
        if (t == NULL)
            return;
        postorder(t->left);
        postorder(t->right);
        cout << t->data << " ";
    }
    void Width()
    {
        Queue Universal;
        Universal.addToQueue(root);

        node* tmp;

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

public:
    BST()
    {
        root = NULL;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void find(int x) {
        node* tmp = root;
        for (;;) {
            if (tmp == NULL)
            {
                cout << x << " not found.\n";
                break;
            }
            if (tmp->data == x) {
                cout << x << " found.\n";
                break;
            }
            else if (x > tmp->data)tmp = tmp->right;
            else tmp = tmp->left;
        }
    }
    void display()
    {
        char c;
        cout << "Please choose output method:\n1) Inorder\n2) Preorder\n3) Postorder\n4) By width\n";
        cin >> c;
        switch (c) {
        case'1':
            inorder(root);
            break;
        case'2':
            preorder(root);
            break;
        case'3':
            postorder(root);
            break;
        case'4':
            Width();
            break;
        default:
            cout << "Wrong input.\n";
            break;

        }
        
        cout << endl;
    }
    
    void GetHeight() {
        cout<<"Height of tree is "<<height(root)+1<<endl;
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

int main()
{
    char c; int tmp;
    bool exit = 0;
    BST t;
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
            t.remove(tmp);
            break;
        case'3':
            t.display();
            break;
        case'4':
            t.GetHeight();
            break;
        case'5':
            cout << "Enter number to find: ";
            cin >> tmp;
            t.find(tmp);
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