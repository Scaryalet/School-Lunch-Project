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

int main()                                                      // The main() function is specified before the other declared functions
{
    processOrder();                                             // Calls the processOrder() function

    return 0;
}

void printHeading()                                             // The printHeading() function displays a custom heading when it is called in the program
{
    cout << endl;
    cout << "****************************\n";
    cout << "School Lunch Ordering System\n";
    cout << "****************************\n";
    cout << endl;
}

void displayMenu(CurrentOrder& order)                           // The displayMenu() function displays the menu options and prices by calling their respective vectors and storing user input in the struct CurrentOrder
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
        order.item = itemNames[0];                              // Assigns the user input to item 'sandwich' which is stored in the itemNames vector
        order.cost = itemPrices[0];                             // Assigns the user input to the cost of 'sandwich' which is stored in the itemPrices vector                         
        break;

    case 2:
        order.item = itemNames[1];                              // Assigns the user input to item 'hot dog' which is stored in the itemNames vector
        order.cost = itemPrices[1];                             // Assigns the user input to the cost of 'hot dog' which is stored in the itemPrices vector  
        break;

    case 3:
        order.item = itemNames[2];                              // Assigns the user input to item 'chips' which is stored in the itemNames vector
        order.cost = itemPrices[2];                             // Assigns the user input to the cost of 'chips' which is stored in the itemPrices vector  
        break;

    case 4:
        order.item = itemNames[3];                              // Assigns the user input to item 'salad' which is stored in the itemNames vector
        order.cost = itemPrices[3];                             // Assigns the user input to the cost of 'salad' which is stored in the itemPrices vector  
        break;

    case 5:
        order.item = itemNames[4];                              // Assigns the user input to item 'water' which is stored in the itemNames vector
        order.cost = itemPrices[4];                             // Assigns the user input to the cost of 'water' which is stored in the itemPrices vector  
        break;

    case 6:
        order.item = itemNames[5];                              // Assigns the user input to item 'fizzy drink' which is stored in the itemNames vector
        order.cost = itemPrices[5];                             // Assigns the user input to the cost of 'fizzy drink' which is stored in the itemPrices vector  
        break;

    case 7:                                                                            // If option 7 is selected, it will call the comboMenu() function to display the combo options
        // Call combo function
        break;

    case 8:                                                                            // If option 8 is selected by the user,  it will exit out of the food menu
        // Return to previous menu, or cancel - if cancel, implement below code
        cout << endl;
        cout << "Goodbye, have a great day....";
        cout << endl;
        break;
    }

    if (choice >= 1 && choice <= 6)                                                    // If statement using logical AND operator. To check if user choice is greater or equal to 1 and if choice is less than or equal to 6. If condition is true, the below code will run
    {
        cout << "Please enter quantity: ";
        cin >> order.quantity;                                                         // Stores user input (quantity) in order.quantity
        order.cost *= order.quantity;                                                  // Multiplies order.cost by order.quantity
    } 
}

void saveOrder(CurrentOrder& order, vector<CurrentOrder>& orders)                      // The saveOrder function takes two parameters - CurrentOrder with object order, and a vector of CurrentOrder objects called orders. This function writes data from order to a file named 'order.txt'
{
    orders.push_back(order);                                                           // Adds the order to the orders vector
    ofstream orderFile;                                                                // Writes to the 'order.txt' file declared as ofstream named orderFile
    orderFile.open("order.txt", ios::out | ios::app);                                  // Opens the 'order.txt' file with output and append
    orderFile << order.item << " " << order.quantity << " " << fixed << setprecision(2) << order.cost << endl;           // Writes to the file from order to orderFile in the order of item, qunatity and cost. Fixed and setprecision(2) is used to ensure the decimal is placed in the correct place
    orderFile.close();                                                                 // Closes the file
}

void displayOrder(CurrentOrder& order)                                                 // The displayOrder() function displays the order item, quantity and cost when called. Uses the CurrentOrder struct as a parameter       
{
    cout << endl;
    cout << "Item: " << order.item << endl;                                            // Will display the item ordered
    cout << "Quantity: " << order.quantity << endl;                                    // Will display the quantity chosen
    cout << "Cost: $" << fixed << setprecision(2) << order.cost << endl;               // Will display the cost of item + the quantity ordered. Fixed + setprecision is used to ensure the format of the decimal point is diplayed correctly   
}

