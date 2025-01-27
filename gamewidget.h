#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QAudioOutput>
#include <QMediaPlayer>
#include "shop.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget() override;
    void startGame();
    void addPlane();
    void check();
    void addCredit();

signals:
    void ShowPause();
    void ShowSave();

private slots:
    void exitGame();
    void pauseGame();
    void receiveShowGame();
    void receiveSaveGame();
    void receiveLoadGame();
    void receiveContinueGame();

private:
    void clearGame();
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    Shop *shop;
    QPushButton *pauseButton;
    QLCDNumber *creditNum;
    QMediaPlayer *buttonPlayer;
    QAudioOutput *buttonOutput;
    int credit;
};

#endif // GAMEWIDGET_H
