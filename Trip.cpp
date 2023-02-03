//
// Created by Yoel on 1/31/2023.
//

#include "Trip.h"
#include "Cost.h"
#include <ctime>
#include <cstring>
#include <iostream>
#include <vector>

//Sets the trip name when this object is created and makes sure the total trip cost is initialized with a value of 0.
Trip::Trip(string tripNameInput)
:tripName(tripNameInput), totalTripCost(0)
{

}

//Clears any allocated memory within this class' object
Trip::~Trip(){

    for (int i =0; i < this->costList.size();i++)
    {
        delete (this->costList[i]);
    }
    this->costList.clear();
}

void Trip::start()
{

    while(true) {
        string selectedInput;
        cout << endl
             << this->tripName << "'s cost calculation"
             << endl
             << "------------------------"
             << endl
             << "The following are your options, choose accordingly: " << endl
             << endl
             << "1 - Add air fare" << endl
             << "2 - Add hotel cost" << endl
             << "3 - Add rental cost" << endl
             << "4 - Add food cost" << endl
             << "5 - Additional expenses (custom)" << endl
             << "6 - Remove added costs" << endl
             << "7 - View total price" << endl
             << "8 - Exit/Back" << endl
             << endl
             << "Please make sure to enter numbers only (1-8)!" << endl;
        getline(cin, selectedInput);

        if(Trip::checkInputNumerical(selectedInput)) {
            int input = stoi(selectedInput);
            switch (input) {
                case 1: //Handle add air fare
                    this->handleAirFare();
                    break;
                case 2: //Handle add hotel cost
                    this->handleHotelCost();
                    break;
                case 3: //Handle add rental cost
                    this->handleRentalCost();
                    break;
                case 4: //Handle add food cost
                    this->handleFoodCost();
                    break;
                case 5: //Handle add additional expenses (custom)
                    this->handleAdditionalExpenses();
                    break;
                case 6: //Handle remove any added costs
                    this->handleRemoveCosts();
                    break;
                case 7: //Handle view total price
                    this->handleTotalPrice();
                    break;
                case 8: //Go back to menu
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

//Returns the name of the trip object's name
string Trip::getTripName() {
    return this->tripName;
}

//Adds Air Fare (either one way or round trip), total price
void Trip::handleAirFare()
{
    string selectedInput;
    string nameInput;
    string departureCity;
    string destinationCity;
    string descriptionInput;
    string airFarePriceInput;
    string tripMethod;

    cout << "Select the following: " << endl
         << "1 - One Way Flight" << endl
         << "2 - Round Trip Flight" << endl
         << endl
         << "Please make sure to enter numbers only (1-2)!" << endl;
    getline(cin, selectedInput);
    cout << "Please enter your airline name: " << endl;
    getline(cin, nameInput);
    cout << "Please enter departure city: " << endl;
    getline(cin, departureCity);
    cout << "Please enter destination city: " << endl;
    getline(cin, destinationCity);
    cout << "Please enter your air fare price: " << endl;
    getline(cin, airFarePriceInput);

    //Checks if the selected input is a number input
    if(!Trip::checkInputNumerical(selectedInput)){
        cerr << "Invalid input! Please try again" << endl;
        return;
    }

    //Checks if the selected input is not 1 or 2
    if(stoi(selectedInput) != 1 && stoi(selectedInput) != 2){
        cerr << "Invalid input! Please try again" << endl;
        return;
    }
    tripMethod = (stoi(selectedInput) == 1) ? "one way" : "round trip";

    descriptionInput = tripMethod + " flight from " + departureCity + " to " + destinationCity;

    if(Trip::checkInputNumerical(airFarePriceInput)){
        double airFarePrice = stod(airFarePriceInput);
        Cost* const airFareCost = new Cost(nameInput, descriptionInput, 0, 0, airFarePrice);
        this->costList.push_back(airFareCost);
        this->totalTripCost += airFarePrice;
        cout << "Successfully added your $" << to_string(airFarePrice) << " " << nameInput << " " << descriptionInput << " air fare!" << endl;
        return;
    }

    cerr << "There was an error trying to calculate your air fare price, please try again!" << endl;

}

//Adds hotel costs
void Trip::handleHotelCost()
{

    string nameInput;
    string locationCityInput;
    string checkInDateInput;
    string checkOutDateInput;
    string hotelPriceInput;

    cout << "Enter name of the hotel: " << endl;
    getline(cin, nameInput);
    cout << "Enter city/location of the hotel: " << endl;
    getline(cin, locationCityInput);
    cout << "Enter check in date (MM/DD/YYYY): " << endl;
    getline(cin, checkInDateInput);
    cout << "Enter check out date (MM/DD/YYYY): " << endl;
    getline(cin, checkOutDateInput);
    cout << "Price per night at this hotel: " << endl;
    getline(cin, hotelPriceInput);

    //Checks the date inputs and converts them into UNIX
    if(Trip::checkInputDate(checkInDateInput) && Trip::checkInputDate(checkOutDateInput)) {

        long long checkInTimestamp = convertToTimestamp(checkInDateInput);  //Converts check in date to seconds
        long long checkOutTimestamp = convertToTimestamp(checkOutDateInput);    //Converts check out date to seconds
        string checkInDate = convertToDate(checkInTimestamp);
        string checkOutDate = convertToDate(checkOutTimestamp);
        int checkInTimestampInteger = checkInTimestamp;
        int checkOutTimestampInteger = checkOutTimestamp;
        int nights = ((checkOutTimestampInteger - checkInTimestampInteger)/86400)+1;
        string descriptionInput = "hotel stay between " + checkInDate + " to " + checkOutDate + " at " + locationCityInput + " (" + to_string(nights) + " nights)";

        //Checks if the date inputs are in correct date order
        if(nights < 0){
            cerr << "Invalid date inputs, please try again!" << endl;
            return;
        }

        if(Trip::checkInputNumerical(hotelPriceInput)){
            double hotelPrice = stod(hotelPriceInput);
            Cost* const hotelCost = new Cost(nameInput, descriptionInput, 0, nights, hotelPrice);
            this->costList.push_back(hotelCost);
            this->totalTripCost += hotelCost->getPrice();
            cout << "Successfully added your " << nameInput << " " << descriptionInput << " with the cost of $" << to_string(hotelCost->getPrice()) << endl;
            return;
        }

    }
    cerr << "There was an error with your check in or check out date input, please try again!" << endl;

}

//Adds rental costs
void Trip::handleRentalCost()
{
    string selectedInput;
    string nameInput;
    string locationCityInput;
    string rentalPickUpDateInput;
    string rentalReturnInput;
    string rentalPriceInput;
    string rentalItemInput;

    cout << "Enter name of the rental company: " << endl;
    getline(cin, nameInput);
    cout << "What are you renting?" << endl
         << "1 - Car" << endl
         << "2 - Motorcycle" << endl
         << "3 - Plane" << endl
         << "4 - Bicycle" << endl
         << "5 - Camping Gear" << endl
         << "6 - Others" << endl
         << "7 - Cancel" << endl
         << endl
         << "Please make sure to enter numbers only (1-7)!" << endl;
    getline(cin, selectedInput);

    if(Trip::checkInputNumerical(selectedInput)) {
        switch(stoi(selectedInput)){
            case 1:
                rentalItemInput = "Car";
                break;
            case 2:
                rentalItemInput = "Motorcycle";
                break;
            case 3:
                rentalItemInput = "Plane";
                break;
            case 4:
                rentalItemInput = "Bicycle";
                break;
            case 5:
                rentalItemInput = "Camping Gear";
                break;
            case 6:
                cout << "Please specify what you are renting: " << endl;
                cin.ignore();
                getline(cin, rentalItemInput);
                break;
            case 7:
                return;
            default:
                cerr << "No matched input! Please try again!" << endl;
                return;
        }

        cout << "Enter city/location of the rental: " << endl;
        getline(cin, locationCityInput);
        cout << "Enter rental pick up date (MM/DD/YYYY): " << endl;
        getline(cin, rentalPickUpDateInput);
        cout << "Enter rental return date (MM/DD/YYYY): " << endl;
        getline(cin, rentalReturnInput);
        cout << "Price per day for rental: " << endl;
        getline(cin, rentalPriceInput);

        //Checks the date inputs and converts them into UNIX
        if(Trip::checkInputDate(rentalPickUpDateInput) && Trip::checkInputDate(rentalReturnInput)) {

            long long rentalPickupTimestamp = convertToTimestamp(rentalPickUpDateInput);  //Converts pick up date to seconds
            long long rentalReturnTimestamp = convertToTimestamp(rentalReturnInput);    //Converts return date to seconds
            string rentalPickupDate = convertToDate(rentalPickupTimestamp);
            string rentalReturnDate = convertToDate(rentalReturnTimestamp);
            int checkInTimestampInteger = rentalPickupTimestamp;
            int checkOutTimestampInteger = rentalReturnTimestamp;
            int days = ((checkOutTimestampInteger - checkInTimestampInteger)/86400);
            string descriptionInput = rentalItemInput + " rental between " + rentalPickupDate + " to " + rentalReturnDate + " at " + locationCityInput + " (" + to_string(days) + " days)";

            //Checks if the date inputs are in correct date order
            if(days < 0){
                cerr << "Invalid date inputs, please try again!" << endl;
                return;
            }

            if(Trip::checkInputNumerical(rentalPriceInput)){
                double rentalPrice = stod(rentalPriceInput);
                Cost* const rentalCost = new Cost(nameInput, descriptionInput, days, 0, rentalPrice);
                this->costList.push_back(rentalCost);
                this->totalTripCost += rentalCost->getPrice();
                cout << "Successfully added your " << nameInput << " " << descriptionInput << " with the cost of $" << to_string(rentalCost->getPrice()) << endl;
                return;
            }
            cerr << "There was an error with your rental date input, please try again!" << endl;
        }
    }
    cerr << "Invalid input! Please try again!" << endl;
}

//Adds food costs
void Trip::handleFoodCost()
{
    string selectionInput;
    string startDateInput;
    string endDateInput;
    string mealsInput;
    string pricePerMealInput;
    string groceryPriceInput;
    double averageCostPerDay;

    cout << "Enter starting food expense date (MM/DD/YYYY): " << endl;
    getline(cin, startDateInput);
    cout << "Enter ending food expense date (MM/DD/YYYY): " << endl;
    getline(cin, endDateInput);
    cout << "How many meals do you eat in a day usually?" << endl;
    getline(cin, mealsInput);

    cout << "How are you going to spend on food between the dates: " << endl
         << "1 - Always Eat Out" << endl
         << "2 - Savvy Eater (Grocery Shop & Eat Out Sometimes)" << endl
         << "3 - Grocery Only" << endl
         << "Please make sure to enter numbers only (1-3)!" << endl;
    getline(cin,selectionInput);

    //Checks the date inputs and converts them into UNIX
    if(Trip::checkInputDate(startDateInput) && Trip::checkInputDate(endDateInput)) {

        long long startTimestamp = convertToTimestamp(startDateInput);  //Converts pick up date to seconds
        long long endTimestamp = convertToTimestamp(endDateInput);    //Converts return date to seconds
        string startDate = convertToDate(startTimestamp);
        string endDate = convertToDate(endTimestamp);
        int startTimestampInteger = startTimestamp;
        int endTimestampInteger = endTimestamp;
        int foodDays = ((endTimestampInteger - startTimestampInteger) / 86400);
        string descriptionInput =
                "average food expense between " + startDate + " to " + endDate + " (" + to_string(foodDays) + " days)";

        //Checks if the date inputs are in correct date order
        if (foodDays < 0) {
            cerr << "Invalid date inputs, please try again!" << endl;
            return;
        }

        if (Trip::checkInputNumerical(mealsInput) && Trip::checkInputNumerical(selectionInput)) {
            switch (stoi(selectionInput)) {
                case 1://Always Eat Out
                    cout
                            << "What is the average price per meal for eating out (e.g. hamburger + drinks) at the destination?"
                            << endl;
                    cin.ignore();
                    getline(cin, pricePerMealInput);
                    if (Trip::checkInputNumerical(pricePerMealInput)) {
                        averageCostPerDay = stod(pricePerMealInput) * stod(mealsInput);
                        Cost* const foodCost = new Cost("Food", descriptionInput, foodDays, 0, averageCostPerDay);
                        this->costList.push_back(foodCost);
                        this->totalTripCost += foodCost->getPrice();
                        cout << "Successfully added!" << endl;
                        return;
                    }
                    break;
                case 2://Savvy Eater
                    cout
                            << "What is the average price per meal for eating out (e.g. hamburger + drinks) at the destination?"
                            << endl;
                    cin.ignore();
                    getline(cin, pricePerMealInput);
                    cout
                            << "What is the average price per grocery shop (e.g. bread loaf + cream cheese/cold cuts + drinks) at the destination? "
                            << endl;
                    getline(cin, groceryPriceInput);
                    if (Trip::checkInputNumerical(pricePerMealInput) && Trip::checkInputNumerical(groceryPriceInput)) {
                        averageCostPerDay = (stod(pricePerMealInput) * 0.6 + stod(groceryPriceInput) * 0.4) * stod(mealsInput);
                        Cost* const foodCost = new Cost("Food", descriptionInput, foodDays, 0, averageCostPerDay);
                        this->costList.push_back(foodCost);
                        this->totalTripCost += foodCost->getPrice();
                        cout << "Successfully added!" << endl;
                        return;
                    }
                    break;
                case 3://Grocery Rat
                    cout
                            << "What is the average price per grocery shop (e.g. bread loaf + cream cheese/cold cuts + drinks) at the destination? "
                            << endl;
                    cin.ignore();
                    getline(cin, groceryPriceInput);
                    if (Trip::checkInputNumerical(groceryPriceInput)) {
                        averageCostPerDay = stod(groceryPriceInput) * stod(mealsInput);
                        Cost* const foodCost = new Cost("Food", descriptionInput, foodDays, 0, averageCostPerDay);
                        this->costList.push_back(foodCost);
                        this->totalTripCost += foodCost->getPrice();
                        cout << "Successfully added!" << endl;
                        return;
                    }
                    break;
                default:
                    cerr << "No matched input!" << endl;
                    break;
            }
        } else {
            cerr << "Invalid inputs! Please try again!" << endl;
        }
    }
    cerr << "There was an error trying to calculate your food costs, please try again!" << endl;
}

//Adds additional expenses (custom)
void Trip::handleAdditionalExpenses()
{
    string customNameInput;
    string customDescriptionInput;
    string expenseInput;
    string recurringInput;
    cout << "Enter name of expected expense: " << endl;
    getline(cin, customNameInput);
    cout << "Enter a brief description of your expense: " << endl;
    getline(cin, customDescriptionInput);
    cout << "Is your expense recurring (daily)? (y/n)" << endl;
    getline(cin, recurringInput);
    cout << "Enter the amount of expense: " << endl;
    getline(cin, expenseInput);

    //Checks recurringInput
    if (recurringInput != "y" && recurringInput != "n"){
        cerr << "Invalid input! Please try again!" << endl;
        return;
    }

    //Validates the expense input before proceeding with switch statement
    if(!Trip::checkInputNumerical(expenseInput)){
        cerr << "Invalid expense input, please try again!" << endl;
        return;
    }

    switch(recurringInput[0]){
        case 'y':{

            string startDateInput;
            string endDateInput;
            cout << "Enter starting expense date (MM/DD/YYYY): " << endl;
            getline(cin, startDateInput);
            cout << "Enter ending expense date (MM/DD/YYYY): " << endl;
            getline(cin, endDateInput);

            if(Trip::checkInputDate(startDateInput) && Trip::checkInputDate(endDateInput)) {
                long long startTimestamp = convertToTimestamp(
                        startDateInput);  //Converts pick up date to seconds
                long long endTimestamp = convertToTimestamp(
                        endDateInput);    //Converts return date to seconds
                string startDate = convertToDate(startTimestamp);
                string endDate = convertToDate(endTimestamp);
                int startTimestampInteger = startTimestamp;
                int endTimestampInteger = endTimestamp;
                int totalDays = ((endTimestampInteger - startTimestampInteger) / 86400);

                //Checks if the date inputs are in correct date order
                if (totalDays < 0) {
                    cerr << "Invalid date inputs, please try again!" << endl;
                    return;
                }

                customDescriptionInput += " (from "+ startDate + " to " + endDate + ")";

                Cost *const customCost = new Cost(customNameInput, customDescriptionInput, totalDays, 0,
                                                  stod(expenseInput));
                this->costList.push_back(customCost);
                this->totalTripCost += customCost->getPrice();
                cout << "Successfully added!" << endl;
                break;
            }
        }
        case 'n': {
            Cost *const customCost = new Cost(customNameInput, customDescriptionInput, 0, 0,stod(expenseInput));
            this->costList.push_back(customCost);
            this->totalTripCost += customCost->getPrice();
            cout << "Successfully added!" << endl;
            break;
        }
        default:
            cerr << "No matched input! Please try again!" << endl;
            return;
    }
}

//Removes any added costs
void Trip::handleRemoveCosts()
{
    if(this->costList.empty()){
        cout << "You do not have any costs associated with " << this->tripName << "!" << endl;
        return;
    }

    string selectedIndexInput;
    cout << "Please enter the index number you wish to delete from " << this->tripName << " trip costs: " << endl
         << "# -|- Name -|- Cost -|- Description" << endl;
    for (int i = 0; i < this->costList.size(); i++) {
        cout << "-----------------------------------" << endl << i + 1 << " - " << this->costList[i]->getName()
             << " - $" << to_string(this->costList[i]->getPrice()) << " - " << this->costList[i]->getDescription()
             << endl;
    }
    cout << endl
         << "Enter -1 to Cancel/Go Back" << endl;
    getline(cin, selectedIndexInput);

    //Checks input if numerical only
    if(!Trip::checkInputNumerical((selectedIndexInput))){
        cerr << "Invalid input! Please try again!" << endl;
        return;
    }

    //Cancel statement
    if(stoi(selectedIndexInput) == -1){
        return;
    }

    //Checks if input is within the range of the vectors' elements indices
    if (stoi(selectedIndexInput) < 0 && stoi(selectedIndexInput) > this->costList.size()) {
        cerr << "Invalid index value! Please try again!" << endl;
        return;
    }

    this->totalTripCost = this->totalTripCost - this->costList[(stoi(selectedIndexInput)-1)]->getPrice();
    delete this->costList[(stoi(selectedIndexInput)-1)];//Deletes the pointer object
    this->costList.erase(this->costList.begin() + (stoi(selectedIndexInput)-1));//Erases any stored address of the pointer that was already deleted at the index of the vector, basically vector is reorganized now
    cout << "Successfully deleted!" << endl;

}

//See all the added costs and grand total price associated to this trip
void Trip::handleTotalPrice()
{
    if(!this->costList.empty()) {
        cout << "Added Costs of " << this->tripName << ": " << endl
             << "# -|- Name -|- Cost -|- Description" << endl;
        for (int i = 0; i < this->costList.size(); i++) {
            cout << "-----------------------------------" << endl << i+1 << " - " << this->costList[i]->getName() << " - $" << to_string(this->costList[i]->getPrice()) << " - " << this->costList[i]->getDescription() << endl;
        }
        cout << endl << "TOTAL PRICE: " << "\t" << "$" << this->totalTripCost << endl;
        cout << endl
             << "Press enter if you're done" << endl;
        cin.sync();
        cin.get();
    } else {
        cout << "You do not have any costs associated with your trip!" << endl;
    }
}

bool Trip::checkInputNumerical(const string& x)
{
    //Checks if the string is empty
    if (x.empty()){
        cerr << "Your input cannot be empty!" << endl;
        return false;
    }

    //Checks if the string contains any spaces
    if (x.contains(" ")){
        cerr << "Your input cannot contain any spaces!" << endl;
        return false;
    }

    //Checks every character in a string if it is a digit or not
    for(char c : x){
        if(isdigit(c) == 0){
            cerr << "Your input cannot contain non-numerical value!" << endl;
            return false;
        }
    }
    return true;
}

bool Trip::checkInputDate(const string& x)
{
    //Checks if the string is longer or less than the date format
    if(x.size() != 10){
        cerr << "Your date input cannot be greater or less than 10!" << endl;
        return false;
    }

    //Checks if the string is empty
    if (x.empty()){
        cerr << "Your input cannot be empty!" << endl;
        return false;
    }

    //Checks if the string contains any spaces
    if (x.contains(" ")){
        cerr << "Your input cannot contain any spaces!" << endl;
        return false;
    }

    //Checks the format
    for(int i=0; i < x.size() ; i++){
        if (i == 2 || i == 5){
            if(x[i] != '/'){
                cout << "You didn't enter correct date format!" << endl;
                return false;
            }
        } else {
            if(isdigit(x[i]) == 0) {
                cerr << "Your input cannot contain non-numerical value except '/'!" << endl;
                return false;
            }
        }
    }
    return true;
}

long long Trip::convertToTimestamp(const string& date) {
    // Parse the input string to extract the month, day, and year
    int month, day, year;
    sscanf(date.c_str(), "%d/%d/%d", &month, &day, &year);

    // Convert the date to a tm struct
    struct tm tm;
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;

    // Convert the tm struct to a unix timestamp
    return mktime(&tm);
}

string Trip::convertToDate(long long timestamp) {
    // Convert the timestamp to a tm struct
    time_t time = timestamp;
    struct tm *tm = localtime(&time);

    // Convert the tm struct to a string in the form "MM/DD/YYYY"
    char buffer[256];
    strftime(buffer, 256, "%m/%d/%Y", tm);
    return buffer;
}