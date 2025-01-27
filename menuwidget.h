#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include "qgraphicsview.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QStringList>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);
    ~MenuWidget();

private slots:
    void on_StartButton_clicked();

    void on_ExitButton_clicked();

    void on_LoadButton_clicked();

    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

signals:
    void ShowGame();
    void LoadGame();

private:
    Ui::MenuWidget *ui;
    QMediaPlayer *musicPlayer;
    QMediaPlayer *soundPlayer;
    QAudioOutput *musicOutput;
    QAudioOutput *soundOutput;
    QStringList playlist;
    int currentTrackIndex = 0;
};

#endif // MENUWIDGET_H
