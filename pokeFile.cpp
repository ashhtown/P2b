#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Nat,Pokemon,HP,Atk,Def,SpA,SpD,Spe,Total,Type I,Type II,Ability I,Ability II,Hidden Ability,
// EV Worth,Gender,Egg Group I,Egg Group II,Catch,Evolve
// 20 columns

struct Pokemon {
    int num;
    string name;
    int hp;
    int atk;
    int def;
    int spAtk;
    int spDef;
    int spd;
    int total;
    string type1;
    string type2;
    string ability1;
    string ability2;
    string abilityHidden;
    string ev; // effort value
    string gender; // "M/F (percentage)"
    string eg1; // egg group 1
    string eg2; // egg group 2
    string catchNum; // not entirely sure what this is atm
    string evolution; // condition/s to evolve
    int generation;
    string region; // first region in which it appears
};

vector<Pokemon> readFiles() {
    ifstream pokemonFile("../pokemon.csv");
    string line;
    vector<Pokemon> Pokedex; // store pokemon objects (like a pokedex)
    getline(pokemonFile, line); // header

    while (getline(pokemonFile, line)) {
        istringstream stream(line);
        string temp;
        Pokemon pokemon;

        // read all data and assign to pokemon object
        // number
        //cout << "num" << endl;
        getline(stream, temp, ',');
        pokemon.num = stoi(temp);
        // name
        getline(stream, pokemon.name, ',');

        // hp
        //cout << "hp" << endl;
        getline(stream, temp, ',');
        pokemon.hp = stoi(temp);
        // attack
        //cout << "atk" << endl;
        getline(stream, temp, ',');
        pokemon.atk = stoi(temp);
        // def
        //cout << "def" << endl;
        getline(stream, temp, ',');
        pokemon.def = stoi(temp);

        // SP attack
        //cout << "spA" << endl;
        getline(stream, temp, ',');
        pokemon.spAtk = stoi(temp);
        // SP def
        //cout << "spD" << endl;
        getline(stream, temp, ',');
        pokemon.spDef = stoi(temp);
        // speed
        //cout << "spd" << endl;
        getline(stream, temp, ',');
        pokemon.spd = stoi(temp);

        // total
        //cout << "total" << endl;
        getline(stream, temp, ',');
        pokemon.total = stoi(temp);

        // type 1
        getline(stream, pokemon.type1, ',');
        // type 2
        getline(stream, pokemon.type2, ',');

        // ability 1
        getline(stream, pokemon.ability1, ',');
        // ability 2
        getline(stream, pokemon.ability2, ',');
        // hidden ability
        getline(stream, pokemon.abilityHidden, ',');

        // EV
        getline(stream, pokemon.ev, ',');
        if (pokemon.ev[0] == '"') {
            getline(stream, temp, '"');
            pokemon.ev += temp;
            pokemon.ev.erase(0,1);
            getline(stream, temp, ',');
        }
        // gender
        getline(stream, pokemon.gender, ',');
        // egg group 1
        getline(stream, pokemon.eg1, ',');
        // egg group 2
        getline(stream, pokemon.eg2, ',');

        // catch
        getline(stream, pokemon.catchNum, ',');
        // evolution condition
        getline(stream, pokemon.evolution, ',');

        // generation (if there's a better way to do this sorry im tired lol)
        if (pokemon.num <= 151) {
            pokemon.generation = 1;
            pokemon.region = "Kanto";
        }else if (pokemon.num <= 251) {
            pokemon.generation = 2;
            pokemon.region = "Johto";
        }else if (pokemon.num <= 386) {
            pokemon.generation = 3;
            pokemon.region = "Hoenn";
        }else if (pokemon.num <= 493) {
            pokemon.generation = 4;
            pokemon.region = "Sinnoh";
        }else if (pokemon.num <= 649) {
            pokemon.generation = 5;
            pokemon.region = "Unova";
        }else if (pokemon.num <= 721) {
            pokemon.generation = 6;
            pokemon.region = "Kalos";
        }else if (pokemon.num <= 809) {
            pokemon.generation = 7;
            pokemon.region = "Alola";
        }else if (pokemon.num <= 905) {
            pokemon.generation = 8;
            pokemon.region = "Galar";
        }else {
            pokemon.generation = 9;
            pokemon.region = "Paldea";
        }

        // add your now initialized pokemon to the Pokedex vector!
        Pokedex.push_back(pokemon);
    }
    pokemonFile.close();
    return Pokedex;
}

void display(vector<Pokemon>& Pokedex, string& name) {
    bool found = false;
    // this is where we would search for the pokemon using data structure
    // and sort using algorithm to display best battle stats (haven't found a data set for yet)
    for (Pokemon pokemon : Pokedex) {
        if (pokemon.name == name) {
            cout << "Pokedex Entry no. " << pokemon.num << endl;
            cout << "Generation: " << pokemon.generation;
            cout << "     Region: " << pokemon.region << endl;
            cout << "Name: " << pokemon.name << endl;
            cout << "Type: " << pokemon.type1;
            if (!pokemon.type2.empty()) {
                cout << "/" << pokemon.type2;
            }
            cout << endl;
            cout << "HP   ATK   DEF   SpA   SpD   Spe   TOTAL" << endl;
            cout << pokemon.hp << "   " << pokemon.atk << "    " << pokemon.def << "    " << pokemon.spAtk << "    " << pokemon.spDef << "    " << pokemon.spd << "     " << pokemon.total << endl;
            cout << "Ability 1: " << pokemon.ability1;
            if (!pokemon.ability2.empty()) {
                cout << "/" << pokemon.ability2;
            }if (!pokemon.abilityHidden.empty()) {
                cout << "      Hidden: " << pokemon.abilityHidden;
            }
            cout << endl;
            cout << "Effort Value: " << pokemon.ev << "   Gender Distribution: " << pokemon.gender << endl;
            cout << "Egg Group: " << pokemon.eg1;
            if (!pokemon.eg2.empty()) {
                cout << "/" << pokemon.eg2;
            }
            cout << endl;
            cout << "Catch: " << pokemon.catchNum << endl;
            cout << "Evolve: " << pokemon.evolution << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Not found. Try again." << endl;
    }
}