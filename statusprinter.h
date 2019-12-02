#ifndef STATUSPRINTER_H
#define STATUSPRINTER_H

#include <iostream>

enum class PitchingResult;

class StatusPrinter {

public:
    StatusPrinter();
    ~StatusPrinter();

    /**
     * Print pitching result in hangul in console.
     *
     * @param strike Current Number of strike
     * @param ball Current Number of ball
     * @param pitchingResult Result of pitching. (please refer to pitchingresult.h)
     */
    void showPitchingResult(unsigned short strike,
                            unsigned short ball,
                            PitchingResult pitchingResult);

    /**
     * Print current score board in console.
     *
     * @param strikeCount Current number of Strike.
     * @param ballCount Current number of Ball.
     * @param outCount Current number of Out.
     */
    void showScoreBoard(unsigned short strikeCount,
                        unsigned short ballCount,
                        unsigned short outCount);

    /**
     * Print the next batter in console.
     */
    void showNextBatter();

    /**
     * Print game end comment in console.
     *
     * @param hitsCount Number of hits when the match ends.
     */
    void showGameEndComment(unsigned short hitsCount);

    void showBatterEnter(unsigned short batterNumber, std::string batterName);
    void showAttackTeam(std::string teamName);
    void showInningTopBottom(unsigned short inning);

private:
    /**
     * Print strike comment in console.
     * And when strikeout occurs, call showThreeStrikeOutOccursComment() to print.
     *
     * @param strikeCount Current number of Strike.
     */
    void showStrikeOccurs(unsigned short strike);

    /**
     * Print ball comment in console
     * And when four-ball occurs, call showFourBallHitsOccursComment() to print.
     *
     * @param ballCount Current number of Ball.
     */
    void showBallOccurs(unsigned short ball);

    /**
     * Print hits comment in console.
     */
    void showHitsOccurs();

    /**
     * Print out comment in console.
     */
    void showOutOccurs();

    /**
     * Print 3 strike out comment in console.
     */
    void showThreeStrikeOutOccursComment();

    /**
     * Print 4 ball hits comment in console.
     */
    void showFourBallHitsOccursComment();
};

#endif // STATUSPRINTER_H
