#include "officialscorer.h"
#include "scoreboard.h"

#include "pitchingresult.h"

OfficialScorer::OfficialScorer(ScoreBoard* scoreBoard) :
    m_pScoreBoard(scoreBoard)
{

}

OfficialScorer::~OfficialScorer()
{

}

bool OfficialScorer::calculatePitchingResult(PitchingResult pitchingResult)
{
    bool bEndAtTheBat = false;

    if ( PitchingResult::STRIKE == pitchingResult ) {
        bEndAtTheBat = calculateStrikeOccurs();
    }
    else if ( PitchingResult::BALL == pitchingResult ) {
        bEndAtTheBat = calculateBallOccurs();
    }
    else if ( PitchingResult::HITS == pitchingResult ) {
        bEndAtTheBat = calculateHitOccurs();
    }
    else if ( PitchingResult::OUT == pitchingResult ) {
        bEndAtTheBat = calculateOutOccurs();
    }

    return bEndAtTheBat;
}

bool OfficialScorer::calculateStrikeOccurs()
{
    bool bEndAtTheBat = false;
    unsigned short nStrikeCount = m_pScoreBoard->getStrikeCount();
    m_pScoreBoard->setStrikeCount(++nStrikeCount);

    if ( static_cast<unsigned short>(SBMaximumCount::THREE_STRIKE) == nStrikeCount ) {
        m_pScoreBoard->setStrikeCount(0);
        m_pScoreBoard->setBallCount(0);

        unsigned short nOutCount = m_pScoreBoard->getOutCount();
        m_pScoreBoard->setOutCount(++nOutCount);

        bEndAtTheBat = true;
    }

    return bEndAtTheBat;
}

bool OfficialScorer::calculateBallOccurs()
{
    bool bEndAtTheBat = false;
    unsigned short nBallCount = m_pScoreBoard->getBallCount();
    m_pScoreBoard->setBallCount(++nBallCount);

    if ( static_cast<unsigned short>(SBMaximumCount::FOUR_BALL) == nBallCount ) {
        m_pScoreBoard->setStrikeCount(0);
        m_pScoreBoard->setBallCount(0);

        unsigned short nHitsCount = m_pScoreBoard->getHitsCount();
        m_pScoreBoard->setHitsCount(++nHitsCount);

        bEndAtTheBat = true;
    }

    return bEndAtTheBat;
}

bool OfficialScorer::calculateHitOccurs()
{
    bool bEndAtTheBat = true;

    unsigned short nHitsCount = m_pScoreBoard->getHitsCount();
    m_pScoreBoard->setHitsCount(++nHitsCount);

    return bEndAtTheBat;
}

bool OfficialScorer::calculateOutOccurs()
{
    bool bEndAtTheBat = true;

    unsigned short nOutCount = m_pScoreBoard->getOutCount();
    m_pScoreBoard->setOutCount(++nOutCount);

    return bEndAtTheBat;
}
