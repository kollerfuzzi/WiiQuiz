#ifndef QARUNFOREVERYPLAYER_HPP
#define QARUNFOREVERYPLAYER_HPP

#include "qasingleplayer.hpp"
#include "player.hpp"

class QARunForEveryPlayer : public QuizAction {
public:
    QARunForEveryPlayer(QASinglePlayer* action);
    ~QARunForEveryPlayer();
    void update(Clock& clock);
    void render();
    bool isDone();
    void reset();
    std::set<std::string> getResourcePaths();
private:
    void _setNextPlayer();
    void _initAction();
    QASinglePlayer* _singleplayerAction = nullptr;
    std::vector<Player*> _players;
    bool _initialized = false;
    bool _done = false;
};

#endif // QARUNFOREVERYPLAYER_HPP
