#include <iostream>
#include "Card.h"

Card::Card(int val, char suit) {
    this->suit = suit;
    if(val > 10 || val == 1) {
        switch(val) {
            case 1:     //Ace, alternate value is handled in the deck class when calcing total
                type = 'A';
                value = 1;
                break;
            case 11:    //Jack
                type = 'J';
                value = 10;
                break;
            case 12:    //Queen
                type = 'Q';
                value = 10;
                break;
            case 13:    //King
                type = 'K';
                value = 10;
                break;
        }
    }
    else {
        value = val;
        type = ' ';
    }
    
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