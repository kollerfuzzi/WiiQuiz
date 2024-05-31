#ifndef QUIZLOADERAPICLIENT_HPP
#define QUIZLOADERAPICLIENT_HPP

#include <vector>
#include <map>
#include "quiz.hpp"
#include "bsod.hpp"
#include "resources.hpp"

class QuizLoaderApiClient : public APIClient {
public:
    QuizLoaderApiClient();
    ~QuizLoaderApiClient();
    std::vector<Quiz*> loadQuizzes(Resources* resources);
private:
    QuizAction* _createLobbyFromJson(nlohmann::json actionJson);
    QuizAction* _createChapterFromJson(nlohmann::json actionJson);
    QuizAction* _createQuestionFromJson(nlohmann::json actionJson);
    QuizAction* _createRythmGameFromJson(nlohmann::json actionJson);
    QuizAction* _createScoreboardFromJson(nlohmann::json actionJson);
    std::map<std::string, QuizAction* (QuizLoaderApiClient::*)(nlohmann::json)> _typeToQuizAction; 
};

#endif // QUIZLOADERAPICLIENT_HPP 
