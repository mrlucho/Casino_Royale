//
// Created by micha on 13.04.2022.
//

#ifndef CASINO_ROYALE_CASINO_H
#define CASINO_ROYALE_CASINO_H

#include <vector>
#include <random>

#include "Karta.h"
#include "Player.h"
#include "Bot.h"
#include "IPlayer.h"



class Casino{
public:
    Casino(Casino const &a) = default;


    void shuffleDeck(int numTimes=100);
    friend std::ostream& operator<<(std::ostream& os, const Casino& casino);
    Karta* popCard();
    void setupGame();
    void play();
    bool checkGameOver();  // check if all passed
    std::string getWinner()const;
    std::string to_string()const;
    int getPlayersNum()const{return players_.size();}




    Casino(int numHumanPlayers=4,int shuffles=100);
    ~Casino();

    //    --------------Debug
    std::string showPlayer(int num); //prints players hand
    int getDeckSize()const{return currentDeck_.size();} //current size
    void printAllCards()const;


private:
    void prepareDeck(); //used once during constr of casino sets rng
    std::mt19937 rng_;
    std::vector<Karta*> currentDeck_;
    std::vector<IPlayer*> players_;
    int currentCardIndexToGive_=0;
};
#endif //CASINO_ROYALE_CASINO_H
