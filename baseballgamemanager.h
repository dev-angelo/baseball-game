#ifndef BASEBALLGAMEMANAGER_H
#define BASEBALLGAMEMANAGER_H

class PitchingResultGenerator;
class ScoreBoard;
class OfficialScorer;
class StatusPrinter;
class BaseballTeam;

class BaseballGameManager
{

public:
    BaseballGameManager();
    ~BaseballGameManager();

    /**
     * It is called for starting Baseball Game.
     */
    void run();

private:
    PitchingResultGenerator *m_pPitchingResultGenerator;
    ScoreBoard *m_pScoreBoard;
    OfficialScorer *m_pOfficialScorer;
    StatusPrinter *m_pStatusPrinter;

    BaseballTeam *m_pHomeTeam;
    BaseballTeam *m_pAwayTeam;

    BaseballTeam *m_pCurrentAttackTeam;

    /**
     * Play one inning.
     *
     */
    void playInning(BaseballTeam* pBaseballTeam);

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

    void startGame();
    bool playAttack(float battingAverage);
}
;

#endif // BASEBALLGAMEMANAGER_H
