#ifndef BASEBALLTEAMMEMBER_H
#define BASEBALLTEAMMEMBER_H

#include <iostream>

class BaseballTeamMember
{
public:
    BaseballTeamMember(std::string name, float battingAverage);
    ~BaseballTeamMember();

    /**
     * Getter about member name.
     */
    std::string getName() const;

    /**
     * Getter about member batting average.
     */
    float getBattingAverage() const;

private:
    std::string m_strName;
    float m_fBattingAverage;

};

#endif // BASEBALLTEAMMEMBER_H
