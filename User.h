//
// Created by Yoel on 1/30/2023.
//

#ifndef TRIPCOSTCALCULATOR_USER_H
#define TRIPCOSTCALCULATOR_USER_H

#include "Trip.h"
#include <string>
#include <vector>

using namespace std;

class User {
    public:
        User(string nameInput, string passwordInput);
        ~User();
        string getName() const;
        string getPassword() const;
        void addTrip(Trip* newTrip);
        vector<Trip*> getTripList() const;

    private:
        string const name;
        string const password;
        vector<Trip*> tripList;
};


#endif //TRIPCOSTCALCULATOR_USER_H
