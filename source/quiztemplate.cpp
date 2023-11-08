#include "quiztemplate.hpp"

#include "qastart.hpp"
#include "qaquestion.hpp"
#include "qascoreboard.hpp"
#include "qachapter.hpp"
#include "qarythmminigame.hpp"

Quiz* QuizTemplate::getDefaultQuiz(Resources* resources) {
    return Quiz::builder()
        .resources(resources)
        .action(QAStart::builder().build())
        .action(QARythmMinigame::builder().build())
        .action(QAChapter::builder().title("Kapitel 1:\nRechnungswesen").build())
        .action(QAQuestion::builder()
                 .question("Was ist der operative casflow?")
                 .correctAnswer("OCF")
                 .wrongAnswer("UCF")
                 .wrongAnswer("FCF")
                 .wrongAnswer("BUEB")
                 .wrongAnswer("BAB")
                 .build())
        /*.action(QAQuestion::builder()
                 .question("Was ist 4x4 (hexadezimal)?")
                 .correctAnswer("10")
                 .wrongAnswer("F")
                 .wrongAnswer("FF")
                 .wrongAnswer("8")
                 .wrongAnswer("NullPointerException")
                 .build())
        .action(QAQuestion::builder()
                 .question("What is the Answer?")
                 .correctAnswer("correct")
                 .wrongAnswer("wrong")
                 .build())*/
        .action(QAScoreboard::builder().build())
        .build();
}
