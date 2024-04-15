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
                            .id(playerJson["id"])
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
        {"id", question.getId()},
        {"prompt", question.getPrompt()},
        {"type", magic_enum::enum_name(question.getType())},
        {"answers", question.getAnswersStr()}
    };

    requestJson(APICommand::ASK_QUESTION, questionJson);
}

void QuizAPIClient::loadAnswers() {
    nlohmann::json answersJson = requestJson(APICommand::GET_ANSWERS);
    std::vector<Answer> answerList;
    for (auto entry = answersJson.begin(); entry != answersJson.end(); ++entry) {
        std::string name = entry.key();
        nlohmann::json answers = entry.value();
        Player* player = _state->getPlayerById(name);
        Answer::Builder answerBuilder = Answer::builder()
            .player(player)
            .approved(answers["approved"]);
        for (std::string answerStr : answers["answers"]) {
            answerBuilder.answer(answerStr);
        }
        answerList.push_back(answerBuilder.build()); 
    }
    _state->setAnswers(answerList);
}

void QuizAPIClient::endQuestion() {
    requestJson(APICommand::END_QUESTION);
}

void QuizAPIClient::setPoints() {
    nlohmann::json playerListJson = nlohmann::json::array();
    for (Player* player : _state->getPlayers()) {
        nlohmann::json playerJson = {
            {"name", player->getName()},
            {"points", player->getPoints()}
        };
        playerListJson.push_back(playerJson);
    }
    requestJson(APICommand::SET_POINTS, playerListJson);
}
