#include "baseballteammember.h"

BaseballTeamMember::BaseballTeamMember(std::string name, float battingAverage) :
    m_strName(name),
    m_fBattingAverage(battingAverage)
{

}

BaseballTeamMember::~BaseballTeamMember()
{

}

std::string BaseballTeamMember::getName() const
{
    return m_strName;
}

float BaseballTeamMember::getBattingAverage() const
{
    return m_fBattingAverage;
}
