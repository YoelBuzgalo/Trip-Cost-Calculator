#include <iostream>
#include <string>
#include "Menu.h"

using namespace std;

int main() {

    cout << endl
         << endl
         <<  "Now starting up your program, please wait!"
         << endl
         << endl;

    Menu* newMenu = new Menu();

    newMenu->start();

    delete newMenu;

    return 0;
}
