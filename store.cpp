#include "proj.h"
#include <iostream>
#include <fstream>

using namespace std;

Store::Store()
{
    s_root = NULL;
    // ifstream file;
    // file.open("store.bin",ios::binary);
    // product t;
    // int n=0;
    // while(file.read((char *)&t,sizeof(t))){
    //     add_item(t.productID,t.name,t.quantity,t.price);
    //     n++;
    // }
    // file.close();
    // cout<<<<"Store: "<<n<<" records are retrieved from the database\n";
}
int Store::check_password(string entered_password)
{
    if (password == entered_password)
        return 1;
    else
        return 0;
}
int Store::height(store_node *sn) const
{
    return (sn == NULL) ? -1 : sn->height;
}
void Store::add_item(const int &x, const string &s, const int &q, const float &p)
{
    add_item(x, s, q, p, s_root);
}

void Store::add_item(const int &x, const string &s, const int &q, const float &p, store_node *&sn)
{
    if (sn == NULL)
    {
        sn = new store_node(x, s, p, q);
    }
    else if (x < sn->productID)
    {
        add_item(x, s, q, p, sn->left);
        if (height(sn->left) - height(sn->right) == 2)
        {
            if (x < sn->left->productID)
                singlerotatewithleft(sn);
            else
                doublerotatewithleft(sn);
        }
    }
    else if (sn->productID < x)
    {
        add_item(x, s, q, p, sn->right);
        if (height(sn->right) - height(sn->left) == 2)
        {
            if (sn->right->productID < x)
                singlerotatewithright(sn);
            else
                doublerotatewithright(sn);
        }
    }
    sn->height = max(height(sn->left), height(sn->right)) + 1;
}
void Store::delete_item(const int &x)
{
    delete_item(x, s_root);
}
void Store::delete_item(const int &x, store_node *&sn)
{
    if (sn == NULL)
        return;

    if (x < sn->productID)
        delete_item(x, sn->left);
    else if (sn->productID < x)
        delete_item(x, sn->right);
    else if (sn->left != NULL && sn->right != NULL)
    {
        sn->productID = findMin(sn->right)->productID;
        delete_item(sn->productID, sn->right);
    }
    else
    {
        store_node *oldNode = sn;
        sn = (sn->left != NULL) ? sn->left : sn->right;
        delete oldNode;
    }
    balance(sn);
    cout << "Product ID " << x << " removed from store\n\n";
}
void Store::balance(store_node *&sn)
{
    if (sn == NULL)
        return;

    if (height(sn->left) - height(sn->right) == 2)
        if (height(sn->left) >= height(sn->left->right))
            singlerotatewithleft(sn);
        else
            doublerotatewithleft(sn);
    else if (height(sn->right) - height(sn->left) == 2)
        if (height(sn->right) >= height(sn->right->left))
            singlerotatewithright(sn);
        else
            doublerotatewithright(sn);

    sn->height = max(height(sn->left), height(sn->right)) + 1;
}
void Store::singlerotatewithleft(store_node *&k2)
{
    store_node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

void Store::singlerotatewithright(store_node *&k2)
{
    store_node *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->right), height(k2->left)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;
    k2 = k1;
}

void Store::doublerotatewithleft(store_node *&k3)
{
    singlerotatewithright(k3->left);
    singlerotatewithleft(k3);
}

void Store::doublerotatewithright(store_node *&k3)
{
    singlerotatewithleft(k3->right);
    singlerotatewithright(k3);
}

int Store::max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

void Store::display()
{
    cout << "\n";
    cout << "Your Store\n";
    cout << "Product Id\tProduct Name\tQuantity\n";
    print(s_root);
}

void Store::print(store_node *&sn)
{
    if (sn != NULL)
    {
        cout << sn->productID << "\t\t" << sn->name << "\t\t" << sn->quantity << endl;
        print(sn->left);
        print(sn->right);
    }
}
void Store::add_quantity(const int &x, int &qty)
{
    add_quantity(x, qty, s_root);
}
void Store::add_quantity(const int &x, int &qty, store_node *&sn)
{
    if (sn == NULL)
    {
        cout << "Product not found\n";
        return;
    }
    if (x == sn->productID)
    {
        cout << "Product found!!" << endl;
        sn->quantity += qty;
    }
    else if (x < sn->productID)
        add_quantity(x, qty, sn->left);
    else
        add_quantity(x, qty, sn->right);
}
void Store::remove_quantity(const int &x, int &qty)
{
    remove_quantity(x, qty, s_root);
}
void Store::remove_quantity(const int &x, int &qty, store_node *&sn)
{
    if (sn == NULL)
    {
        cout << "Product not found\n";
        return;
    }
    if (x == sn->productID)
    {
        cout << "Product found!!" << endl;
        sn->quantity -= qty;
    }
    else if (x < sn->productID)
        remove_quantity(x, qty, sn->left);
    else
        remove_quantity(x, qty, sn->right);
}
string Store::check_quantity(const int &x, int &qty)
{
    string s = check_quantity(x, qty, s_root);
    return s;
}
string Store::check_quantity(const int &x, int &qty, store_node *&sn)
{
    if (sn != NULL)
    {
        if (x == sn->productID)
        {
            if (sn->quantity >= qty)
                return sn->name;
            else
                return "";
        }
        else if (x < sn->productID)
            remove_quantity(x, qty, sn->left);
        else
            remove_quantity(x, qty, sn->right);
    }
    return "-1";
}

float Store::get_price(const int &x)
{
    return get_price(x, s_root);
}

float Store::get_price(const int &x, store_node *&sn)
{
    if (sn != NULL)
    {
        if (x == sn->productID)
        {
            return sn->price;
        }
        else if (x < sn->productID)
            get_price(x, sn->left);
        else
            get_price(x, sn->right);    
    }
    else
        cout << "Product not found\n";
    return -1;
}