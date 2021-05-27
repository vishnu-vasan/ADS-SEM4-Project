#include <iostream>
using namespace std;
#include "proj.h"

Cart::Cart()
{
    root = NULL;
}

void Cart::insert(const int &x, const string &s, const int &q, const float &p)
{
    insert(x, s, q, p, root);
}

int Cart::height(node *t) const
{
    return (t == NULL) ? -1 : t->height;
}

void Cart::insert(const int &x, const string &s, const int &q, const float &p, node *&t)
{
    if (t == NULL)
    {
        t = new node(x, s, p, q);
    }
    else if (x < t->productID)
    {
        insert(x, s, q, p, t->left);
        if (height(t->left) - height(t->right) == 2)
        {
            if (x < t->left->productID)
                singlerotatewithleft(t);
            else
                doublerotatewithleft(t);
        }
    }
    else if (t->productID < x)
    {
        insert(x, s, q, p, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if (t->right->productID < x)
                singlerotatewithright(t);
            else
                doublerotatewithright(t);
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;
}

void Cart::singlerotatewithleft(node *&k2)
{
    node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

void Cart::singlerotatewithright(node *&k2)
{
    node *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->right), height(k2->left)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;
    k2 = k1;
}

void Cart::doublerotatewithleft(node *&k3)
{
    singlerotatewithright(k3->left);
    singlerotatewithleft(k3);
}

void Cart::doublerotatewithright(node *&k3)
{
    singlerotatewithleft(k3->right);
    singlerotatewithright(k3);
}

int Cart::max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

void Cart::display()
{
    cout << "\n";
    cout << "Your cart\n";
    cout << "Product Id\tProduct Name\tQuantity\tTotal amount(per item)\n";
    print(root);
}

void Cart::print(node *&t)
{
    if (t != NULL)
    {
        cout << t->productID << "\t\t" << t->name << "\t\t" << t->quantity << "\t\t" << t->quantity * t->price << endl;
        print(t->left);
        print(t->right);
    }
}

void Cart::remove(const int &x)
{
    remove(x, root);
}

void Cart::remove(const int &x, node *&t)
{
    if (t == NULL)
        return;

    if (x < t->productID)
        remove(x, t->left);
    else if (t->productID < x)
        remove(x, t->right);
    else if (t->left != NULL && t->right != NULL)
    {
        t->productID = findMin(t->right)->productID;
        remove(t->productID, t->right);
    }
    else
    {
        node *oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
    balance(t);
    cout << "Product ID " << x << " removed from cart\n\n";
}

void Cart::balance(node *&t)
{
    if (t == NULL)
        return;

    if (height(t->left) - height(t->right) == 2)
        if (height(t->left) >= height(t->left->right))
            singlerotatewithleft(t);
        else
            doublerotatewithleft(t);
    else if (height(t->right) - height(t->left) == 2)
        if (height(t->right) >= height(t->right->left))
            singlerotatewithright(t);
        else
            doublerotatewithright(t);

    t->height = max(height(t->left), height(t->right)) + 1;
}
int Cart::get_quantity(const int &x)
{
    return get_quantity(x, root);
}
int Cart::get_quantity(const int &x, node *&t)
{
    if (t == NULL)
    {
        cout << "Product not found\n";
        return -1;
    }
    if (x == t->productID)
    {
        return t->quantity;
    }
    else if (x < t->productID)
        get_quantity(x, t->left);
    else
        get_quantity(x, t->right);
}
