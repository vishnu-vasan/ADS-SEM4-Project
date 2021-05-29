#include <iostream>
#include <fstream>
#include "proj.h"
#include <iomanip>

using namespace std;

Cart::Cart()
{
    root = NULL;
}

void Cart::add_item(const int &x, const string &s, const int &q, const float &p)
{
    add_item(x, s, q, p, root);
}

int Cart::height(node *t) const
{
    return (t == NULL) ? -1 : t->height;
}

void Cart::add_item(const int &x, const string &s, const int &q, const float &p, node *&t)
{
    if (t == NULL)
    {
        t = new node(x, s, p, q);
    }
    else if (x < t->productID)
    {
        add_item(x, s, q, p, t->left);
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
        add_item(x, s, q, p, t->right);
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

void Cart::display_cart()
{
    cout << "\n";
    cout << "Your cart\n\n";
    cout <<"Product Id  |"<<setw(30)<<"Product Name  |"<<"  Quantity  |"<<" Total Price \n";
    cout<<"---------------------------------------------------------------------\n";
    float bill = display_cart(root);
    cout<<"Total Amount: "<<bill<<"\n";
}

float Cart::display_cart(node *&t, ostream &out)
{
    float tot = 0;
    if (t != NULL)
    {
        out <<setw(10)<< t->productID<<"  |"<<setw(27)<< t->name <<"  |"<< setw(10)<< t->quantity <<"  | "<< t->quantity*t->price << endl;
        tot += display_cart(t->left,out);
        tot += display_cart(t->right,out);
        tot += t->quantity*t->price;
        return tot;
    }
    return 0;
}

void Cart::generate_bill(){
    string name, phoneno;
    cout<<"Enter Name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter Phone Number: ";
    getline(cin,phoneno);
    //   dd-mm-yyyy_hh:mm:ss format
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    string res="";
    strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
    string str(buffer);
    res=str+"_"+to_string(5+timeinfo->tm_hour)+":"+to_string(30+timeinfo->tm_min)+":"+to_string(timeinfo->tm_sec);
    res.append(".txt");
    ofstream fout(res.data());
    fout<<setprecision(2)<<fixed;
    fout<<"\t\tBill "<<"\n\n";
    fout<<"Name: "<<name<<"\n";
    fout<<"Phone No:"<<phoneno<<"\n\n";
    fout <<"Product Id  |"<<setw(30)<<"Product Name  |"<<"  Quantity  |"<<" Total Price \n";
    fout<<"---------------------------------------------------------------------\n";
    float bill = display_cart(root,fout);
    fout<<"\nTotal Amount: "<<bill<<"\n";
    fout.close();
}

void Cart::delete_item(const int &x)
{
    delete_item(x, root);
}

void Cart::delete_item(const int &x, node *&t)
{
    if (t == NULL)
        return;

    if (x < t->productID)
        delete_item(x, t->left);
    else if (t->productID < x)
        delete_item(x, t->right);
    else if (t->left != NULL && t->right != NULL)
    {
        t->productID = findMin(t->right)->productID;
        delete_item(t->productID, t->right);
    }
    else
    {
        node *oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
    balance_cart(t);
    cout << "Product ID " << x << " removed from cart\n\n";
}

void Cart::balance_cart(node *&t)
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
    if (t != NULL)
    {
        if (x == t->productID)
            return t->quantity;
        else if (x < t->productID)
            get_quantity(x, t->left);
        else
            get_quantity(x, t->right);
    }
    else
        cout << "Product not found\n";
    return -1;
}

bool Cart::isEmpty(){
    return (root==NULL);
}
