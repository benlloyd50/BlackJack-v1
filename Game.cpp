#include <iostream>
#include "Game.h"

Game::Game() { 
    _deck.clear();
    pHand.clear();
    dHand.clear();
    _deck = PopulateDeck();
    srand(time(0));
    ag = ArtGenerator();
}

int Game::CalcHandTotal(char who) {
    std::vector<Card> tempDeck;
    
    if(who == player)
        tempDeck = pHand;
    else if(who == dealer)
        tempDeck = dHand;

    int sum = 0;

    for(int i = 0; i < tempDeck.size(); i++) {
        sum += tempDeck.at(i).GetValue();
    }

    return sum;
}

void Game::ShowHand(char who) {
    std::vector<Card> tempDeck;
    std::string name = "";
    if(who == player) { 
        tempDeck = pHand;
        name = "Player";
    }
    else if(who == dealer) { 
        tempDeck = dHand;
        name = "Dealer";
    }

    std::cout << "=" << name << "'s Cards=====================\n"; 

    ag.DrawCardArray(tempDeck);

    std::cout << "====================================\n";

    if(!HasAceCard(tempDeck))
        std::cout << name << "\'s cards are worth " << CalcHandTotal(who) << std::endl;
    else if(HasAceCard(tempDeck) > 0) {
        int tempSum = CalcHandTotal(who);
        std::cout << name << "\'s cards are worth " << tempSum << " or with ace high " << (tempSum + 10) << std::endl;
    }
}

int Game::Dealer() {
    //Dealer uses the traditional Bicycle logic to try and beat the player
    DrawCard(dealer);
    if(CalcHandTotal(dealer) > 16) {
        return Stand(dealer);
    }
    else if(CalcHandTotal(dealer) < 17) {
        int acehigh = ( CalcHandTotal(dealer) + 10 );
        if(HasAceCard(dHand) && acehigh >= 17 && acehigh < 22 ) {
            return Stand(dealer);
        }
        else {
            return Dealer();
        }
    }
    return Dealer(); 
}

bool Game::DidYouBust(char who) {
    if(CalcHandTotal(who) > 21) 
        return true;
    else 
        return false;
}

int Game::Stand(char who) {
    std::vector<Card> tempDeck;
    if(who == player)
        tempDeck = pHand;
    else if(who == dealer)
        tempDeck = dHand;
    
    int total = CalcHandTotal(who);
    
    if(HasAceCard(tempDeck)){
        char tempChoice;
        if(who == 'p') {
            std::cout << "Are you playing ace low or high (H/L)";
            std::cin >> tempChoice;
        }
        if(toupper(tempChoice) == 'H' || who == 'd') {
            return ( total + 10 );
        }
        else if(toupper(tempChoice) == 'L') {
            return total;
        }
        else {
            Stand(who); 
        }
    }
    return total;
    
}


bool Game::HasAceCard(std::vector<Card> v) {
    for(int i = 0; i < v.size(); i++) {
        if(v.at(i).GetType() == 'A') {
            return true;
        }
    }
    return false;
}

void Game::DrawCard(char who) {
    int deckDraw = rand() % _deck.size();

    if(who == player) 
        pHand.push_back(_deck.at(deckDraw));  
    else if(who == dealer) 
        dHand.push_back(_deck.at(deckDraw)); 
    
    _deck.erase(_deck.begin() + deckDraw);
}

void Game::DrawCard(char who, int amt) {
    for(int i = 0; i < amt; i++)
        DrawCard(who);
}

//Some coupled logic to the card class
std::vector<Card> Game::PopulateDeck() {
    std::vector<Card> tempDeck;
    char cSuit;
    for (int suit = 1; suit < 5; suit++) {
        for (int i = 1; i < 14; i++) {
            switch(suit) {
                case 1:
                    cSuit = 'D';
                    break;
                case 2:
                    cSuit = 'C';
                    break;
                case 3:
                    cSuit = 'S';
                    break;
                case 4:
                    cSuit = 'H';
                    break;
            }
            Card tempCard = Card(i, cSuit);            
            tempDeck.push_back(tempCard);
        }
    }
    return tempDeck;
}


char Game::DecideWinner() {
    int pTotal = Stand(player);
    //Play the Dealer's Turn
    int dTotal = Dealer();

    //Decide the winner
    if( ( dTotal > pTotal && dTotal <= 21 ) || ( dTotal < pTotal && pTotal > 21 ) ) {
        std::cout << "\nThe dealer wins! and you had  " << pTotal << std::endl;
        ShowHand(dealer);
        return dealer;
    }
    else if( ( pTotal > dTotal && pTotal <= 21 ) || ( pTotal < dTotal && dTotal > 21 ) ) {
        std::cout << "\nYou win! and the dealer had " << dTotal << std::endl;
        ShowHand(player);
        return player;
    }
    else {
        std::cout << "\nStalemate, no winner this round." << std::endl;
        ShowHand(player);
        ShowHand(dealer);
        return ' ';
    }
}

