#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

 
void menu();                                // Function prototypes
void comboMenu();
void orderMenu();
void secondMenu();
void orderTotal();
void sandwich();
void hotDog();
void chips();
void salad();
void water(); 
void fizzyDrink();

struct Items                                 // Declaring a structure called Items, struct names (tag) should begin with an uppercase letter
{
    double sandwich;                         // Structure member type double
    double hotDog;                           // Structure member type double
    double chips;                            // Structure member type double
    double salad;                            // Structure member type double
    double water;                            // Structure member type double
    double fizzyDrink;                       // Structure member type double

    Items()                                  // Structure constructor to initilise members
    {
        sandwich = 8.00;                     // Initilising the structure members
        hotDog = 6.50;
        chips = 5.00;
        salad = 6.00;
        water = 3.00;
        fizzyDrink = 4.00;
    }
};

struct UserInfo
{
    string name;
    string payment;
    vector<Items> cost;
};

struct CurrentOrder
{
    string item;
    int quantity;
    double cost;

    CurrentOrder(int a = 0, double b = 0)
    {
        quantity = a;
        cost = b;
    }
};

/*struct Order
{
    string userName;
    string paymentType;
    vector<Items> orderedItems;
};*/


void menu()
{
    int choice;

    // printHeading()

    cout << "Food Menu" << endl;
    cout << "*********\n" << endl;

    cout << "Item:\t\t\tCost:\n" << endl;
    cout << "[1] Sandwich\t\t$8.00" << endl;
    cout << "[2] Hot Dog\t\t$6.50" << endl;
    cout << "[3] Chips\t\t$5.00" << endl;
    cout << "[4] Salad\t\t$6.00" << endl;
    cout << "[5] Water\t\t$3.00" << endl;
    cout << "[6] Fizzy Drink\t\t$4.00" << endl;  
    cout << "[7] Combo Meal\n" << endl;
    cout << "[8] Cancel\n" << endl;
    cout << "Please choose an option: ";
    cin >> choice;
    cout << endl;

    while (choice > 8 || choice < 1)
    {
        cout << "Please enter a valid choice: " << endl;
        cin >> choice;
    }

    switch (choice)
    {
    case 1:
        sandwich();
        break;

    case 2:
        hotDog();
        break;
    
    case 3: 
        chips();
        break;

    case 4:
        salad();
        break;

    case 5:
        water();
        break;

    case 6:
        fizzyDrink();
        break;

    case 7:
        comboMenu();
        break;

    case 8:
        // Return to previous menu
        break;
    }

}

void comboMenu()
{
    int choice;

    // printHeading()

    cout << "Combo Options" << endl;
    cout << "*************\n" << endl;
    cout << "All combos include chips and a drink of your choice\n" << endl;

    cout << "[1] Sandwich Combo" << endl;
    cout << "[2] Hot Dog Combo" << endl;
    cout << "[3] Salad Combo" << endl;
    cout << "[4] Return to Menu" << endl;
    cout << "[5] Cancel\n" << endl;

    cout << "Please choose an option: ";
    cin >> choice;

    while (choice > 5 || choice < 1)
    {
        cout << "Please enter a valid choice: ";
        cin >> choice;
    }
}

void orderMenu()
{
    int choice;

    cout << "How would you like to proceed?\n" << endl;
    cout << "[1] Add to Order" << endl;
    cout << "[2] View Order Total\n" << endl;
    cout << "Please enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        menu();
    }

    else if (choice == 2)
    {
        orderTotal();
    }

    else
        cout << "Wrong selection, please choose again: ";
}

void secondMenu()
{
    int choice;
    cout << endl;
    cout << "How would you like to proceed?\n" << endl;
    cout << "[1] Continue to Payment" << endl;
    cout << "[2] Add to Order" << endl;
    cout << "[3] Cancel Order\n" << endl;
    cout << "Please enter your choice: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
    case 1:
        // include payment function

    case 2:
        menu();
        break;

    case 3:
        // go to previous menu or exit?
        break;
    }
}

