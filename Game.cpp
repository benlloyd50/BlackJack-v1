#include <iostream>
#include "Game.h"

Game::Game() { 
    _deck.clear();
    pHand.clear();
    dHand.clear();
    _deck = PopulateDeck();
    srand(time(0));
    ag = ArtGenerator();
    pTotal = 0;
    dTotal = 0;
}

int Game::CalcHandTotal(char who) {
    std::vector<Card> tempDeck;
    if(who == 'p') { tempDeck = pHand; }
    else if(who == 'd') { tempDeck = dHand; }

    int sum = 0;

    for(int i = 0; i < tempDeck.size(); i++) {
        sum += tempDeck.at(i).GetValue();
    }

    return sum;
}

void Game::ShowHand(char who) {
    std::vector<Card> tempDeck;
    std::string name = "";
    if(who == 'p') { 
        tempDeck = pHand;
        name = "Player";
    }
    else if(who == 'd') { 
        tempDeck = dHand;
        name = "Dealer";
    }

    std::cout << "=" << name << "'s Cards=====================\n"; 
    /*
    for (int i = 0; i < tempDeck.size(); i++) {
        tempDeck.at(i).PrintTextCard(); 
    }
    */

    ag.DrawCardArray(tempDeck);

    std::cout << "====================================\n";

    if(!HasAceCard(tempDeck))
        std::cout << "Cards are worth " << CalcHandTotal(who) << std::endl;
    else if(HasAceCard(tempDeck) > 0) {
        int tempSum = CalcHandTotal(who);
        std::cout << "Cards are worth " << tempSum << " or with ace high " << (tempSum + 10) << std::endl;
    }

}

int Game::Dealer() {
    char d = 'd';

    //Dealer uses the traditional Bicycle logic to try and beat the player
    DrawCard(d);
    if(CalcHandTotal(d) > 16) {
        return Stand(d);
    }
    else if(CalcHandTotal(d) < 17) {
        int acehigh = ( CalcHandTotal(d) + 10 );
        if(HasAceCard(dHand) && acehigh >= 17 && acehigh < 22 ) {
            return Stand(d);
        }
        else {
            return Dealer();
        }
    }
    return Dealer(); 
}

bool Game::DidYouBust(char who) {
    if(CalcHandTotal(who) > 21) {
        return true;
    }
    else {
        return false;
    }

}

int Game::Stand(char who) {
    std::vector<Card> tempDeck;
    if(who == 'p') { tempDeck = pHand; }
    else if(who == 'd') { tempDeck = dHand; }
    
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
    if(who == 'p') { 
        pHand.push_back(_deck.at(deckDraw));  
    }
    else if(who == 'd') { 
        dHand.push_back(_deck.at(deckDraw)); 
    }
    _deck.erase(_deck.begin() + deckDraw);
}

void Game::DrawCard(char who, int amt) {
    for(int i = 0; i < amt; i++)
        DrawCard(who);
}

//Some parallel logic to card, but I think it gets the job done pretty well?
std::vector<Card> Game::PopulateDeck() {
    std::vector<Card> tempDeck;
    char cSuit;
    for (int suit = 0; suit < 4; suit++) {
        for (int i = 0; i < 13; i++) {
            switch(suit) {
                case 0:
                    cSuit = 'D';
                    break;
                case 1:
                    cSuit = 'C';
                    break;
                case 2:
                    cSuit = 'S';
                    break;
                case 3:
                    cSuit = 'H';
                    break;
            }
            Card tempCard = Card(i, cSuit);
            //std::cout << "Added a " << tempCard.GetSuit() << " of value " << tempCard.GetValue() << std::endl;
            
            tempDeck.push_back(tempCard);
        }
    }
    return tempDeck;
}


char Game::DecideWinner() {
    char player = 'p';
    char dealer = 'd';
    char winner;

    pTotal = Stand(player);
    //Play the Dealer's Turn
    dTotal = Dealer();

    //Decide the winner
    if( ( dTotal > pTotal && dTotal <= 21 ) || ( dTotal < pTotal && pTotal > 21 ) ) {
        winner = dealer;
        std::cout << "\nThe dealer wins! and you had  " << pTotal << std::endl;
        ShowHand(dealer);
    }
    else if( ( pTotal > dTotal && pTotal <= 21 ) || ( pTotal < dTotal && dTotal > 21 ) ) {
        winner = player;
        std::cout << "\nYou win! and the dealer had " << dTotal << std::endl;
        ShowHand(player);
    }
    else {
        winner = ' ';
        std::cout << "\nStalemate, no winner this round." << std::endl;
        ShowHand(player);
        ShowHand(dealer);
    }
    
    return winner;

}

void Game::TestShowDeck() {
    for (int i = 0; i < _deck.size(); i++) {
        _deck.at(i).PrintTextCard();
    }
}

