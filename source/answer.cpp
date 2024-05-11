#include "answer.hpp"

Player* Answer::getPlayer() {
    return _player;
}

std::vector<std::string> Answer::getAnswers() {
    return _answers;
}

bool Answer::isApproved() {
    return _approved;
}

Answer::Builder Answer::builder() {
    return Answer::Builder();
}

Answer::Answer(Player* player, std::vector<std::string> answers, bool approved) {
    _player = player;
    _answers = answers;
}

Answer::Builder& Answer::Builder::player(Player* player) {
    _player = player;
    return *this;
}

Answer::Builder& Answer::Builder::answer(std::string answer) {
    _answers.push_back(answer);
    return *this;
}

Answer::Builder& Answer::Builder::approved(bool approved) {
    _approved = approved;
    return *this;
}

Answer Answer::Builder::build() {
    return Answer(_player, _answers, _approved);
}