void orderTotal()
{
    string item;
    int quantity;
    double cost, total = 0;
    ifstream order;

    system("cls");
    // printHeading()

    cout << "Order Total" << endl;
    cout << "***********\n" << endl;

    order.open("order.txt", ios::in);                            // Pulling orders from order.txt
    if (order.is_open())
    {
        while (order >> item >> quantity >> cost)
        {
            CurrentOrder newOrder;
            newOrder.item = item;
            newOrder.quantity = quantity;
            newOrder.cost = cost;

            cout << endl;
            cout << "Item: " << newOrder.item << endl;
            cout << "Quantity: " << newOrder.quantity << endl;
            cout << "Cost: " << newOrder.cost << endl;
            cout << endl;

            total += newOrder.cost;

            cout << "Total: " << total;
            cout << endl;
        }   
        
    }

    else
      cout << "Unable to retreive order\n";
      // enter function for main menu or food menu

    order.close();
    secondMenu();
}

void sandwich()
{
    Items a;
    CurrentOrder newOrder;
    ofstream order;

    cout << "How many sandwiches do you want to order?: ";
    cin >> newOrder.quantity;

    order.open("order.txt", ios::out);
    newOrder.item = "Sandwich";
    newOrder.cost = a.sandwich * newOrder.quantity;

    order << newOrder.item << endl;
    order << newOrder.quantity << endl;
    order << newOrder.cost << endl;
    order.close();

    cout << endl;
    cout << "Thank you, you've added " << newOrder.quantity << " sandwich/es to your order\n" << endl;

    orderMenu();
}

void hotDog()
{
    Items a;
    CurrentOrder newOrder;
    ofstream order;

    cout << "How many hot dogs do you want to order?: ";
    cin >> newOrder.quantity;

    order.open("order.txt", ios::out);
    newOrder.item = "Hot Dog";
    newOrder.cost = a.hotDog * newOrder.quantity;

    order << newOrder.item << endl;
    order << newOrder.quantity << endl;
    order << newOrder.cost << endl;
    order.close();

    cout << endl;
    cout << "Thank you, you've added " << newOrder.quantity << " hot dog/s to your order\n" << endl;

    orderMenu();
}

void chips()
{
    Items a;
    CurrentOrder newOrder;
    ofstream order;

    cout << "How many pottles of chips do you want to order?: ";
    cin >> newOrder.quantity;

    order.open("order.txt", ios::out | ios::app);
    newOrder.item = "Chips";
    newOrder.cost = a.chips * newOrder.quantity;

    order << newOrder.item << endl;
    order << newOrder.quantity << endl;
    order << newOrder.cost << endl;
    order.close();

    cout << endl;
    cout << "Thank you, you've added " << newOrder.quantity << " pottles of chips to your order\n" << endl;

    orderMenu();
}
void salad()
{
    Items a;
    CurrentOrder newOrder;
    ofstream order;

    cout << "How many salads do you want to order?: ";
    cin >> newOrder.quantity;

    order.open("order.txt", ios::out | ios::app);
    newOrder.item = "Salad";
    newOrder.cost = a.salad * newOrder.quantity;

    order << newOrder.item << endl;
    order << newOrder.quantity << endl;
    order << newOrder.cost << endl;
    order.close();

    cout << endl;
    cout << "Thank you, you've added " << newOrder.quantity << " salad/s to your order\n" << endl;

    orderMenu();
}

void water()
{
    Items a;
    CurrentOrder newOrder;
    ofstream order;

    cout << "How many hot dogs do you want to order?: ";
    cin >> newOrder.quantity;

    order.open("order.txt", ios::out | ios::app);
    newOrder.item = "Water";
    newOrder.cost = a.water * newOrder.quantity;

    order << newOrder.item << endl;
    order << newOrder.quantity << endl;
    order << newOrder.cost << endl;
    order.close();

    cout << endl;
    cout << "Thank you, you've added " << newOrder.quantity << " water/s to your order\n" << endl;

    orderMenu();
}

void fizzyDrink()
{
    Items a;
    CurrentOrder newOrder;
    ofstream order;

    cout << "How many fizzy drinks do you want to order?: ";
    cin >> newOrder.quantity;

    order.open("order.txt", ios::out | ios::app);
    newOrder.item = "Fizzy Drink";
    newOrder.cost = a.fizzyDrink * newOrder.quantity;

    order << newOrder.item << endl;
    order << newOrder.quantity << endl;
    order << newOrder.cost << endl;
    order.close();

    cout << endl;
    cout << "Thank you, you've added " << newOrder.quantity << " fizzy drink/s to your order\n" << endl;

    orderMenu();
}


int main()
{ 
    menu();
    
    return 0;
}
