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

void OfficialScorer::clearSBHO()
{
    m_pScoreBoard->setStrikeCount(0);
    m_pScoreBoard->setBallCount(0);
    m_pScoreBoard->setHitsCount(0);
    m_pScoreBoard->setOutCount(0);
}

void OfficialScorer::setIsCurrentHomeTeam(const bool isCurrentHomeTeam)
{
    m_bIsCurrentHomeTeam = isCurrentHomeTeam;
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
    m_pScoreBoard->setBallCount(m_pScoreBoard->getBallCount() + 1);

    if ( static_cast<unsigned short>(SBMaximumCount::FOUR_BALL) == m_pScoreBoard->getBallCount() ) {
        handleSBHOFourBallOccurs();

        bEndAtTheBat = true;
    }

    return bEndAtTheBat;
}

bool OfficialScorer::calculateHitOccurs()
{
    bool bEndAtTheBat = true;

    unsigned short nHitsCount = m_pScoreBoard->getHitsCount();
    m_pScoreBoard->setScore(m_pScoreBoard->getScore(getIsCurrentHomeTeam()) + (m_pScoreBoard->getHitsCount() + 1) / 4, getIsCurrentHomeTeam());
    m_pScoreBoard->setHitsCount(++nHitsCount);

    if ( 4 == m_pScoreBoard->getHitsCount() )
        m_pScoreBoard->setHitsCount(0);

    m_pScoreBoard->setStrikeCount(0);
    m_pScoreBoard->setBallCount(0);

    return bEndAtTheBat;
}

bool OfficialScorer::calculateOutOccurs()
{
    bool bEndAtTheBat = true;

    unsigned short nOutCount = m_pScoreBoard->getOutCount();
    m_pScoreBoard->setOutCount(++nOutCount);

    m_pScoreBoard->setStrikeCount(0);
    m_pScoreBoard->setBallCount(0);

    return bEndAtTheBat;
}

bool OfficialScorer::getIsCurrentHomeTeam() const
{
    return m_bIsCurrentHomeTeam;
}

void OfficialScorer::handleSBHOFourBallOccurs()
{
    m_pScoreBoard->setStrikeCount(0);   m_pScoreBoard->setBallCount(0);
    m_pScoreBoard->setScore(m_pScoreBoard->getScore(getIsCurrentHomeTeam()) + (m_pScoreBoard->getHitsCount() + 1) / 4, getIsCurrentHomeTeam());
    m_pScoreBoard->setHitsCount(m_pScoreBoard->getHitsCount() + 1);

    if ( 4 == m_pScoreBoard->getHitsCount())
        m_pScoreBoard->setHitsCount(0);
}
