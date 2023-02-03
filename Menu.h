//
// Created by Yoel on 1/30/2023.
//

#ifndef TRIPCOSTCALCULATOR_MENU_H
#define TRIPCOSTCALCULATOR_MENU_H

#include "User.h"
#include <vector>

using namespace std;

class Menu {
    public:
        Menu();
        ~Menu();
        void start();
        void userCreation();
        void handleLogin();
        void handleTripCalculator();
        void handleTripCreation();
        void handleLoadTrip();
        void handleRemoveTrip();
        static bool checkInput(const string& nameInput, const string& passwordInput);
        User* findUserInList(const string& nameInput, const string& passwordInput) const;

    private:
        User* currentLoggedInUser;
        vector<User*> userList;
};


#endif //TRIPCOSTCALCULATOR_MENU_H
