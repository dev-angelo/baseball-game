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
    bool calculatePitchingResult(PitchingResult pitchingResult);

    void clearSBO();

private:
    ScoreBoard* m_pScoreBoard;

    /**
     * Calculate sbo count when strike occurs
     */
    bool calculateStrikeOccurs();

    /**
     * Calculate sbo count when ball occurs
     */
    bool calculateBallOccurs();

    /**
     * Calculate hits count when hits occurs
     */
    bool calculateHitOccurs();

    /**
     * Calculate sbo count when out occurs
     */
    bool calculateOutOccurs();
};

#endif // OFFICIALSCORER_H
