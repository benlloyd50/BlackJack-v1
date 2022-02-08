#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include <random>
#include "Card.h"
#include "ArtGenerator.h"

class Game {
    public:
        Game();    //Creates the game and resets all variables
        std::vector<Card> PopulateDeck();   //Populates the initial deck with all 52 cards
        void DrawCard(char who);    //Randomly draws a card based on deck size and adds it to (who)'s deck
        void DrawCard(char who, int amt);
        void ShowHand(char who);    //Displays (who)'s hand
        int CalcHandTotal(char who);    //Calcs the hand of the person(who)
        bool DidYouBust(char who);      //Checks if the player(who) has more than 21 pts
        bool HasAceCard(std::vector<Card> v);    //Checks if (v) contains an Ace Card
        int Stand(char who);    //Saves Hand Total of (who)
        int Dealer();    //Plays the dealer turn and returns his hand total
        char DecideWinner();    //Declares a winner and returns their identity through a char
        
        //Test Methods NOT USED IN ACTUAL GAME ONLY FOR TESTING DONT GET THEM CONFUSED
        void TestShowDeck();    //Displays the deck, ONLY FOR TESTING
    private:
        std::vector<Card> _deck;    //The Deck
        std::vector<Card> pHand;    //Player's Hand
        std::vector<Card> dHand;    //Dealer's Hand
        int pTotal = 0;
        int dTotal = 0;
        ArtGenerator ag;
};

#endif