#include <iostream>
#include <unordered_map>
using namespace std;
#include "proj.h"

int main()
{
    Store st;
    Cart c;
    st.store_load();
    while (1)
    {
        int choice;
        unordered_map<int,int> quantity;
        cout << "\nEnter the option:" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            string pw;
            cout << "Enter admin password:";
            cin >> pw;
            if (st.check_password(pw) == 1)
            {
                while (1)
                {
                    int ch;
                    cout << "\n1. Add new item" << endl;
                    cout << "2. Delete item" << endl;
                    cout << "3. View Store" << endl;
                    cout << "4. Increase Quantity of an item" << endl;
                    cout << "5. Exit" << endl;
                    cin >> ch;
                    if (ch == 1)
                    {
                        int pid, qty;
                        char s[25]; 
                        float price;
                        cout << "Enter Product ID: ";
                        cin >> pid;
                        cout << "Enter Product Name: ";
                        cin.ignore();
                        cin.getline(s,25,'\n');
                        cout << "Enter Product Cost(per item): ";
                        cin >> price;
                        cout << "Enter Quantity to add in store: ";
                        cin >> qty;
                        st.add_item(pid, s, qty, price);
                    }
                    else if (ch == 2)
                    {
                        int p;
                        cout << "Enter Product ID to delete: ";
                        cin >> p;
                        st.delete_item(p);
                    }
                    else if (ch == 3)
                    {
                        st.display();
                    }
                    else if (ch == 4)
                    {
                        int q, pid;
                        cout << "Enter ProductID to increase quantity: ";
                        cin >> pid;
                        cout << "Enter the increase in quantity: ";
                        cin >> q;
                        st.add_quantity(pid, q);
                    }
                    else if (ch == 5)
                    {
                        break;
                    }
                    else
                    {
                        cout << "\nEnter a valid option:" << endl;
                    }
                }
            }
            else
            {
                cout << "Authentication failed\n";
            }
        }
        else if (choice == 2)
        {
            while (1)
            {
                int u;
                
                cout << "\n1. Add items(search and add)" << endl;
                cout << "2. Delete items" << endl;
                cout << "3. View Cart" << endl;
                cout << "4. Checkout" << endl;
                cout << "5. Cancel Booking" << endl;
                cin >> u;
                if (u == 1)
                {
                    st.display();
                    int n, qt;
                    cout << "\nEnter the product ID: ";
                    cin >> n;
                    cout << "Enter quantity required: ";
                    cin >> qt;
                    string s = st.check_quantity(n, qt);
                    if (s == "" || s == "-1")
                    {
                        cout << "Product not found in store / out of stock\n";
                    }
                    else
                    {
                        float p = st.get_price(n);
                        c.add_item(n, s, qt, p); 
                        quantity.insert(make_pair(n,qt));
                        cout << endl
                            << "Product ID " << n << " added to the cart" << endl;
                        st.remove_quantity(n, qt);
                    }
                }
                else if (u == 2)
                {
                    int n;
                    cout << "\nEnter the product ID to be removed: ";
                    cin >> n;
                    int q = c.get_quantity(n);
                    c.delete_item(n);
                    cout << endl
                         << "Product ID " << n << " deleted from the cart" << endl;
                    st.add_quantity(n, q);
                }
                else if (u == 3)
                {
                    cout << "\nYour cart is:" << endl;
                    c.display_cart();
                }
                else if (u == 4)
                {
                }
                else if (u == 5)
                {
                    // unordered_map<int,int>:: iterator itr;
                    // for (itr = quantity.begin(); itr != quantity.end(); itr++)
                    // {
                    //     st.add_quantity(itr->first, itr->second);
                    //     cout<< itr->first<< itr->second;
                    //    cout<<"hi";
                    // }        
                    for (auto x : quantity)
                        st.add_quantity(x.first, x.second);
                    cout<<"\nBooking cancelled\n";
                    break;
                }
                else
                {
                    cout << "\nEnter a valid option" << endl;
                }
            }
        }
        else if (choice == 3)
        {
            st.store_save();
            exit(0);
        }
        else
        {
            cout << "\nEnter a valid option" << endl;
        }
    }
    return 0;
}
