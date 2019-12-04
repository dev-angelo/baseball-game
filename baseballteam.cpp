#include "baseballteam.h"
#include <sstream>

unsigned short BaseballTeam::objectCount = 0;

BaseballTeam::BaseballTeam() :
    m_strName(""),
    m_nNumber(0)
{
    m_nNumber = objectCount;
    objectCount++;

    m_lMemberName.clear();
    m_lMemberBattingAverage.clear();
}

BaseballTeam::~BaseballTeam()
{
    m_lMemberName.clear();
    m_lMemberBattingAverage.clear();
}

void BaseballTeam::setName(const std::string name)
{
    m_strName = name;
}

std::string BaseballTeam::getName() const
{
    return m_strName;
}

double BaseballTeam::getMemberBattingAverage(const unsigned short memberIndex) const
{
    double fBattingAverage = 0;

    if ( m_lMemberBattingAverage.size() <= memberIndex ) {
        fBattingAverage = 0;
    }
    else {
        fBattingAverage = m_lMemberBattingAverage.at(memberIndex);
    }

    return fBattingAverage;
}

std::string BaseballTeam::getMemberName(const unsigned short memberIndex) const
{
    std::string strName;

    if ( m_lMemberName.size() <= memberIndex ) {
        strName = "";
    }
    else {
        strName = m_lMemberName.at(memberIndex);
    }

    return strName;
}

void BaseballTeam::inputTeamData()
{
    std::cout << std::endl;
    std::cout << m_nNumber + 1 << "팀의 이름을 입력하세요> ";
    std::string strTeamName = receiveTeamName();
    setName(strTeamName);

    std::cout << std::endl << "타자 정보 입력 (이름, 타율 -> ex. 타이거, 0.35) : 0.1 < 타율 < 0.5" << std::endl;
    for ( int index = 0 ; index < 9 ; ++index ) {
        std::cout << index + 1 << "번 타자 정보 입력> ";
        std::vector<std::string> memberInformation = receiveTeamMemberInformation();
        appendMember(memberInformation.at(0), std::stod(memberInformation.at(1)));
    }
    std::cout << std::endl;
}

std::string BaseballTeam::receiveTeamName() const
{
    std::string strTeamName = "";

    while ( true == checkIsStringEmpty(strTeamName) ) {
        std::getline(std::cin, strTeamName);

        if ( true == checkIsStringEmpty(strTeamName) )
            std::cout << "팀 명을 입력해주세요. >";
    }

    return strTeamName;
}

std::vector<std::string> BaseballTeam::receiveTeamMemberInformation() const
{
    std::vector<std::string> memberInformation;
    std::string strBuffer = "";

    while ( false == checkUserInputAvailable(strBuffer) ) {
        std::getline(std::cin, strBuffer);

        if ( true == checkUserInputAvailable(strBuffer) ) {
            memberInformation = parseTeamMemberInformation(strBuffer);
        }
        else {
            std::cout << "올바른 정보를 입력해주세요. >";
        }
    }

    return memberInformation;
}

std::vector<std::string> BaseballTeam::parseTeamMemberInformation(const std::string buffer) const
{
    int count = 0;
    std::string strData;
    std::stringstream streamBuffer; streamBuffer.clear(); streamBuffer.str(buffer);
    std::vector<std::string> memberInformation; memberInformation.clear();

    while ( getline(streamBuffer, strData, ',') ) {
        if ( 2 <= count ) { break; }
        else { memberInformation.push_back(strData); count++; }
    }

    return memberInformation;
}

void BaseballTeam::appendMember(const std::string name, const double battingAverage)
{
    m_lMemberName.push_back(name);
    m_lMemberBattingAverage.push_back(battingAverage);
}

bool BaseballTeam::checkUserInputAvailable(const std::string userInput) const
{
    bool bIsAvailable = false;
    std::vector<std::string> memberInformation;
    unsigned short commaCount = getContainsCharacterCount(userInput, ",");

    if ( 1 == commaCount ) {
        memberInformation = parseTeamMemberInformation(userInput);

        if ( memberInformation.size() == 2 && false == checkIsStringEmpty(memberInformation.at(0)) && false == checkIsStringEmpty(memberInformation.at(1)) &&
            true == checkIsExceptionNotOccur(memberInformation.at(1)) && true == checkIsBattingAverageInRange(std::stod(memberInformation.at(1))))
            bIsAvailable = true;
    }
    else
        bIsAvailable = false;

    return bIsAvailable;
}

unsigned short BaseballTeam::getContainsCharacterCount(const std::string userInput, const std::string delimiter) const
{
    unsigned short occurrences = 0;

    std::string::size_type pos = 0;

    while ((pos = userInput.find(delimiter, pos )) != std::string::npos) {
        ++occurrences;
        pos += delimiter.length();
    }

    return occurrences;
}

bool BaseballTeam::checkIsExceptionNotOccur(const std::string userInput) const
{
    bool result = true;

    try {
        std::stod(userInput);
    }
    catch (std::invalid_argument) {
        result = false;
    }
    catch (std::out_of_range) {
        result = false;
    }

    return result;
}

bool BaseballTeam::checkIsBattingAverageInRange(const double battingAverage) const
{
    bool result = false;

    if ( (static_cast<double>(0.1) < battingAverage) &&
         (static_cast<double>(0.5) > battingAverage) ) {
        result = true;
    }
    else {
        result = false;
    }

    return result;
}

bool BaseballTeam::checkIsStringEmpty(const std::string string) const
{
    bool result = false;

    if ( true == string.empty() )
        result = true;

    if ( true == (string.find_first_not_of(' ') == std::string::npos) )
        result = true;

    return result;
}

void BaseballTeam::showTeamData()
{
    std::cout << getName() << " 팀 정보" << std::endl;

    for ( std::vector<int>::size_type index = 0 ; index < 9 ; ++index )
    {
        std::cout << index + 1 << "번 " << m_lMemberName.at(index) << ", "
                  << m_lMemberBattingAverage.at(index) << std::endl;
    }
}
