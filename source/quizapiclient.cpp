#include "quizapiclient.hpp"

#include <string>
#include <vector>
#include "stringutils.hpp"
#include "screendebug.hpp"
#include "magic_enum.hpp"

QuizAPIClient::QuizAPIClient(QuizState *state) {
    _state = state;
}

void QuizAPIClient::loadPlayers() {
    std::vector<std::string> response = request(ApiCommand::GET_PLAYERS);
    std::vector<Player*> players;
    for (std::string& playerLn : response) {
        std::vector<std::string> playerParts = StringUtils::split(playerLn, ';');
        Player* player = Player::builder()
                             .name(playerParts[0])
                             .points(std::stoi(playerParts[1]))
                             .build();
        players.push_back(player);
    }
    _state->setPlayers(players);
}

std::string QuizAPIClient::getServerAddress() {
    return request(ApiCommand::GET_SERVER_ADDR)[0];
}

void QuizAPIClient::askQuestion(Question& question) {
    std::vector<std::string> requestLines;
    requestLines.push_back(question.getPrompt());
    std::string type("TYPE:");
    type += magic_enum::enum_name(question.getType());
    requestLines.push_back(type);
    for (std::string& answer : question.getAnswers()) {
        requestLines.push_back(answer);
    }
    request(ApiCommand::ASK_QUESTION, requestLines);
}

void QuizAPIClient::loadAnswers() {
    std::vector<std::string> lines = request(ApiCommand::GET_ANSWERS);
    std::vector<Answer> answers;
    for (std::string& line : lines) {
        std::vector<std::string> answerParts = StringUtils::split(line, ';');
        Player* player = _state->getPlayerByName(answerParts[0]);
        Answer answer = Answer::builder()
                .player(player)
                .answer(answerParts[1])
                .build();
        answers.push_back(answer);
    }
    _state->setAnswers(answers);
}

void QuizAPIClient::endQuestion() {
    request(ApiCommand::END_QUESTION);
}

void QuizAPIClient::setPoints() {
    std::vector<std::string> requestLines;
    for (Player* player : _state->getPlayers()) {
        std::string playerWithPoints(player->getName());
        playerWithPoints += ";";
        playerWithPoints += std::to_string(player->getPoints());
        requestLines.push_back(playerWithPoints);
    }
    request(ApiCommand::SET_POINTS, requestLines);
}
