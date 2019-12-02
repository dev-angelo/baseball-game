#include "scoreboard.h"

ScoreBoard::ScoreBoard() :
    m_nStrikeCount(0),
    m_nBallCount(0),
    m_nHitsCount(0),
    m_nOutCount(0)
{
    for ( int index = 0 ; index < 6 ; ++index )
    {
        m_lHomeTeamScore[index] = 0;
        m_lAwayTeamScore[index] = 0;
    }
}

ScoreBoard::~ScoreBoard()
{

}

void ScoreBoard::setStrikeCount(const unsigned short strikeCount)
{
    m_nStrikeCount = strikeCount;
}

void ScoreBoard::setBallCount(const unsigned short ballCount)
{
    m_nBallCount = ballCount;
}

void ScoreBoard::setHitsCount(const unsigned short hitsCount)
{
    m_nHitsCount = hitsCount;
}

void ScoreBoard::setOutCount(const unsigned short outCount)
{
    m_nOutCount = outCount;
}

void ScoreBoard::setScore(const unsigned short score,
                          const unsigned short inning,
                          const bool isHomeTeam)
{
    unsigned short nCvtInning = (inning / 2);

    if ( true == isHomeTeam ) {
        m_lHomeTeamScore[nCvtInning] = score;
    }
    else {
        m_lAwayTeamScore[nCvtInning] = score;
    }
}

unsigned short ScoreBoard::getStrikeCount() const
{
    return m_nStrikeCount;
}

unsigned short ScoreBoard::getBallCount() const
{
    return m_nBallCount;
}

unsigned short ScoreBoard::getHitsCount() const
{
    return m_nHitsCount;
}

unsigned short ScoreBoard::getOutCount() const
{
    return m_nOutCount;
}

unsigned short ScoreBoard::getScore(const bool isHomeTeam) const
{
    unsigned short nScore = 0;
    const unsigned short* pCurrentTeamScore = (isHomeTeam == true) ? m_lHomeTeamScore : m_lAwayTeamScore;

    for ( int index = 0 ; index < 6 ; ++index ) {
        nScore += *(pCurrentTeamScore + index);
    }

    return nScore;
}

unsigned short ScoreBoard::getScore(const unsigned short inning, const bool isHomeTeam) const
{
    unsigned short nScore = 0;
    unsigned short nCvtInning = (inning / 2);

    if ( true == isHomeTeam ) {
        nScore = m_lHomeTeamScore[nCvtInning];
    }
    else {
        nScore = m_lAwayTeamScore[nCvtInning];
    }

    return nScore;
}
