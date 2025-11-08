#include "pokeFile.cpp"
#include <iostream>
using namespace std;

int main() {
    // this is just me testing
    vector<Pokemon> mons = readPokeFiles();
    bool searching = true;
    while (searching) {
        string input;
        cout << "Search for a Pokemon! Enter 'done' to exit." << endl;
        getline(cin, input);
        if (input == "done") {
            cout << "thank you for using battledex" << endl;
            searching = false;
        }else {
            cout << "searching for " << input << endl;
            display(mons, input);
        }
    }

    return 0;
}

// #include "pokeFile.cpp"
// #include <iostream>
// using namespace std;
//
// int main() {
//     // this is just me testing
//     vector<Pokemon> mons = readPokeFiles();
//     bool searching = true;
//         cout << "|---------------------------------------------------------------|" << endl;
//         cout << "|--------------------|     WELCOME  TO     |--------------------|" << endl;
//         cout << "|--------------------|  B A T T L E D E X  |--------------------|" << endl;
//         cout << "|---------------------------------------------------------------|" << endl;
//     while (searching) {
//         string input;
//             cout << "|---------------------------------------------------------------|" << endl;
//             cout << "|  MENU:                                                        |" << endl;
//             cout << "|  1 - search for a pokemon                                     |" << endl;
//             cout << "|  2 - view pokemon rankings                                    |" << endl;
//             cout << "|  3 - exit                                                     |" << endl;
//             cout << "|                                                               |" << endl;
//             cout << "|  ENTER A MENU OPTION #:                                       |" << endl;
//         getline(cin, input);
//         if (input == "1") { // SEARCHING AND STORING
//             cout << "|---------------------------------------------------------------|" << endl;
//             cout << "|-----------------------|  S E A R C H  |-----------------------|" << endl;
//             cout << "|---------------------------------------------------------------|" << endl;
//             cout << "|  SEARCH FOR A POKEMON:                                        |" << endl;
//             cout << "|  0 - back to main menu                                        |" << endl;
//             getline(cin, input);
//         }else if (input == "2") { // SORTING
//             cout << "|---------------------------------------------------------------|" << endl;
//             cout << "|-------------------|  V I E W   S T A T S  |-------------------|" << endl;
//             cout << "|---------------------------------------------------------------|" << endl;
//             cout << "|  SELECT A FILTER:                                             |" << endl;
//             cout << "|  0 - back to main menu                                        |" << endl;
//             cout << "|  1 - generation                                               |" << endl;
//             cout << "|  2 - region                                                   |" << endl;
//             cout << "|  3 - type                                                     |" << endl;
//             cout << "|  4 - meta                                                     |" << endl; // uses viability ranking
//         }else if (input == "3") {
//             cout << "|---------------------------------------------------------------|" << endl;
//             cout << "|--------------|  thank you for using battledex!  |-------------|" << endl;
//             cout << "|--------------|      ~ t e a m  s h i n y ~      |-------------|" << endl;
//             cout << "|---------------------------------------------------------------|" << endl;
//             searching = false;
//         }else {
//             cout << "|               INVALID INPUT -- PLEASE TRY AGAIN!              |" << endl;
//         }
//     }
//
//     return 0;
// }
