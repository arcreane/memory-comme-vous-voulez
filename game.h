#ifndef GAME_H
#define GAME_H

#include "card.h"
#include <csignal>

class Game
{
    public:
        Game(int difficulty, std::vector<QLabel*> label);
        void discoveredCard();
        void endGame();
    private:
        int difficulty;
        std::vector<Card*> cardList;
        Card* currentCard;
        int pv;
};

#endif // GAME_H
