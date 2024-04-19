#include "quiz.hpp"

Quiz::~Quiz() {
    if (_state != nullptr) {
        delete _state;
    }
    if (_client != nullptr) {
        delete _client;
    }
}

void Quiz::update(Clock &clock) {
    QuizAction* currentAction = _state->getCurrentAction();
    if (currentAction->isDone()) {
        if (_state->hasNextAction()) {
            currentAction = _state->nextAction();
        } else {
            _isDone = true;
        }
    }
    currentAction->update(clock);
}

void Quiz::render() {
    _state->getCurrentAction()->render();
}

bool Quiz::isDone() {
    return _isDone;
}

void Quiz::reset() {
    _state->setCurrentAction(0);
    for (QuizAction* action : _state->getActons()) {
        action->reset();
    }
}

QuizState *Quiz::getState() {
    return _state;
}

Quiz::Builder Quiz::builder() {
    return Quiz::Builder();
}

Quiz::Quiz(QuizState* state, QuizAPIClient *client) {
    _resources = state->getResources();
    _state = state;
    _client = client;
}

Quiz::Builder& Quiz::Builder::resources(Resources* resources) {
    _resources = resources;
    return *this;
}

Quiz::Builder& Quiz::Builder::action(QuizAction* action) {
    _actions.push_back(action);
    return *this;
}

Quiz::Builder& Quiz::Builder::player(Player* player) {
    _players.push_back(player);
    return *this;
}

Quiz* Quiz::Builder::build() {
    QuizState* state = new QuizState(_resources);
    QuizAPIClient* client = new QuizAPIClient(state);
    state->setPlayers(_players);
    state->setActions(_actions);
    for (QuizAction* action : _actions) {
        action->setClient(client);
        action->setState(state);
        action->setResources(_resources);
    }

    return new Quiz(state, client);
}
