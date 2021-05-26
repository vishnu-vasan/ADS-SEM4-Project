#include <iostream>
using namespace std;
#include "proj.h"

int main()
{
    
    while (1)
    {
        int q;
        cout << "\nEnter the option:" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit" << endl;
        cin >> q;
        if (q == 1)
        {
            
        }
        else if (q == 2)
        {
            Cart c;
            while(1)
            {
                int u;
                cout<<"1. Add items(display and search)"<< endl;
	            cout<<"2. Delete items"<< endl;
                cout<<"3. View Cart"<< endl;
                cout<<"4. Checkout"<< endl;
                cout<<"5. Exit"<< endl;
                cin>>u;
                if (u == 1)
                {
                    int n;
                    string s;
                    cout << "\nEnter the product ID: ";
                    cin >> n;
                    // cout<< "Enter the product name: ";
                    // cin >> s;
                    // retireve product name from store class
                    //retrieve cost of the item from store class 
                    cout<<"Enter quantity required: ";
                    cin>>q;
                    //check if the quantity required is available in store
                    float p=3.2;
                    s="chips";
                    c.insert(n,s,q,p);     //p-price per item
                    cout << endl<< "Product ID "<<n<<" added to the cart" << endl;
                }
                else if (u == 2)
                {
                    int n;
                    cout << "\nEnter the product ID to be removed: ";
                    cin >> n;
                    c.remove(n);
                }
                else if (u == 3)
                {
                    cout << "\nYour cart is:" << endl;
                    c.display();
                }
                else if (u == 4)
                {
                    
                }
                else if (u == 5)
                {
                    break;
                }
                else
                {
                    cout << "\nEnter a valid option" << endl;
                }
            }
        }
        else if (q == 3)
        {
            exit(0);
        }
        else
        {
            cout << "\nEnter a valid option" << endl;
        }
    }
    return 0;
}
