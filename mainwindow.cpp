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
    QGridLayout* gridLayout = new QGridLayout();
    std::vector<Card*> cardList;
    std::vector<QString> urlList;
    QObject::connect(ui->quitterButton, SIGNAL(clicked()), this, SLOT(close()));
    this->currentCard = NULL;
    this->pv = 3;

    for (int i = 0; i < 8; i++){
        urlList.push_back(QString(":/logos/logo%1.png").arg(i));
        urlList.push_back(QString(":/logos/logo%1.png").arg(i));
    }

    const int rowCount = 4;
    const int columnCount = 4;
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {

            ClickableLabel* label = new ClickableLabel(QString("Label %1-%2").arg(row).arg(column));
            label->setAlignment(Qt::AlignCenter);
            label->setFrameStyle(QFrame::Panel | QFrame::Raised);
            label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            int index = rand() % urlList.size();
            cardList.push_back(new Card(urlList[index], column * rowCount + row, label));
            urlList.erase(urlList.begin() + index);

            // Connecter le signal clicked() à votre slot de gestion de clics
            QObject::connect(label, &ClickableLabel::clicked, [=]() {
                cardList[cardList.size() - 1]->discoveredCard(this->currentCard);
                if (this->currentCard == NULL) {
                    this->currentCard = cardList[cardList.size() - 1];
                } else if(this->currentCard != cardList[cardList.size() - 1]) {
                    this->currentCard = NULL;
                    this->pv--;
                    ui->pv->setText("PV : " + QString::number(this->pv));
                    if (this->pv == 0) {
                        MainWindow::gameOver();
                    }
                }
            });
            gridLayout->addWidget(label, row, column);
        }
    }

    ui->verticalWidget_2->setLayout(gridLayout);
    window.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gameOver()
{
    close();
}
