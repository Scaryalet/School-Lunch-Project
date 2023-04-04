#include <iostream>                               // Libraries to be used
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;                               // Using the standard namespace

struct CurrentOrder                                // Defining a struct called CurrentOrder (with struct name beginning with an uppercase letter)
{
    string item;                                   // Structure member type string
    int quantity;                                  // Structure member type int
    double cost;                                   // Structure member type double

    CurrentOrder(int a = 0 , double b = 0.00)      // Initialising quantity and cost members with default constructor 
    {
        quantity = a;
        cost = b;
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
};*/

void printHeading();                                                     // Function prototypes
void displayMenu(CurrentOrder& order);                                   // '&' is used to pass by reference. Changes made to 'order' within the 'displayMenu' function will affect the CurrentOrder struct            
void saveOrder(CurrentOrder& order, vector<CurrentOrder>& orders);         
void displayOrder(CurrentOrder& order);
void orderSummary(vector<CurrentOrder>& orders);
void displayTotal(double total);
void processOrder();
void secondMenu();

vector<double> itemPrices = { 8.00, 6.50, 5.00, 6.00, 3.00, 4.00 };                                      // Vector to store the item prices
vector<string> itemNames = { "Sandwich", "Hot Dog", "Chips", "Salad", "Water", "Fizzy Drink" };          // Vector to store item names

int main()                                        // The main() function is specified before the other declared functions
{
    processOrder();                               // Calls the processOrder() function

    return 0;
}

void printHeading()                               // The printHeading() function displays a custom heading when it is called in the program
{
    cout << endl;
    cout << "****************************\n";
    cout << "School Lunch Ordering System\n";
    cout << "****************************\n";
    cout << endl;
}

void displayMenu(CurrentOrder& order)                           // The displayMenu() function displays the menu options and prices by calling their respective vectors 
{ 
    int choice;                                                 // Declaring the variable 'choice' to store the user's input
    
    printHeading();                                             // Calls the printHeading() function to display the 'school lunch ordering' heading
     
    cout << "Food Menu" << endl;                                // Food menu heading
    cout << "*********\n" << endl;

    cout << "Item:\t\t\tCost:\n" << endl;                       // Displays the menu options with prices
    for (int i = 0; i < itemNames.size(); i++)                  // For loop to iterate through the itemNames vector (and itemPrices)
    {
        cout << "[" << i + 1 << "] " << itemNames[i] << "\t\t$" << setfill('0') << fixed << setprecision(2) << itemPrices[i] << endl;   // [" << i + 1 << "] displays a number next to each menu item. itemNames[i] retrieves the menu item at index i. fixed and setprecision(2) ensure that the price is displayed with the correct decimal placement i.e 0.00. itemPrices[i] retrieves the price of the menu item
    }
    
    cout << "[7] Combo Meal\n" << endl;                         // Displays the combo meal option 
    cout << "[8] Cancel\n" << endl;                             // Displays the cancel option
    cout << "Please choose an option: ";
    cin >> choice;                                              // Get user input and stores it in the variable 'choice'
    cout << endl;

    while (choice > 8 || choice < 1)                            // Check if the user's choice is within range. If user selects a number above 8 and below 1, the following will be displayed
    {
        cout << "Please enter a valid choice: " << endl;        // Will display text to the user
        cin >> choice;
    }

    switch (choice)                                             // Switch statement to perform cases dependent on the user's input
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

    if (choice >= 1 && choice <= 6)
    {
        cout << "Please enter quantity: ";
        cin >> order.quantity;
        order.cost *= order.quantity;
    } 
}

void saveOrder(CurrentOrder& order, vector<CurrentOrder>& orders)
{
    orders.push_back(order);                                                                  // Adds the new order to the vector
    ofstream orderFile;
    orderFile.open("order.txt", ios::out | ios::app);
    orderFile << order.item << " " << order.quantity << " " << fixed << setprecision(2) << order.cost << endl; 
    orderFile.close();
}

void displayOrder(CurrentOrder& order)
{
    cout << endl;
    cout << "Item: " << order.item << endl; 
    cout << "Quantity: " << order.quantity << endl;
    cout << "Cost: $" << fixed << setprecision(2) << order.cost << endl;                       // Fixed + setprecision is used to ensure the format of the decimal point is diplayed correctly   
}

void displayTotal(double total)
{ 
    cout << endl;
    cout << "******************" << endl; 
    cout << "Total cost: $" << fixed << setprecision(2) << total << endl;
    cout << "******************" << endl;
}

void orderSummary(vector<CurrentOrder>& orders)
{
    cout << endl;
    cout << "*************\n";
    cout << "Order Summary" << endl;
    cout << "*************\n";

    for (int i = 0; i < orders.size(); i++) 
    {
        displayOrder(orders[i]);
    }
}

void processOrder()
{
    vector<CurrentOrder> orders;
    double total = 0;
    int count = 0;
    char repeat;

    do
    {
        CurrentOrder order;
        displayMenu(order);
        saveOrder(order, orders);
        displayOrder(order);

        total += order.cost;
        count++;

        cout << endl;
        cout << "Do you want to add another item? (y/n) ";
        cin >> repeat;

    } while (repeat == 'y' || repeat == 'Y');

    orderSummary(orders);
    displayTotal(total);
    secondMenu();
}

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
        break;

    case 2:
        // go to user menu or exit?
        cout << "Goodbye....";
        cout << endl;
        break;
    }
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
