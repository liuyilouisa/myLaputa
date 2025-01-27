#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
    setWindowTitle("Laputa~Castle in the Sky");

    playlist << "qrc:/res/menu1.mp3" << "qrc:/res/menu2.mp3";
    musicOutput = new QAudioOutput;
    musicOutput->setVolume(0.02);
    soundOutput = new QAudioOutput;
    soundOutput->setVolume(0.1);

    musicPlayer = new QMediaPlayer;
    musicPlayer->setAudioOutput(musicOutput);
    musicPlayer->setSource(QUrl(playlist[currentTrackIndex]));
    musicPlayer->setLoops(1);
    musicPlayer->play();

    soundPlayer = new QMediaPlayer;
    soundPlayer->setAudioOutput(soundOutput);
    soundPlayer->setSource(QUrl("qrc:/res/button1.mp3"));
    soundPlayer->setLoops(1);

    connect(musicPlayer, &QMediaPlayer::mediaStatusChanged, this, &MenuWidget::onMediaStatusChanged);
}

MenuWidget::~MenuWidget()
{
    delete ui;
    delete musicPlayer;
    delete soundPlayer;
    delete musicOutput;
    delete soundOutput;
}

void MenuWidget::on_StartButton_clicked()
{
    soundPlayer->play();
    QApplication::setOverrideCursor(Qt::WaitCursor);
    emit ShowGame();
}


void MenuWidget::on_ExitButton_clicked()
{
    this->close();
}


void MenuWidget::on_LoadButton_clicked()
{
    soundPlayer->play();
    emit ShowGame();
    emit LoadGame();
}

void MenuWidget::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        currentTrackIndex = (currentTrackIndex + 1) % playlist.size();
        musicPlayer->setSource(QUrl(playlist[currentTrackIndex]));
        musicPlayer->play();
    }
}
