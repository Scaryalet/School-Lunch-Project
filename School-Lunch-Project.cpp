using namespace std;

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>



int choice;
bool found = false;
// structures here


//Admin Structures
struct LastOrder {
    string paymentMethod;
    vector<string> pastOrders;
};
struct Users {
    string username;
    string password;
    string fname;
    string lastName;
    int roomNum = NULL;
    LastOrder lastOrder;
};




//combo vectors 
vector<double> comboPrices = { 15.00, 13.50, 15.00 };
vector<string> comboNames = { "sandwich Combo", "Hot Dog Combo", "Salad Combo" };

// vectors here



//Admin Vectors
vector <Users> userList;

// admin function prototypes
void adminMainScreen();
void adminReviewOrders();
void adminPullUserInfo();
void adminAddUsers();
void adminEditUsers();
void adminRemoveUsers();
void printHeading();

// signup-login function prototypes
void createAccount();
void successfulLogin();
void login();
void adminLogin();

// Payment function prototypes
void discountSearch();
void displayOrder();
void payment();

//combo function prototype
/*
~~~~~TO BE UNCOMMENTED ONCE TANISHAS CODE HAS BEEN ADDED~~~~~
void comboMenu(CurrentOrder& order)
*/


int main()
{
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

//Defined Functions go here:

//payment functions defined:
void discountSearch()           //Function to search file for vaild discount code
{
    string discount;
    ifstream infile("discountCodes.txt");
    if (infile)
    {
        string line;

        while (getline(infile, line))
        {
            if (line.find(discount) != string::npos)
            {
                found = true;
                // Code to apply discount goes here, Waiting on orderTotal function.
                cout << "A 15% discount has been applied to your order!\n\n";
                break;
            }
        }

        infile.close();
    }

    if (!found)
    {
        cout << "Invalid discount code, Please try again.\n\n";
    }
}


void displayOrder() {           //function to display users current order
    ifstream orderFile("order.txt");
    string line;

    while (getline(orderFile, line)) {
        cout << line << endl;
    }

    orderFile.close();
}

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
        displayOrder();
        cout << "Total cost: \t \t" << "\n\n";//total cost either calculated here or within displayOrder function.

        cout << "[1] Enter discount code \n";
        cout << "[2] Pay with cash \n";
        cout << "[3] Pay with card \n";

        cout << "Please select an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Use discount code YouGetAnA+ for 15% off your order! \n";
            cout << "Please enter your discount code: \n";
            cin >> discount;
            discountSearch();
            break;

        case 2:
            cout << "Please make your payment when collecting your order from the lunchroom\n\n";
            successfulLogin();
            break;

        case 3:
            cout << "please enter your card number: \n";
            cin >> cardNumber;
            cout << "please enter your cvc number: \n";
            cin >> cvc;
            cout << "Your payment has been successful! Please collect your order from the lunchroom at lunch time.\n\n";
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
            //Tanisha's order menu function here
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
            Users user;

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
    string inputUsername;
    string inputPassword;
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
       
        string line;
        Users user;

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
        cout << "Invalid username or password. Please try again.\n";
    }
}

//combo function defined
/*
 
 ~~~~~TO BE UNCOMMENTED ONCE TANISHAS CODE HAS BEEN ADDED~~~~~

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
    cout << "[5] Cancel\n" << endl;

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
        //back to menu
        //menu function here
        break;

    case 5:
        //cancel or exit?
        //where to go from here?

    default:
        cout << "Invalid choice, Please try again.\n";
        break;
    }
}
*/

//Admin functions defined:

