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

    double getMemberBattingAverage(const unsigned short memberIndex) const;
    std::string getMemberName(const unsigned short memberIndex) const;
    std::vector<std::string> getMemberName() const;

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
    std::vector<double> m_lMemberBattingAverage;
    unsigned short m_nNumber;

    static unsigned short objectCount;

    /**
     * Setter about team name.
     */
    void setName(const std::string name);

    /**
     * Input team name from user.
     */
    std::string receiveTeamName() const;

    /**
     * Input member name and member batting average.
     */
    std::vector<std::string> receiveTeamMemberInformation() const;

    /**
     * Parse to separate a string consisting of (Tom, 0.35) etc. by comma
     */
    std::vector<std::string> parseTeamMemberInformation(const std::string buffer) const;

    /**
     * Append member
     * @param name Member's name (ex. Tom)
     * @param battingAverage Member's batting average (ex. 0.325)
     *
     */
    void appendMember(const std::string name, const double battingAverage);

    bool checkUserInputAvailable(const std::string userInput) const;
    unsigned short getContainsCharacterCount(const std::string userInput, const std::string delimiter) const;
    bool checkIsExceptionNotOccur(const std::string userInput) const;
    bool checkIsBattingAverageInRange(const double battingAverage) const;
    bool checkIsStringEmpty(const std::string string) const;
};

#endif // BASEBALLTEAM_H
