//
// Created by Yoel on 1/30/2023.
//

#include "Menu.h"
#include "User.h"
#include "Trip.h"
#include <iostream>
#include <vector>

using namespace std;

Menu::Menu()//Resets any pointers to account that is currently logged in when this menu object is created + enables main menu from start
:currentLoggedInUser(nullptr)
{
}

//Clears any allocated memory within this class' object
Menu::~Menu(){

    delete this->currentLoggedInUser;

    for (int i =0; i < this->userList.size();i++)
    {
        delete (this->userList[i]);
    }
    this->userList.clear();

}

void Menu::start()
{
    //Will continue running in loop unless #5 is selected (return)
    while(true) {
        string selectedInput;
        cout << "--------------------------"
             << endl
             << "YOEL'S TRIP CALCULATOR V1.2"
             << endl
             << "--------------------------"
             << endl
             << endl;
        if(currentLoggedInUser != nullptr){
            cout << "Hello, " << currentLoggedInUser->getName() <<", you're logged in!" << endl;
        } else {
            cout << "Please log in..." << endl;
        }
        cout << endl
             << "Please select the following: " << endl
             << "1 - Create Account" << endl
             << "2 - Login" << endl
             << "3 - Logout" << endl
             << "4 - Enter Trip Calculation" << endl
             << "5 - Exit Program" << endl
             << endl
             << "Please make sure to enter numbers only (1-4)!"
             << endl;
        getline(cin, selectedInput);

        if(Trip::checkInputNumerical(selectedInput)){
            int input = stoi(selectedInput);
            switch (input) {
                case 1://Handle account creation
                    if (this->currentLoggedInUser != nullptr) {
                        cout << "You're already logged in, please log out first to create an account!" << endl;
                    } else {
                        this->userCreation();
                    }
                    break;
                case 2://Handle login
                    if (this->currentLoggedInUser == nullptr){
                        this->handleLogin();
                    } else {
                        cout << "You're already logged in, please log out first to log in different account if you wish." << endl;
                    }
                    break;
                case 3://Handle logout
                    if (this->currentLoggedInUser != nullptr){
                        this->currentLoggedInUser = nullptr;
                        cout << "Okay, you're logged out!" << endl;
                    } else {
                        cout << "You're already logged out!" << endl;
                    }
                    break;
                case 4://Handle trip calculator
                    if (this->currentLoggedInUser != nullptr){
                        this->handleTripCalculator();
                    } else {
                        cout << "You need to log in first to proceed!" << endl;
                    }
                    break;
                case 5://Exits the program
                    return;
                default://Error no matched input
                    cerr << "Error! No matched input, please try again!" << endl;
                    break;
            }
        } else {
            cerr << "Invalid input! Please try again!" << endl;
        }
    }
}

void Menu::userCreation(){

    string nameInput;
    string passwordInput;

    cout << "Alright let's create your account!" << endl
         << "Enter name: " << endl;
    //cin.ignore();
    getline(cin, nameInput);
    cout << "Enter password: " << endl;
    getline(cin, passwordInput);

    if (Menu::checkInput(nameInput, passwordInput)) { //Checks input to validate before proceeding with user creation
        User* newUser = new User(nameInput, passwordInput);//Creates the user object
        this->userList.push_back(newUser); //Adds the new created user object to the list in userList
        this->currentLoggedInUser = newUser; //Logs you in instantly upon creation
        cout << "Successfully created your account, you are now currently logged in!" << endl;
    }

}

void Menu::handleLogin() {

    string nameInput;
    string passwordInput;

    cout << "Please enter your name: " << endl;
    getline(cin, nameInput);
    cout << "Please enter your password: " << endl;
    getline(cin, passwordInput);

    if(!Menu::checkInput(nameInput, passwordInput)){
        cerr << "Invalid input, please try again!" << endl;
        return;
    }

    User* tempFoundUser = this->findUserInList(nameInput, passwordInput); //Calls to find the pointer of the user in the list, if none is found nullptr is returned.
    if (tempFoundUser != nullptr) { //If the pointer is not returned empty (nullptr) then we know the user was found (matched).
        cout << "Hello, " << tempFoundUser->getName() << endl; //Notice of succession
        currentLoggedInUser = tempFoundUser; //Assigns the pointer to current logged-in user.
        return;
    }

    cout << "No matched credentials or no such user exists!" << endl;
}

bool Menu::checkInput(const string& nameInput, const string& passwordInput){
    if(nameInput.contains(" ")){ // Checks if there is spaces in name
        cerr << "You cannot have spaces in your name, please try again!" << endl;
        return false;
    }
    if(nameInput.empty()){ //Checks if name input is not an empty string
        cerr << "Your name cannot be an empty string, please try again!" << endl;
        return false;
    }
    if(passwordInput.contains(" ")){ // Checks if there is space in password
        cerr << "You cannot have spaces in your password, please try again!" << endl;
        return false;
    }
    if(passwordInput.empty()){ // Checks if password input is not an empty string
        cerr << "Your password cannot be an empty string, please try again!" << endl;
        return false;
    }
    return true;
}

