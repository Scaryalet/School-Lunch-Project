using namespace std;

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>



// structures here

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



// vectors here

vector <Users> userList;

// admin function prototypes
void adminMainScreen();
void adminReviewOrders();
void adminPullUserInfo();
void adminAddUsers();
void adminEditUsers();
void adminRemoveUsers();
void printHeading();


// put your prototypes here


int main()
{


   


    






}

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
    printHeading();
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


void adminReviewOrders() {

    system("cls");
    printHeading();

    cout << "Review Orders" << endl;
    cout << "*************" << endl << endl;

    // choose from list of users

    for (int i = 0; i < userList.size(); i++) {
        cout << userList[i].fname << " " << userList[i].lastName << ", class " << userList[i].roomNum << endl;
    }
    cout << endl << endl << "Enter 1 to review a users order or 2 to go back to main menu: ";

    string choice;
    cin.ignore();
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
                    cout << "Combo Discount: -$2" << endl;
                    cout << "Total: $10" << endl;
                    cout << "Payment Method: " << userList[i].lastOrder.paymentMethod << endl << endl; // print payment method      
                }
            }
        }
        else if (choice == "2") {
            adminMainScreen();
        }


    }
    if (choice != "1" && choice != "2") {
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

        cin.ignore();
    start:

        // print headings

        printHeading();
        cout << "Approve or Remove New Users" << endl;
        cout << "***************************" << endl << endl;



        for (int i = 0; i < usersToApprove.size(); i++) {
            cout << usersToApprove[i].fName << " " << usersToApprove[i].lName << " Class Number: " << usersToApprove[i].classNum << endl;
        }

        cout << endl << endl << "Enter First and Last names or enter 1 to return to main menu: ";


        getline(cin, temp); //getline is used because using only cin would read the first word only, not both words.


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
                goto start;
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
start:
    system("cls");
    printHeading();
    cout << "Edit User Details" << endl;
    cout << "*****************" << endl << endl;

    // print list of users from vector

    for (int i = 0; i < userList.size(); i++) {
        cout << userList[i].fname << " " << userList[i].lastName << ", class " << userList[i].roomNum << endl;
    }

    // menu

    cout << endl << endl << "Enter First and Last names or enter 1 to return to main menu: ";
    string temp;
    int found = 0;

    cin.ignore();
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


                    /// SAVE USERLISTS VECTOR TO FILE, OVERWRITE

                }
            }
            else {
                found = 0;
            }
        }
        if (found == 0) {
            cout << "No user found" << endl << endl;
            system("pause");
            goto start;
        }
    }

    if (temp == "1") {
        ofstream file("users.txt", ios::trunc);

        for (int i = 0; i < userList.size(); i++) {
            file << userList[i].username << endl << userList[i].password << endl << userList[i].fname << endl <<
                userList[i].lastName << endl << userList[i].roomNum << endl << endl;



            /// fix saving not working, fix no user found bug

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