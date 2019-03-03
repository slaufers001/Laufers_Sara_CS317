#include "CardDeck.cpp" // also contains Card.cpp
#include <stdlib.h>
#include <iostream>
#include <array>
#include <list>
#include <stack>
#include <set>
#include <random>
using namespace std;

class Test{
    public:
    CardDeck cardDeck;

    Test(){
        test_GetSize_UnshuffledDeck();
        test_ViewUnShuffDeck();
        test_Shuffle();
        test_ViewShuffDeck();
        test_getShuffCard();
        test_removeShuffCard();
    }

    //====================================== TEST METHODS OF CARD DECK ======================================
    void test_GetSize_UnshuffledDeck(){
        cout << "======== Now testing: check the un-shuffled deck's size ========" << endl;
        int deckSize = cardDeck.getSize();
        cout << "Size of the un-shuffled deck is " + to_string(deckSize) << endl;
    }

    void test_ViewUnShuffDeck(){
        cout << "======== Now testing: view the contents of the unshuffled deck ========" << endl;
        cardDeck.viewUnShuffDeck();
    }

    void test_Shuffle(){
        cout << "======== Now testing: shuffling the un-shuffled deck ========" << endl;
        cardDeck.shuffle();
    }

    void test_ViewShuffDeck(){
        cout << "======== Now testing: view the contents of the shuffled deck ========" << endl;
        cardDeck.viewShuffDeck();
    }
    //====================================== TEST METHODS OF CARD ======================================
    void test_getShuffCard(){
        cout << "======== Now testing: getting the card at a certain index ========" << endl;
        int index = 2;
        Card card = cardDeck.getShuffCard(index);
        cout << "Card at index " << to_string(index) << " is " << card.toString() << endl;
    }

    void test_removeShuffCard(){
        int index = 0;
        cout << "======== Now testing: removing the card at a certain index ========" << endl;
        cout << "*** Shuffled Deck Before... ***" << endl;
        cardDeck.viewShuffDeck();
        cout << "*** removing card " << cardDeck.getShuffCard(0).toString() << " at index " << index << " ***" << endl;
        cardDeck.removeShuffCard(index);
        cout << "*** Shuffled Deck After... ***" << endl;
        cardDeck.viewShuffDeck();
    }
};

int main(){
    new Test();
    return 0;
}