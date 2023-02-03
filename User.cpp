//
// Created by Yoel on 1/30/2023.
//

#include "User.h"
#include <string>
#include <vector>

using namespace std;

User::User(string nameInput, string passwordInput)
:name(nameInput), password(passwordInput) // sets name and password when account is created
{
}

//Clears any allocated memory within this class' object
User::~User(){

    for (int i =0; i < this->tripList.size();i++)
    {
        delete (this->tripList[i]);
    }
    this->tripList.clear();
}

string User::getName() const { // function to retrieve account name
    return this->name;
}

string User::getPassword() const { // function to retrieve account's password
    return this->password;
}

void User::addTrip(Trip *newTrip) {
    this->tripList.push_back(newTrip);
}

void User::removeTrip(int index) {
    delete this->tripList[index];   //Deletes the trip's pointer object
    this->tripList.erase(this->tripList.begin() + index);   //Clears any stored pointer address in the vector, reorganizes the vector basically.
}

vector<Trip*> User::getTripList() const {
    return this->tripList;
}
