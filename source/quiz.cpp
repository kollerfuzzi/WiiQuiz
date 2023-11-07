#include "quiz.hpp"

Quiz::~Quiz() {
    delete _state;
}

void Quiz::update(const Clock &clock) {
    QuizAction* currentAction = _state->getCurrentAction();
    if (currentAction->isDone()) {
        currentAction = _state->nextAction();
    }
    currentAction->update(clock);
}

void Quiz::render() {
    _state->getCurrentAction()->render();
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
