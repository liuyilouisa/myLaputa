#include "gamewidget.h"
#include "map.h"
#include "fighter.h"
#include "airship.h"
#include "rocket.h"
// #include "button.h"
#include "sun.h"
#include <QFile>
#include <QDataStream>
#include <QDateTime>
#include <QDir>

GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}
    ,credit(0)
{
    buttonOutput = new QAudioOutput;
    buttonOutput->setVolume(0.1);

    buttonPlayer = new QMediaPlayer;
    buttonPlayer->setAudioOutput(buttonOutput);
    buttonPlayer->setLoops(1);
    buttonPlayer->setSource(QUrl("qrc:/res/button1.mp3"));

    // setAutoFillBackground(true);
    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(5, 20, 710, 780);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    shop = new Shop;
    shop->setPos(659, 450);
    scene->addItem(shop);
    // Button *button = new Button(timer);
    // button->setPos(659, 40);
    // scene->addItem(button);
    Map *map = new Map(shop);
    map->setPos(270, 400);
    scene->addItem(map);

    pauseButton = new QPushButton("Pause");
    pauseButton->setCursor(Qt::PointingHandCursor);
    pauseButton->setGeometry(600,25,120,60);
    QFont buttonFont = pauseButton->font();
    buttonFont.setPointSize(20);
    pauseButton->setFont(buttonFont);
    pauseButton->setStyleSheet("border-image: url(:/res/Button.png);");
    connect(pauseButton,&QPushButton::clicked,this,&GameWidget::pauseGame);
    scene->addWidget(pauseButton);

    creditNum = new QLCDNumber();
    creditNum->setGeometry(0,25,120,60);
    creditNum->setDigitCount(10);
    creditNum->display(credit);
    scene->addWidget(creditNum);

    view = new QGraphicsView(scene, this);
    view->resize(720,800);
    view->setRenderHint(QPainter::Antialiasing);
    static int num;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 3);
    num = dis(gen);
    switch(num){
    case 1:
        view->setBackgroundBrush(QPixmap(":/res/DayBackground.png"));break;
    case 2:
        view->setBackgroundBrush(QPixmap(":/res/NightBackground.png"));break;
    case 3:
        view->setBackgroundBrush(QPixmap(":/res/RainbowBackground.png"));break;
    }
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &GameWidget::addPlane);
    connect(timer, &QTimer::timeout, this, &GameWidget::check);
    this->hide();
}

GameWidget::~GameWidget(){
    delete timer;
    delete scene;
    delete view;
    delete buttonOutput;
    delete buttonPlayer;
}

void GameWidget::addCredit(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> randomCredit(10,20);
    credit += randomCredit(gen);
    creditNum->display(credit);
}

void GameWidget::addPlane(){
    static std::random_device rd;
    static std::mt19937 gen(rd());

    static int low = 4;
    static int high = 8;
    static int maxtime = 10 * 1000 / 33;
    static int time = maxtime / 2;
    static int counter = 0;
    if (++counter >= time)
    {
        if (++low > high)
        {
            maxtime /= 2;
            high *= 2;
        }
        counter = 0;
        static std::uniform_int_distribution<> randomTime(maxtime/3, maxtime);
        static std::uniform_int_distribution<> randomType(1, 100);
        static std::uniform_int_distribution<> randomColumn(0, 4);
        time = randomTime(gen);
        int type = randomType(gen);
        Plane *plane;
        if (type <= 50)
            plane = new Fighter;
        else if (type <= 75)
            plane = new Airship;
        else
            plane = new Rocket;
        int i = randomColumn(gen);
        plane->setPos(130 + 98 * i, 800);
        plane->setFlags(QGraphicsItem::ItemIsSelectable);
        scene->addItem(plane);
    }
}

void GameWidget::check(){
    static int time = .25 * 1000 / 33;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
            if (item->type() == Plane::Type)
            {
                if (item->y() < 50){
                    exitGame();
                    return;
                }else if (Plane* plane = dynamic_cast<Plane*>(item);plane && plane->hp <= 0){
                    addCredit();
                }
            }
    }
}
void GameWidget::clearGame(){
    credit = 0;
    creditNum->display(credit);
    QList<QGraphicsItem *> items = scene->items();
    foreach (QGraphicsItem *item, items){
        if (item->type() == Plane::Type || item->type() == Cloud::Type || item->type() == Sun::Type){
            scene->removeItem(item);
            delete item;
        }
    }
}
void GameWidget::exitGame(){
    timer->stop();
    shop->sun = 2000;
    clearGame();
    this->hide();
}

void GameWidget::pauseGame(){
    buttonPlayer->play();
    timer->stop();
    emit ShowPause();
}

void GameWidget::receiveShowGame(){
    buttonPlayer->play();
    timer->start(33);
    view->show();
    this->show();
    QApplication::restoreOverrideCursor();
}

void GameWidget::receiveSaveGame(){
    buttonPlayer->play();
    QString filePath("save.txt");
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Failed to open file for writing:" << filePath;
        return;
    }
    QDataStream out(&file);
    out << credit;
    out << shop->sun;
    QList<QGraphicsItem *> items = scene->items();
    int itemCount(items.size());
    out << itemCount;
    foreach (QGraphicsItem *item, items)
    {
        // if (item->type() == Cloud::Type)
        // {
        //     out << item->type();
        //     Cloud *cloud = dynamic_cast<Cloud *>(item);
        //     if (cloud)
        //     {
        //         out << cloud->pos();
        //         out << cloud->name;
        //         out << cloud->hp;
        //     }
        // }
        if (item->type() == Plane::Type)
        {
            // out << item->type();
            Plane *plane = dynamic_cast<Plane *>(item);
            if (plane && plane->hp >= 0)
            {
                out << plane->pos();
                out << plane->name;
            }
        }
    }
    out << timer->interval();
    file.close();
    QApplication::restoreOverrideCursor();
    receiveContinueGame();
}

void GameWidget::receiveLoadGame(){
    buttonPlayer->play();
    {
        clearGame();
        QString filePath("save.txt");
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning() << "Failed to open file for reading:" << filePath;
            return;
        }
        QDataStream in(&file);
        {
            in >> credit;
            creditNum->display(credit);
            in >> shop->sun;
            QList<QGraphicsItem *> items = scene->items();
            int itemCount;
            in >> itemCount;
            for (int i = 0; i < itemCount; ++i)
            {
                // in >>
                QPointF pos;
                QString name;
                in >> pos >> name;

                Plane *plane;
                if (name == "Fighter")
                    plane = new Fighter;
                else if (name == "Airship")
                    plane = new Airship;
                else if (name == "Rocket")
                    plane = new Rocket;
                else
                    continue;

                plane->setPos(pos);
                plane->setFlags(QGraphicsItem::ItemIsSelectable);
                scene->addItem(plane);
            }
            int interval;
            in >> interval;
            timer->setInterval(interval);
        }

        file.close();
    }
    QApplication::restoreOverrideCursor();
    receiveContinueGame();
}

void GameWidget::receiveContinueGame(){
    buttonPlayer->play();
    timer->start(33);
}

