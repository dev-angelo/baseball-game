#ifndef OFFICIALSCORER_H
#define OFFICIALSCORER_H

#include <map>

class ScoreBoard;
enum class PitchingResult;

class OfficialScorer
{
public:
    OfficialScorer(ScoreBoard* scoreBoard);
    ~OfficialScorer();

    /**
     * Calculate strike, ball, hits, out through pithing result
     *
     * @param pitchingResult
     * @return If out occurs or on base (true), else (false)
     */
    bool calculatePitchingResult(const PitchingResult pitchingResult) const;

    /**
     * Clear current Strike, Ball, Hits, Out value
     */
    void clearSBHO();

    /**
     * Function to set whether the current home team's attack turn or away team's attack turn.
     *
     * @param isCurrentHomeTeam A value indicating whether the attacking team is home or not.
     */
    void setIsCurrentHomeTeam(const bool isCurrentHomeTeam);

    void setCurrentInning(const unsigned short currentInning);

    void increaseTeamPitchingCount() const;
    void increaseTeamThreeOutCount() const;
    void increaseTeamHitsCount() const;

private:
    ScoreBoard* m_pScoreBoard;
    bool m_bIsCurrentHomeTeam;
    unsigned short m_nCurrentInning;

    /**
     * Calculate strike count when strike occurs
     */
    bool calculateStrikeOccurs() const;

    /**
     * Calculate ball count when ball occurs
     */
    bool calculateBallOccurs() const;

    /**
     * Calculate hits count when hits occurs
     */
    bool calculateHitOccurs() const;

    /**
     * Calculate out count when out occurs
     */
    bool calculateOutOccurs() const;

    /**
     * Return whether the current home team's attack turn or away team's attack turn.
     */
    bool getIsCurrentHomeTeam() const;

    /**
     * Function to handle SBHO when 4 balls occur
     */
    void handleSBHOFourBallOccurs() const;
    void handleSBHOThreeStrikeOccurs() const;

    unsigned short getCurrentInning() const;
};

#endif // OFFICIALSCORER_H
