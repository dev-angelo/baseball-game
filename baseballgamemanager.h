#ifndef BASEBALLGAMEMANAGER_H
#define BASEBALLGAMEMANAGER_H

class PitchingResultGenerator;
class ScoreBoard;
class OfficialScorer;
class StatusPrinter;

class BaseballGameManager
{

public:
    BaseballGameManager();
    ~BaseballGameManager();

    /**
     * It is called for starting Baseball Game.
     */
    void startGame();

    /**
     * Play one inning.
     *
     */
    void playInning();

    /**
     * Determine whether the game is finished through outCount.
     *
     * @param outCount Number of out.
     * @return finished (true) or not finished (false).
     */
    bool isGameEnd(unsigned short outCount);

    /**
     * Show baseball game menu.
     */
    void showMenu();

    /**
     * Receive user's menu select input.
     */
    unsigned short receiveUserMenuSelect();

    /**
     * Perform the menu selected by user.
     */
    void performUserMenuSelection(unsigned short userInput);


private:
    PitchingResultGenerator *m_pPitchingResultGenerator;
    ScoreBoard *m_pScoreBoard;
    OfficialScorer *m_pOfficialScorer;
    StatusPrinter *m_pStatusPrinter;
}
;

#endif // BASEBALLGAMEMANAGER_H
