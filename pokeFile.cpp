#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// Nat,Pokemon,HP,Atk,Def,SpA,SpD,Spe,Total,Type I,Type II,Ability I,Ability II,Hidden Ability,
// EV Worth,Gender,Egg Group I,Egg Group II,Catch,Evolve
// 20 columns

struct Pokemon {
    //string imgURL; // http://www.serebii.net/xy/pokemon/[Pokemon.num].png  -  have to figure out how to do that in SFML :3
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
    string gender; // "M/F (percentage)" MAYBE DON'T DISPLAY, IRRELEVANT
    string eg1; // egg group 1 MAYBE DON'T DISPLAY, IRRELEVANT
    string eg2; // egg group 2 MAYBE DON'T DISPLAY, IRRELEVANT
    string catchNum; // MAYBE DONT DISPLAY, IRRELEVANT
    string evolution; // condition/s to evolve
    int generation;
    string region; // first region in which it appears

    // from gen[N].csv
    //int rank;
    double usage;

    // from gen[N]moveset.csv
    vector<string> ctWtVc, abilities, items, spreads, moveRates, teraTypes, teamRates, checksCounters;
    vector<vector<string>> movesetData= {ctWtVc, abilities, items, spreads, moveRates, teraTypes, teamRates, checksCounters};
};

map<string, double> assignUsage() { // currently gen 1 only
    ifstream usageFile("../gen1.csv");
    string line, name;
    int rank;
    double usage;
    getline(usageFile, line); // header
    map<string, double> stats; // format: <string Name, [rank, usage%]>
    while (getline(usageFile, line)) {
        istringstream stream(line);
        string temp;
        getline(stream, temp, ',');
        rank = stoi(temp);
        getline(stream, name, ',');
        getline(stream, temp, '%');
        usage = stod(temp);
        stats.insert({name, usage});
    }
    return stats;
}

map<string, vector<vector<string>>> readMovesetFiles() { // gen 1 only rn
    map<string, vector<vector<string>>> moveset; // format: <Name, [ vec1[Moves-Teammates, move usage rates], vec2[Teammates, Checks and Counters, team usage rates] ]
    vector<string> gens = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    //string genFile = "../POKEDATA - gen" + gens[i] + "moveset.csv"
    ifstream movesetFile("../POKEDATA - gen1moveset.csv");
    string line, temp; // temp fix for name issue
    int ctLines = 0;
    while (getline(movesetFile, line)) { // no header
        istringstream stream(line);
        string name;

        // all below go into movesetData;
        vector<vector<string>> movesetData;
        vector<string> ctWtVc, abilities, items, spreads, moveRates, teraTypes, teamRates, checksCounters;

        if (ctLines > 0) {
            name = temp;
        }else {
            name = line;
            ctLines++;
            getline(movesetFile, line, '\n');
        }
        while (line != "Abilities") { // 3 lines after name
            ctWtVc.push_back(line);
            getline(movesetFile, line, '\n');
        }
        movesetData.push_back(ctWtVc);

        getline(movesetFile, line, '\n'); // "Abilities"
        while (line != "Items") {
            abilities.push_back(line);
            getline(movesetFile, line, '\n');
        }
        movesetData.push_back(abilities);

        getline(movesetFile, line, '\n'); // "Items"
        while (line != "Spreads") {
            items.push_back(line);
            getline(movesetFile, line, '\n');
        }
        movesetData.push_back(items);

        getline(movesetFile, line, '\n'); // "Spreads"
        while (line != "Moves") {
            spreads.push_back(line);
            getline(movesetFile, line, '\n');
        }
        movesetData.push_back(spreads);

        getline(movesetFile, line, '\n'); // "Moves"
        while (line != "Tera Types") {
            moveRates.push_back(line);
            getline(movesetFile, line, '\n');
        }
        movesetData.push_back(moveRates);

        getline(movesetFile, line, '\n'); // "Tera Types"
        while (line != "Teammates") {
            teraTypes.push_back(line);
            getline(movesetFile, line, '\n');
        }
        movesetData.push_back(teraTypes);

        getline(movesetFile, line, '\n'); // "Teammates"
        while (line != "Checks and Counters") {
            teamRates.push_back(line);
            getline(movesetFile, line, '\n');
        }
        movesetData.push_back(teamRates);

        // used temp fix here
        getline(movesetFile, line, '\n');
        while (line.find(")") != string::npos) {
            checksCounters.push_back(line);
            getline(movesetFile, line, '\n');
            temp = line;
        }

        movesetData.push_back(checksCounters);

        moveset.insert({name, movesetData});
    }
    return moveset;
}

vector<Pokemon> readPokeFiles() {
    ifstream pokemonFile("../pokemon.csv");
    string line, temp;

    vector<Pokemon> Pokedex; // store pokemon objects (like a pokedex)
    map<string, double> stats = assignUsage();
    map<string, vector<vector<string>>> moveset = readMovesetFiles();
    map<string, vector<vector<string>>>::iterator mvIT;

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
        pokemon.usage = stats[pokemon.name];

        mvIT = moveset.find(pokemon.name);
        if (mvIT != moveset.end()) { // https://cplusplus.com/reference/map/
            pokemon.movesetData = mvIT->second;
            pokemon.ctWtVc = mvIT->second[0];
            pokemon.abilities = mvIT->second[1];
            pokemon.items = mvIT->second[2];
            pokemon.spreads = mvIT->second[3];
            pokemon.moveRates = mvIT->second[4];
            pokemon.teraTypes = mvIT->second[5];
            pokemon.teamRates = mvIT->second[6];
            pokemon.checksCounters = mvIT->second[7];
        }

        // add your now initialized pokemon to the Pokedex vector!
        Pokedex.push_back(pokemon);
    }
    pokemonFile.close();
    return Pokedex;
}

void display(vector<Pokemon>& Pokedex, string& name) {
    bool found = false;
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
            cout << "Usage Rate: " << pokemon.usage << "%" << endl;
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

            // ctWtVc, abilities, items, spreads, moveRates, teraTypes, teamRates, checksCounters
            if (!pokemon.movesetData[0].empty()) {
                for (int i = 0; i < 3; i++) {
                    cout << '\n' << pokemon.ctWtVc[i] << endl;
                }
                cout << "\n" << "Moves: " << endl;
                for (const auto& i : pokemon.moveRates) {
                    cout << i << endl;
                }
                cout << "\n" << "Teammates: " << endl;
                for (const auto& i : pokemon.teamRates) {
                    cout << i << endl;
                }
                cout << "\n" << "Checks and Counters: " << endl;
                for (const auto& i : pokemon.checksCounters) {
                    cout << i << endl;
                }
            }

            found = true;
        }
    }
    if (!found) {
        cout << "Not found. Try again." << endl;
    }
}

// using battle data
void compare(string& pokemon1, string& pokemon2) {
    // enter pokemon names in separate fields, press one button to enter
    // list usage rates and best counters from over 100,000 battles

}