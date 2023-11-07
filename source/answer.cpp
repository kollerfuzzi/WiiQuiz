#include "answer.hpp"

Player* Answer::getPlayer() {
    return _player;
}

std::string Answer::getAnswer() {
    return _answer;
}

Answer::Builder Answer::builder() {
    return Answer::Builder();
}

Answer::Answer(Player* player, std::string answer) {
    _player = player;
    _answer = answer;
}

Answer::Builder &Answer::Builder::player(Player* player) {
    _player = player;
    return *this;
}

Answer::Builder &Answer::Builder::answer(std::string answer) {
    _answer = answer;
    return *this;
}

Answer Answer::Builder::build() {
    return Answer(_player, _answer);
}
