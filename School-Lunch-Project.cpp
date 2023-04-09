#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;


int choice;
bool found = false;
double total = 0;  // declared globally so that all functions have access to it (payment function, process oder, display total)


struct CurrentOrder                                // Defining a struct called CurrentOrder (with struct name beginning with an uppercase letter)
{
    string item;                                   // Structure member type string
    int quantity;                                  // Structure member type int
    double cost;                                   // Structure member type double

    CurrentOrder(int a = 0, double b = 0.00)      // Initialising quantity and cost members with default constructor 
    {
        quantity = a;
        cost = b;
    }
};
//Admin Structures
struct LastOrder {
    string paymentMethod;
    string cost;
    vector<string> pastOrderItems;
};
struct Users {
    string username;
    string password;
    string fname;
    string lastName;
    int roomNum = NULL;
    LastOrder lastOrder;
};
Users user;


vector<double> comboPrices = { 15.00, 13.50, 15.00 };
vector<string> comboNames = { "sandwich Combo", "Hot Dog Combo", "Salad Combo" };
vector<CurrentOrder> orders;
vector<double> itemPrices = { 8.00, 6.50, 5.00, 6.00, 3.00, 4.00 };                                      // Vector to store the item prices
vector<string> itemNames = { "Sandwich", "Hot Dog", "Chips", "Salad", "Water", "Fizzy Drink" };          // Vector to store item names
vector <Users> userList;


// admin function prototypes
void adminMainScreen();
void adminReviewOrders();
void adminPullUserInfo();
void adminAddUsers();
void adminEditUsers();
void adminRemoveUsers();
void printHeading();
void adminSaveUsersToFile();
// order menu functions
void displayMenu(CurrentOrder& order);                                   // '&' is used to pass by reference. Changes made to 'order' within the 'displayMenu' function will affect the CurrentOrder struct            
void saveOrder();
void displayOrder(CurrentOrder& order);
void orderSummary(vector<CurrentOrder>& orders);
void displayTotal(double total);
void processOrder();
void comboMenu(CurrentOrder& order);
void secondMenu();
// signup-login function prototypes
void createAccount();
void successfulLogin();
void login();
void adminLogin();
// Payment function prototypes
void discountSearch(double& total);
void payment();


