// Declaration file
#include <string>

// Needs a constructor that takes 1 or more parameteres
// Has a default (parameterless) constructor
// Has private variables and functions
// Has a public getter and setter function
class Pokemon {
public: 
    Pokemon();
    Pokemon(std::string type, std::string species);
    std::string getSpecies() const;
    int getHp() const;
    void setHp(int hp);
private:
    int hp, level;
    std::string type, species;
    void setSpecies(std::string species);
};