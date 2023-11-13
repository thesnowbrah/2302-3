#include <iostream>
#include <fstream>
using namespace std;

struct node {
    int key;
    struct node* left, * right, * parent;
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

struct node* newNode(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left  = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}

void inorder(struct node* root) {
    if (root != NULL ) {
        inorder(root->left);

        cout << root->key << " ";

        inorder(root->right);
    }
    
}
void preorder(struct node* root) {
    if (root != NULL) {

        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }

}
void postorder(struct node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }

}

struct node* insert(struct node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
        node->left->parent = node;
    }
    
    else {
        node->right = insert(node->right, key);
        node->right->parent = node;
    }
    return node;
}

node* InsertFile(node* node) {
    fstream f; int tmp;
    f.open("Text11.txt", ios::in);
    while (!f.eof()) {
        f >> tmp;
        node=insert(node, tmp);
    }
    return node;
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}
struct node* maxValueNode(struct node* node) {
    struct node* current = node;

    while (current && current->right != NULL)
        current = current->right;

    return current;
}

struct node* deleteNode(struct node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
node* Succesor(node* Node) {
    if (Node->right != NULL) {
        Node = Node->right;
        Node = minValueNode(Node);
    }
    else {
        node* tmp = Node;
        if (tmp->parent != NULL) {
            while (tmp == tmp->parent->right) {
                tmp = tmp->parent;
            }
            if (tmp->parent != NULL) { Node = tmp->parent; }
            
        }
       
    }
    return Node;
}
node* Predecessor(node* Node) {
    if (Node->left != NULL) {
        Node = Node->left;
        Node = maxValueNode(Node);
    }
    else {
        node* tmp = Node;
        if (tmp->parent != NULL) {
            while (tmp == tmp->parent->left) {
                tmp = tmp->parent;
            }
            if (tmp->parent != NULL) { Node = tmp->parent; }

        }

    }
    return Node;
}
void Delete(node* Node) {
    if (Node->right != NULL) {
        node* tmp = Succesor(Node);
        Node->key = tmp->key;
        Delete(tmp);
    }
    else {
        if (Node->left != NULL) {
            if(Node->parent!=NULL){
                Node->left->parent = Node->parent;
                if (Node == Node->parent->left)Node->parent->left = Node->left;
                else Node->parent->right = Node->left;
                free(Node->left);
                free(Node->right);
                free(Node);
                Node = NULL;
            }
            else {
                free(Node->left);
                free(Node->right);
                free(Node);
                Node = NULL;
            }
        }
        else {
            free(Node->left);
            free(Node->right);
            free(Node);
            Node = NULL;
        }
    }
}

int tree_height(node* root) {
    if (!root)
        return 0;
    else {
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

void Find(node* Node, int key) {
    node* tmp = Node;
    for (;;) {
        if (tmp == NULL)
        {
            cout << key << " not found.\n";
            break;
        }
        if (tmp->key == key) {
            cout << key << " found.\n";
            break;
        }
        else if (key > tmp->key)tmp = tmp->right;
        else tmp = tmp->left;
    }
}

void Width(node*root)
{
    Queue Universal;
    Universal.addToQueue(root);

    node* tmp;

    while (!Universal.isEmpty())
    {
        tmp = Universal.delQueue();
        cout << tmp->key << " ";

        if (tmp->left != NULL)
            Universal.addToQueue(tmp->left);
        if (tmp->right != NULL)
            Universal.addToQueue(tmp->right);
    }
}

void Menu(node* root) {
    char c, b; int tmp; bool exit = 0; int num;
    node* temp;
    //root=InsertFile(root);
    for (;;) {
        cout << "Please enter command: \n1) Insert new node;\n2) Output;\n3) Delete;\n4) Min key;\n5) Max key;\n6) Height of tree;\n7) Find key;\n0) Exit.\n";
        cin >> c;
        switch (c) {
        case '1':
            cout << "Please enter new node key: ";
            cin >> tmp;
            root=insert(root, tmp);
                break;
        case '2':
            cout << "Please choose output method: \n1) InOrder\n2) PreOrder\n3) PostOrder\n4) By width\n";
            cin >> b;
            switch(b){
            case'1':
                inorder(root);
                cout << endl;
                break;
            case'2':
                preorder(root);
                cout << endl;
                break;
            case'3':
                postorder(root);
                cout << endl;
                break;
            case'4':
                Width(root);
                cout << endl;
                break;
            default: 

                break;
            }
            break;
        case '3':
            cout << "Enter key for deletion: ";
            
            cin >> tmp;
            deleteNode(root, tmp);
            break;
        case '4':
            temp =minValueNode(root);
            cout <<"Minimum value: "<< temp->key<<endl;
            break;
        case '5':
            temp = maxValueNode(root);
            cout << "Minimum value: " << temp->key << endl;
            break;
        case '6':
            num = tree_height(root);
            cout << "Tree height is " << num << endl;
            break;
            
            
            break;
        case '7':
            cout << "Please enter key to find: ";
            cin >> num;
            Find(root, num);
            break;
        case '0':
            cout << "Exitting, bye!\n";
            exit = 1;
            break;
        default:
            cout << "Wrong input.\n";
            break;
        }
        if (exit == 1)break;
        inorder(root);
        cout << endl;
    }
}

int main() {
    struct node* root = NULL;
    
    Menu(root);
}