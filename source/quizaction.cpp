#include "quizaction.hpp"

QuizAction::~QuizAction() {

}

void QuizAction::setResources(Resources* resources) {
    this->_resources = resources;
}

void QuizAction::setPlayers(std::vector<Player*> players) {
    this->_players = players;
}
