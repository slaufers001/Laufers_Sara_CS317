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

    // ============== CONSTRUCTORS ==================
    GameController(){
        initSolitaire();
        run();
    }
};