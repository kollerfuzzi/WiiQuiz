#include "quiztemplate.hpp"

#include "qastart.hpp"
#include "qaquestion.hpp"
#include "qascoreboard.hpp"
#include "qachapter.hpp"
#include "qarythmminigame.hpp"

Quiz* QuizTemplate::getDefaultQuiz(Resources* resources) {
    return Quiz::builder()
        .resources(resources)
        //.action(QAStart::builder().build())
        .action(QARythmMinigame::builder()
                    .img(Texture::LINK_BOLERO)
                    .audio(Audio::BOLERO_OF_FIRE)
                    .data("PATH:audio/bolero_of_fire.wav;TICK_COUNT:148;LENGTH_MS:18000;START_DELAY_MS:800#TWO/800000;A/1768000;TWO/2736000;ONE/3704000;LEFT/4672000;ONE/5640000;TWO/6608000;ONE/7092000;A/7576000;RIGHT/8060000;LEFT/8544000;TWO/9512000;A/9754000;ONE/9996000;A/10238000;TWO/10480000;A/10722000;ONE/10964000;A/11206000;TWO/11448000;A/11690000;ONE/11932000;A/12174000;TWO/12416000;A/12658000;ONE/12900000;A/13142000;TWO/13384000;A/13626000;UP/14110000;LEFT/14594000;DOWN/14836000;RIGHT/15078000;ONE/15320000;TWO/15562000")
                    .delayMs(-200)
                    .build())
        .action(QARythmMinigame::builder()
                    .img(Texture::QUALLE)
                    .audio(Audio::DISCOQUALLEN)
                    .data("PATH:audio/discoquallen.wav;TICK_COUNT:1248;LENGTH_MS:148471;START_DELAY_MS:1529#ONE/2001000;TWO/2473000;ONE/2945000;TWO/3417000;ONE/3889000;TWO/4361000;ONE/4833000;TWO/5305000;A/5305000;ONE/5777000;TWO/6249000;A/6249000;ONE/6721000;TWO/7193000;A/7193000;ONE/7665000;TWO/8137000;A/8137000;ONE/8609000;TWO/9081000;A/9081000;ONE/9553000;A/10025000;TWO/10025000;ONE/10497000;TWO/10969000;A/10969000;ONE/11441000;A/11913000;TWO/11913000;ONE/12385000;TWO/12857000;A/12857000;ONE/13329000;A/13801000;TWO/13801000;ONE/14273000;TWO/14745000;A/14745000;ONE/15217000;TWO/15807000;ONE/16043000;A/16161000;LEFT/16633000;LEFT/17105000;LEFT/17577000;RIGHT/18049000;LEFT/18521000;LEFT/18993000;LEFT/19465000;RIGHT/19937000;LEFT/20409000;LEFT/20881000;LEFT/21353000;RIGHT/21825000;LEFT/22061000;UP/22297000;UP/22769000;UP/23241000;LEFT/23713000")
                    .build())

        .action(QAChapter::builder().title("Kapitel 1:\nRechnungswesen").build())
        .action(QAQuestion::builder()
                 .question("Was ist der operative casflow?")
                 .correctAnswer("OCF")
                 .wrongAnswer("UCF")
                 .wrongAnswer("FCF")
                 .wrongAnswer("BUEB")
                 .wrongAnswer("BAB")
                 .build())
        .action(QAQuestion::builder()
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
                 .build())


        .action(QAScoreboard::builder().build())




        .action(QAScoreboard::builder().build())

        .build();
}
