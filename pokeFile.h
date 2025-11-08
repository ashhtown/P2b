//
// Created by BJayJ on 11/8/2025.
//

#ifndef POKEFILE_H
#define POKEFILE_H
#pragma once
#include <vector>
#include <string>
#include "pokemon.h"

std::vector<Pokemon> readPokeFiles();
void display(const std::vector<Pokemon>& Pokedex, const std::string& name);

#endif //POKEFILE_H
