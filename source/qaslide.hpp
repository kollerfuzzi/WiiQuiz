
#ifndef QASLIDE_HPP
#define QASLIDE_HPP

#include "qaquestion.hpp"

class QASlide : public QuizAction {
public:
    QASlide();
    ~QASlide();
    void update(Clock& clock);
    void render();
    bool isDone();
    void reset();
    std::set<std::string> getResourcePaths();
protected:
    void init();
    std::map<Player*, TextBox*> _playerAnswerMap;
};

#endif // QASLIDE_HPP
