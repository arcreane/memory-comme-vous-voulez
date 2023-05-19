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
        void discoveredCard();
        bool checkCard(Card card);
        void deleteCard();

    public slots:
        void changeDirection();

    private:
        int id;
        bool isDiscovered;
        QPixmap image;
        ClickableLabel* item;
        QPixmap backCard;
        QString imageUrl;
};

#endif // CARD_H
