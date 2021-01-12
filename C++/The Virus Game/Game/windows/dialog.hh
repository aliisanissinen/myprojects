#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief Constructor
    */
    explicit Dialog(QWidget *parent = nullptr);

    /**
    * @brief Deconstructor
    */
    ~Dialog();

    /**
    * @brief Gives info, the name of the player and choosen level
    * @return Pair with name and level
    * @post Exception guarantee: nothrow.
    */
    std::pair<QString, int> giveInfo();

signals:
    void okClicked();

private slots:

    void on_cancelButton_clicked();
    void on_levelBox_activated(const QString &arg1);
    void on_okButton_clicked();

private:
    Ui::Dialog *ui;
    QString name_;
    int level_ = 1;
    bool start_ = false;
};

#endif // DIALOG_HH
