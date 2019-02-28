#include "CardDeck.cpp"
#include <vector>
#include <stdlib.h>
#include <stack>
#include <set>
#include <iostream>
#include <array>
#include <string>
#include <chrono>
using namespace std;

class GameController{
    // ============== INSTANCES ==================
    public:
    CardDeck deck;
    std::list<Card> shuffledDeck;
    std::array<list<Card>,7> lowerPiles;
    std::list<Card> topDiamonds, topSpades, topHearts, topClubs;
    std::list<Card> flipPile;
    // ============== CONSTRUCTORS ==================
    GameController(){
        initSolitaire();
        run();
    }

    // ============== INIT SOLITAIRE ==================
    // This method initializes/sets up the solitaire game
    void initSolitaire(){
        //set up the shuffled deck
        deck = CardDeck();
        shuffledDeck = deck.shuffledDeck;
        //set up the lower piles
        for(int i=0; i<7; i++){
            lowerPiles[i] = makePile(i+1);
        }
    }
    // ============== MAKE PILE ==================
    // This method makes a pile for the lowerPiles
    // @param numCards the number of cards (1-7) that the pile will have
    std::list<Card> makePile(int numCards){
        std::list<Card> pile;
        // transfer numCards from the shuffled deck to the pile
        for(int i=0; i<numCards; i++){
            pile.push_front(shuffledDeck.front());
            shuffledDeck.pop_front();
        }
        // set the front card of this pile to visible
        pile.front().setVisible(true);
        return pile;
    }
    // ============== MAKE PILE ==================
    // This method flips a card from the shuffled deck to the flip pile.
    void flipCard(){
        if(!shuffledDeck.empty()){ // if the deck is not empty
            //transfer the top card of the shuffled deck to the flip pile
            flipPile.push_front(shuffledDeck.front());
            shuffledDeck.pop_front();
            flipPile.front().setVisible(true);
        }
        else{ // if the deck is empty

        }
    }
};