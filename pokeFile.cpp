#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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

    // functions
    // For max heap comparison
    bool operator<(const Pokemon& other) const {
        return usage < other.usage;
    }
};

map<string, double> assignUsage() { // currently gen 1 only
    map<string, double> stats; // format: <string Name, usage%]>
    vector<string> gens = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    for (const auto& gen : gens) {
        string filename = "../data CSVs/gen" + gen + ".csv";
        ifstream usageFile(filename);
        string line, name;
        int rank;
        double usage;
        getline(usageFile, line); // header
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
    }
    return stats;
}

map<string, vector<vector<string>>> readMovesetFiles() { // gen 1 only rn
    map<string, vector<vector<string>>> moveset; // format: <Name, [ vec1[Moves-Teammates, move usage rates], vec2[Teammates, Checks and Counters, team usage rates] ]
    vector<string> gens = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    //vector<string> gens = {"9"};
    for (const auto& gen : gens) {
        string filename = "../data CSVs/POKEDATA - gen" + gen + "moveset.csv";
        ifstream movesetFile(filename);
        string line, temp; // temp fix for name issue
        int ctLines = 0;
        while (getline(movesetFile, line)) {
            // no header
            istringstream stream(line);
            string name;

            // all below go into movesetData;
            vector<vector<string>> movesetData;
            vector<string> ctWtVc, abilities, items, spreads, moveRates, teraTypes, teamRates, checksCounters;

            if (ctLines > 0) {
                name = temp;
            }else {
                name = line;
                temp = name;
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
            }
            temp = line;

            movesetData.push_back(checksCounters);

            moveset.insert({name, movesetData});
        }
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
        }else {
            //moveset[pokemon.name, pokemon.movesetData];
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
            if (pokemon.usage > 0) {
                cout << "OU Usage Rate: " << pokemon.usage << "%" << endl;
            }else {
                cout << "Usage Rate: 0% in OU tier competitive play." << endl;
            }
            cout << "HP   ATK   DEF   SpA   SpD   Spe   TOTAL" << endl;
            cout << pokemon.hp << "   " << pokemon.atk << "    " << pokemon.def << "    " << pokemon.spAtk << "    " << pokemon.spDef << "    " << pokemon.spd << "     " << pokemon.total << endl;
            cout << "Ability 1: " << pokemon.ability1;
            if (!pokemon.ability2.empty()) {
                cout << endl << "Ability 2:" << pokemon.ability2;
            }
            cout << endl;
            if (!pokemon.abilityHidden.empty()) {
                cout << "Hidden Ability: " << pokemon.abilityHidden;
            }else {
                cout << "No Hidden Ability" << endl;
            }
            cout << endl;
            //cout << "Effort Value: " << pokemon.ev << "   Gender Distribution: " << pokemon.gender << endl;
            //cout << "Egg Group: " << pokemon.eg1;
            // if (!pokemon.eg2.empty()) {
            //     cout << "/" << pokemon.eg2;
            // }
            //cout << endl << "Catch: " << pokemon.catchNum << endl;
            //cout << "Evolve: " << pokemon.evolution << endl << endl;

            // ctWtVc, abilities, items, spreads, moveRates, teraTypes, teamRates, checksCounters
            if (!pokemon.movesetData[0].empty()) { // if pokemon is used in OU tier (has moveset data)
                for (int i = 0; i < 3; i++) {
                    cout << pokemon.ctWtVc[i] << endl;
                }
                cout << "\n" << "Moves: " << endl;
                for (const auto& i : pokemon.moveRates) {
                    cout << i << endl;
                }
                cout << "\n" << "Teammates: " << endl;
                for (const auto& i : pokemon.teamRates) {
                    cout << i << endl;
                }
                if (!pokemon.checksCounters.empty()) {
                    cout << "\n" << "Checks and Counters: " << endl;
                    for (const auto& i : pokemon.checksCounters) {
                        //replace(i.begin(), i.end(), "±", "+/-");
                        cout << i << endl;
                    }
                }
                cout << endl;
            }

            found = true;
        }
    }
    if (!found) {
        cout << "Not found. Try again." << endl;
    }
}


// Filters Pokémon by generation
std::vector<Pokemon> filterByGeneration(const std::vector<Pokemon>& all, int gen) {
    std::vector<Pokemon> result;
    for (const auto& p : all) {
        if (p.generation == gen)
            result.push_back(p);
    }
    return result;
}

// Filters Pokémon by type
std::vector<Pokemon> filterByType(const std::vector<Pokemon>& all, string type) {
    std::vector<Pokemon> result;
    for (const auto& p : all) {
        if (p.type1 == type)
            result.push_back(p);
    }
    return result;
}

// QuickSort helper for partitioning based on usage rate
int partition(std::vector<Pokemon>& arr, int low, int high) {
    float pivot = arr[high].usage;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].usage > pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive QuickSort using usage rate in descending order
void quickSort(std::vector<Pokemon>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Merge function for MergeSort
void merge(std::vector<Pokemon>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Pokemon> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].usage >= R[j].usage) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Recursive MergeSort on usage rate, descending
void mergeSort(std::vector<Pokemon>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Maintains max-heap property for usage rate
void heapify(std::vector<Pokemon>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].usage > arr[largest].usage)
        largest = left;

    if (right < n && arr[right].usage > arr[largest].usage)
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// HeapSort to sort Pokémon by usage rate in descending order
void heapSort(std::vector<Pokemon>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

    std::reverse(arr.begin(), arr.end());
}

// int main() {
//     std::vector<Pokemon> allPokemons = generateTestData();
//
//     // QuickSort test
//     std::vector<Pokemon> gen1_quick = filterByGeneration(allPokemons, 1);
//     std::cout << "Gen 1 Pokémon BEFORE QuickSort:\n";
//     for (const auto& p : gen1_quick)
//         std::cout << "- " << p.name << " (Usage Rate: " << p.usageRate << ")\n";
//
//     quickSort(gen1_quick, 0, gen1_quick.size() - 1);
//     std::cout << "\nGen 1 Pokémon AFTER QuickSort:\n";
//     for (const auto& p : gen1_quick)
//         std::cout << "- " << p.name << " (Usage Rate: " << p.usageRate << ")\n";
//
//     // MergeSort test
//     std::vector<Pokemon> gen1_merge = filterByGeneration(allPokemons, 1);
//     mergeSort(gen1_merge, 0, gen1_merge.size() - 1);
//     std::cout << "\nGen 1 Pokémon AFTER MergeSort:\n";
//     for (const auto& p : gen1_merge)
//         std::cout << "- " << p.name << " (Usage Rate: " << p.usageRate << ")\n";
//
//     // HeapSort test
//     std::vector<Pokemon> gen1_heap = filterByGeneration(allPokemons, 1);
//     heapSort(gen1_heap);
//     std::cout << "\nGen 1 Pokémon AFTER HeapSort:\n";
//     for (const auto& p : gen1_heap)
//         std::cout << "- " << p.name << " (Usage Rate: " << p.usageRate << ")\n";
//
//     return 0;
// }