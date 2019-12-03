#include "scoreboard.h"

ScoreBoard::ScoreBoard() :
    m_nStrikeCount(0),
    m_nBallCount(0),
    m_nHitsCount(0),
    m_nOutCount(0)
{
    initTeamScore();
    initTeamPitchingCount();
    initTeamThreeOutCount();
    initTeamHitsCount();
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
        m_lTeamScore[0][nCvtInning] = score;
    }
    else {
        m_lTeamScore[1][nCvtInning] = score;
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
    const unsigned short* pCurrentTeamScore = (isHomeTeam == true) ? m_lTeamScore[0] : m_lTeamScore[1];

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
        nScore = m_lTeamScore[0][nCvtInning];
    }
    else {
        nScore = m_lTeamScore[1][nCvtInning];
    }

    return nScore;
}

void ScoreBoard::initTeamScore()
{
    for ( int teamIndex = 0 ; teamIndex < 2 ; ++teamIndex )
    {
        for ( int memberIndex = 0 ; memberIndex < 6 ; ++memberIndex )
        {
            m_lTeamScore[teamIndex][memberIndex] = 0;
        }
    }
}

void ScoreBoard::initTeamPitchingCount()
{
    for ( int teamIndex = 0 ; teamIndex < 2 ; ++teamIndex )
    {
        for ( int memberIndex = 0 ; memberIndex < 6 ; ++memberIndex )
        {
            m_lTeamPitchingCount[teamIndex][memberIndex] = 0;
        }
    }
}

void ScoreBoard::initTeamThreeOutCount()
{
    for ( int teamIndex = 0 ; teamIndex < 2 ; ++teamIndex )
    {
        for ( int memberIndex = 0 ; memberIndex < 6 ; ++memberIndex )
        {
            m_lTeamThreeOutCount[teamIndex][memberIndex] = 0;
        }
    }
}

void ScoreBoard::initTeamHitsCount()
{
    for ( int teamIndex = 0 ; teamIndex < 2 ; ++teamIndex )
    {
        for ( int memberIndex = 0 ; memberIndex < 6 ; ++memberIndex )
        {
            m_lTeamHitsCount[teamIndex][memberIndex] = 0;
        }
    }
}
