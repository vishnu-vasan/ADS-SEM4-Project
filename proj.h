#include <string>
using namespace std;
#ifndef PROJ_H_
#define PROJ_H_

struct product
{
    int productID, quantity, height;
    string name;
    float price;
    product(int pid=0, string name="", float p = 9999.99, int qty = 0, int h = -1)
    {
        productID = pid;
        this->name = name;
        price = p;
        quantity = qty;
        height = h;
    }
};

class Store
{
    struct store_node : public product
    {
        store_node *left, *right;
        store_node(int pid, string name, float p = 9999.99, int qty = 0, int h = -1) : product(pid, name, p, qty)
        {
            left = NULL;
            right = NULL;
        }
    };
    store_node *s_root;
    string password = "admin_1234";

    void add_item(const int &x, const string &s, const int &q, const float &p, store_node *&sn);
    void delete_item(const int &x, store_node *&sn);
    void add_quantity(const int &x, int &qty, store_node *&sn);
    int height(store_node *sn) const;
    void singlerotatewithleft(store_node *&k2);
    void singlerotatewithright(store_node *&k2);
    void doublerotatewithleft(store_node *&k3);
    void doublerotatewithright(store_node *&k3);
    int max(int a, int b);
    void print(store_node *&sn);
    void balance(store_node *&sn);
    void remove_quantity(const int &x, int &qty, store_node *&sn);
    string check_quantity(const int &x, int &qty, store_node *&sn);
    float get_price(const int &x, store_node *&sn);
    store_node *findMin(store_node *&sn) const
    {
        if (sn == NULL)
            return NULL;
        if (sn->left == NULL)
            return sn;
        return findMin(sn->left);
    }
    product remove_root(store_node *&);

public:
    Store();
    int check_password(string entered_password);
    void add_item(const int &x, const string &s, const int &q, const float &p);
    void delete_item(const int &x);
    void add_quantity(const int &x, int &qty);
    void display();
    void remove_quantity(const int &x, int &qty);
    string check_quantity(const int &x, int &qty);
    float get_price(const int &x);
    void store_save();
    void store_load();
};

class Cart
{
    struct node : public product
    {
        node *left, *right;
        node(int pid, string name, float p = 9999.99, int qty = 0, int h = -1) : product(pid, name, p, qty)
        {
            left = NULL;
            right = NULL;
        }
    };
    node *root;

    int height(node *t) const;
    void insert(const int &x, const string &s, const int &q, const float &p, node *&t);
    void singlerotatewithleft(node *&k2);
    void singlerotatewithright(node *&k2);
    void doublerotatewithleft(node *&k3);
    void doublerotatewithright(node *&k3);
    int max(int a, int b);
    void print(node *&t);    
    int get_quantity(const int &x, node *&t);
    node *findMin(node *t) const
    {
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return findMin(t->left);
    }
    void remove(const int &x, node *&t);
    void balance(node *&t);
public:
    Cart();
    void insert(const int &x, const string &s, const int &q, const float &p);
    void display();
    void remove(const int &x);
    int get_quantity(const int &x);
    bool isEmpty();
};

#endif