#include <iostream>
#include "ArtGenerator.h"

void ArtGenerator::Intro() {
    std::cout << "┏━━┓┏┓╋╋╋╋╋╋┏┓╋╋╋┏┓╋╋╋╋╋┏┓\n";
    std::cout << "┃┏┓┃┃┃╋╋╋╋╋╋┃┃╋╋╋┃┃╋╋╋╋╋┃┃\n";
    std::cout << "┃┗┛┗┫┃┏━━┳━━┫┃┏┓╋┃┣━━┳━━┫┃┏┓\n";
    std::cout << "┃┏━┓┃┃┃┏┓┃┏━┫┗┛╋┓┃┃┏┓┃┏━┫┗┛┛\n";
    std::cout << "┃┗━┛┃┗┫┏┓┃┗━┫┏┓┫┗┛┃┏┓┃┗━┫┏┓┓\n";
    std::cout << "┗━━━┻━┻┛┗┻━━┻┛┗┻━━┻┛┗┻━━┻┛┗┛\n";
}
        
void ArtGenerator::DrawCard(Card c, std::vector<std::string>& d) {
    //Need to print a suit and either val or type
    //Need to convert letter suit to symbols
    std::string suit = FindSuitSymbol(c);
    std::string identity = FindCardIdentity(c);
    
    if(identity != "10") {
        d.at(1) += " |" + identity + "      |";
        d.at(5) += " |______" + identity + "|";
    }
    else if(identity == "10") {
        d.at(1) += " |" + identity + "     |";
        d.at(5) += " |_____" + identity + "|";
    }

    d.at(0) += " _________";
    d.at(2) += " |       |";
    d.at(3) += " |   " + suit + "   |";
    d.at(4) += " |       |";
}
        
void ArtGenerator::DrawCardArray(std::vector<Card> v) {
    //Combine each line and print together ie print top line, then the next and go til bottom.
    std::vector<std::string> ASCIIHand = std::vector<std::string>(6); 
    //Populate ASCIIHand
    for(int i = 0; i < v.size(); i++) {
        DrawCard(v.at(i), ASCIIHand);
    }
    //Print ASCIIHand
    for(int i = 0; i < ASCIIHand.size(); i++) {
        std::cout << ASCIIHand.at(i) << std::endl;
    }
}

std::string ArtGenerator::FindCardIdentity(Card c) {
    std::string identity = "";
    char type = c.GetType();

    if(type == ' ') {
        identity = std::to_string(c.GetValue());
    }
    else {
        identity = type;
    }
    
    return identity;
}

std::string ArtGenerator::FindSuitSymbol(Card c) {
    char suit = c.GetSuit();
    std::string suitSymbol = "";

    switch(suit) {
        case 'C':   //Club
            suitSymbol = "♣";
            break;
        case 'H':   //Heart
            suitSymbol = "♥";
            break;
        case 'D':   //Diamond
            suitSymbol = "♦";
            break;
        case 'S':   //Spade
            suitSymbol = "♠";
            break;
        default:    //Your code messed up 
            suitSymbol = "Error";
            break;
    }

    return suitSymbol;
}