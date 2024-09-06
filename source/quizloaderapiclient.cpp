#include "quizloaderapiclient.hpp"

#include "qaquestioncreator.hpp"
#include "qarunforeveryplayer.hpp"
#include "qalobby.hpp"
#include "qachapter.hpp"
#include "qaslide.hpp"
#include "qascoreboard.hpp"
#include "qarythmminigame.hpp"
#include "magic_enum.hpp"
#include "tinyuuidv4.hpp"

QuizLoaderApiClient::QuizLoaderApiClient() {
    _typeToQuizAction["LOBBY"] = &QuizLoaderApiClient::_createLobbyFromJson;
    _typeToQuizAction["CHAPTER"] = &QuizLoaderApiClient::_createChapterFromJson;
    _typeToQuizAction["SLIDE"] = &QuizLoaderApiClient::_createSlideFromJson;
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

QuizAction* QuizLoaderApiClient::_createSlideFromJson(nlohmann::json actionJson) {
    return QASlide::Builder()
        .title(actionJson.contains("title") ? _loadTextboxFromJson(actionJson["title"]) : TextBox::builder())
        .text(actionJson.contains("text") ? _loadTextboxFromJson(actionJson["text"]) : TextBox::builder())
        .bgImgPath(actionJson.contains("bgImg") ? actionJson["bgImg"] : "")
        .bgVideo(actionJson.contains("bgVideo") ? _loadVideoFromJson(actionJson["bgVideo"]) : AVResource::none())
        .bgAudioPath(actionJson.contains("bgAudio") ? actionJson["bgAudio"] : "")
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
        questionBuilder.answer(answer["text"], answer["correct"]);
    }

    return QAQuestionCreator::of(questionBuilder.build());
}

QuizAction* QuizLoaderApiClient::_createRythmGameFromJson(nlohmann::json actionJson) {
    QARythmMinigame* game = QARythmMinigame::builder()
        .img(actionJson["cubeImg"])
        .audio(actionJson["audio"])
        .delayMs(actionJson["startDelay"])
        .data(actionJson["notes"])
        .maxPts(actionJson["maxPts"])
        .build();
    return new QARunForEveryPlayer(game);
}

QuizAction *QuizLoaderApiClient::_createScoreboardFromJson(nlohmann::json actionJson) {
    return QAScoreboard::builder()
            .build();
}

AVResource QuizLoaderApiClient::_loadVideoFromJson(nlohmann::json videoJson) {
    if (!videoJson.contains("video")) {
        BSOD::raise("Video definition without video source");
    }
    std::string video = videoJson["video"];
    std::string audio = videoJson.contains("audio") ? videoJson["audio"] : "";
    return AVResource::of(video, audio);
}

TextBox::Builder QuizLoaderApiClient::_loadTextboxFromJson(nlohmann::json textJson) {
    return TextBox::Builder()
        .text(textJson.contains("text") ? textJson["text"] : "")
        .color(textJson.contains("color") ? _rgbaStrToInt(textJson["color"]) : 0xFFFFFFFF)
        .fontSize(textJson.contains("fontSize") ? (int) textJson["fontSize"] : 20)
        .marginTop(textJson.contains("marginTop") ? (int) textJson["marginTop"] : 40)
        .marginLeft(textJson.contains("marginLeft") ? (int) textJson["marginLeft"] : 40)
        .marginRight(textJson.contains("marginRight") ? (int) textJson["marginRight"] : 40)
        .animationSpeed(textJson.contains("animationSpeed") ? (int) textJson["animationSpeed"] : 30);
}

int QuizLoaderApiClient::_rgbaStrToInt(std::string string) {
    unsigned int x;   
    std::stringstream ss;
    ss << std::hex << string;
    ss >> x;
    return x;
}
