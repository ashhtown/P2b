#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// #,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary [newline]
// 13 columns

struct Pokemon {
    int num;
    string name;
    string type1;
    string type2;
    int total;
    int hp;
    int atk;
    int def;
    int spAtk;
    int spDef;
    int spd;
    int generation;
    bool legendary;
};

void readFiles() {
    ifstream pokemonFile("pokemon.csv");
    string line;
    vector<Pokemon> Pokedex; // store pokemon objects (like a pokedex)
    getline(pokemonFile, line); // header

    while (getline(pokemonFile, line)) {
        istringstream stream(line);
        string temp;
        Pokemon pokemon;

        // read all data and assign to pokemon object
        // number
        getline(stream, temp, ',');
        pokemon.num = stoi(temp);
        // name
        getline(stream, pokemon.name, ',');
        // type 1
        getline(stream, pokemon.type1, ',');
        // type 2
        getline(stream, pokemon.type2, ',');
        // total
        getline(stream, temp, ',');
        pokemon.total = stoi(temp);
        // hp
        getline(stream, temp, ',');
        pokemon.hp = stoi(temp);
        // attack
        getline(stream, temp, ',');
        pokemon.atk = stoi(temp);
        // def
        getline(stream, temp, ',');
        pokemon.def = stoi(temp);
        // SP attack
        getline(stream, temp, ',');
        pokemon.spAtk = stoi(temp);
        // SP def
        getline(stream, temp, ',');
        pokemon.spDef = stoi(temp);
        // speed
        getline(stream, temp, ',');
        pokemon.spd = stoi(temp);
        // generation
        getline(stream, temp, ',');
        pokemon.generation = stoi(temp);
        // legendary
        getline(stream, temp, ',');
        if (temp == "true"){pokemon.legendary = true;}
        else{pokemon.legendary = false;}

        // add your now initialized pokemon to the Pokedex vector!
        Pokedex.push_back(pokemon);
    }
}
