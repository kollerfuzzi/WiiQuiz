#include "qascoreboard.hpp"

QAScoreboard::QAScoreboard() {

}

QAScoreboard::~QAScoreboard(){

}

void QAScoreboard::update(const Clock &clock) {
    if (!this->_initialized) {
        //TextBox textbox = TextBox.builder()
        //     .text("the scoreboard");
    }
}

void QAScoreboard::render() {

}

bool QAScoreboard::isDone() {

}

QAScoreboard::Builder QAScoreboard::builder() {
    return QAScoreboard::Builder();
}

QAScoreboard *QAScoreboard::Builder::build() {
    return new QAScoreboard();
}
