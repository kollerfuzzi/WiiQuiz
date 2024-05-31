#ifndef QUIZ_HPP
#define QUIZ_HPP


#include <vector>
#include "player.hpp"
#include "quizaction.hpp"
#include "clock.hpp"
#include "renderable.hpp"
#include "resources.hpp"
#include "quizstate.hpp"
#include "quizapiclient.hpp"

class Quiz : public Renderable {
public:
    ~Quiz();
    void update(Clock& clock);
    void render();
    bool isDone();
    void reset();
    std::string getName();
    QuizState* getState();

    class Builder {
    public:
        Builder& name(std::string name);
        Builder& resources(Resources* resources);
        Builder& action(QuizAction* action);
        Builder& player(Player* player);
        Quiz* build();
    private:
        std::string _name;
        std::vector<QuizAction*> _actions;
        std::vector<Player*> _players;
        Resources* _resources;
    };
    static Builder builder();
    std::set<std::string> getResourcePaths() override;
private:
    Quiz(std::string name, QuizState* state, QuizAPIClient* client);
    std::string _name;
    QuizState* _state = nullptr;
    Resources* _resources = nullptr;
    QuizAPIClient* _client = nullptr;
    bool _isDone = false;
};

#endif // QUIZ_HPP
