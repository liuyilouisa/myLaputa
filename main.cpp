#include "menuwidget.h"
#include "gamewidget.h"
#include "pausewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWidget menuWidget;
    GameWidget gameWidget(&menuWidget);
    PauseWidget pauseWidget(&gameWidget);
    menuWidget.show();
    QObject::connect(&menuWidget,SIGNAL(ShowGame()),&gameWidget,SLOT(receiveShowGame()));
    QObject::connect(&menuWidget,SIGNAL(LoadGame()),&gameWidget,SLOT(receiveLoadGame()));

    QObject::connect(&gameWidget,SIGNAL(ShowPause()),&pauseWidget,SLOT(receiveShowPause()));

    QObject::connect(&pauseWidget,SIGNAL(ContinueGame()),&gameWidget,SLOT(receiveContinueGame()));
    QObject::connect(&pauseWidget,SIGNAL(Exit()),&gameWidget,SLOT(exitGame()));
    QObject::connect(&pauseWidget,SIGNAL(SaveGame()),&gameWidget,SLOT(receiveSaveGame()));
    QObject::connect(&pauseWidget,SIGNAL(LoadGame()),&gameWidget,SLOT(receiveLoadGame()));
    return a.exec();
}
