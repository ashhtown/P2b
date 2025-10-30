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
    string ev;
    string gender; // "M/F (percentage)"
    string eg1; // egg group 1
    string eg2; // egg group 2
    int catchNum; // not entirely sure what this is atm
    string evolution; // what lvl they evolve at
    //int generation;
    //bool legendary;
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

        // total
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
        // gender
        getline(stream, pokemon.gender, ',');
        // egg group 1
        getline(stream, pokemon.eg1, ',');
        // egg group 2
        getline(stream, pokemon.eg2, ',');

        // catch
        getline(stream, temp, ',');
        pokemon.catchNum = stoi(temp);
        // evolves at
        getline(stream, pokemon.evolution, ',');

        /* generation
        getline(stream, temp, ',');
        pokemon.generation = stoi(temp);
        // legendary
        getline(stream, temp, ',');
        if (temp == "true"){pokemon.legendary = true;}
        else{pokemon.legendary = false;}*/

        // add your now initialized pokemon to the Pokedex vector!
        Pokedex.push_back(pokemon);
    }
}
