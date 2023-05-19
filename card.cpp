#include "card.h"
#include <iostream>
#include <QDebug>
#include <unistd.h>

Card::Card(QString url, int idCard, ClickableLabel* item)
{
    this->isDiscovered= false;
    this->id = idCard;
    this->item = item;
    this->imageUrl = url;

    QString adresseRessource = QString(url);
    QPixmap pixmap(adresseRessource);
    this->image = pixmap;
    QString backCard = QString(":/back/moi.png");
    QPixmap pixmapCard(backCard);
    this->backCard = pixmapCard;
    this->item->setPixmap(pixmapCard);
    this->item->setScaledContents(true);
}

void Card::discoveredCard(Card* currentCard){
    if (this->isDiscovered == true && this == currentCard) {
        return;
    }
    this->currentCard = currentCard;
    int maxWidth = this->item->size().width();
    QPropertyAnimation* mMoveAnimation = new QPropertyAnimation(this->item, "geometry");
    mMoveAnimation->setDuration(500);
    mMoveAnimation->setStartValue( QRect( this->item->pos(), this->item->size()) );
    mMoveAnimation->setEndValue( QRect( QPoint(this->item->pos().x() + 135, this->item->pos().y()), QSize(0, this->item->size().height())));
    mMoveAnimation->start();
    connect(mMoveAnimation, SIGNAL(finished()), this, SLOT(changeDirection()));
}

bool Card::checkCard(Card* card){
    if (card->imageUrl == this->imageUrl)
        return true;
    return false;
}

void Card::deleteCard() {
    this->item->setDisabled(true);
}

void Card::changeDirection()
{
    this->item->setVisible(false);
    if (this->isDiscovered == true) {
        this->isDiscovered = false;
        this->item->setPixmap(this->backCard);
    } else {
        this->isDiscovered = true;
        this->item->setPixmap((this->image));
    }
    this->item->size().setWidth(0);
    this->item->setVisible(true);
    QPropertyAnimation* mMoveAnimation = new QPropertyAnimation(this->item, "geometry");
    mMoveAnimation->setDuration(500);
    mMoveAnimation->setStartValue( QRect( QPoint(this->item->pos().x() + 135, this->item->pos().y()), QSize(0, this->item->size().height())));
    mMoveAnimation->setEndValue( QRect( this->item->pos(), this->item->size()));
    mMoveAnimation->start();
    connect(mMoveAnimation, SIGNAL(finished()), this, SLOT(flipCard()));
}

void Card::flipCard()
{
    if(this->currentCard != NULL) {
        if (this->checkCard(this->currentCard)){
            this->currentCard->deleteCard();
            this->deleteCard();
        } else {
            this->currentCard->discoveredCard(NULL);
            this->discoveredCard(NULL);
        }
    }
}