User* Menu::findUserInList(const string& nameInput, const string& passwordInput) const {
    if(!this->userList.empty()) {
        for (User* userVar : userList) {
            if (nameInput == userVar->getName() && passwordInput == userVar->getPassword()) {
                return userVar;
            }
        }
    }
    return nullptr;
}

void Menu::handleTripCalculator() {

    while (true) {
        string selectedInput;
        cout << endl
             << "------------------------"
             << endl
             << "Select the following options: " << endl
             << "1 - Create Trip" << endl
             << "2 - Load Trip" << endl
             << "3 - Delete Trip" << endl
             << "4 - Exit/Back" << endl
             << endl
             << "Please make sure to enter numbers only (1-4)!" << endl;
        getline(cin, selectedInput);

        if(Trip::checkInputNumerical(selectedInput)) {
            int input = stoi(selectedInput);
            switch (input) {
                case 1://Handle Trip Creation
                    this->handleTripCreation();
                    break;
                case 2://Handle Trip Loading
                    this->handleLoadTrip();
                    break;
                case 3://Delete a Trip
                    this->handleRemoveTrip();
                    break;
                case 4://Go Back to Main Menu
                    return;
                default:
                    cerr << "Error! No matched input, please try again!" << endl;
                    break;
            }
        } else {
            cerr << "Invalid input! Please try again!" << endl;
        }
    }
}

void Menu::handleTripCreation()
{
    string tripNameInput;
    cout << "Okay! Lets create your trip.." << endl
         << "Enter trip name: " << endl;
    getline(cin, tripNameInput);
    Trip* newTrip = new Trip(tripNameInput);
    currentLoggedInUser->addTrip(newTrip);
    newTrip->start();
}

void Menu::handleLoadTrip() {

    //Exits out if the user's trip list is empty
    if (this->currentLoggedInUser->getTripList().empty()){
        cout << "You do not have any trips associated with " << this->currentLoggedInUser->getName() << "!" << endl;
        return;
    }

    vector<Trip*> userTripList = this->currentLoggedInUser->getTripList();

    cout << userTripList.size() << endl;

    string selectedIndexInput;
    cout << "Please enter the index number you wish to load into from this " << this->currentLoggedInUser->getName()
         << " account: " << endl
         << "# -|- Trip Name -|" << endl;
    for (int i = 0; i < this->currentLoggedInUser->getTripList().size(); i++) {
        cout << "-----------------------------------" << endl << i + 1 << " - "
             << this->currentLoggedInUser->getTripList()[i]->getTripName()
             << endl;
    }
    cout << endl
         << "Enter -1 to Cancel/Go Back" << endl;
    getline(cin, selectedIndexInput);

    //Checks input to be numerical
    if(!Trip::checkInputNumerical(selectedIndexInput)){
        cerr << "Invalid input, please try again!" << endl;
        return;
    }

    //Cancel statement
    if (stoi(selectedIndexInput) == -1) {
        return;
    }

    //Checks if selected number is an existing index number
    if (stoi(selectedIndexInput) > this->currentLoggedInUser->getTripList().size() || stoi(selectedIndexInput) < 0){
        cerr << "Invalid index selection, no such index exists!" << endl;
        return;
    }

    //Converts the selected number to integer, and loads the selected trip menu
    int selectedIndex = (stoi(selectedIndexInput) - 1);
    this->currentLoggedInUser->getTripList()[selectedIndex]->start();//Starts the trip menu

}


void Menu::handleRemoveTrip() {

    //Exits out if the user's trip list is empty
    if (this->currentLoggedInUser->getTripList().empty()){
        cout << "You do not have any trips associated with " << this->currentLoggedInUser->getName() << "!" << endl;
        return;
    }

    string selectedIndexInput;
    cout << "Please enter the index number you wish to delete from this " << this->currentLoggedInUser->getName() << " account: " << endl
         << "# -|- Trip Name -|" << endl;
    for (int i = 0; i < this->currentLoggedInUser->getTripList().size(); i++) {
        cout << "-----------------------------------" << endl << i+1 << " - " << this->currentLoggedInUser->getTripList()[i]->getTripName()
             << endl;
    }
    cout << endl
         << "Enter -1 to Cancel/Go Back" << endl;
    getline(cin, selectedIndexInput);

    //Checks input to be numerical
    if(!Trip::checkInputNumerical(selectedIndexInput)){
        cerr << "Invalid input, please try again!" << endl;
        return;
    }

    //Cancel statement
    if (stoi(selectedIndexInput) == -1) {
        return;
    }

    //Checks if selected number is an existing index number
    if (stoi(selectedIndexInput) > this->currentLoggedInUser->getTripList().size() || stoi(selectedIndexInput) < 0){
        cerr << "Invalid index selection, no such index exists!" << endl;
        return;
    }

    //Deletes the pointer to trip object in the vector and erases the content of that index inside the vector
    int selectedIndex = stoi(selectedIndexInput)-1;
    this->currentLoggedInUser->removeTrip(selectedIndex);//Deletes the pointer object
    cout << "Successfully deleted!" << endl;

}