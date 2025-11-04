#include "pokeFile.cpp"
#include <iostream>
using namespace std;

int main() {
    // this is just me testing
    vector<Pokemon> mons = readPokeFiles();
    string input;
    cout << "Search for a Pokemon: " << endl;
    cin >> input;
    cout << "the program is going to find that pokemon now:" << endl;
    display(mons, input);
    cout << "\n" << "done" << endl;
    //map<string, vector<vector<string>>> moveset = readMovesetFiles();

    return 0;
}
