#ifndef QUIZAPICLIENT_HPP
#define QUIZAPICLIENT_HPP

#include "apiclient.hpp"
#include "player.hpp"
#include "quizstate.hpp"
#include "question.hpp"
#include "answer.hpp"

class QuizState;

class QuizAPIClient : public APIClient {
public:
    QuizAPIClient(QuizState* state);
    void loadPlayers();
    std::string getServerAddress();
    void askQuestion(Question& question);
    void loadAnswers();
    void endQuestion();
    void setPoints();
private:
    QuizState* _state;
};

#endif // QUIZAPICLIENT_HPP