void adminPullUserInfo() {
    // when admin logs in

    ifstream users("users.txt");
    ifstream orders("orders.txt");
    string line;
    string fname, lname, username, password;
    int roomNum;

    if (users.is_open()) {


        // pulling user from users.txt
        while (users >> username >> password >> fname >> lname >> roomNum) {
            // storing that user in a struct
            Users user;
            user.username = username;
            user.password = password;
            user.fname = fname;
            user.lastName = lname;
            user.roomNum = roomNum;
            ifstream orders("orders.txt");
            if (orders.is_open()) { // check if open
                // pulling that users last order from orders.txt
                while (getline(orders, line)) { // read line by line
                    if (line == fname) // if fname found
                        while (getline(orders, line)) { // continue to read line by line                      
                            if (line == "cash" || line == "card" || line == "Cash" || line == "Card") { // store payment method for previous order
                                user.lastOrder.paymentMethod = line;
                            }
                            else {
                                user.lastOrder.pastOrders.push_back(line); //push order item to back of pastOrderItems vector
                            }
                            if (line.empty()) { // break out of statement when empty line is found
                                break;
                            }
                        }
                }
                userList.push_back(user); // push user struct to back of userList vector
            }
        }
    }

    users.close();
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
    cout << "[5] Log Out" << endl << endl;

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
        exit;
        // login screen function here/return to main()

    }

}

//Emma needs to add total calculating to this function, currently just prints a set amount.
void adminReviewOrders() {

    system("cls"); //clears screen
    printHeading();//prints main heading

    cout << "Review Orders" << endl;
    cout << "*************" << endl << endl;

    // Prints list of users to allow user to choose from

    for (int i = 0; i < userList.size(); i++) {
        cout << userList[i].fname << " " << userList[i].lastName << ", class " << userList[i].roomNum << endl;
    }
    cout << endl << endl << "Enter 1 to review a users order or 2 to go back to main menu: ";

    string choice;
    cin.ignore(); //used to clear input stream for following getline code.
    getline(cin, choice);

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
                    for (int j = 0; j < userList[i].lastOrder.pastOrders.size(); j++) { // loop through chosen users last order items
                        if (userList[i].lastOrder.pastOrders.size() > 0) { // make sure there are items
                            cout << userList[i].lastOrder.pastOrders[j] << endl; // print order items
                        }
                        else {
                            cout << "no previous order found" << endl;
                        }
                    }
                    cout << "Combo Discount: -$2" << endl; //this needs to be finished once ordering system is complete.
                    cout << "Total: $10" << endl;
                    cout << "Payment Method: " << userList[i].lastOrder.paymentMethod << endl << endl; // print payment method      
                }
            }
        }
        else if (choice == "2") {
            adminMainScreen(); //returns user to main screen.
        }
    }

    if (choice != "1" && choice != "2") { //prevents user from putting in an incorrect value.
        cout << endl << "Please enter an appropriate value" << endl << endl;
    }

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

void adminAddUsers() {
    string temp;
    struct NewUser {
        string username;
        string password;
        string fName;
        string lName;
        string classNum;
    };

    vector <NewUser> usersToApprove;

    ifstream newUserFile("newUsers.txt");
    string u, p, f, l, c;

    system("cls");

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
                file << usersToApprove[i].username << endl << usersToApprove[i].password << endl << usersToApprove[i].fName <<
                    endl << usersToApprove[i].lName << endl << usersToApprove[i].classNum << endl << endl;
            }
            adminMainScreen();
        }
    }
}


void adminEditUsers() {
start: //jumps to here if user wants to edit another user.
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

    ofstream file("users.txt", ios::app);

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
                switch (option1) {
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
            goto start; //returns to start of this function to allow user to re-enter and input.
        }
    }
    // Overwriting the file by saving the vector contents to it.

    if (temp == "1") {
        ofstream file("users.txt", ios::trunc);

        for (int i = 0; i < userList.size(); i++) {
            file << userList[i].username << endl << userList[i].password << endl << userList[i].fname << endl <<
                userList[i].lastName << endl << userList[i].roomNum << endl << endl;

        }
        file.close();

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

        for (int i = 0; i < userList.size(); i++) {

            file << userList[i].username << endl << userList[i].password << endl << userList[i].fname <<
                endl << userList[i].lastName << endl << userList[i].roomNum << endl << endl;


        }
        file.close();
        adminMainScreen();

    }

}

void printHeading() {
    cout << "****************************" << endl;
    cout << "SCHOOL LUNCH ORDERING SYSTEM" << endl;
    cout << "****************************" << endl << endl;
}