//
// Created by Yoel on 1/31/2023.
//

#include "Cost.h"

Cost::Cost(string nameInput, string descriptionInput, int daysInput, int nightsInput, double priceInput)
:name(nameInput), description(descriptionInput), days(daysInput), nights(nightsInput), price(priceInput)
{

}

string Cost::getName() const {
    return this->name;
}
string Cost::getDescription() const {
    return this->description;
}

//int Cost::getDays() const {
//    return this->days;
//}
//
//int Cost::getNights() const {
//    return this->nights;
//}

double Cost::getPrice() const {
    if (this->nights != 0){
        return this->price*this->nights;
    }
    if (this->days != 0){
        return this->price*this->days;
    }
    return this->price;
}