#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class AudioManager : public QObject
{
    Q_OBJECT
public:
    static AudioManager* instance();
    void playSound(const QString &soundPath);

private:
    AudioManager(QObject *parent = nullptr);
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    QMap<QString, QMediaPlayer*> soundPlayers;
    QAudioOutput* output;
    static AudioManager* _instance;
};

#endif // AUDIOMANAGER_H
