#include <string>

using namespace std;

struct product
{
    int productID, quantity;
    string name;
    float price;
    product(int pid,string name, float p=9999.99, int qty=0){
        productID = pid;
        this->name = name;
        price = p;
        quantity = qty;
    }
};

class Store{
    struct node:public product{
        node *left, *right;
        node(int pid,string name, float p=9999.99, int qty=0):product(pid,name,p,qty){;}
    };
    public:

};

class Cart{
    struct node:public product{
        node *left, *right;
        node(int pid,string name, float p=9999.99, int qty=0):product(pid,name,p,qty){;}
    };
    public:
};