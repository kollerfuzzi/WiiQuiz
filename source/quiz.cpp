#include "quiz.hpp"

Quiz::~Quiz() {
    if (_state != nullptr) {
        delete _state;
        _state = nullptr;
    }
    if (_client != nullptr) {
        delete _client;
        _client = nullptr;
    }
}

void Quiz::update(Clock& clock) {
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
    _isDone = false;
    _state->setCurrentAction(0);
    for (QuizAction* action : _state->getActons()) {
        action->reset();
    }
}

std::string Quiz::getName() {
    return _name;
}

QuizState *Quiz::getState() {
    return _state;
}

Quiz::Builder Quiz::builder() {
    return Quiz::Builder();
}

std::set<std::string> Quiz::getResourcePaths() {
    std::set<std::string> resourcePaths;
    for (QuizAction* action : _state->getActons()) {
        std::set<std::string> actionResourcePaths = action->getResourcePaths();
        resourcePaths.insert(actionResourcePaths.begin(), actionResourcePaths.end());
    }
    return resourcePaths;
}

Quiz::Quiz(std::string name, QuizState* state, QuizAPIClient *client) {
    _name = name;
    _resources = state->getResources();
    _state = state;
    _client = client;
}

Quiz::Builder& Quiz::Builder::name(std::string name) {
    _name = name;
    return *this;
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

    return new Quiz(_name, state, client);
}
