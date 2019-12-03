#include "officialscorer.h"
#include "scoreboard.h"

#include "pitchingresult.h"

OfficialScorer::OfficialScorer(ScoreBoard* scoreBoard) :
    m_pScoreBoard(scoreBoard),
    m_nCurrentInning(0)
{

}

OfficialScorer::~OfficialScorer()
{

}

bool OfficialScorer::calculatePitchingResult(const PitchingResult pitchingResult) const
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

void OfficialScorer::setCurrentInning(const unsigned short currentInning)
{
    m_nCurrentInning = currentInning;
}

void OfficialScorer::increaseTeamPitchingCount() const
{
    bool bIsCurrentHomeTeam = getIsCurrentHomeTeam();

    m_pScoreBoard->setTeamPitchingCount(m_pScoreBoard->getTeamPitchingCount(bIsCurrentHomeTeam) + 1
                                    , bIsCurrentHomeTeam);
}

void OfficialScorer::increaseTeamThreeOutCount() const
{
    bool bIsCurrentHomeTeam = getIsCurrentHomeTeam();

    m_pScoreBoard->setTeamThreeOutCount(m_pScoreBoard->getTeamThreeOutCount(bIsCurrentHomeTeam) + 1
                                    , bIsCurrentHomeTeam);
}

void OfficialScorer::increaseTeamHitsCount() const
{
    bool bIsCurrentHomeTeam = getIsCurrentHomeTeam();

    m_pScoreBoard->setTeamHitsCount(m_pScoreBoard->getTeamHitsCount(bIsCurrentHomeTeam) + 1
                                    , bIsCurrentHomeTeam);
}

bool OfficialScorer::calculateStrikeOccurs() const
{
    bool bEndAtTheBat = false;
    unsigned short nStrikeCount = m_pScoreBoard->getStrikeCount();
    m_pScoreBoard->setStrikeCount(++nStrikeCount);

    if ( static_cast<unsigned short>(SBMaximumCount::THREE_STRIKE) == nStrikeCount ) {
        handleSBHOThreeStrikeOccurs();

        bEndAtTheBat = true;
    }

    return bEndAtTheBat;
}

bool OfficialScorer::calculateBallOccurs() const
{
    bool bEndAtTheBat = false;
    m_pScoreBoard->setBallCount(m_pScoreBoard->getBallCount() + 1);

    if ( static_cast<unsigned short>(SBMaximumCount::FOUR_BALL) == m_pScoreBoard->getBallCount() ) {
        handleSBHOFourBallOccurs();

        bEndAtTheBat = true;
    }

    return bEndAtTheBat;
}

bool OfficialScorer::calculateHitOccurs() const
{
    bool bEndAtTheBat = true;

    m_pScoreBoard->setHitsCount(m_pScoreBoard->getHitsCount() + 1);

    if ( 4 <= m_pScoreBoard->getHitsCount() )
        m_pScoreBoard->setTeamScore(m_pScoreBoard->getTeamScore(getCurrentInning(), getIsCurrentHomeTeam()) + 1,
                                getCurrentInning(), getIsCurrentHomeTeam());

    m_pScoreBoard->setStrikeCount(0);
    m_pScoreBoard->setBallCount(0);

    increaseTeamHitsCount();

    return bEndAtTheBat;
}

bool OfficialScorer::calculateOutOccurs() const
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

void OfficialScorer::handleSBHOThreeStrikeOccurs() const
{
    m_pScoreBoard->setStrikeCount(0);
    m_pScoreBoard->setBallCount(0);

    unsigned short nOutCount = m_pScoreBoard->getOutCount();
    m_pScoreBoard->setOutCount(++nOutCount);

    increaseTeamThreeOutCount();
}

void OfficialScorer::handleSBHOFourBallOccurs() const
{
    m_pScoreBoard->setStrikeCount(0);   m_pScoreBoard->setBallCount(0);
    m_pScoreBoard->setHitsCount(m_pScoreBoard->getHitsCount() + 1);

    if ( 4 <= m_pScoreBoard->getHitsCount())
        m_pScoreBoard->setTeamScore(m_pScoreBoard->getTeamScore(getCurrentInning(), getIsCurrentHomeTeam()) + 1,
                                getCurrentInning(),
                                getIsCurrentHomeTeam());

    increaseTeamHitsCount();
}

unsigned short OfficialScorer::getCurrentInning() const
{
    return m_nCurrentInning;
}
