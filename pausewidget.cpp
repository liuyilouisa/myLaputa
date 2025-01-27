#include "pausewidget.h"
#include "ui_pausewidget.h"

PauseWidget::PauseWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PauseWidget)
{
    ui->setupUi(this);
    this->hide();
}

PauseWidget::~PauseWidget()
{
    delete ui;
}

void PauseWidget::receiveShowPause(){
    this->show();
}

void PauseWidget::on_continueButton_clicked()
{
    this->hide();
    emit ContinueGame();
}



void PauseWidget::on_exitButton_clicked()
{
    this->hide();
    emit Exit();
}


void PauseWidget::on_saveButton_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    this->hide();
    emit SaveGame();
}


void PauseWidget::on_loadButton_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    this->hide();
    emit LoadGame();
}

