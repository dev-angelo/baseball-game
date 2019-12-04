#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <iostream>

class OfficialScorer;

class ScoreBoard
{

public:
    ScoreBoard();
    ~ScoreBoard();

    friend OfficialScorer;

    /**
     * Return ScoreBoard's strike count value.
     *
     * @return strike count value of Score Board.
     */
    unsigned short getStrikeCount() const;

    /**
     * Return ScoreBoard's ball count value
     *
     * @return ball count value of Score Board.
     */
    unsigned short getBallCount() const;

    /**
     * Return ScoreBoard's hits count value.
     *
     * @return hits count value of Score Board.
     */
    unsigned short getHitsCount() const;

    /**
     * Return ScoreBoard's out count value.
     *
     * @return out count value of Score Board.
     */
    unsigned short getOutCount() const;

    /**
     * Return the score of home team or away team through isHomeTeam value.
     *
     * @param isHomeTeam Indicates whether or not it is the home team.
     * @return score.
     */
    unsigned short getTeamScore(const bool isHomeTeam) const;
    unsigned short getTeamScore(const unsigned short inning, const bool isHomeTeam) const;

    unsigned short getTeamPitchingCount(const bool isHomeTeam) const;
    unsigned short getTeamThreeOutCount(const bool isHomeTeam) const;
    unsigned short getTeamHitsCount(const bool isHomeTeam) const;

    void setTeamName(std::vector<std::string> teamName);
    void setTeamMemberName(const std::vector<std::vector<std::string>> teamMemberName);

    void showScoreBoard(const unsigned short nCurrentInning, const unsigned short nCurrentBatterIndex);

    void setIsCurrentHomeTeam(const bool isCurrentHomeTeam);

private:
    unsigned short m_nStrikeCount;
    unsigned short m_nBallCount;
    unsigned short m_nHitsCount;
    unsigned short m_nOutCount;
    bool m_bIsCurrentHomeTeam;

    unsigned short m_lTeamScore[2][6];
    unsigned short m_lTeamPitchingCount[2];
    unsigned short m_lTeamThreeOutCount[2];
    unsigned short m_lTeamHitsCount[2];

    std::vector<std::string> m_lTeamName;
    std::vector<std::vector<std::string>> m_lTeamMemberName;

    void initTeamScore();
    void initTeamPitchingCount();
    void initTeamThreeOutCount();
    void initTeamHitsCount();


    /**
     * Set ScoreBoard's strike count value
     *
     * @param strikeCount for ScoreBoard's strike count.
     */
    void setStrikeCount(const unsigned short strikeCount);

    /**
     * Set ScoreBoard's ball count value
     *
     * @param ballCount for ScoreBoard's ball count.
     */
    void setBallCount(const unsigned short ballCount);

    /**
     * Set ScoreBoard's hits count value
     *
     * @param hitsCount for ScoreBoard's hits count.
     */
    void setHitsCount(const unsigned short hitsCount);

    /**
     * Set ScoreBoard's out count value
     *
     * @param outCount for ScoreBoard's out count.
     */
    void setOutCount(const unsigned short outCount);

    /**
     * Set score of home team or away team through isHomeTeam value.
     *
     * @param score Score to be saved
     * @param isHomeTeam Indicates whether or not it is the home team.
     */
    void setTeamScore(const unsigned short score, const unsigned short inning, const bool isHomeTeam);

    void setTeamPitchingCount(const unsigned short pitchingCount, const bool isHomeTeam);
    void setTeamThreeOutCount(const unsigned short threeOutCount, const bool isHomeTeam);
    void setTeamHitsCount(const unsigned short hitsCount, const bool isHomeTeam);

    void showTitle();
    void showTeamScore();
    void showTeamName();
    void showTeamMemberName(const unsigned short currentInning, const unsigned short batterIndex);
    void showTeamPitchingAndStrikeCount();
    void showTeamThreeStrikeAndBallCount();
    void showTeamHitsAndOutCount();
    void showCurrentInning(const unsigned short currentInning);
};

#endif // SCOREBOARD_H
