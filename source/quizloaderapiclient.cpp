#include "quizloaderapiclient.hpp"

#include "qaquestioncreator.hpp"
#include "qarunforeveryplayer.hpp"
#include "qalobby.hpp"
#include "qachapter.hpp"
#include "qascoreboard.hpp"
#include "qarythmminigame.hpp"
#include "magic_enum.hpp"
#include "tinyuuidv4.hpp"

QuizLoaderApiClient::QuizLoaderApiClient() {
    _typeToQuizAction["LOBBY"] = &QuizLoaderApiClient::_createLobbyFromJson;
    _typeToQuizAction["CHAPTER"] = &QuizLoaderApiClient::_createChapterFromJson;
    _typeToQuizAction["QUESTION"] = &QuizLoaderApiClient::_createQuestionFromJson;
    _typeToQuizAction["RYTHM_GAME"] = &QuizLoaderApiClient::_createRythmGameFromJson;
    _typeToQuizAction["SCOREBOARD"] = &QuizLoaderApiClient::_createScoreboardFromJson;
}

QuizLoaderApiClient::~QuizLoaderApiClient() {
}

std::vector<Quiz*> QuizLoaderApiClient::loadQuizzes(Resources* resources) {
    std::vector<Quiz*> quizzesList;
    nlohmann::json quizzes = requestJson(APICommand::GET_QUIZZES);
    for (nlohmann::json quiz : quizzes) {
        if (!quiz.contains("name")) {
            BSOD::raise("the quiz has no name");
        }
        Quiz::Builder quizBuilder = Quiz::builder()
            .name(quiz["name"])
            .resources(resources);
        std::string name = quiz["name"];
        nlohmann::json actions = quiz["actions"];
        for (nlohmann::json actionJson : actions) {
            std::string actionType = actionJson["type"];
            if (!_typeToQuizAction.contains(actionType)) {
                std::string error = actionType;
                error += " action type not supported.";
                BSOD::raise(error);
            }
            quizBuilder.action(((*this).*(_typeToQuizAction[actionType]))(actionJson));
        }
        quizzesList.push_back(quizBuilder.build());
    }
    return quizzesList;
}

QuizAction* QuizLoaderApiClient::_createLobbyFromJson(nlohmann::json actionJson) {
    return QALobby::builder()
            .build();
}

QuizAction* QuizLoaderApiClient::_createChapterFromJson(nlohmann::json actionJson) {
    return QAChapter::builder()
            .title(actionJson["text"])
            .build();
}

QuizAction* QuizLoaderApiClient::_createQuestionFromJson(nlohmann::json actionJson) {
    std::string id;
    if (actionJson.contains("id")) {
        id = actionJson["id"];
    } else {
        id = TinyUuidV4::generate();
    }

    Question::Builder questionBuilder = Question::builder()
        .id(id)
        .type(magic_enum::enum_cast<QuestionType>((std::string) actionJson["questionType"]).value())
        .prompt(actionJson["prompt"]);

    for (nlohmann::json answer : actionJson["answers"]) {
        questionBuilder.answer(answer["answer"], answer["correct"]);
    }

    return QAQuestionCreator::of(questionBuilder.build());
}

QuizAction* QuizLoaderApiClient::_createRythmGameFromJson(nlohmann::json actionJson) {
    QARythmMinigame* game = QARythmMinigame::builder()
        .img(actionJson["cubeImg"])
        .audio(actionJson["audio"])
        .delayMs(actionJson["startDelay"])
        .data(actionJson["data"])
        .maxPts(actionJson["maxPts"])
        .build();
    return new QARunForEveryPlayer(game);
}

QuizAction *QuizLoaderApiClient::_createScoreboardFromJson(nlohmann::json actionJson) {
    return QAScoreboard::builder()
            .build();
}
