#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <list>
#include <vector>
#include "Card.cpp"
#include <random>
#include <array>
using namespace std;

class CardDeck{
// =================== INSTANCES  ===================
    public:
    std::vector<Card> unShuffledDeck;   // The deck before it is shuffled
    std::list<Card> shuffledDeck;       // The deck after it is shuffled
    int randomInt;                      // Random integer which aids in shuffling the deck
    int size;

// =================== CONSTRUCTOR  ===================
    CardDeck(){
        makeSuit(13, "C");
        makeSuit(13, "H");
        makeSuit(13, "D");
        makeSuit(13, "S");
        //shuffle();
    }
// =================== METHODS  ===================

    // This method takes a CardDeck and checks
    // how many elements (size) are in it.
    int getSize(){
        return this->size;
    }

    // This method makes a group of cards based on a suit
    void makeSuit(int numCards, std::string suit){
        for(int i=1; i<=numCards; i++){
            unShuffledDeck.emplace_back(i, suit, false);
            this->size++;
        }
    }

    // This method will print out the cards in the UN-SHUFFLED deck
    // @param cardDeck the deck we want to look at
    void viewUnShuffDeck(){
        for(int i=0; i<unShuffledDeck.size(); i++){
            Card temp = unShuffledDeck[i];
            cout << temp.toString() << ", ";
            if(i == unShuffledDeck.size()-1){
                cout << "<bottom of deck>" << endl;
            }
        }
    }

    // This method will print out the cards in the SHUFFLED deck
    // @param cardDeck the deck we want to look at
    void viewShuffDeck(){
        int shuffSize = shuffledDeck.size();
        for(int i=0; i<shuffSize; i++){
            Card temp = shuffledDeck.front();
            shuffledDeck.pop_front();
            shuffledDeck.push_back(temp);
            cout << temp.toString() << ", ";
            if(i == shuffSize-1){
                cout << "<bottom of deck>" << endl;
            }
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

    // This method gets a card from the SHUFFLED CardDeck according to its index.
    // Index 0 is the top of the deck, while n-1 is the bottom of the deck.
    // @return card a card from the shuffled deck
    Card getShuffCard(int index){
        std::list<Card>:: iterator itr = shuffledDeck.begin();
        if(index >= shuffledDeck.size() || index < 0){
            cout << "ERROR: The index is out of bounds." << endl;
        }
        else{
            advance(itr, index);
            return *itr;
        }
        cout << "ERROR: Reached non-reachable statement." << endl;
        Card card = *itr;
        cout << "ERROR: non-reach card at deck.begin is >> " << card.toString() << endl;
        return *itr;
    }

    // This method removes a card from the SHUFFLED CardDeck according to its index.
    // Index 0 is the top of the deck, while n-1 is the bottom of the deck.
    // @return true the card was removed from the deck
    bool removeShuffCard(int index){
        std::list<Card>:: iterator itr = shuffledDeck.begin();
        if(index >= shuffledDeck.size() || index < 0){
            cout << "ERROR: The index is out of bounds." << endl;
        }
        else{
            advance(itr, index);
            shuffledDeck.erase(itr);
            return true;
        }
        cout << "ERROR: Reached non-reachable statement: returning false" << endl;
        return false;
    }
};