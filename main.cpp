#include "pokeFile.cpp"
#include <iostream>
using namespace std;

int main() {
    // this is just me testing
    string input;
    cout << "Search for a Pokemon:" << endl;
    cin >> input;
    cout << "the program is going to find that pokemon now:" << endl;
    vector<Pokemon> mons = readFiles();
    display(mons, input);
    cout << "done listing pokemon" << endl;

    return 0;
}
