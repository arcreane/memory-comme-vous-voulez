#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void gameOver();
    void game(std::vector<QString> urlList);
    void victory();

public slots:
    void easy();
    void medium();
    void hard();
    void restart();

private:
    Ui::MainWindow *ui;

    Card* currentCard;
    int score;
    std::vector<QString> urlList;
    int pv;
};
#endif // MAINWINDOW_H
