//
// Created by Taj Miller on 11/2/25.
//

#ifndef POKEMON_H
#define POKEMON_H
#pragma once

#include <string>
using namespace std;
#include <vector>

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

#endif //POKEMON_H
