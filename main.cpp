#include <iostream>
#include "Game.h"

int main() {
    char tempChoice;
    char player = 'p', dealer = 'd';
    char winner = ' ';
    
    std::cout << "┏━━┓┏┓╋╋╋╋╋╋┏┓╋╋╋┏┓╋╋╋╋╋┏┓\n";
    std::cout << "┃┏┓┃┃┃╋╋╋╋╋╋┃┃╋╋╋┃┃╋╋╋╋╋┃┃\n";
    std::cout << "┃┗┛┗┫┃┏━━┳━━┫┃┏┓╋┃┣━━┳━━┫┃┏┓\n";
    std::cout << "┃┏━┓┃┃┃┏┓┃┏━┫┗┛╋┓┃┃┏┓┃┏━┫┗┛┛\n";
    std::cout << "┃┗━┛┃┗┫┏┓┃┗━┫┏┓┫┗┛┃┏┓┃┗━┫┏┓┓\n";
    std::cout << "┗━━━┻━┻┛┗┻━━┻┛┗┻━━┻┛┗┻━━┻┛┗┛\n";
    
    std::cout << "=Welcome to BlackJack=\n";
    std::cout << "Controls: h - hit, s - stand, h/l to play ace high or low\n"; 
    std::cout << "Would you like to play? (Y/N) ";
    std::cin >> tempChoice;

    while(toupper(tempChoice) != 'N') {
        std::cout << "\n\n\n\n";
        Game game;
        game.DrawCard(player, 2);
        game.DrawCard(dealer);
        while(toupper(tempChoice) != 'N') {
            if(game.DidYouBust(player)){
                game.ShowHand(player);
                std::cout << "Oopsie you busted with " << game.CalcHandTotal(player) << ", Dealer Wins!\n";
                winner = dealer;
                break;
            }
            game.ShowHand(player);

            game.ShowHand(dealer);

            std::cout << "Would you like a hit or stand? (H/S)";
            std::cin >> tempChoice;

            //Hit
            if(toupper(tempChoice) == 'H') {
                game.DrawCard(player);
            }

            //Stand
            else if(toupper(tempChoice) == 'S') {
                game.DecideWinner();
                break; //GameOver
            }
        
            std::cout << "\n\n\n\n\n\n";
        }
        std::cout << "Would you like to play again? (Y/N)" << std::endl;
        std::cin >> tempChoice;
        
        //Resets winner, this will be used with the betting update
        winner = ' '; 
    }
}