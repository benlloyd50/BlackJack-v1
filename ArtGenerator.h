#ifndef ARTGENERATOR_H
#define ARTGENERATOR_H
#include <string>
#include <vector>
#include "Card.h"

class ArtGenerator {
    public:
        void Intro();   //Just some ASCII Text I ripped from the web
        void DrawCard(Card c, std::vector<std::string>& d);    //Draw Individual Cards
        void DrawCardArray(std::vector<Card> v);    //Combine Individual Cards line by line
        std::string FindSuitSymbol(Card c);    //Creates the symbol of the suit
        std::string FindCardIdentity(Card c);   //Finds the identity of the card, ie num val or AJQK
};

#endif