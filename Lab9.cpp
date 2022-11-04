#include<iostream>
#include<queue>
using namespace std;
template<typename T>
class AVL{
    struct node{
        node*left;
        node*right;
        T data;
        node(T data)
        {
            this->data=data;
            this->left=this->right=nullptr;
        }
    };
    node*root;
public:
    AVL(){
        this->root=nullptr;
    }
    bool insert(int data)
    {
        return insert_(root, data);
    }
    bool insert_(node *&root, int data)
    {
        if (root == NULL)
        {
            node *n_node = new node(data);
            root = n_node;
            return true;
        }
        if (root->data == data)
            return false;
        if (data < root->data)
            return insert_(root->left, data);
        if (data > root->data)
            return insert_(root->right, data);
        return true;
    }

    int get_height(node*root)
    {
        if(root==nullptr)
            return 0;
        return (1+max(get_height(root->left), get_height(root->right)));
    }
    int height()
    {
        return get_height(root);
    }
    int factor()
    {
        return this->get_balancing_factor(root);
    }
    int get_balancing_factor(node*root)
    {
        if(root==nullptr)
            return 0;
        return (get_height(root->left)-get_height(root->right));
    }
    int get_node_data(node *root)
    {
        node *t = root;
        while (t->left != NULL)
            t = t->left;
        return t->data;
    }
    void delete_node(node *&root, int data)
    {
        if (root == NULL)
            return;
        if (root->data == data)
        {
            if (root->left == NULL && root->right == NULL)
            {
                node *t = root;
                root = NULL;
                delete t;
                return;
            }
            if (root->left == NULL)
            {
                node *t = root;
                root = root->right;
                delete t;
                return;
            }
            if (root->right == NULL)
            {
                node *t = root;
                root = root->left;
                delete t;
                return;
            }
            if (root->left != NULL && root->right != NULL)
            {
                int data1 = get_node_data(root->right);
                root->data = data1;
                delete_node(root->right, data1);
                return;
            }
        }
        if (data > root->data)
            delete_node(root->right, data);
        else
            delete_node(root->left, data);
    }
    void del_n(int key)
    {
        delete_node(this->root, key);
    }
//    T get_max(node*root)
//    {
//        if(root==nullptr)
//            return 0;
//        if(root->right==nullptr)
//            return root->data;
//       return get_max(root->right);
//    }
    void get_max(node *root, queue<int> &q)
    {
        if (root == NULL)
            return;
        get_max(root->left, q);
        q.push(root->data);
        get_max(root->right, q);

    }
    int get_max_k(int k)
    {
        queue<int> q;
        get_max(this->root, q);
        int s=q.size();
        for (int i = 1; i <s-k;   q.pop(),i++);
        return q.front();
    }
    void preorder(node*root)
    {
        if(root==nullptr)
            return;
        cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }
    void preorder()
    {
        this->preorder(root);
    }
    void inorder(node*root)
    {
        if(root==nullptr)
            return;
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
    void inorder()
    {
        this->inorder(root);
    }
    void postorder(node*root)
    {
        if(root==nullptr)
            return;
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<" ";

    }
    void postorder()
    {
        this->postorder(root);
    }

};
int main()
{
    AVL<int>*avl=new AVL<int>;
  avl->insert(10);
  avl->insert(20);
  avl->insert(4);
  avl->insert(40);
  avl->insert(30);
  avl->insert(15);
  cout<<"inorder is:-\n";
  avl->inorder();
  cout<<endl;
    cout<<"preorder is:-\n";
  avl->preorder();
  cout<<endl;
    cout<<"postorder is:-\n";
  avl->postorder();
  cout<<endl;
  cout<<"AVL Factor:-\n";
  cout<<avl->factor()<<endl;
  cout<<"First Max is:-\n";
  cout<<avl->get_max_k(0)<<endl;
    cout<<"Second Max is:-\n";
  cout<<avl->get_max_k(1)<<endl;
    cout<<"Third Max is:-\n";
  cout<<avl->get_max_k(2)<<endl;
  return 0;


}
