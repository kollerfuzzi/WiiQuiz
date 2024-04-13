#include "quizapiclient.hpp"

#include <string>
#include <vector>
#include "stringutils.hpp"
#include "screendebug.hpp"
#include "magic_enum.hpp"
#include "json.hpp"

QuizAPIClient::QuizAPIClient(QuizState* state) {
    _state = state;
}

QuizAPIClient::~QuizAPIClient() {

}

void QuizAPIClient::loadPlayers() {
    nlohmann::json playersJson = requestJson(APICommand::GET_PLAYERS);
    std::vector<Player*> players;
    for (nlohmann::json playerJson : playersJson) {
        Player* player = Player::builder()
                            .name(playerJson["name"])
                            .points(playerJson["points"])
                            .build();
        players.push_back(player);
    }
    _state->setPlayers(players);
}

std::string QuizAPIClient::getServerAddress() {
    nlohmann::json serverAddrJson = requestJson(APICommand::GET_SERVER_ADDR);
    std::string address = serverAddrJson["serverAddress"];
    return address;
}

void QuizAPIClient::askQuestion(Question& question) {
    nlohmann::json questionJson = {
        {"prompt", question.getPrompt()},
        {"type", magic_enum::enum_name(question.getType())},
        {"answers", question.getAnswers()}
    };

    nlohmann::json status = requestJson(APICommand::ASK_QUESTION, questionJson);
    assertStatusOk(status);
}

void QuizAPIClient::loadAnswers() {
    std::vector<std::string> lines = request(APICommand::GET_ANSWERS);
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
    assertStatusOk(requestJson(APICommand::END_QUESTION));
}

void QuizAPIClient::setPoints() {
    std::vector<std::string> requestLines;
    for (Player* player : _state->getPlayers()) {
        std::string playerWithPoints(player->getName());
        playerWithPoints += ";";
        playerWithPoints += std::to_string(player->getPoints());
        requestLines.push_back(playerWithPoints);
    }
    request(APICommand::SET_POINTS, requestLines);
}
