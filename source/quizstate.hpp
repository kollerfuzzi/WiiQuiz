#ifndef QUIZSTATE_HPP
#define QUIZSTATE_HPP

#include <vector>
#include <map>
#include <algorithm>
#include "player.hpp"
#include "quizaction.hpp"
#include "screendebug.hpp"
#include "answer.hpp"


class QuizAction;

class QuizState {
public:
    QuizState(Resources* resources);
    ~QuizState();
    Resources* getResources();
    void sortPlayersByScore();
    void setPlayers(std::vector<Player*>& players);
    std::vector<Player*>& getPlayers();
    Player* getPlayerById(std::string id);
    void setActions(std::vector<QuizAction*>& actions);
    std::vector<QuizAction*>& getActons();
    void setAnswers(std::vector<Answer>& answers);
    std::vector<Answer>& getAnswers();
    void setCurrentAction(size_t currentAction);
    QuizAction* getCurrentAction();
    QuizAction* nextAction();
    bool hasNextAction();
private:
    void _deletePlayers();
    void _deleteActions();
    Resources* _resources;
    std::vector<Player*> _players;
    std::vector<QuizAction*> _actions;
    std::vector<Answer> _answers;
    size_t _currentAction = 0;
};

#endif // QUIZSTATE_HPP
