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
}

void Card::discoveredCard(){
    int maxWidth = this->item->size().width();
    QPropertyAnimation* mMoveAnimation = new QPropertyAnimation(this->item, "geometry");
    mMoveAnimation->setDuration(500);
    mMoveAnimation->setStartValue( QRect( this->item->pos(), this->item->size()) );
    mMoveAnimation->setEndValue( QRect( this->item->pos(), QSize(0, this->item->size().height())));
    mMoveAnimation->start();
    connect( mMoveAnimation, SIGNAL(finished()), this, SLOT(changeDirection()) );
//    while(this->item->width() > 200){
//        this->item->resize(this->item->width() - 5, this->item->height());
//        this->item->setFixedWidth(this->item->width() - 5);
//        qInfo() << this->item->width();
//        std::cout << this->isDiscovered << std::endl;
//        if(this->isDiscovered == false) {
//            std::cout << this->isDiscovered << std::endl;
//            this->item->setPixmap(this->backCard.scaled(this->item->width() - 5, this->item->height()));
//        } else {
//            this->item->setPixmap(this->image.scaled(this->item->width() - 5, this->item->height()));
//        }

//    }
//    while(this->item->size().width() < maxWidth){
//        qInfo("2e");
//        if(this->isDiscovered == false) {
//            this->item->setPixmap(this->backCard.scaled(this->item->width() + 5, this->item->height()));
//        } else {
//            this->item->setPixmap(this->image.scaled(this->item->width() + 5, this->item->height()));
//        }
//    }
}



bool Card::checkCard(Card card){
    if (card.imageUrl == this->imageUrl)
        return true;
    return false;
}

void Card::deleteCard() {
    this->item->setPixmap(QPixmap());
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
    mMoveAnimation->setStartValue( QRect( this->item->pos(), QSize(0, this->item->size().height())));
    mMoveAnimation->setEndValue( QRect( this->item->pos(), QSize(265, this->item->size().height())));
    mMoveAnimation->start();
}
