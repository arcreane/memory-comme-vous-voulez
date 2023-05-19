#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QPixmap>
#include "clickablelabel.h"

class Card : public QObject
{
    Q_OBJECT

    public:
        Card(QString url, int id, ClickableLabel* item);
        void discoveredCard(Card* currentCard);
        bool checkCard(Card* card);
        void deleteCard();

    public Q_SLOTS:
        void changeDirection();
        void flipCard();

    private:
        int id;
        bool isDiscovered;
        QPixmap image;
        ClickableLabel* item;
        QPixmap backCard;
        QString imageUrl;
        Card* currentCard;
};

#endif // CARD_H
