#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "clickablelabel.h"
#include <QPushButton>
#include "card.h"
#include <cstdlib>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget window;

    QObject::connect(ui->leave, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->easy, SIGNAL(clicked()), this, SLOT(easy()));
    QObject::connect(ui->medium, SIGNAL(clicked()), this, SLOT(medium()));
    QObject::connect(ui->hard, SIGNAL(clicked()), this, SLOT(hard()));
    QObject::connect(ui->restart, SIGNAL(clicked()), this, SLOT(restart()));

    window.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::easy(){
    std::vector<QString> urlList;
    this->score = 0;
    this->pv = 5;
    ui->pv->setText("PV : " + QString::number(this->pv));
    for (int i = 0; i < 8; i++){
        urlList.push_back(QString(":/logos/logo%1.png").arg(i));
        urlList.push_back(QString(":/logos/logo%1.png").arg(i));
    }
    game(urlList);
    ui->medium->setDisabled(true);
    ui->hard->setDisabled(true);
}
void MainWindow::medium(){
    std::vector<QString> urlList;
    this->score = 0;
    this->pv = 4;
    ui->pv->setText("PV : " + QString::number(this->pv));
    for (int i = 0; i < 8; i++){
        urlList.push_back(QString(":/cars/car%1.png").arg(i));
        urlList.push_back(QString(":/cars/car%1.png").arg(i));
    }
    game(urlList);
    ui->easy->setDisabled(true);
    ui->hard->setDisabled(true);
}
void MainWindow::hard(){
    std::vector<QString> urlList;
    this->score = 0;
    this->pv = 3;
    ui->pv->setText("PV : " + QString::number(this->pv));
    for (int i = 0; i < 8; i++){
        urlList.push_back(QString(":/shifters/shifter%1.png").arg(i));
        urlList.push_back(QString(":/shifters/shifter%1.png").arg(i));
    }
    game(urlList);
    ui->medium->setDisabled(true);
    ui->easy->setDisabled(true);
}



void MainWindow::game(std::vector<QString> urlList)
{
    QGridLayout* gridLayout = new QGridLayout();
    std::vector<Card*> cardList;
    this->currentCard = NULL;

    const int rowCount = 4;
    const int columnCount = 4;
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {

            ClickableLabel* label = new ClickableLabel(QString("Label %1-%2").arg(row).arg(column));
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("QLabel { background-color : white; }");
            label->setFrameStyle(QFrame::Panel | QFrame::Raised);
            label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//            label->setFixedSize(250, 600);

            int index = rand() % urlList.size();
            cardList.push_back(new Card(urlList[index], column * rowCount + row, label));
            urlList.erase(urlList.begin() + index);

            // Connecter le signal clicked() à votre slot de gestion de clics
            QObject::connect(label, &ClickableLabel::clicked, [=]() {
                cardList[cardList.size() - 1]->discoveredCard(this->currentCard);
                if (this->currentCard == NULL) {
                    this->currentCard = cardList[cardList.size() - 1];
                } else if(this->currentCard->imageUrl != cardList[cardList.size() - 1]->imageUrl) {
                    this->currentCard = NULL;
                    this->pv--;
                    ui->pv->setText("PV : " + QString::number(this->pv));
                    if (this->pv == 0) {
                        MainWindow::gameOver();
                    }
                } else {
                    this->currentCard = NULL;
                    this->score+=5;
                    ui->score->setText("SCORE : " + QString::number(this->score));
                    if (this->score == 40) {
                        MainWindow::victory();
                    }
                }
            });
            gridLayout->addWidget(label, row, column);
        }
    }
    ui->verticalWidget_2->setLayout(gridLayout);
}

void MainWindow::gameOver() {
    ui->gamestate->setText("Perdu !");
    ui->easy->setDisabled(true);
    ui->medium->setDisabled(true);
    ui->hard->setDisabled(true);
    ui->restart->setDisabled(false);
    ui->leave->setDisabled(false);
    ui->verticalWidget_2->setDisabled(true);
}

void MainWindow::victory() {
    ui->gamestate->setText("Victoire !");
    ui->easy->setDisabled(true);
    ui->medium->setDisabled(true);
    ui->hard->setDisabled(true);
    ui->restart->setDisabled(false);
    ui->leave->setDisabled(false);
    ui->verticalWidget_2->setDisabled(true);
}

void MainWindow::restart() {

}
