#include "dialog.hh"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(600, 387);
    QImage background(":/Pics/Pics/virus.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    ui->infoLabel->setText
            ("Instant Game: The size of the viruses is large.\nGame time 15 seconds.");
    ui->pointsLCD->display(0);
}

Dialog::~Dialog()
{
    delete ui;
}

std::pair<QString, int> Dialog::giveInfo()
{
    std::pair<QString, int> info(name_, level_);
    return info;
}

void Dialog::on_cancelButton_clicked()
{
    qDebug() << "Cancel clicked";
    this->close();
}

void Dialog::on_levelBox_activated(const QString &arg1)
{
    if (arg1 == "Instant Game") {
        level_ = 1;
        ui->infoLabel->setText
                ("Instant Game: The size of the viruses is large.\nGame time 15 seconds.");
    }
    else if (arg1 == "Normal Game") {
        level_ = 2;
        ui->infoLabel->setText
                ("Normal Game: The size of the viruses is medium.\nGame time 30 seconds.");
    }
    else if (arg1 == "Long Game") {
        level_ = 3;
        ui->infoLabel->setText
                ("Long Game: The size of the viruses is medium.\nGame time 60 seconds.");
    }
    else {
        qDebug() << "Problem in levels";
    }
}

void Dialog::on_okButton_clicked()
{
    qDebug() << "Ok clicked";
    start_ = true;
    name_ = ui->nameLine->text();
    emit okClicked();
    this->close();
}