int main()
{
   
    system("cls");
    cout << "*********************************************\n";
    cout << "WELCOME TO THE SCHOOLS LUNCH ORDERING SYSTEM!\n";
    cout << "*********************************************\n\n";

    do {
        cout << "Please choose an option: \n";
        cout << "1. Create an account \n";
        cout << "2. Parent/Student Login \n";
        cout << "3. Admin login \n";
        cout << "4. Exit \n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            login();
            break;

        case 3:
            adminLogin();
            break;

        case 4:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}



void discountSearch(double& total)           //Function to search file for valid discount code
{

    string discount;
    ifstream infile("discountCodes.txt");
    bool found = false; // variable to check if valid code is found
    static bool discountApplied = false; // Variable to track if code already applied

    if (infile) {
        string line;
        cin >> discount;

        while (getline(infile, line)) {
            if (line.find(discount) != string::npos) {
                if (!discountApplied) { // check if a discount has already been applied
                    double discountAmount = total * 0.05;
                    total -= discountAmount;
                    cout << "A 5% discount has been applied to your order!\n\n";
                    discountApplied = true;
                }
                else {
                    cout << "Discount code already applied to this order!\n\n";
                }
                found = true;
                break;
            }
        }

        infile.close();
    }

    if (!found) {
        cout << "Invalid discount code, Please try again.\n\n";
    }

    orders.push_back(total);
}

void payment() {            //function for payment section
    string discount;
    string cardNumber;
    int cvc;

    do {
        cout << "****************************\n";
        cout << "SCHOOL LUNCH ORDERING SYSTEM\n";
        cout << "****************************\n\n";

        cout << "Payment options \n";
        cout << "*************** \n\n";

        cout << "Your order: \n";
        for (int i = 0; i < orders.size(); i++) {           //displays the users order
            cout << orders[i].quantity << "X " << orders[i].item << endl;
        }
        cout << "Total cost: \t \t" << total << endl;           // total displays the total cost of the order

        cout << "[1] Enter discount code \n";
        cout << "[2] Pay with cash \n";
        cout << "[3] Pay with card \n";

        cout << "Please select an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Use discount code YouGetAnA+ for 5% off your order! \n";
            cout << "Please enter your discount code: \n";
            discountSearch(total);
            break;

        case 2:
            cout << "Please make your payment when collecting your order from the lunchroom\n\n";
            user.lastOrder.paymentMethod = "cash";
            saveOrder();
            successfulLogin();
            break;

        case 3:
            cout << "please enter your card number: \n";
            cin >> cardNumber;
            cout << "please enter your cvc number: \n";
            cin >> cvc;
            cout << "Your payment has been successful! Please collect your order from the lunchroom at lunch time.\n\n";
            user.lastOrder.paymentMethod = "card";
            saveOrder();
            successfulLogin();
            break;

        default:
            cout << "Invalid choice, Please try again.\n";
            break;

        }
    } while (choice != 3);
}
//signup-login functions defined:
void createAccount()            //function to create a new account
{
    Users user;

    //User details
    cout << "\n\n";
    cout << "CREATE A NEW ACCOUNT \n";
    cout << "Please enter your first name: ";
    cin >> user.fname;
    cout << "Please enter your last name: ";
    cin >> user.lastName;
    cout << "Please enter the students classroom number: ";
    cin >> user.roomNum;
    cout << "Please enter a username: ";
    cin >> user.username;
    cout << "Please enter a password: ";
    cin >> user.password;

    //Open file and append user details
    ofstream outfile("newUsers.txt", ios::app);
    outfile << user.username << "\n" << user.password << "\n" << user.fname << "\n" << user.lastName << "\n" << user.roomNum << endl;
    outfile.close();

    cout << "Account created successfully. Please wait for admin approval.\n";
}
void successfulLogin()          //function for a successful login
{
    do {
        cout << "****************************\n";
        cout << "SCHOOL LUNCH ORDERING SYSTEM\n";
        cout << "****************************\n\n";

        cout << "Welcome \n\n";

        cout << "[1] Create new order \n";
        cout << "[2] Exit \n\n";

        cout << "Please select an option: \n";
        cin >> choice;


        switch (choice)
        {
        case 1:
            processOrder();
            break;

        case 2:
            exit(0);            //exit(0) ends program
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 2);
}
void login()            // Function to log in to an existing account
{
    string inputUsername;
    string inputPassword;
    bool found = false;
    int attempts = 0; 

    while (!found && attempts < 3) {
        // Get user details for login
        cout << "\n\n";
        cout << "LOG IN TO AN EXISTING ACCOUNT\n";
        cout << "Please enter your username: ";
        cin >> inputUsername;
        cout << "Please enter your password: ";
        cin >> inputPassword;

        // Open file to find login
        ifstream infile("users.txt");
        if (infile)
        {
            string line;
            

            while (infile >> user.username >> user.password >> user.fname >> user.lastName >> user.roomNum) {                            
            
                if (user.username == inputUsername && user.password == inputPassword)           //compares content of file with user input if match is found successful login
                {
                    found = true;
                    cout << "Login successful.\n";
                    successfulLogin();
                    break;
                }
                
            }

            infile.close();
        }

        if (!found)
        {
            attempts++;
            if (attempts < 3) {         //statement to limit users to 3 attempts 
                cout << "Invalid username or password. Please try again.\n";
            } else {
                cout << "Too many failed login attempts. Exiting program.\n";
                exit(0);
            }
        }
    }
}
// Function for admin login
void adminLogin()
{
    system("cls");
    string inputUsername, inputPassword, uName, password;
    bool found = false;

    // Get user details for login
    cout << "LOG IN TO AN EXISTING ACCOUNT \n";
    cout << "Please enter your username: ";
    cin >> inputUsername;
    cout << "Please enter your password: ";
    cin >> inputPassword;

    // Open file to find login
    ifstream infile("admin.txt");
    if (infile)
    {
        while (infile >> uName >> password ) {           

            if (uName == inputUsername && password == inputPassword) //compares content of file with user input if match is found successful login
            {
                found = true;
                cout << "Login successful.\n";
                adminPullUserInfo();
                adminMainScreen();
                break;
            }

        }

            infile.close();
    }

    if (!found)
    {
        cout << "Invalid username or password. Please try again.\n";
    }
}
//combo function defined
void comboMenu(CurrentOrder& order)
{
    int choice;

    // printHeading()

    cout << "Combo Options" << endl;
    cout << "*************\n" << endl;
    cout << "All combos include chips and a drink of your choice, drinks can be selected upon pickup\n" << endl;

    cout << "Item:\t\t\tCost:\n" << endl;                         // Displays the menu options with prices
    for (int i = 0; i < comboNames.size(); i++)
    {
        cout << "[" << i + 1 << "] " << comboNames[i] << "\t\t$" << setfill('0') << fixed << setprecision(2) << comboPrices[i] << endl;
    }
    cout << "[4] Return to Menu" << endl;
    cout << "[5] Exit\n" << endl;

    cout << "Please choose an option: ";
    cin >> choice;

    while (choice > 5 || choice < 1)
    {
        cout << "Please enter a valid choice: ";
        cin >> choice;
    }

    switch (choice)
    {
    case 1:
        order.item = "Sandwich Combo";
        order.cost = comboPrices[0];
        break;

    case 2:
        order.item = "Hot Dog Combo";
        order.cost = comboPrices[1];
        break;

    case 3:
        order.item = "Salad Combo";
        order.cost = comboPrices[2];
        break;

    case 4:
        displayMenu(order);
        break;

    case 5:
        exit(0);
        break;

    default:
        cout << "Invalid choice, Please try again.\n";
        break;
    }

    if (choice >= 1 && choice <= 6)                                                    
    {
        cout << "Please enter quantity: ";
        cin >> order.quantity;                                                         
        order.cost *= order.quantity;                                                 
    }
}




//Admin functions defined:
void adminPullUserInfo() {
    // when admin logs in
    ifstream orders("order.txt"); //opens the order.txt file to read from
    ifstream users("users.txt"); //opens the users.txt file to read from.
    string line;
    string fname, lname, username, password;
    int roomNum;

    if (users.is_open()) {
        // pulling user from users.txt
        while (users >> username >> password >> fname >> lname >> roomNum) {
            // storing that user in a struct
            user.username = username;
            user.password = password;
            user.fname = fname;
            user.lastName = lname;
            user.roomNum = roomNum;
            if (orders.is_open()) { // check if open
                // pulling that users last order from orders.txt
                while (getline(orders, line)) { // read line by line
                    if (line == username) {// if fname found
                        while (getline(orders, line)) { // continue to read line by line  
                            user.lastOrder.cost = line;
                            while (getline(orders, line)) {
                                if (line == "cash" || line == "card" || line == "Cash" || line == "Card") { // store payment method for previous order
                                    user.lastOrder.paymentMethod = line;
                                }
                                else {
                                    user.lastOrder.pastOrderItems.push_back(line); //push order item to back of pastOrderItems vector
                                }
                                if (line.empty()) { // break out of statement when empty line is found
                                    break;
                                }
                            }
                        }
                    }
                }
                userList.push_back(user); // push user struct to back of userList vector
            }
        }
    }
    users.close();
    orders.close();
}
void adminMainScreen() {


    // main menu
    system("cls");
    printHeading(); //calls function to print main heading

    cout << "Admin options" << endl;
    cout << "*************" << endl << endl;
    cout << "[1] Review Orders" << endl;
    cout << "[2] Add Users" << endl;
    cout << "[3] Edit User Details" << endl;
    cout << "[4] Remove Users" << endl;
    cout << "[5] Log Out and Exit" << endl << endl;

    int choice;
    // user input
    cout << "Choose an option: ";
    cin >> choice;
    // switch/case for user input(main menu)
    switch (choice) {
    case 1:
        adminReviewOrders();
        break;
    case 2:
        adminAddUsers();
        break;
    case 3:
        adminEditUsers();
        break;
    case 4:
        adminRemoveUsers();
        break;
    case 5:
        exit(0);
        

    }

}
void adminReviewOrders() {
    cin.ignore(); //used to clear input stream for following getline code.
    
    system("cls"); //clears screen to make the console easier to read
    printHeading();//prints main heading

    cout << "Review Orders" << endl;
    cout << "*************" << endl << endl;

    // Prints list of users to allow user to choose from
    int count = 0;
    for (int i = 0; i < userList.size(); i++) {
        
        if (userList[i].lastOrder.pastOrderItems.size() > 0) { //if users are found with a past order, then they are printed.
            cout << userList[i].fname << " " << userList[i].lastName << ", class " << userList[i].roomNum << endl;
            count++;
        }
    }
    if (count == 0) { //if no users are found with a past order, than app tells admin, then returns to main menu.
        cout << "No users with orders found, returning you to the main menu" << endl << endl;
        system("pause");
        adminMainScreen();
    }
    cout << endl << endl << "Enter 1 to review a users order or 2 to go back to main menu: ";

    string choice; //choice is set to a string due to bug found when using an int variable. The app would go in an infinite loop if a name was accidently
                   // put in this input.
    getline(cin, choice); //getline is used as well to fix the bug mentioned above.

    while (choice == "1" || choice == "2") {
        if (choice == "1") {

            string tempFName, tempLName;
            cout << endl << endl << "Enter First and Last Names: ";
            cin >> tempFName >> tempLName;


            // display last order of chosen user

            for (int i = 0; i < userList.size(); i++) { // loop through user list
                if (tempFName == userList[i].fname && tempLName == userList[i].lastName) {  // if chosen user is found
                    system("cls");
                    cout << "School Lunch Ordering System" << endl << endl;
                    cout << "Order for " << userList[i].fname << " " << userList[i].lastName << endl;
                    cout << "Class: " << userList[i].roomNum << endl << endl;
                    for (int j = 0; j < userList[i].lastOrder.pastOrderItems.size(); j++) { // loop through chosen users last order items
                        cout << userList[i].lastOrder.pastOrderItems[j] << endl; // prints order items
                    }
                    cout << "Total: $" << userList[i].lastOrder.cost << endl; //prints total.
                    cout << "Payment Method: " << userList[i].lastOrder.paymentMethod << endl << endl; // prints payment method

                    // review another order or go back to main menu
                    int option = NULL;
                    while (option != 1 && option != 2) {
                        cout << "[1] Review another order" << endl << "[2] Back to Admin Menu" << endl << endl;
                        cout << "Choose an option: ";

                        cin >> option;
                        switch (option) {
                        case 1:
                            adminReviewOrders();
                        case 2:
                            adminMainScreen();
                        default:
                            cout << endl << "Enter an appropriate value" << endl << endl;
                            

                        }
                    }
                }
            }
        }
        else if (choice == "2") {
            adminMainScreen(); //returns user to main screen.
        }
    }

    if (choice != "1" && choice != "2") { //prevents user from putting in an incorrect value.
        cout << endl << "Please enter an appropriate value" << endl << endl;
        adminReviewOrders();
    }

    
    
}
void adminAddUsers() {
    string temp;
    struct NewUser { //struct to store new user information.
        string username;
        string password;
        string fName;
        string lName;
        string classNum;
    };

    vector <NewUser> usersToApprove; //vector which uses NewUser struct.

    ifstream newUserFile("newUsers.txt"); //opens newUsers.txt file and reads from it.
    string u, p, f, l, c;

    system("cls"); //clears screen.

    if (newUserFile.is_open()) {

        while (newUserFile >> u >> p >> f >> l >> c) {

            NewUser user;
            user.username = u;
            user.password = p;
            user.fName = f;
            user.lName = l;
            user.classNum = c;
            usersToApprove.push_back(user);
        }

        cin.ignore(); // this is placed outside of the start, as it was only needed once to clear input stream.

    start: //Jumps to here when wanting to approve/remove another user.

        // print headings

        printHeading();
        cout << "Approve or Remove New Users" << endl;
        cout << "***************************" << endl << endl;


        // Prints user list to console from vector.
        for (int i = 0; i < usersToApprove.size(); i++) {
            cout << usersToApprove[i].fName << " " << usersToApprove[i].lName << " Class Number: " << usersToApprove[i].classNum << endl;
        }

        cout << endl << endl << "Enter First and Last names or enter 1 to return to main menu: ";


        getline(cin, temp); //getline used instead of cin because cin will only read the first word, not the whole line.


        ofstream file("users.txt", ios::app); //opens user.txt file to write new user to file.

        while (temp != "1") {
            string first, last;
            // split user input into two strings

            size_t pos = temp.find(' '); //this finds the space

            if (pos != string::npos) {
                first = temp.substr(0, pos); //sets first string to the word before the space
                last = temp.substr(pos + 1); //sets last string to word that is after the space
            }

            // APPROVE USER
            // add user to users.txt

            int found = 0; // 0 if false, 1 if true

            for (int i = 0; i < usersToApprove.size(); i++) {
                if (usersToApprove[i].fName == first && usersToApprove[i].lName == last) {

                    // flag to track if user is found

                    found = 1;

                    // approve user if statement yes or no 

                    cout << "Do you want to approve or remove this user? (approve/remove): ";
                    string approve;
                    cin >> approve;

                    if (approve == "approve") {

                        // append file

                        file << usersToApprove[i].username << endl << usersToApprove[i].password << endl << usersToApprove[i].fName <<
                            endl << usersToApprove[i].lName << endl << usersToApprove[i].classNum << endl << endl;

                        // delete user from usersToApprove vector

                        usersToApprove.erase(usersToApprove.begin() + i);

                        cout << endl << endl << "User Added Succesfully!" << endl << endl;


                    }
                    else if (approve == "remove") {

                        usersToApprove.erase(usersToApprove.begin() + i);

                        cout << endl << endl << "User Removed Succesfully!" << endl << endl;

                    }
                }
            }
            if (found != 1) {

                cout << endl << endl << "No user found, please check spelling" << endl << endl;
                system("pause");
                system("cls");
                goto start;

            }
            cout << "Enter 1 to return to main menu or 2 to approve/remove another user: ";
            cin >> temp;

            if (temp == "2") {
                system("cls");
                goto start; // Goes back to start to allow user to add/remove another user.
            }
        }
        file.close(); // close the file
        if (temp == "1") {

            // save vector to newUsers.txt and overwrite (leaving only unaproved users in the file)

            ofstream file("newUsers.txt", ios::trunc);
            for (int i = 0; i < usersToApprove.size(); i++) {
                // only if vector > 0, add
                string uName = usersToApprove[i].username;
                
                file << usersToApprove[i].username << endl << usersToApprove[i].password << endl << usersToApprove[i].fName <<
                    endl << usersToApprove[i].lName << endl << usersToApprove[i].classNum << endl << endl;
            }
            adminMainScreen();
        }
    }
}
void adminEditUsers() {
    system("cls"); //clears screen

    //Prints headings
    printHeading();
    cout << "Edit User Details" << endl;
    cout << "*****************" << endl << endl;

    // print list of users from vector

    for (int i = 0; i < userList.size(); i++) {
        cout << userList[i].fname << " " << userList[i].lastName << ", class " << userList[i].roomNum << endl;
    }

    // Gives User option to enter name or return to menu

    cout << endl << endl << "Enter First and Last names or enter 1 to return to main menu: ";
    string temp;
    int found = 0;

    cin.ignore(); //this is used to clear the input stream before using getline.
    getline(cin, temp);
    string first, last;

    ofstream file("users.txt", ios::app); //opens user.txt file to write to it.

    while (temp != "1") {

        // split user input into two strings

        size_t pos = temp.find(' ');

        if (pos != string::npos) {
            first = temp.substr(0, pos);
            last = temp.substr(pos + 1);
        }

        for (int i = 0; i < userList.size(); i++) {
            if (userList[i].fname == first && userList[i].lastName == last) {
                found = 1;
            startEdit:
                system("cls");
                cout << "Edit details for user: " << userList[i].fname << " " << userList[i].lastName << " (" << userList[i].username << ")" << endl << endl;
                cout << endl << "What user details do you want to edit?" << endl << endl;
                cout << "[1] Username" << endl << "[2] Password" << endl << "[3] Last Name" << endl << "[4] Class Number" << endl << endl
                    << "[5] Back to user list" << endl << "[6] Back to admin menu" << endl << endl;
                cout << "Choose an option: ";
                int option1;
                cin >> option1;
                string tempUserName, tempPassword, tempLName;
                int tempClassNum;
                switch (option1) { //switch case for the different options that admin can choose from.
                case 1:
                    cout << "Enter new username: ";
                    cin >> tempUserName;
                    userList[i].username = tempUserName;
                    cout << endl << "username updated succesfully!" << endl << endl;
                    system("pause");
                    goto startEdit;
                case 2:
                    cout << "Enter new password: ";
                    cin >> tempPassword;
                    userList[i].password = tempPassword;
                    cout << endl << "password updated succesfully!" << endl << endl;
                    system("pause");
                    goto startEdit;
                case 3:
                    cout << "Enter new last name: ";
                    cin >> tempLName;
                    userList[i].lastName = tempLName;
                    cout << endl << "last name updated succesfully!" << endl << endl;
                    system("pause");
                    goto startEdit;
                case 4:
                    cout << "Enter new class number: ";
                    cin >> tempClassNum;
                    userList[i].roomNum = tempClassNum;
                    cout << endl << "class number updated succesfully!" << endl << endl;
                    system("pause");
                    goto startEdit;
                case 5:
                    adminEditUsers();
                case 6:
                    adminSaveUsersToFile();
                    adminMainScreen();

                }
            }
            else {
                found = 0;
            }
        }
        if (found == 0) { //if name doesn't match, then prints no user found.
            cout << "No user found, please check spelling" << endl << endl;
            system("pause");
            adminEditUsers(); //returns to start of this function to allow user to re-enter and input.
        }
    }
    // Overwriting the file by saving the vector contents to it.

    if (temp == "1") {
        adminSaveUsersToFile();

        adminMainScreen();

    }

}
void adminRemoveUsers() {



    ofstream file("users.txt", ios::trunc);
    string temp;
    do {
        system("cls");
        printHeading();

        cout << "Remove User Menu" << endl;
        cout << "****************" << endl << endl;

        // print list of users from vector

        for (int i = 0; i < userList.size(); i++) {
            cout << userList[i].fname << " " << userList[i].lastName << ", class " << userList[i].roomNum << endl;
        }

        cout << endl << "Enter First and Last names or enter 1 to return to main menu: ";

        int found = 0;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, temp); 
        string first, last;

        // split user input into two strings

        size_t pos = temp.find(' '); //finds the space

        if (pos != string::npos) {
            first = temp.substr(0, pos); //sets first string to word before space
            last = temp.substr(pos + 1);//sets last string to word after space
        }
        for (int i = 0; i < userList.size(); i++) {
            if (userList[i].fname == first && userList[i].lastName == last) {//if first and last name match, following code is executed:
                found = 1;
                string choice;
                cout << endl << "You have choosen " << first << " " << last << " are you sure you would you like to remove this user? [y/n]";
                cin >> choice;

                if (choice == "y" || choice == "Y") {
                    cout << endl << "User has been removed!" << endl << endl;

                    //delete from vector
                    userList.erase(userList.begin() + i);


                    cout << "Press 1 return to main menu, press 2 to choose a new user: ";
                    cin >> temp;
                }
                else {
                    cout << endl << "User was not removed!" << endl << endl;
                    cout << "Press 1 return to main menu, press 2 to choose a new user: ";
                    cin >> temp;
                }
            }
        }
    } while (temp != "1");

    if (temp == "1") {

        adminSaveUsersToFile();
        adminMainScreen();

    }

}
void printHeading() {
    cout << "****************************" << endl;
    cout << "SCHOOL LUNCH ORDERING SYSTEM" << endl;
    cout << "****************************" << endl << endl;
}
void adminSaveUsersToFile() {
    ofstream file("users.txt", ios::trunc);
    system("pause");
    for (int i = 0; i < userList.size(); i++) {
        file << userList[i].username << endl << userList[i].password << endl << userList[i].fname << endl <<
            userList[i].lastName << endl << userList[i].roomNum << endl << endl;

    }
    file.close();
}



