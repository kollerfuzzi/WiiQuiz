#include "quizaction.hpp"

QuizAction::~QuizAction() {

}

void QuizAction::setResources(Resources* resources) {
    _resources = resources;
}

void QuizAction::setState(QuizState* state) {
    _state = state;
}

void QuizAction::setClient(QuizAPIClient* client) {
    _client = client;
}
