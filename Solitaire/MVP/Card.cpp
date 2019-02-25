#include <stdlib.h>     /* srand, rand */
#include <iostream>

class Card {
// =================== INSTANCES  ===================
    public:
    int num;            // the number/rank of the card
    std::string suit;   // the type/suit of the card
    bool isVis;         // whether the card is face up (true) or face down (false)

// =================== CONSTRUCTOR ===================
    Card(int number, std::string cardSuit, bool visible){
        num = number;
        suit = cardSuit;
        isVis = visible;
    }

// =================== METHODS ===================

// ------------------- ACCESSORS -------------------
    int getNum(){
        return num;
    }
};