// order menu functions
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
        comboMenu(order);
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
void saveOrder()                      // The saveOrder function takes two parameters - CurrentOrder with object order, and a vector of CurrentOrder objects called orders. This function writes data from order to a file named 'order.txt'
{
   
    ofstream orderFile;                                                                // Writes to the 'order.txt' file declared as ofstream named orderFile
    orderFile.open("order.txt", ios::out | ios::app);                                  // Opens the 'order.txt' file with output and append
    orderFile << user.username << endl << total << endl << user.lastOrder.paymentMethod << endl;           // Writes to the file from order to orderFile in the order of item, qunatity and cost. Fixed and setprecision(2) is used to ensure the decimal is placed in the correct place
    
    for (int i = 0; i < orders.size(); i++) {
        orderFile << orders[i].quantity << "x " << orders[i].item << endl; 
    }
    orderFile << endl;

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
    
                                                        // Declaring variable total to keep track of total costs - set to 0
    char repeat;                                                         // Declaring variable repeat to take user input
    
    do                                                                   // do-while loop that will continue to run until user selects 'n'
    {
        
        CurrentOrder order;                                                 // CurrentOrder struct called order
        displayMenu(order);                                              // Calls the displayMenu() function. order is passed to the function as a parameter/argument to allow user input to be kept updated
                                             
        displayOrder(order);                                             // Calls the displayOrder() function. Which displays the info of order - displaying the item, quantity and cost of order
        orders.push_back(order);
        total += order.cost;                                             // Used to calculate the total cost of each order. When a new order is entered, the order.cost is added to the total

        cout << endl;
        cout << "Do you want to add another item? (y/n) ";               // Asks the user if they want to add more to their order
        cin >> repeat;                                                   // Stores users choice in the variable 'repeat'

    } while (repeat == 'y' || repeat == 'Y');                            // Runs the do-while loop if the condition 'y' is entered by the user

    orderSummary(orders);                                                // Calls the orderSummary() function to display every order ordered - orders is the argument
    displayTotal(total); 
    // Calls the displayTotal() function to display that calculated cost of the entire order - total is the argument
   
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
        payment();
        break;

    case 2:                                                              // Case 2 will execute if user selects option 2
        // Go to user menu or exit? - if exit, implement below code
        cout << endl;
        cout << "Goodbye, have a great day....";
        cout << endl;
        break;
    }
}
