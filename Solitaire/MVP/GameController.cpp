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
    int movedFlip, movedLower; // used for cardFlip method to check for if you lose the game
    int failCount;
    bool gameLost, gameWon;
    int visCount; // the number of lower cards we want to move as a group (used in lastVis method)
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
            shuffledDeck.swap(flipPile);
            shuffledDeck.reverse();
            // Check if there were any moves done since the last shuffle
            if((movedFlip == 0) && (movedLower == 0)){ // no moves = lose game
                failCount++;
                if(failCount > 2){
                    gameLost = true;
                }
            }
            else{ // moves = continue game
                movedFlip = 0;
                movedLower = 0;
                failCount = 0;
            }
        }
    }

    // ================ CHECK LOWER MOVE ====================
    bool checkLowerMove(int pile){
        int n = 0;
        // Make sure the pile integer is in range
        if(pile>=0 && pile<=6){
            //list<Card>::iterator itr; //-------------- NOT NEEDED
            // so long as the current pile is not empty...
            if(!lowerPiles[pile].empty()){
                Card lastVis = lastVisible(lowerPiles[pile]); // get the last visible card
                //itr = lowerPiles[pile].begin(); //-------------- NOT NEEDED
                //for each of the lower piles...
                for(int i=0; i<7; i++){
                    // so long as we are not comparing the pile to itself,
                    // and the pile we are comparing to is not empty,
                    // and the last visible card is not a king...
                    if((i!=pile) && (!lowerPiles[i].empty()) && (lastVis.getNum() != 13)){
                        // so long as the numbers of the cards are different by 1
                        // and the colors do not match...
                        if(lowerPiles[i].front().getNum() == lastVis.getNum()+1
                        && lowerPiles[i].front().isRed() != lastVis.isRed()){
                            moveCard(visCount, lowerPiles[pile],lowerPiles[i]);
                            return true;
                        }
                    }
                    // else If
                    // so long as we are not comparing the pile to itself,
                    // and the pile we are comparing to IS empty,
                    // and the last visible card is a king...
                    else if((i!=pile) && (lowerPiles[i].empty()) && (lastVis.getNum() == 13)){
                        moveCard(visCount, lowerPiles[pile],lowerPiles[i]);
                        return true;
                    }
                }
            }
            else{ // else if the pile we are thinking of moving is empty
                return checkLowerMove(pile -1);
            }
        }
        return false;
    }
    // ================ LAST VISIBLE CARD ====================
    Card lastVisible(std::list<Card>& pile){
        //int visCount = 0; //-------------- NOT NEEDED
        list<Card>::iterator itrVis = pile.begin();
        //if there is more than one card..
        if(pile.size()>1){
            for(itrVis=pile.begin(); itrVis!=pile.end();++itrVis){
                if(itrVis->getVisible() == true){
                    visCount++;
                }
                else{ // if you see a non-visible card
                    itrVis--; // go back one step, to where the visible card is
                    return *itrVis; // return the card
                }
            }
        }
        // else if there is 1 card
        else if(pile.size()==1){
            return *itrVis;
        }
        // else the pile is empty
        else{
            cout << "The pile is empty" << endl;
        }
        return pile.front();
    }

    // ====================== GET CARD ======================
    Card getCard(std::list<Card>& myList, int index){
        list<Card>::iterator it = myList.begin();
        for(int i=0; i<index; i++){
            ++it;
        }
        //--it;
        return *it;
    }
    // ======================= MOVE CARD ====================
    void moveCard(int numCards, list<Card>& source, list<Card>& dest)
    {
        //cout << "moveCard called " << endl;
        if (numCards == 1){  //If there is just one card it is moved to the destination pile and then it is remove from the source pile
            dest.push_front(source.front());
            source.pop_front();
        }
        else{ // If there is more than one card then the top card through numCards is spoliced from the source pile to the destination pile
            std::list<Card>::iterator it;
            it = source.begin();
            advance(it, numCards);
            source.splice(dest.begin(), source, source.begin(), it);
        }
        if(!source.front().getVisible())
            source.front().setVisible(true);
    }
    // =============== CHECK FLIP CARD ======================
    bool checkFlip(){
        int hasMovedFlip = 0;
        if(!flipPile.empty()){
            // get the flip-card and it's properties
            Card flipCard = flipPile.front();
            int fNum = flipCard.getNum();
            bool fRed = flipCard.isRed();
            // If the flipped card is an ace...
            if(fNum == 1){
                int moved = moveAceCardToAcePile(flipPile); // move it to the correct ace pile
                if(moved == 1){
                    hasMovedFlip++;
                }
            }
            // If the flipped card is a king...
            else if (fNum == 13){
                // Check the ace piles to see if it can fit there
                if((topDiamonds.front().getNum() == 12) && (flipCard.getSuit() == "D")){
                    moveCard(1, flipPile, topDiamonds);
                    hasMovedFlip++;
                }
                else if((topHearts.front().getNum() == 12) && (flipCard.getSuit() == "H")){
                    moveCard(1, flipPile, topHearts);
                    hasMovedFlip++;
                }
                else if((topSpades.front().getNum() == 12) && (flipCard.getSuit() == "S")){
                    moveCard(1, flipPile, topSpades);
                    hasMovedFlip++;
                }
                else if((topClubs.front().getNum() == 12) && (flipCard.getSuit() == "C")){
                    moveCard(1, flipPile, topClubs);
                    hasMovedFlip++;
                }
                else{// Else check to see if the king can fit into the lower piles
                    for(int i=0; i<7; i++){
                        if(lowerPiles[i].empty()){
                            moveCard(1, flipPile, lowerPiles[i]);
                            hasMovedFlip++;
                        }
                    }
                }
            }
            // Else if the number is neither an ace nor a king
            //else if(fNum > 1 && fNum < 13){
                // Check the lower piles
                for(int i=0; i<7; i++){
                    // if the lower pile is not empty,
                    // and the cards' numbers are diff by one,
                    // and the card of the lower pile is not 2,
                    // and the cards are not the same color
                    if((!lowerPiles[i].empty())
                        && (lowerPiles[i].front().getNum() == fNum + 1)
                        && (lowerPiles[i].front().getNum() != 2)
                        && (lowerPiles[i].front().isRed() != fRed)){
                            moveCard(1, flipPile, lowerPiles[i]);
                            hasMovedFlip++;
                    }
                }
                // Check the ace-piles
                if((topHearts.front().getNum() == fNum-1) && (flipCard.getSuit() == "H")){
                    moveCard(1, flipPile, topHearts);
                    hasMovedFlip++;
                }
                else if((topDiamonds.front().getNum() == fNum-1) && (flipCard.getSuit() == "D")){
                    moveCard(1, flipPile, topDiamonds);
                    hasMovedFlip++;
                }
                else if((topClubs.front().getNum() == fNum-1) && (flipCard.getSuit() == "C")){
                    moveCard(1, flipPile, topClubs);
                    hasMovedFlip++;
                }
                else if((topSpades.front().getNum() == fNum-1) && (flipCard.getSuit() == "S")){
                    moveCard(1, flipPile, topSpades);
                    hasMovedFlip++;
                }
            //}
            flipCard();
            if(hasMovedFlip != 0){
                return true;
            }
            return false;
        }
        flipCard();
        return false;
    }
    // ==================== MOVE TO ACE CARD TO ACE PILE =======================
    int moveAceCardToAcePile(std::list<Card>& pile){
        if(!pile.empty()){
            Card card = pile.front();
            if(card.getNum() == 1){ // if the card is an ace
                if(card.getSuit() == "D" && topDiamonds.empty()){
                    moveCard(1, pile, topDiamonds);
                    return 1;
                }
                else if(card.getSuit() == "S" && topSpades.empty()){
                    moveCard(1, pile, topSpades);
                    return 1;
                }
                else if(card.getSuit() == "H" && topHearts.empty()){
                    moveCard(1, pile, topHearts);
                    return 1;
                }
                else{
                    if(topClubs.empty()){
                        moveCard(1, pile, topClubs);
                        return 1;
                    }
                }
            }
            return 0;
        }
        return 0;
    }
};