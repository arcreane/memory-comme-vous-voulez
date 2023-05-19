#include "game.h"
#include <qobjectdefs.h>
#include <QtWidgets>

Game::Game(int difficulty, std::vector<QLabel*> label)
{
    this->difficulty = difficulty;
    this->pv = 3;
    this->currentCard = NULL;
}
