#include "pokeFile.h"
#include <iostream>
#include <string>
#include <random>  // random_device
#include <thread>   // sleep
#include <chrono>   // time   -    https://cplusplus.com/reference/thread/this_thread/sleep_for/
using namespace std;
#include "algo1.h"

int main() {
    std::random_device rand;
    int menu = 0;
    vector<string> silly = {"why did the torchic cross the road?", "don't look a gift horse in the meowth", "curiosity killed the mew", "like a venomoth to a flame", "you can lead a ponyta to water...", "two pidgeys, one stone", "don't put all your exeggcutes in one basket!", "early bird gets the wurmple", "there are plenty of magikarps in the sea.", "hold your horseas"};
    vector<string> searchRand = {"searching...", "exploring archives...", "consulting pokedex data...", "seeking your answer...", "searching at the speed of light"};
    vector<string> sortRand = {"tabulating...", "analyzing data...", "sorting...", "compiling records...", "gotta sort 'em all!", "prepare for O(n)... and make it O(n^2)"};
    vector<Pokemon> mons = readPokeFiles();
    bool searching = true;
        cout << "|---------------------------------------------------------------|" << endl;
        cout << "|--------------------|     WELCOME  TO     |--------------------|" << endl;
        cout << "|--------------------|  B A T T L E D E X  |--------------------|" << endl;
        cout << "|---------------------------------------------------------------|" << endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    while (searching) {
        string input;
            cout << "|  MENU:                                                        |" << endl;
            cout << "|  1 - about battledex                                          |" << endl;
            cout << "|  2 - search for a pokemon                                     |" << endl;
            cout << "|  3 - view pokemon rankings                                    |" << endl;
            cout << "|  4 - jokemon                                                  |" << endl;
            cout << "|  5 - exit                                                     |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "   ENTER MENU SELECTION :                                        " << endl;
            getline(cin, input, '\n');
        if (input == "1") { // ABOUT US
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|-------------------|    A B O U T  U S:    |-------------------|" << endl;
            cout << "|-------------------|  t e a m   s h i n y  |-------------------|" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|                                                               |" << endl;
            cout << "|    O U R   P R O J E C T:                                     |" << endl;
            cout << "|      BATTLEDEX fetches, catalogs, and organizes the most      |" << endl;
            cout << "|      current and comprehensive data from www.smogon.com,      |" << endl;
            cout << "|      an accurate resource and community made up of over       |" << endl;
            cout << "|      450,000 members. Their database contains millions of     |" << endl;
            cout << "|      battle records gathered across decades of gameplay       |" << endl;
            cout << "|      from in-house and professional tournaments like VGC.     |" << endl;
            cout << "|      BATTLEDEX data is gathered from the OverUsed tier,       |" << endl;
            cout << "|      the most popular gameplay tier by far. OU allows the     |" << endl;
            cout << "|      use of almost every single pokemon from across the       |" << endl;
            cout << "|      9 generations and across several other gameplay tiers.   |" << endl;
            cout << "|      For those getting started in competitive Pokemon         |" << endl;
            cout << "|      battling, BATTLEDEX is your one stop shop for high       |" << endl;
            cout << "|      ranking team comps, movesets, powerful counters, and     |" << endl;
            cout << "|      more! Thank you for reading this far, lol                |" << endl;
            cout << "|                                                               |" << endl;
            cout << "|                                                               |" << endl;
            cout << "|  T H E   B A T T L E D E X   T E A M:                         |" << endl;
            cout << "|  1 Ashley Horan :D                                            |" << endl;
            cout << "|    '-> big snorlax fan                                        |" << endl;
            cout << "|  2 Taj Miller :)                                              |" << endl;
            cout << "|    '-> pokemon go pro                                         |" << endl;
            cout << "|  3 Brenley Jean :P                                            |" << endl;
            cout << "|    '-> pokemon master                                      |" << endl;
            cout << "|                                                               |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        } // ABOUT US SECTION <-
        else if (input == "2") { // SEARCHING AND STORING
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|-----------------------|  S E A R C H  |-----------------------|" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|  SEARCH FOR A POKEMON:                 0 - back to main menu  |" << endl;
            cout << "|                                                               |" << endl;
            cout << "|  ENTER A NAME:                                                |" << endl;
            getline(cin, input, '\n');
            cout << searchRand[rand() % 5] << endl;
            cout << "                                                                 " << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "|---------------------------------------------------------------|" << endl;
            display(mons, input);

        }else if (input == "3") { // SORTING
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|-------------------|  V I E W   S T A T S  |-------------------|" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|  SELECT A FILTER:                      0 - back to main menu  |" << endl;
            cout << "|  1 - generation                                               |" << endl;
            cout << "|  2 - region                                                   |" << endl;
            cout << "|  3 - type                                                     |" << endl;
            cout << "|  4 - meta                                                     |" << endl; // uses viability ranking
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "   ENTER SELECTION:                                              " << endl;
            getline(cin, input, '\n');
            cout << sortRand[rand() % 5] << endl;
            cout << "                                                                 " << endl;
            this_thread::sleep_for(chrono::seconds(2));
            string filter, typeSort;
            if (input == "0") {
                continue;
            }else if (input == "1") {
                cout << "|---------------------------------------------------------------|" << endl;
                cout << "|           which GENERATION would you like to see?             |" << endl;
                cout << "|---------------------------------------------------------------|" << endl;
                cout << "|    GEN 1  ->  RED / BLUE       |   GEN 5 -> X & Y             |" << endl;
                cout << "|    GEN 2  ->  GOLD / SILVER    |   GEN 6 -> SUN / MOON        |" << endl;
                cout << "|    GEN 3  ->  RUBY / SAPPHIRE  |   GEN 7 -> SWORD / SHIELD    |" << endl;
                cout << "|    GEN 4  ->  DIAMOND / PEARL  |   GEN 8 -> Z - A             |" << endl;
                cout << "|    GEN 5  ->  BLACK / WHITE    |                              |" << endl;
                cout << "|---------------------------------------------------------------|" << endl;
                cout << "   ENTER SELECTION:                                              " << endl;
                getline(cin, filter, '\n');

            }else if (input == "2") {
                cout << "|            which REGION would you like to see?                |" << endl;
                cout << "|---------------------------------------------------------------|" << endl;
                cout << "|          1  ->  KANTO       |      5  ->  KALOS               |" << endl;
                cout << "|          2  ->  JOHTO       |      6  ->  ALOLA               |" << endl;
                cout << "|          3  ->  HOENN       |      7  ->  GALAR               |" << endl;
                cout << "|          4  ->  SINNOH      |      8  ->  PALDEA              |" << endl;
                cout << "|          5  ->  UNOVA       |                                 |" << endl;
                cout << "|---------------------------------------------------------------|" << endl;
                cout << "   ENTER SELECTION:                                              " << endl;
                getline(cin, filter, '\n');

            }else if (input == "3") {
                cout << "|          which pokemon TYPE would you like to see?            |" << endl;
                cout << "|---------------------------------------------------------------|" << endl;
                cout << "|          1  ->  NORMAL       |      10  ->  BUG               |" << endl;
                cout << "|          2  ->  GRASS        |      11  ->  POISON            |" << endl;
                cout << "|          3  ->  WATER        |      12  ->  GROUND            |" << endl;
                cout << "|          4  ->  FIRE         |      13  ->  ROCK              |" << endl;
                cout << "|          5  ->  ICE          |      14  ->  GHOST             |" << endl;
                cout << "|          6  ->  ELECTRIC     |      15  ->  DRAGON            |" << endl;
                cout << "|          7  ->  FIGHTING     |      16  ->  DARK              |" << endl;
                cout << "|          8  ->  FLYING       |      17  ->  STEEL             |" << endl;
                cout << "|          9  ->  PSYCHIC      |      18  ->  FAIRY             |" << endl;
                cout << "|---------------------------------------------------------------|" << endl;
                cout << "   ENTER SELECTION:                                              " << endl;
                getline(cin, filter, '\n');

            }else if (input == "4") {
                string temp;
                cout << "|           how many pokemon would you like to see?             |" << endl;
                cout << "|---------------------------------------------------------------|" << endl;
                cout << "   ENTER NUMBER:                                                 " << endl;
                getline(cin, temp, '\n');
                int metaCT = stoi(temp); // number of pokemon to display

                // do function here

                // sort by viability ceiling (highest player 'elo' that used this pokemon) in descending order
                // display viability ceiling and usage rate

            }

            // FILTERED SORT  !!!!!!!!  using string filter !!!!!!!!
            // this is how we compare them
            cout << "|           which sorting algorithm should we use?              |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|           1  ->  M E R G E  S O R T                           |" << endl;
            cout << "|           2  ->  Q U I C K  S O R T                           |" << endl;
            cout << "|           3  ->    H E A P  S O R T                           |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "   ENTER SELECTION:                                              " << endl;
            getline(cin, typeSort, '\n');

            // Example: sort Pokémon by generation
            vector<Pokemon> filtered;

            // Convert filter input (generation number)
            try {
                int genNum = stoi(filter);
                for (auto& p : mons) {
                    if (p.generation == genNum) filtered.push_back(p);
                }
            } catch (...) {
                filtered = mons; // fallback if input wasn't a number
            }

            if (filtered.empty()) {
                cout << "No Pokémon found for that filter.\n";
                continue;
            }

            // Apply chosen sorting algorithm
            auto start = chrono::high_resolution_clock::now();

            if (typeSort == "1") {
                mergeSort(filtered, 0, filtered.size() - 1);
                cout << "\nSorted with Merge Sort!\n";
            } else if (typeSort == "2") {
                quickSort(filtered, 0, filtered.size() - 1);
                cout << "\nSorted with Quick Sort!\n";
            } else if (typeSort == "3") {
                heapSort(filtered);
                cout << "\nSorted with Heap Sort!\n";
            } else {
                cout << "Invalid selection.\n";
                continue;
            }

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|      TOP 10 POKÉMON BY USAGE RATE (GEN " << filter << ")       |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;

            // Display top 10
            int displayCount = min(10, (int)filtered.size());
            for (int i = 0; i < displayCount; i++) {
                auto& p = filtered[i];
                cout << i + 1 << ". " << p.name
                     << " | Type: " << p.type1;
                if (!p.type2.empty()) cout << "/" << p.type2;
                cout << " | Usage Rate: " << p.usage << endl;
            }

            cout << "|---------------------------------------------------------------|" << endl;
            cout << "Sorting completed in " << duration << " ms\n";
            cout << "|---------------------------------------------------------------|" << endl;



        }else if (input == "4") { // for fun
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|----------------------|  J O K E M O N  |----------------------|" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|  generating jokemon...                                        |" << endl;
            cout << "|                                                               |" << endl;
            cout << "|  " << silly[rand() % 10] << endl;
            cout << "|                                                               |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (input == "5") {
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|--------------|  thank you for using battledex!  |-------------|" << endl;
            cout << "|--------------|      ~ t e a m  s h i n y ~      |-------------|" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            searching = false;
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
//     while (searching) {
//         string input;
//         cout << "Search for a Pokemon! Enter 'done' to exit." << endl;
//         getline(cin, input);
//         if (input == "done") {
//             cout << "thank you for using battledex" << endl;
//             searching = false;
//         }else {
//             cout << "searching for " << input << endl;
//             display(mons, input);
//         }
//     }
//
//     return 0;
// }