#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct CurrentOrder                           // Defining a struct called CurrentOrder (with struct name beginning with an uppercase letter
{
    string item;                              // Structure member type string
    int quantity;                             // Structure member type int
    double cost;                              // Structure member type double

    CurrentOrder()
    {
        int quantity = NULL;
        double cost = NULL;
    }
};

/*struct UserInfo
{
    string name;
    string payment;
};*/

/*struct Order
{
    string userName;
    string paymentType;
    vector<Items> orderedItems;
};*/

                                          
//void comboMenu();                                // Function prototypes
//void orderMenu();
void secondMenu();

void displayMenu(CurrentOrder& order);          // & is used to pass by reference                
void saveOrder(CurrentOrder order);
void displayOrder(CurrentOrder order);
void displayTotal(double total, int count);
void processOrder();
void printHeading();

vector<double> itemPrices = {8.00, 6.50, 5.00, 6.00, 3.00, 4.00};        // Vector to store the item prices

int main()
{
    processOrder();

    return 0;
}

void displayMenu(CurrentOrder& order)
{
    int choice;

    printHeading();                                               // Calls the printHeading() function to display application's heading

    cout << "Food Menu" << endl;
    cout << "*********\n" << endl;

    cout << "Item:\t\t\tCost:\n" << endl;                         // Displays the menu options with prices
    cout << "[1] Sandwich\t\t$" << itemPrices[0] << endl;
    cout << "[2] Hot Dog\t\t$" << itemPrices[1] << endl;
    cout << "[3] Chips\t\t$" << itemPrices[2] << endl;
    cout << "[4] Salad\t\t$" << itemPrices[3] << endl;
    cout << "[5] Water\t\t$" << itemPrices[4] << endl;
    cout << "[6] Fizzy Drink\t\t$" << itemPrices[5] << endl;
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
        order.item = "Sandwich";
        order.cost = itemPrices[0];
        break;

    case 2:
        order.item = "Hot Dog";
        order.cost = itemPrices[1];
        break;

    case 3:
        order.item = "Chips";
        order.cost = itemPrices[2];
        break;

    case 4:
        order.item = "Salad";
        order.cost = itemPrices[3];
        break;

    case 5:
        order.item = "Water";
        order.cost = itemPrices[4];
        break;

    case 6:
        order.item = "Fizzy Drink";
        order.cost = itemPrices[5];
        break;

    case 7:
        // combo function
        break;

    case 8:
        // Return to previous menu, cancel
        break;
    }

    cout << "Please enter quantity: ";
    cin >> order.quantity;

    order.cost *= order.quantity;
}

void saveOrder(CurrentOrder order)
{
    ofstream orderFile;
    orderFile.open("order.txt", ios::out | ios::app);
    orderFile << order.item << " " << order.quantity << " " << fixed << order.cost << endl; 
    orderFile.close();
}

void displayOrder(CurrentOrder order)
{
    cout << endl;
    cout << "Current Order" << endl; 
    cout << "*************\n" << endl; 

    cout << "Item: " << order.item << endl; 
    cout << "Quantity: " << order.quantity << endl;
    cout << "Cost: $" << fixed << setprecision(2) << order.cost << endl;                       // Fixed is used to ensure the format of the decimal point is diplayed correctly 
    cout << endl; 
}

void displayTotal(double total, int count)
{
    cout << endl; 
    cout << "Total cost: $" << fixed << total << endl;
    cout << "Number of orders: " << count << endl;
}

void processOrder()
{
    CurrentOrder order;
    double total = 0;
    int count = 0;
    char repeat;

    do
    {
        displayMenu(order);
        saveOrder(order);
        displayOrder(order);

        total += order.cost;
        count++;

        cout << "Do you want to add another item? (y/n) ";
        cin >> repeat;

    } while (repeat == 'y' || repeat == 'Y');

    displayTotal(total, count);
    secondMenu();
}
/*void comboMenu()
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
}*/

/*void orderMenu()
{
    int choice;

    cout << "How would you like to proceed?\n" << endl;
    cout << "[1] Add to Order" << endl;
    cout << "[2] View Order Total\n" << endl;
    cout << "Please enter your choice: ";
    cin >> choice;

    while (choice > 2 || choice < 1)
    {
        cout << "Please enter a valid choice: ";
        cin >> choice;
    }

    if (choice == 1)
    {
        displayMenu(order);
    }

    else if (choice == 2)
    {
        displayOrder(order);
        displayTotal(total, count);
        secondMenu();
    }
}*/

void secondMenu()
{
    int choice;
    cout << endl;
    cout << "How would you like to proceed?\n" << endl;
    cout << "[1] Continue to Payment" << endl;
    cout << "[2] Cancel Order\n" << endl;
    cout << "Please enter your choice: ";
    cin >> choice;
    cout << endl;

    while (choice > 3 || choice < 1)
    {
        cout << "Please enter a valid choice: ";
        cin >> choice;
    }

    switch (choice)
    {
    case 1:
        // include payment function

    case 2:
        // go to previous menu or exit?
        break;
    }
}


void printHeading()
{
    cout << endl;
    cout << "****************************\n";
    cout << "School Lunch Ordering System\n";
    cout << "****************************\n";
    cout << endl;
}