#include <string>

using namespace std;

struct product
{
    int productID, quantity, height;
    string name;
    float price;
    product(int pid,string name, float p=9999.99, int qty=0, int h=-1){
        productID = pid;
        this->name = name;
        price = p;
        quantity = qty;
        height=h;
    }
};


class Store{
    struct node:public product{
        node *left, *right;
        node(int pid,string name, float p=9999.99, int qty=0, int h=-1):product(pid,name,p,qty){;}
    };
    public:

};

class Cart{
    struct node:public product{
        node *left, *right;
        node(int pid,string name, float p=9999.99, int qty=0, int h=-1):product(pid,name,p,qty){
            left=NULL;
            right=NULL;
        }
    };
    node *root;
    public:
        Cart();
        void insert(const int &x, const string &s, const int &q, const float &p);
        int height(node *t) const;
        void insert(const int &x, const string &s, const int &q, const float &p, node *&t);
        void singlerotatewithleft(node *&k2);
        void singlerotatewithright(node *&k2);
        void doublerotatewithleft(node *&k3);
        void doublerotatewithright(node *&k3);
        int max(int a, int b);
        void display();
        void print(node *&t);
        void remove(const int &x);
        void remove(const int &x, node *&t);
        void balance(node *&t);
        node *findMin(node *t) const{
            if (t == NULL)
                return NULL;
            if (t->left == NULL)
                return t;
            return findMin(t->left);
        }
};