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

class Test{
    public:
    CardDeck cardDeck;

    Test(){
        // test
        test_GetSize_UnshuffledDeck();
        test_ViewUnShuffDeck();
        test_Shuffle();
        test_ViewShuffDeck();
        test_getShuffCard();
        test_removeShuffCard();
        test_getNum();
        test_getSuit();
        test_getVisibile();
        test_setVisibile();
        test_setNotVisibile();
    }

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

    void test_getNum(){
        cout << "======== Now testing: getting the number of the card ========" << endl;
        Card aCard = cardDeck.getShuffCard(0);
        cout << "The number of card " << aCard.toString() << " is " << aCard.getNum() << endl;
    }

    void test_getSuit(){
        cout << "======== Now testing: getting the suit of the card ========" << endl;
        Card aCard = cardDeck.getShuffCard(0);
        cout << "The suit of card " << aCard.toString() << " is " << aCard.getSuit() << endl;
    }

    void test_getVisibile(){
        cout << "======== Now testing: getting the visibility of the card ========" << endl;
        Card aCard = cardDeck.getShuffCard(0);
        cout << "The visibility of card " << aCard.toString() << " is " << aCard.getVisible() << endl;
    }

    void test_setVisibile(){
        cout << "======== Now testing: setting the visibility of the card to true(1) ========" << endl;
        Card aCardB = cardDeck.getShuffCard(0);
        Card aCardA = cardDeck.getShuffCard(0);
        aCardA.setVisible();
        cout << "The visibility of card " << aCardB.toString() << " is now " << aCardA.toString() << endl;
    }

    void test_setNotVisibile(){
        cout << "======== Now testing: setting the visibility of the card to false(0) ========" << endl;
        Card aCardBefore = cardDeck.getShuffCard(0);
        Card aCardAfter = cardDeck.getShuffCard(0);
        aCardAfter.setNotVisible();
        cout << "The visibility of card " << aCardBefore.toString() << " is now " << aCardAfter.toString() << endl;
    }
};

int main(){
    new Test();
    return 0;
}