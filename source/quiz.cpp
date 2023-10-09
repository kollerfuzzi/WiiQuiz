#include "quiz.hpp"

Quiz::~Quiz() {
    for (QuizAction* quizAction: this->_actions) {
        delete quizAction;
    }
    for (Player* player: this->_players) {
        delete player;
    }
}

void Quiz::update(const Clock &clock) {
    QuizAction* currentAction = _actions[_currentAction];
    if (currentAction->isDone() && _actions.size() != _currentAction + 1) {
        ++_currentAction;
        currentAction++;
    }
    currentAction->update(clock);
}

void Quiz::render() {
    _actions[_currentAction]->render();
}

Quiz::Builder Quiz::builder() {
    return Quiz::Builder();
}

Quiz::Quiz(Resources *resources, std::vector<QuizAction*> actions, std::vector<Player*> players) {
    _resources = resources;
    _actions = actions;
    _players = players;
}

Quiz::Builder& Quiz::Builder::resources(Resources* resources) {
    this->_resources = resources;
    return *this;
}

Quiz::Builder& Quiz::Builder::action(QuizAction* action) {
    this->_actions.push_back(action);
    return *this;
}

Quiz::Builder& Quiz::Builder::player(Player* player) {
    this->_players.push_back(player);
    return *this;
}

Quiz* Quiz::Builder::build() {
    for (QuizAction* action : this->_actions) {
        action->setResources(this->_resources);
        action->setPlayers(this->_players);
    }
    return new Quiz(this->_resources, this->_actions, this->_players);
}
