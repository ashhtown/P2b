//
// Created by Taj Miller on 11/2/25.
//

#ifndef POKEMON_H
#define POKEMON_H

#include <string>

struct Pokemon {
    std::string name;
    std::string type1;
    std::string type2;
    int attack;
    int speed;
    float score = 0.0;
    float usageRate = 0.0;
    int generation = 1;

    // For max heap comparison
    bool operator<(const Pokemon& other) const {
        return score < other.score;
    }
};

#endif //POKEMON_H
