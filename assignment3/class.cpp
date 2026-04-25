// Definition file
#include "class.h"

Pokemon::Pokemon() {
    level = 1;
    hp = 100;
    species = "Pikachu";
    type = "Electric";
}

Pokemon::Pokemon(std::string type, std::string species) {
    this->type = type;
    this->species = species;
    level = 1;
    hp = 100;
}

std::string Pokemon::getSpecies() const {
    return species;
}

int Pokemon::getHp() const {
    return hp;
}

void Pokemon::setHp(int hp) {
    this->hp = hp;
}

void Pokemon::setSpecies(std::string species) {
    this->species = species;
}