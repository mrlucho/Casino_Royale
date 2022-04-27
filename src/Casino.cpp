
#include <random>
#include "Casino.h"
#include <sstream>
#include <utility>
#include <ctime>


void Casino::prepareDeck() {
//    prepare random num gen
    std::mt19937 rng(time(0));
    rng_ = rng;

    for(int colour = 0;colour<4;colour++){
        for(int figureNum =0;figureNum<13;figureNum++) {
            currentDeck_.push_back(new Karta(colour,figureNum));
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Casino &casino) {
    for(auto playerPtr : casino.players_){
        os<<playerPtr->showHand()<<std::endl;
    }
    return os;
}

void Casino::shuffleDeck(int numTimes) {
    int cardsNum = currentDeck_.size();
    std::uniform_int_distribution<int> CardDist(0,cardsNum-1);
    for(int i=0;i<numTimes;i++){
        int index1 = CardDist(rng_);
        int index2 = CardDist(rng_);
//        todo: make swap
        if(index1 != index2) {
            Karta* temp = currentDeck_[index1];
            currentDeck_[index1] = currentDeck_[index2];
            currentDeck_[index2] = temp;
        }

    }
}

Karta *Casino::popCard() {
    Karta* card = currentDeck_[currentCardIndexToGive_];
    currentCardIndexToGive_++;
    return card;
}



void Casino::setupGame() {
    for(auto playerPtr : players_){
        Karta* card = this->popCard();
        playerPtr->takeCard(card);

        Karta* card2 = this->popCard();
        playerPtr->takeCard(card2);
    }
}

void Casino::playRound() {
    setupGame(); // give two cards to every player

    std::cout<< this->to_string()<<std::endl;

    while (not checkGameOver()){
        for(auto playerPtr : players_){
            playerPtr->PunktyRzeczywiscieWyjebalo();
            if( not playerPtr->askToPass()){
                playerPtr->takeCard(this->popCard());
            }
        }
        std::cout<< this->to_string()<<std::endl;
    }
    std::cout<<getWinner()<<std::endl;
}

bool Casino::checkGameOver() {
    for(auto player : this->players_){
//        if even one player not passed playRound on
        if(not player->getPass()){
            return false;
        }
    }
    return true;
}

//looks like working func
std::string Casino::getWinner() const {
    std::ostringstream os;
    os<<"---------------------"<<std::endl;
    std::vector<IPlayer*> winner21P;
    std::vector<int> allPlPoints;
    for(auto playerPtr : players_){
        if(playerPtr->isWinner()){
            winner21P.push_back(playerPtr);
        }
        allPlPoints.push_back(playerPtr->getPoints());
    }
    allPlPoints.push_back(0);
    int indexHighestPointsLessThan21 = allPlPoints.size()-1; //last index
    for (int i = 0; i < getPlayersNum(); ++i) {
        if(allPlPoints[i] < 21 and allPlPoints[i] > allPlPoints[indexHighestPointsLessThan21]){
            indexHighestPointsLessThan21 = i;
//          fixme  in case 2 winners here neglect it now
        }
    }



    if(winner21P.empty() and indexHighestPointsLessThan21 == allPlPoints.size()-1){
        os<<"no one won"<<std::endl;
    }
    else if(winner21P.size() == 1){
        os<<"the winner is : "<<std::endl<<*(winner21P[0]);
    }

    else if ( not winner21P.empty()){
        os<<"the winners are ";
        for(auto playerPtr : winner21P){
            os<<*playerPtr <<", ";
        }
        os<<std::endl;
    }
    else{
        os<<"the winner is : "<<std::endl<<*(players_[indexHighestPointsLessThan21]);
    }

    os<<"---------------------"<<std::endl;
    return os.str();
}


std::string Casino::showPlayer(int num) {
    return players_[num]->showHand();
}

std::string Casino::to_string()const {
    std::string result;
    for(auto playerPtr : players_){
        result+=playerPtr->showHand();
    }
    return result;
}


Casino::Casino(int numHumanPlayers,int shuffles ) {
    prepareDeck();
    shuffleDeck(shuffles);
    Player* p= nullptr;
    for (int i = 0; i < numHumanPlayers; ++i) {
        p = new Player("Player"+ std::to_string(i+1));
        players_.push_back(p);
    }
    Bot* d = nullptr;
    int botNum = 1;
    for (int j = numHumanPlayers; j < 4; j++) {
        d = new Bot("Bot"+ std::to_string(botNum),Courage::rash);
        players_.push_back(d);
        botNum++;
    }

}

void Casino::printAllCards() const {
    for (auto cardPtr : currentDeck_){
        cardPtr->wypisz();
    }
}
Casino::~Casino() {
//    don't touch it
    for (auto pObj = players_.begin();
         pObj != players_.end(); ++pObj) {
        delete *pObj;
    }
    for (auto pObj = currentDeck_.begin();
         pObj != currentDeck_.end(); ++pObj) {
        delete *pObj; // Note that this is deleting what pObj points to,
        // which is a pointer
    }
}