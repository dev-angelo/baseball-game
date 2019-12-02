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
    void showPitchingResult(const unsigned short strike,
                            const unsigned short ball,
                            const PitchingResult pitchingResult);

    /**
     * Print current score board in console.
     *
     * @param strikeCount Current number of Strike.
     * @param ballCount Current number of Ball.
     * @param outCount Current number of Out.
     */
    void showScoreBoard(const unsigned short strikeCount,
                        const unsigned short ballCount,
                        const unsigned short outCount);

    /**
     * Print the next batter in console.
     */
    void showNextBatter();

    /**
     * Print game end comment in console.
     *
     * @param hitsCount Number of hits when the match ends.
     */
    void showGameEndComment(const std::string homeTeamName, const std::string awayTeamName,
                            const unsigned short homeTeamScore, const unsigned short awayTeamScore);

    /**
     * Print current batter number and name
     *
     * @param batterNumber Number of batter entered at plate
     * @param batterName Name of batter entered at plate
     */
    void showBatterEnter(const unsigned short batterNumber, const std::string batterName);

    /**
     * Print the team to attack
     *
     * @param teamName Team name of the attacking position
     */
    void showAttackTeam(const std::string teamName);

    /**
     * Print wheater top of inning or bottom of inning
     *
     * @param teamName Team name of the attacking position
     */
    void showInningTopBottom(const unsigned short inning);

private:
    /**
     * Print strike comment in console.
     * And when strikeout occurs, call showThreeStrikeOutOccursComment() to print.
     *
     * @param strikeCount Current number of Strike.
     */
    void showStrikeOccurs(const unsigned short strike);

    /**
     * Print ball comment in console
     * And when four-ball occurs, call showFourBallHitsOccursComment() to print.
     *
     * @param ballCount Current number of Ball.
     */
    void showBallOccurs(const unsigned short ball);

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
