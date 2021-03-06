#include "proj.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

#define file_name "store.bin"

using namespace std;

Store::Store()
{
    s_root = NULL;
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
void Store::delete_item(const int &x, int b)
{
    delete_item(x, s_root, b);
}
void Store::delete_item(const int &x, store_node *&sn, int b)
{
    if (sn == NULL)
        return;

    if (x < sn->productID)
        delete_item(x, sn->left);
    else if (sn->productID < x)
        delete_item(x, sn->right);
    else if (sn->left != NULL && sn->right != NULL)
    {
        store_node *temp = findMin(sn->right);
        sn->productID = temp->productID;
        sn->name = temp->name;
        sn->price = temp->price;
        sn->quantity = temp->quantity;
        delete_item(sn->productID, sn->right);
    }
    else
    {
        store_node *oldNode = sn;
        sn = (sn->left != NULL) ? sn->left : sn->right;
        delete oldNode;
    }
    balance(sn);
    if (!b)
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
    cout << "Inventory:\n\n";
    cout << "Product Id  |" << setw(28) << "Product Name  |"
         << "  Quantity  | "
         << "Price\n";
    cout << "---------------------------------------------------------------\n";
    print(s_root);
}

void Store::print(store_node *&sn)
{
    if (sn != NULL)
    {
        print(sn->left);
        cout << setw(11) << sn->productID << " | " << setw(25) << sn->name << " |" << setw(10) << sn->quantity << "  | " << sn->price << endl;
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
        // cout << "Product found" << endl;
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
            return check_quantity(x, qty, sn->left);
        else
            return check_quantity(x, qty, sn->right);
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
            return get_price(x, sn->left);
        else
            return get_price(x, sn->right);
    }
    else
        cout << "Product not found\n";
    return -1;
}

product Store::remove_root()
{
    return remove_root(s_root->productID, s_root);
}

product Store::remove_root(const int &x, store_node *&sn)
{
    if (sn == NULL)
    {
        product p(-1, "");
        return p;
    }
    else if (sn->left != NULL && sn->right != NULL)
    {
        product p(sn->productID, sn->name, sn->price, sn->quantity, sn->height);
        store_node *temp;
        temp = findMin(sn->right);
        sn->productID = temp->productID;
        sn->name = temp->name;
        sn->price = temp->price;
        sn->quantity = temp->quantity;
        delete_item(sn->productID, sn->right, 1);
        return p;
    }
    else
    {
        product p(sn->productID, sn->name, sn->price, sn->quantity, sn->height);
        store_node *oldNode = sn;
        sn = (sn->left != NULL) ? sn->left : sn->right;
        delete oldNode;
        return p;
    }
}

void Store::store_save()
{
    struct prod
    {
        int pid;
        char name[25];
        int qty;
        float price;
    } p;
    remove(file_name);
    ofstream file(file_name, ios::binary);
    product t;
    char name[25];
    int n = 0;
    while (s_root != NULL)
    {
        t = remove_root();
        p.pid = t.productID;
        t.name.copy(p.name, t.name.length(), 0);
        p.name[t.name.length()] = '\0';
        p.price = t.price;
        p.qty = t.quantity;
        file.write((char *)&p, sizeof(p));
        n++;
    }
    file.close();
    cout << "Store: " << n << " records stored into database\n";
}

void Store::store_load()
{
    struct prod
    {
        int pid;
        char name[25];
        int qty;
        float price;
    } p;
    int n = 0;
    ifstream file;
    char name[25];
    file.open(file_name, ios::binary);
    if (file)
    {
        product t;
        size_t s;
        while (file.read((char *)&p, sizeof(p)))
        {
            t.productID = p.pid;
            t.name.assign(p.name);
            t.quantity = p.qty;
            t.price = p.price;
            add_item(t.productID, t.name, t.quantity, t.price);
            n++;
        }
        file.close();
    }
    cout << "Store: " << n << " records are retrieved from the database\n";
}