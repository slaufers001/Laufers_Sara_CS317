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
        this->num = number;
        this->suit = cardSuit;
        this->isVis = visible;
    }

// =================== METHODS ===================

// ------------------- ACCESSORS -------------------
    // This method returns the number/rank of the card
    // @return num the number/rank of the card
    int getNum(){
        return this->num;
    }

    // This method returns the suit/type of the card
    // @return suit the suit of the card
    std::string getSuit(){
        return this->suit;
    }

    // This method returns whether the card is visible (true) or not (false)
    // @return isVis the visibility of the card
    bool getVisible(){
        return this->isVis;
    }

// ------------------- MUTATORS -------------------

    // This method sets the visibility of the card to true
    void setVisible(bool visibilty){
        this->isVis = visibilty;
    }

    // This method compares this card to another card and sees if they can
    // be placed on top of one another.
    // @return true the cards can be placed on one another (otherCard on this card)
    // @return false the cards cannot be placed on one another
    bool compareCard(Card otherCard){
        if((this->num = otherCard.getNum()+1) &&
            this->isRed() != otherCard.isRed()){
                return true;
        }
        else{
            return false;
        }
    }

    // This method return a boolean telling if this card is red (true) or not (false)
    // @return true the card is red
    // @return false the card is black or another color
    bool isRed(){
        if((this->suit == "H") || (this->suit == "D")){ // If this card is a heart or a diamond, the card is red
            return true;
        }
        else if((this->suit) == "C" || (this->suit == "S")){ // If this card is a Club or a Spade, the card is not red
            return false;
        }
        else{
            return bool(nullptr);
        }
    }

    std::string toString(){
        return std::to_string(num) + suit + std::to_string(this->isVis) + "\n";
    }
};