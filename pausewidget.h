#ifndef PAUSEWIDGET_H
#define PAUSEWIDGET_H

#include <QWidget>

namespace Ui {
class PauseWidget;
}

class PauseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PauseWidget(QWidget *parent = nullptr);
    ~PauseWidget();

signals:
    void ContinueGame();
    void Exit();
    void SaveGame();
    void LoadGame();

private slots:
    void receiveShowPause();
    void on_continueButton_clicked();

    void on_exitButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::PauseWidget *ui;
};

#endif // PAUSEWIDGET_H
