//
// Created by Yoel on 1/31/2023.
//

#ifndef TRIPCOSTCALCULATOR_TRIP_H
#define TRIPCOSTCALCULATOR_TRIP_H

#include "Cost.h"
#include <string>
#include <vector>

using namespace std;

class Trip {
public:
    Trip(string tripName);
    ~Trip();
    void start();
    string getTripName();
    void handleAirFare();
    void handleHotelCost();
    void handleRentalCost();
    void handleFoodCost();
    void handleAdditionalExpenses();
    void handleRemoveCosts();
    void handleTotalPrice();
    static bool checkInputNumerical(const string& x, const char& type);
    static bool checkInputDate(const string& x);
    static long long convertToTimestamp(const string& date);
    static string convertToDate(long long timestamp);

private:
    string const tripName;
    double totalTripCost;
    vector<Cost*> costList;

};


#endif //TRIPCOSTCALCULATOR_TRIP_H
