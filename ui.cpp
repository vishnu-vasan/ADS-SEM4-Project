#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include "proj.h"
using namespace std;

void clrscr()
{
    cout << "\033[2J\033[1;1H";
}

void getch()
{
    cin.ignore();
    getchar();
}

void admin_ui(Store &st)
{
    bool exit = false;
    int choice;
    int pid, qty;
    char s[25];
    float price;
    do
    {
        clrscr();
        cout << setw(35) << "Store Management\n";
        cout << setw(35) << "----- ----------\n\n";
        cout << "Admin Menu\n";
        cout << "1. Add new item\n"
             << "2. Delete item\n"
             << "3. View Store\n"
             << "4. Increase Quantity of an item \n"
             << "5. Exit\n"
             << "Enter Choice: ";
        cin >> choice;
        cout << "\n";
        switch (choice)
        {
        case 1:
            cout << "Enter Product ID: ";
            cin >> pid;
            cout << "Enter Product Name: ";
            cin.ignore();
            cin.getline(s, 25, '\n');
            cout << "Enter Product Cost(per item): ";
            cin >> price;
            cout << "Enter Quantity to add in store: ";
            cin >> qty;
            st.add_item(pid, s, qty, price);
            break;
        case 2:
            cout << "Enter Product ID to delete: ";
            cin >> pid;
            st.delete_item(pid);
            break;
        case 3:
            st.display();
            cout << "\nPress any key to continue\n";
            getch();
            break;
        case 4:
            cout << "Enter ProductID to increase quantity: ";
            cin >> pid;
            cout << "Enter the increase in quantity: ";
            cin >> qty;
            st.add_quantity(pid, qty);
            ;
            break;
        case 5:
            exit = true;
            break;
        default:
            cout << "Error: Invalid choice!\n";
        }
    } while (!exit);
}

void cart_ui(Store &st, Cart &c)
{
    int choice;
    bool exit = false;
    bool checkout = false;
    unordered_map<int, int> quantity;
    string s;
    int n, qt;
    do
    {
        clrscr();
        cout << setw(35) << "Store Management\n";
        cout << setw(35) << "----- ----------\n\n";
        cout << "Customer Menu\n";
        cout << "1. Add items(search and add)\n"
             << "2. Delete items\n"
             << "3. View Cart\n"
             << "4. Clear Cart\n"
             << "5. Checkout\n"
             << "6. Exit\n"
             << "Enter Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            st.display();
            cout << "\nEnter the product ID: ";
            cin >> n;
            cout << "Enter quantity required: ";
            cin >> qt;
            s = st.check_quantity(n, qt);
            cout << s;
            if (s == "" || s == "-1")
            {
                cout << "Product not found in store / out of stock\n";
                cout << "Press any key to continue\n";
                getch();
            }
            else
            {
                float p = st.get_price(n);
                c.add_item(n, s, qt, p);
                quantity.insert(make_pair(n, qt));
                cout << endl
                     << "Product ID " << n << " added to the cart" << endl;
                st.remove_quantity(n, qt);
            }
            break;
        case 2:
            cout << "\nEnter the product ID to be removed: ";
            cin >> n;
            qt = c.get_quantity(n);
            c.delete_item(n);
            cout << endl
                 << "Product ID " << n << " deleted from the cart" << endl;
            st.add_quantity(n, qt);
            break;
        case 3:
            cout << "\nYour cart is:" << endl;
            c.display_cart();
            cout << "\nPress any key to continue";
            getch();
            break;
        case 4:
            for (auto x : quantity)
            {
                st.add_quantity(x.first, x.second);
                c.delete_item(x.first);
            }
            cout << "\nCart cleared\n";
            break;
        case 5:
            c.display_cart();
            cout << "Confirm order:\n1. Yes\n2. No\n: ";
            cin >> n;
            switch (n)
            {
            case 1:
                c.generate_bill();
                for (auto x : quantity)
                {
                    c.delete_item(x.first);
                }
                cout << "Order Confirmed\nPress any key to go back to main menu\n";
                // getch();
                getchar();
                exit = true;
                checkout = true;
                ;
                break;
            case 2:;
                break;
            default:
                cout << "Error: Invalid choice!\n";
                cout << "Press any key to continue\n";
                getch();
            }
            break;
        case 6:
            if (!checkout)
            {
                cout << "Confirm order:\n1. Yes\n2. No\n: ";
                cin >> n;
                switch (n)
                {
                case 1:
                    c.generate_bill();
                    cout << "Order Confirmed\nPress any key to go back to main menu\n";
                    getchar();
                    checkout = true;
                    break;
                case 2:
                    cout << "\nBooking cancelled\n";
                    break;
                default:
                    cout << "Error: Invalid choice!\n";
                    cout << "Press any key to continue\n";
                    getch();
                }
            }
            exit = true;
            break;
        default:
            cout << "Error: Invalid choice!\n";
            cout << "Press any key to continue\n";
            getch();
        }
    } while (!exit);
}

void main_ui()
{
    Store st;
    Cart c;
    cout << setprecision(2) << fixed;
    st.store_load();
    bool exit = false;
    int choice;
    string pw;
    do
    {
        clrscr();
        string pw;
        cout << setw(35) << "Store Management\n";
        cout << setw(35) << "----- ----------\n\n";
        cout << "Menu\n";
        cout << "1. Admin Login\n"
             << "2. User Login\n"
             << "3. Exit\n"
             << "Enter Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nEnter admin password:";
            cin >> pw;
            if (st.check_password(pw) == 1)
                admin_ui(st);
            else
            {
                cout << "\nError: Authentication failed\nPress any key to continue";
                getch();
            }
            break;
        case 2:
            cart_ui(st, c);
            break;
        case 3:
            exit = true;
            break;
        default:
            cout << "Error: Invalid choice!\nPress any key to continue";
            getch();
        }
    } while (!exit);
    clrscr();
    st.store_save();
}
