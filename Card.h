#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

class Card {
    public:
        Card(int val, char suit);
        void PrintTextCard();   //Prints a text version of the playing cards
        int GetValue();
        char GetSuit();
        char GetType();
    private:
        int value;
        char suit;
        char type;
};

#endif