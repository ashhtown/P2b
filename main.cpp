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
        cin >> input;
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
