#include "quizstate.hpp"

QuizState::QuizState(Resources* resources) {
    _resources = resources;
}

QuizState::~QuizState() {
    _deletePlayers();
    _deleteActions();
}

Resources *QuizState::getResources() {
    return _resources;
}

bool pointSort(Player* p1, Player* p2) {
    return p1->getPoints() > p2->getPoints();
}

void QuizState::sortPlayersByScore() {
    std::sort(_players.begin(), _players.end(), pointSort);
}

void QuizState::setPlayers(std::vector<Player*>& players) {
    _deletePlayers();
    _players = players;
}

std::vector<Player*>& QuizState::getPlayers() {
    return _players;
}

Player *QuizState::getPlayerById(std::string id) {
    for (Player* player : _players) {
        if (player->getId() == id) {
            return player;
        }
    }
    return nullptr;
}

void QuizState::setActions(std::vector<QuizAction*>& actions) {
    _deleteActions();
    _actions = actions;
}

std::vector<QuizAction*>& QuizState::getActons() {
    return _actions;
}

void QuizState::setAnswers(std::vector<Answer>& answers) {
    _answers = answers;
}

std::vector<Answer>& QuizState::getAnswers() {
    return _answers;
}

void QuizState::setCurrentAction(size_t currentAction) {
    _currentAction = currentAction;
}

QuizAction* QuizState::getCurrentAction() {
    return _actions[_currentAction];
}

QuizAction* QuizState::nextAction() {
    _currentAction++;
    return _actions[_currentAction];
}

bool QuizState::hasNextAction() {
    return _currentAction < _actions.size() - 1;
}

void QuizState::_deletePlayers() {
    for (Player* player : _players) {
        delete player;
    }
    _players.clear();
}

void QuizState::_deleteActions() {
    for (QuizAction* action : _actions) {
        delete action;
    }
    _actions.clear();
}
