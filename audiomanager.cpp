#include "audiomanager.h"
AudioManager* AudioManager::_instance = nullptr;
AudioManager::AudioManager(QObject *parent)
    : QObject{parent}
{
    output = new QAudioOutput(this);
    output->setVolume(0.15);
}

void AudioManager::playSound(const QString &soundPath)
{
    if (!soundPlayers.contains(soundPath))
    {
        QMediaPlayer* player = new QMediaPlayer(this);
        player->setAudioOutput(output);
        soundPlayers[soundPath] = player;
    }

    QMediaPlayer* player = soundPlayers[soundPath];

    if (player->playbackState() != QMediaPlayer::PlayingState)
    {
        player->setSource(QUrl(soundPath));
        player->play();
    }
}
AudioManager* AudioManager::instance()
{
    if (!_instance) {
        _instance = new AudioManager;
    }
    return _instance;
}
