// SECOND comparable algorithm
// quicksort or mergesort descending order usage rates and best counters in said generation (like no comparing gen 1 to gen 7)

// SECOND comparable algorithm
// Graph-based type effectiveness analyzer — finds best counter types and Pokémon in the same generation

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include "pokemon.h"
using namespace std;

// Graph class representing Pokémon type effectiveness
class TypeGraph {
private:
    unordered_map<string, vector<pair<string, float>>> adjList; // {attackerType -> [(defenderType, multiplier)]}

public:
    // Add edge: how effective one type is against another
    void addEdge(const string& from, const string& to, float multiplier) {
        adjList[from].push_back({to, multiplier});
    }

    // Get all counter types that are effective (> 1x damage)
    vector<string> getEffectiveCounters(const string& defenderType) {
        vector<string> counters;
        for (auto& [attackerType, edges] : adjList) {
            for (auto& [defender, multiplier] : edges) {
                if (defender == defenderType && multiplier > 1.0) {
                    counters.push_back(attackerType);
                }
            }
        }
        return counters;
    }
};

// Filters Pokémon by generation
vector<Pokemon> filterByGeneration(const vector<Pokemon>& all, int gen) {
    vector<Pokemon> result;
    for (const auto& p : all) {
        if (p.generation == gen)
            result.push_back(p);
    }
    return result;
}

// Generates test Pokémon (can be replaced with CSV import later)
vector<Pokemon> generateTestData() {
    return {
        {"Pikachu", "Electric", "", 55, 90, 0.0, 0.21, 1},
        {"Charizard", "Fire", "Flying", 84, 100, 0.0, 0.76, 1},
        {"Blastoise", "Water", "", 83, 78, 0.0, 0.64, 1},
        {"Venusaur", "Grass", "Poison", 82, 80, 0.0, 0.60, 1},
        {"Garchomp", "Dragon", "Ground", 130, 102, 0.0, 0.89, 4},
        {"Lucario", "Fighting", "Steel", 110, 90, 0.0, 0.55, 4},
        {"Greninja", "Water", "Dark", 103, 122, 0.0, 0.83, 6}
    };
}

int main() {
    // Build the type effectiveness graph
    TypeGraph g;
    g.addEdge("Water", "Fire", 2.0);
    g.addEdge("Electric", "Water", 2.0);
    g.addEdge("Grass", "Water", 2.0);
    g.addEdge("Ground", "Electric", 2.0);
    g.addEdge("Fire", "Grass", 2.0);
    g.addEdge("Rock", "Fire", 2.0);
    g.addEdge("Fighting", "Steel", 2.0);
    g.addEdge("Dark", "Psychic", 2.0);

    vector<Pokemon> allPokemons = generateTestData();

    string inputType;
    int genInput;

    cout << "Enter opponent's type: ";
    cin >> inputType;
    cout << "Enter generation to analyze: ";
    cin >> genInput;

    // Find effective counter types
    vector<string> counterTypes = g.getEffectiveCounters(inputType);

    if (counterTypes.empty()) {
        cout << "\nNo strong counters found for type: " << inputType << endl;
        return 0;
    }

    cout << "\nEffective counter types against " << inputType << ": ";
    for (const auto& type : counterTypes)
        cout << type << " ";
    cout << "\n\nTop Pokemon counters in Generation " << genInput << ":\n";

    // Filter Pokémon by generation
    vector<Pokemon> genFiltered = filterByGeneration(allPokemons, genInput);

    // Display Pokémon of effective counter types, sorted by usage rate (descending)
    vector<Pokemon> counters;
    for (const auto& p : genFiltered) {
        for (const auto& c : counterTypes) {
            if (p.type1 == c || p.type2 == c) {
                counters.push_back(p);
                break;
            }
        }
    }

    sort(counters.begin(), counters.end(), [](const Pokemon& a, const Pokemon& b) {
        return a.usageRate > b.usageRate;
    });

    if (counters.empty()) {
        cout << "No Pokemon in Generation " << genInput << " match counter types.\n";
    } else {
        for (const auto& p : counters) {
            cout << "- " << p.name << " (" << p.type1;
            if (!p.type2.empty()) cout << "/" << p.type2;
            cout << ") | Usage Rate: " << p.usageRate << endl;
        }
    }

    return 0;
}