void displayTotal(double total)                                                        // The displayTotal() function will display the total cost of each item and quantity ordered. double total as a parameter
{ 
    cout << endl;
    cout << "******************" << endl; 
    cout << "Total cost: $" << fixed << setprecision(2) << total << endl;              // Will display the total cost when called. Fixed and setprecision(2) is used to ensure the decimal is in the correct place
    cout << "******************" << endl;
}

void orderSummary(vector<CurrentOrder>& orders)                                        // The orderSummary will display the entire order. A vector of CurrentOrder orders is included in the parenthesis to hold CurrentOrder objects
{
    cout << endl;
    cout << "*************\n";
    cout << "Order Summary" << endl;                                                   // Heading for order summary
    cout << "*************\n";

    for (int i = 0; i < orders.size(); i++)                                            // For loop iterates through the elements in orders
    {
        displayOrder(orders[i]);                                                       // Calls the displayOrder() function to display each order
    }
}

void processOrder()                                                      // The processOrder() function takes no arguments and calls multiple functions that are defined above to implememt the ordering process
{
    vector<CurrentOrder> orders;
    double total = 0;                                                    // Declaring variable total to keep track of total costs - set to 0
    char repeat;                                                         // Declaring variable repeat to take user input

    do                                                                   // do-while loop that will continue to run until user selects 'n'
    {
        CurrentOrder order;                                              // CurrentOrder struct called order
        displayMenu(order);                                              // Calls the displayMenu() function. order is passed to the function as a parameter/argument to allow user input to be kept updated
        saveOrder(order, orders);                                        // Calls the saveOrder() function. Which saves the order to orders vector and saves input to the 'order.txt' file
        displayOrder(order);                                             // Calls the displayOrder() function. Which displays the info of order - displaying the item, quantity and cost of order

        total += order.cost;                                             // Used to calculate the total cost of each order. When a new order is entered, the order.cost is added to the total

        cout << endl;
        cout << "Do you want to add another item? (y/n) ";               // Asks the user if they want to add more to their order
        cin >> repeat;                                                   // Stores users choice in the variable 'repeat'

    } while (repeat == 'y' || repeat == 'Y');                            // Runs the do-while loop if the condition 'y' is entered by the user

    orderSummary(orders);                                                // Calls the orderSummary() function to display every order ordered - orders is the argument
    displayTotal(total);                                                 // Calls the displayTotal() function to display that calculated cost of the entire order - total is the argument
    secondMenu();                                                        // Calls the secondMenu() function which will display another menu to the user
}

void secondMenu()                                                        // The secondMenu() function displays another menu to the user after they have added all items to their order
{
    int choice;                                                          // Declaring variable choice with type int
    cout << endl;
    cout << "How would you like to proceed?\n" << endl;
    cout << "[1] Continue to Payment" << endl;                           // Choice 1 to continue to payment
    cout << "[2] Cancel Order\n" << endl;                                // Choice 2 to cancel order
    cout << "Please enter your choice: ";
    cin >> choice;                                                       // Stores the user's input in variable 'choice'
    cout << endl;

    while (choice > 2 || choice < 1)                                     // While loop if the user inputs a choice less than one and greater than 2
    {
        cout << "Please enter a valid choice: ";                         // Tells the user to enter a valid choice
        cin >> choice;                                                   // Stores the user's input in variable 'choice'
    } 

    switch (choice)                                                      // Switch statement to execute the user's input choice
    {
    case 1:                                                              // Case 1 will execute if user selects option 1
        // Include payment function processPayment()?
        break;

    case 2:                                                              // Case 2 will execute if user selects option 2
        // Go to user menu or exit? - if exit, implement below code
        cout << endl;
        cout << "Goodbye, have a great day....";
        cout << endl;
        break;
    }
}


/*void comboMenu()            - This is a mock up of comboMenu()
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
