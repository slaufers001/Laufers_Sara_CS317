#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <list>
#include "Card.cpp"
#include<random>

class CardDeck{
// =================== INSTANCES  ===================
    public:
    std::vector<Card> unShuffledDeck;   // The deck before it is shuffled
    std::list<Card> shuffledDeck;       // The deck after it is shuffled
    int randomInt;                      // Random integer which aids in shuffling the deck

// =================== CONSTRUCTOR  ===================
    CardDeck(){
        makeSuit(13, "C");
        makeSuit(13, "S");
        makeSuit(13, "H");
        makeSuit(13, "D");
    }
// =================== METHODS  ===================

    // This method makes a suit of cards depending on the number
    // of cards you want as well as the type of suit you want.
    // @param numCards the number of cards you want (usually 13)
    // @param suit the suit you want the card to be
    void makeSuit(int numCards, std::string suit){
        for(int i = 1; i <= numCards; i = i + 1){
            unShuffledDeck.emplace_back(i, suit, false);
        }
    }

    // This method shuffles the deck using the original fisher yates theory
    // @return
    std::list<Card> shuffle(){
        for(int i = unShuffledDeck.size(); i > 0; i--){
            srand(time(NULL));
            randomInt = rand() % unShuffledDeck.size();
            Card temp = unShuffledDeck[randomInt];
            shuffledDeck.push_back(temp);
            unShuffledDeck.erase(unShuffledDeck.begin() + randomInt);
        }
        return shuffledDeck;
    }
};