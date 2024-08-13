#include "qarunforeveryplayer.hpp"
#include "bsod.hpp"

QARunForEveryPlayer::QARunForEveryPlayer(QASinglePlayer* action) {
    _singleplayerAction = action;
}

QARunForEveryPlayer::~QARunForEveryPlayer() {
    if (_singleplayerAction == nullptr) {
        delete _singleplayerAction;
        _singleplayerAction = nullptr;
    }
}

void QARunForEveryPlayer::update(Clock& clock) {
    if (!_initialized) {
        _players = _state->getPlayers();
        _initAction();
        _initialized = true;
    }
    
    if (_singleplayerAction->isDone()) {
        _singleplayerAction->reset();
        if (_players.empty()) {
            _done = true; 
        } else {
            _setNextPlayer();
        }
    }
    if (!_done) {
        _singleplayerAction->update(clock);
    }
}

void QARunForEveryPlayer::render() {
    if (_initialized && !_done) {
        _singleplayerAction->render();
    }
}

bool QARunForEveryPlayer::isDone() {
    return _done;
}

void QARunForEveryPlayer::reset() {
    _initialized = false;
    _done = false;
    _players.clear();
    _singleplayerAction->reset();
}

std::set<std::string> QARunForEveryPlayer::getResourcePaths() {
    return _singleplayerAction->getResourcePaths();
}

void QARunForEveryPlayer::_setNextPlayer() {
    _singleplayerAction->setPlayer(_players[0]);
    _players.erase(_players.begin());
}

void QARunForEveryPlayer::_initAction() {
    _singleplayerAction->setClient(_client);
    _singleplayerAction->setState(_state);
    _singleplayerAction->setResources(_resources);
    _setNextPlayer();
}
