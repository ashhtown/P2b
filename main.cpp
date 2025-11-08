#include "pokeFile.cpp"
#include <iostream>
#include <string>
#include <random>  // random_device
#include <thread>   // sleep
#include <chrono>   // time   -    https://cplusplus.com/reference/thread/this_thread/sleep_for/
#include <cctype>
using namespace std;

int main() {

    std::random_device rand;
    vector<string> silly = {"why did the torchic cross the road?", "don't look a gift horse in the meowth", "curiosity killed the mew", "like a venomoth to a flame", "you can lead a ponyta to water...", "two pidgeys, one stone", "don't put all your exeggcutes in one basket!", "early bird gets the wurmple", "there are plenty of magikarps in the sea.", "hold your horseas"};
    vector<string> searchRand = {"searching...", "exploring archives...", "consulting pokedex data...", "seeking your answer...", "searching at the speed of light"};
    vector<string> sortRand = {"tabulating...", "analyzing data...", "sorting...", "compiling records...", "gotta sort 'em all!", "prepare for O(n)... and make it O(n^2)"};
    vector<Pokemon> mons = readPokeFiles();
    vector<string> types = {"NORMAL", "GRASS", "WATER", "FIRE", "ICE", "ELECTRIC", "FIGHTING", "FLYING", "PSYCHIC", "BUG", "POISON", "GROUND", "ROCK", "GHOST", "DRAGON", "DARK", "STEEL", "FAIRY"};
    vector<string> regions = {"KANTO", "JOHTO", "HOENN", "SINNOH", "UNOVA", "KALOS", "ALOLA", "GALAR", "PALDEA"};

    bool searching = true;
        cout << "|---------------------------------------------------------------|" << endl;
        cout << "|--------------------|     WELCOME  TO     |--------------------|" << endl;
        cout << "|--------------------|  B A T T L E D E X  |--------------------|" << endl;
        cout << "|---------------------------------------------------------------|" << endl;

    while (searching) {
        string input;

            cout << "|  MENU:                                                        |" << endl;
            cout << "|  1 - about battledex                                          |" << endl;
            cout << "|  2 - search for a pokemon                                     |" << endl;
            cout << "|  3 - view pokemon rankings                                    |" << endl;
            cout << "|  4 - jokemon                                                  |" << endl;
            cout << "|  5 - exit                                                     |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|                                                               |" << endl;

            cout << "   ENTER MENU SELECTION:  ";
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
            cout << "|    '-> pokemon master                                         |" << endl;
            cout << "|                                                               |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
        } // ABOUT US SECTION <-

        else if (input == "2") { // SEARCHING AND STORING
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|-----------------------|  S E A R C H  |-----------------------|" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|  SEARCH FOR A POKEMON:                 0 - back to main menu  |" << endl;
            cout << "|                                                               |" << endl;
            cout << "|                                                               |" << endl;
            cout << "   ENTER A NAME:  ";
            getline(cin, input, '\n');
            if (input == "0") {
                continue;
            }
            cout << searchRand[rand() % 5] << endl; // displays message
            cout << "                                                                 " << endl;
            this_thread::sleep_for(chrono::seconds(2));

            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|                                                               |" << endl;
            cout << "   "; display(mons, input);
            cout << "|                                                               |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
        }

        else if (input == "3") {
            // SORTING
            string filter, typeSort;
            vector<Pokemon> monsToSort;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|-------------------|  V I E W   S T A T S  |-------------------|" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|  SELECT A FILTER:                      0 - back to main menu  |" << endl;
            cout << "|  1 - generation                                               |" << endl;
            cout << "|  2 - region                                                   |" << endl;
            cout << "|  3 - type                                                     |" << endl;
            cout << "|  4 - meta                                                     |" << endl; // uses viability ranking
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|                                                               |" << endl;
            cout << "   ENTER SELECTION:  ";
            getline(cin, input, '\n');

            if (input == "0") {
                continue;
            }

            int filterNum = 0;
            int regNum = 1;
            bool filtering = true;
            while (filtering) {
                if (input == "1") {
                    cout << "|---------------------------------------------------------------|" << endl;
                    cout << "|           which GENERATION would you like to see?             |" << endl;
                    cout << "|---------------------------------------------------------------|" << endl;
                    cout << "|    GEN 1  ->  RED / BLUE       |   GEN 6 -> X & Y             |" << endl;
                    cout << "|    GEN 2  ->  GOLD / SILVER    |   GEN 7 -> SUN / MOON        |" << endl;
                    cout << "|    GEN 3  ->  RUBY / SAPPHIRE  |   GEN 8 -> SWORD / SHIELD    |" << endl;
                    cout << "|    GEN 4  ->  DIAMOND / PEARL  |   GEN 9 -> Z - A             |" << endl;
                    cout << "|    GEN 5  ->  BLACK / WHITE    |                              |" << endl;
                    cout << "|---------------------------------------------------------------|" << endl;
                    cout << "|                                                               |" << endl;
                    cout << "   ENTER GENERATION (#):  ";
                    getline(cin, filter, '\n');
                    if (filter < "1" || filter > "9") {
                        cout << "   please enter the generation as a number 1-9!" << endl;
                        continue;
                    }
                    filterNum = 1;
                    filtering = false;

                }
                else if (input == "2") {
                    cout << "|---------------------------------------------------------------|" << endl;
                    cout << "|            which REGION would you like to see?                |" << endl;
                    cout << "|---------------------------------------------------------------|" << endl;
                    cout << "|          1  ->  KANTO       |      6  ->  KALOS               |" << endl;
                    cout << "|          2  ->  JOHTO       |      7  ->  ALOLA               |" << endl;
                    cout << "|          3  ->  HOENN       |      8  ->  GALAR               |" << endl;
                    cout << "|          4  ->  SINNOH      |      9  ->  PALDEA              |" << endl;
                    cout << "|          5  ->  UNOVA       |                                 |" << endl;
                    cout << "|---------------------------------------------------------------|" << endl;
                    cout << "|                                                               |" << endl;
                    cout << "   ENTER REGION (#):  ";
                    getline(cin, filter, '\n');

                    if (filter < "1" || filter > "9") {
                        cout << "   please enter the corresponding region number!" << endl;
                        continue;
                    }
                    filterNum = 2;
                    filtering = false;

                }else if (input == "3") {
                    cout << "|---------------------------------------------------------------|" << endl;
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
                    cout << "|                                                               |" << endl;
                    cout << "   ENTER TYPE NAME:  ";
                    getline(cin, filter, '\n');

                    // check if valid type then convert input to be the same case as pokemon.type1 or 2
                    string check;
                    for (char& c : filter) {
                        c = static_cast<char>(toupper(c));
                        check.push_back(c);
                    }
                    if (find(types.begin(), types.end(), check) != types.end()) {
                        filter[0] = static_cast<char>(toupper(filter[0]));
                        for (int i = 1; i < filter.size(); i++) {
                            filter[i] = static_cast<char>(tolower(filter[i]));
                        }
                        filterNum = 3;
                        filtering = false;
                    }else {
                        cout << "   please enter a valid pokemon type name!" << endl;
                    }

                }else if (input == "4") {
                    filterNum = 4;
                    filtering = false;

                }else {
                    cout << "   please enter your filter selection as a number!" << endl;
                }
            }

            // data
            vector<Pokemon> Pokedex = readPokeFiles();

            // COMPARING ALGS! FILTERED SORT  !!!!!!!!  using string filter !!!!!!!!
            cout << "|           which sorting algorithm should we use?              |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|                1  ->  M E R G E  S O R T                      |" << endl;
            cout << "|                2  ->  Q U I C K  S O R T                      |" << endl;
            cout << "|                3  ->    H E A P  S O R T                      |" << endl;
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|                                                               |" << endl;
            cout << "   ENTER SELECTION:  ";
            getline(cin, typeSort, '\n');

            cout << sortRand[rand() % 5] << endl; // displays message
            cout << "                                                                 " << endl;
            this_thread::sleep_for(chrono::seconds(2));
            if (filterNum == 1){
                vector<Pokemon> filtered;

                // Example: sort Pokémon by generation
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
                cout << "          TOP 10 POKEMON BY USAGE RATE  -  GEN " << filter << endl;
                cout << "|---------------------------------------------------------------|" << endl;

                // Display top 10
                int displayCount = min(10, (int)filtered.size());
                for (int i = 0; i < displayCount; i++) {
                    auto& p = filtered[i];
                    cout << "   " << i + 1 << ". " << p.name
                         << " | Type: " << p.type1;
                    if (!p.type2.empty()) cout << "/" << p.type2;
                    cout << " | Usage Rate: " << p.usage << endl;
                }

                cout << "|---------------------------------------------------------------|" << endl;
                cout << "              Sorting completed in " << duration << " ms\n";
                cout << "|---------------------------------------------------------------|" << endl;
            }else if (filterNum == 2) { // region
                vector<Pokemon> filtered = filterByGeneration(Pokedex, stoi(filter));

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
                cout << "            TOP 10 POKEMON BY USAGE RATE  -  " << regions[stoi(filter)-1] << endl;
                cout << "|---------------------------------------------------------------|" << endl;

                // Display top 10
                int displayCount = min(10, (int)filtered.size());
                for (int i = 0; i < displayCount; i++) {
                    auto& p = filtered[i];
                    cout << "   " << i + 1 << ". " << p.name
                         << " | Type: " << p.type1;
                    if (!p.type2.empty()) cout << "/" << p.type2;
                    cout << " | Usage Rate: " << p.usage << endl;
                }

                cout << "|---------------------------------------------------------------|" << endl;
                cout << "              Sorting completed in " << duration << " ms\n";
                cout << "|---------------------------------------------------------------|" << endl;
            }
            else if (filterNum == 3) { // type
                vector<Pokemon> filtered = filterByType(Pokedex, filter);

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

                string typeUpper;
                for (char& c : filter) {
                    c = static_cast<char>(toupper(c));
                    typeUpper.push_back(c);
                }

                cout << "|---------------------------------------------------------------|" << endl;
                cout << "          TOP 10 POKEMON BY USAGE RATE  -  " << typeUpper << " TYPE" << endl;
                cout << "|---------------------------------------------------------------|" << endl;

                // Display top 10
                int displayCount = min(10, (int)filtered.size());
                for (int i = 0; i < displayCount; i++) {
                    auto& p = filtered[i];
                    cout << "   " << i + 1 << ". " << p.name
                         << " | Type: " << p.type1;
                    if (!p.type2.empty()) cout << "/" << p.type2;
                    cout << " | Usage Rate: " << p.usage << endl;
                }

                cout << "|---------------------------------------------------------------|" << endl;
                cout << "              Sorting completed in " << duration << " ms\n";
                cout << "|---------------------------------------------------------------|" << endl;
            }
            else if (filterNum == 4) { // top 10 meta

                auto start = chrono::high_resolution_clock::now();

                if (typeSort == "1") {
                    mergeSort(Pokedex, 0, Pokedex.size() - 1);
                    cout << "\nSorted with Merge Sort!\n";
                } else if (typeSort == "2") {
                    quickSort(Pokedex, 0, Pokedex.size() - 1);
                    cout << "\nSorted with Quick Sort!\n";
                } else if (typeSort == "3") {
                    heapSort(Pokedex);
                    cout << "\nSorted with Heap Sort!\n";
                } else {
                    cout << "Invalid selection.\n";
                    continue;
                }

                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                string typeUpper;
                for (char& c : filter) {
                    c = static_cast<char>(toupper(c));
                    typeUpper.push_back(c);
                }

                cout << "|---------------------------------------------------------------|" << endl;
                cout << "          TOP 10 POKEMON BY USAGE RATE  -  OVERALL" << endl;
                cout << "|---------------------------------------------------------------|" << endl;

                // Display top 10
                int displayCount = min(10, (int)Pokedex.size());
                for (int i = 0; i < displayCount; i++) {
                    auto& p = Pokedex[i];
                    cout << "   " << i + 1 << ". " << p.name
                         << " | " << p.type1;
                    if (!p.type2.empty()) cout << "/" << p.type2;
                    cout << " | Usage Rate: " << p.usage;
                    cout << " | Gen " << p.generation << endl;
                }

                cout << "|---------------------------------------------------------------|" << endl;
                cout << "              Sorting completed in " << duration << " ms\n";
                cout << "|---------------------------------------------------------------|" << endl;
            }

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