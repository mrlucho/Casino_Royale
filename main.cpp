#include <iostream>
//#include "Karta.h"
#include "Casino.h"
//#include <Player.h>
int main() {
//    Casino casinoRoyale = Casino(true);
//    casinoRoyale.shuffleDeck();
//    casinoRoyale.setupGame();

//    Player player1 =  Player("pl 1");
//    Player player2 = Player("pl 2");
//    Player player3 = Player("pl 3");
//    Bot bot1 = Bot("Bot1",Courage::rash);
//    std::vector<Player*> players = {&player1,&player2,&player3,&bot1};


    Casino casinoRoyale = Casino(3);
//    casinoRoyale.shuffleDeck();
//    casinoRoyale.setupGame();
//    std::cout<<casinoRoyale.showPlayer(0);
//    std::cout<<casinoRoyale.getDeckSize()<<std::endl;
//    std::cout<<casinoRoyale;
    casinoRoyale.play();
//std::cout<<casinoRoyale

    return EXIT_SUCCESS;
}