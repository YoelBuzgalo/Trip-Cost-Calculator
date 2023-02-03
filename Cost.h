//
// Created by Yoel on 1/31/2023.
//

#ifndef TRIPCOSTCALCULATOR_COST_H
#define TRIPCOSTCALCULATOR_COST_H

#include <string>

using namespace std;

class Cost {
public:
    Cost(string nameInput, string descriptionInput, int daysInput, int nightsInput, double priceInput);
    string getName() const;
    string getDescription() const;
//    int getDays() const;
//    int getNights() const;
    double getPrice() const;

private:
    string const name;
    string const description;
    int const days;
    int const nights;
    double const price;
};


#endif //TRIPCOSTCALCULATOR_COST_H
