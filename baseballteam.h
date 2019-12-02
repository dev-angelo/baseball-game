#ifndef BASEBALLTEAM_H
#define BASEBALLTEAM_H

#include <iostream>
#include <vector>

class BaseballTeam
{
public:
    BaseballTeam();
    ~BaseballTeam();

    /**
     * Getter about team name.
     */
    std::string getName() const;

    float getMemberBattingAverage(unsigned short memberIndex);
    std::string getMemberName(unsigned short memberIndex);

    /**
     * Input team and team member information from user.
     */
    void inputTeamData();

    /**
     * Print information about team name and all members name & batting average.
     */
    void showTeamData();

private:
    std::string m_strName;
    std::vector<std::string> m_lMemberName;
    std::vector<float> m_lMemberBattingAverage;
    unsigned short m_nNumber;

    static unsigned short objectCount;

    /**
     * Setter about team name.
     */
    void setName(const std::string name);

    /**
     * Input team name from user.
     */
    std::string receiveTeamName();

    /**
     * Input member name and member batting average.
     */
    std::vector<std::string> receiveTeamMemberInformation();

    /**
     * Parse to separate a string consisting of (Tom, 0.35) etc. by comma
     */
    std::vector<std::string> parseTeamMemberInformation(std::string buffer);

    /**
     * Append member
     * @param name Member's name (ex. Tom)
     * @param battingAverage Member's batting average (ex. 0.325)
     *
     */
    void appendMember(std::string name, float battingAverage);

    bool checkUserInputAvailable(std::string userInput);
    unsigned short getContainsCharacterCount(std::string userInput, std::string delimiter);
    bool checkIsExceptionNotOccur(std::string userInput);
};

#endif // BASEBALLTEAM_H
