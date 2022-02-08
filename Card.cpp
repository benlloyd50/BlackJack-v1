#include <iostream>
#include "Card.h"

Card::Card(int val, char suit) {
    
    this->suit = suit;
    if(val > 9 || val == 0) {
        switch(val) {
            case 0:     //Ace, alternate value is handled in the deck class when calcing total
                type = 'A';
                value = 1;
                break;
            case 10:    //Jack
                type = 'J';
                value = 10;
                break;
            case 11:    //Queen
                type = 'Q';
                value = 10;
                break;
            case 12:    //King
                type = 'K';
                value = 10;
                break;
        }
    }
    else {
        value = val + 1;
        type = ' ';
    }
    
}

void Card::PrintTextCard() {
    if(type == ' ')
        std::cout << suit << " | " << value << std::endl;
    else
        std::cout << suit << " | " << type << std::endl;
}


int Card::GetValue() {
    return value;
}
        
char Card::GetSuit() {
    return suit;
}

char Card::GetType() {
    return type;
}