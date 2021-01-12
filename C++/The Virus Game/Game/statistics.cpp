#include "statistics.hh"


Statistics::Statistics()
{

}

Statistics::~Statistics()
{

}

void Statistics::getLevel(int level)
{
    Q_ASSERT(1 <= level && level <= 3);

    invariant();
    level_ = level;
    invariant();
}

void Statistics::getName(QString name)
{
    playerName_ = name.toStdString();
}

void Statistics::addPoints(int points)
{
    Q_ASSERT(0 <= points_);

    invariant();
    points_ += points;
    invariant();
}

void Statistics::readData()
{
    invariant();

    QString filename = "Game/scoreData.txt";
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    filecontent_ = file.readAll();
    std::string content = filecontent_.toStdString();
    file.close();

    while(content.size() >= 1){
         std::string line = content.substr(0, content.find("\n"));

         std::string delimiter = ";";
         std::string name = line.substr(0, line.find(delimiter));
         line.erase(0, line.find(delimiter) + delimiter.length());
         std::string score;

         if (level_ == 1) {
             score = line.substr(0, line.find(delimiter));
         }
         else if (level_ == 2) {
             line.erase(0, line.find(delimiter) + delimiter.length());
             score = line.substr(0, line.find(delimiter));
         }
         else if (level_ == 3){
             line.erase(0, line.find(delimiter) + delimiter.length());
             line.erase(0, line.find(delimiter) + delimiter.length());
             score = line.substr(0, line.find(delimiter));
         }

         int points = std::stoi(score);
         topScore_.insert({points, name});
         QString qname = QString::fromStdString(name);
         content.erase(0, content.find("\n") + 1);
    }
    invariant();
}

void Statistics::writeData()
{
    if(playerName_ != ""){
        QFile file("Game/scoreData.txt");
        if(file.open(QFile::WriteOnly | QFile::Text) ) {

            QTextStream out(&file);

            std::string content = filecontent_.toStdString();
            std::string contentCopy = filecontent_.toStdString();

            std::size_t found = content.find(playerName_) + 1;
            if(found){
                content.erase(0, found + playerName_.size());
                std::string score = content.substr(0, content.find("\n"));

                if(level_ == 1){
                    std::size_t scoreLength = score.find(";");
                    int levelScore = std::stoi(score.substr(0, scoreLength));

                    if ( points_ > levelScore ){
                        // replace(pointsStartPosition, endingPosition, to)
                        contentCopy.replace(contentCopy.begin() + found
                                            + playerName_.size(),
                                            contentCopy.begin() + found
                                            + playerName_.size() + scoreLength,
                                            std::to_string(points_));
                    }
                }
                else if(level_ == 2){
                    std::size_t firstLevelLength = score.find(";") + 1;
                    score.erase(0, firstLevelLength);

                    std::size_t scoreLength = score.find(";");
                    int levelScore = std::stoi(score.substr(0, scoreLength));

                    if ( points_ > levelScore ){
                        // replace(pointsStartPosition, endingPosition, to)
                        contentCopy.replace(contentCopy.begin() + found
                                            + playerName_.size() + firstLevelLength,
                                            contentCopy.begin() + found
                                            + playerName_.size() + firstLevelLength
                                            + scoreLength,
                                            std::to_string(points_));
                    }
                }
                else if(level_ == 3){
                    std::size_t firstLevelLength = score.find(";") + 1;
                    score.erase(0, firstLevelLength);
                    std::size_t secondLevelLength = score.find(";") + 1;
                    score.erase(0, secondLevelLength);

                    std::size_t scoreLength = score.size();
                    int levelScore = std::stoi(score.substr(0, scoreLength));

                    if ( points_ > levelScore ){
                        // replace(pointsStartPosition, endingPosition, to)
                        contentCopy.replace(contentCopy.begin() + found
                                            + playerName_.size() + firstLevelLength
                                            + secondLevelLength,
                                            contentCopy.begin() + found
                                            + playerName_.size() + firstLevelLength
                                            + secondLevelLength + scoreLength,
                                            std::to_string(points_));
                    }
                }
            }
            else if(level_ == 1){
                contentCopy += playerName_ + ";" + std::to_string(points_) + ";0;0\n";
            }
            else if(level_ == 2){
                contentCopy += playerName_ + ";0;" + std::to_string(points_) + ";0\n";
            }
            else if(level_ == 3){
                contentCopy += playerName_ + ";0;0;" + std::to_string(points_) + "\n";
            }

            out <<  QString::fromStdString( contentCopy );
            file.close();
        }
    }
}

std::map<int, std::string> Statistics::giveData()
{
    invariant();

    return topScore_;
    invariant();
}

int Statistics::givePoints()
{
    Q_ASSERT(0 <= points_);
    invariant();
    return points_;
}

int Statistics::giveLevel()
{
    invariant();
    return level_;
}

void Statistics::invariant() const
{
    Q_ASSERT(0 <= points_);
    Q_ASSERT(1 <= level_ && level_ <= 3);
}
