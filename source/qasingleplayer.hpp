#ifndef QASINGLEPLAYER_HPP
#define QASINGLEPLAYER_HPP

#include "quizaction.hpp"
#include "player.hpp"

class QASinglePlayer : public QuizAction {
public:
    QASinglePlayer();
    ~QASinglePlayer();
    void setPlayer(Player* player);
protected:
    Player* _player = nullptr;
};

#endif // QASINGLEPLAYER_HPP
