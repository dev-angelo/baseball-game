#ifndef SCOREBOARD_H
#define SCOREBOARD_H

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
    unsigned short getScore(const bool isHomeTeam) const;
    unsigned short getScore(const unsigned short inning, const bool isHomeTeam) const;

private:
    unsigned short m_nStrikeCount;
    unsigned short m_nBallCount;
    unsigned short m_nHitsCount;
    unsigned short m_nOutCount;

    unsigned short m_lTeamScore[2][6];
    unsigned short m_lTeamPitchingCount[2][6];
    unsigned short m_lTeamThreeOutCount[2][6];
    unsigned short m_lTeamHitsCount[2][6];

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
    void setScore(const unsigned short score, const unsigned short inning, const bool isHomeTeam);
};

#endif // SCOREBOARD_H
