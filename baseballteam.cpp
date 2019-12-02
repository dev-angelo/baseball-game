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

float BaseballTeam::getMemberBattingAverage(unsigned short memberIndex)
{
    float fBattingAverage = 0;

    if ( m_lMemberBattingAverage.size() < memberIndex ) {
        fBattingAverage = 0;
    }
    else {
        fBattingAverage = m_lMemberBattingAverage.at(memberIndex);
    }

    return fBattingAverage;
}

std::string BaseballTeam::getMemberName(unsigned short memberIndex)
{
    std::string strName;

    if ( m_lMemberName.size() < memberIndex ) {
        strName = "";
    }
    else {
        strName = m_lMemberName.at(memberIndex);
    }

    return strName;
}

void BaseballTeam::inputTeamData()
{
    std::cout << m_nNumber + 1 << "팀의 이름을 입력하세요> ";
    std::string strTeamName = receiveTeamName();
    setName(strTeamName);

    std::cout << std::endl << "타자 정보 입력 (ex. 타이거, 0.3)" << std::endl;
    for ( int index = 0 ; index < 9 ; ++index ) {
        std::cout << index + 1 << "번 타자 정보 입력> ";
        std::vector<std::string> memberInformation = receiveTeamMemberInformation();
        appendMember(memberInformation.at(0), std::stof(memberInformation.at(1)));
    }
}

std::string BaseballTeam::receiveTeamName()
{
    std::string strTeamName;
    std::getline(std::cin, strTeamName);

    return strTeamName;
}

std::vector<std::string> BaseballTeam::receiveTeamMemberInformation()
{
    std::vector<std::string> memberInformation;
    std::string strBuffer = ""; bool bIsErrorNotOccurs = false;

    while ( false == checkUserInputAvailable(strBuffer) || false == bIsErrorNotOccurs ) {
        std::getline(std::cin, strBuffer);

        if ( true == checkUserInputAvailable(strBuffer) ) {
            memberInformation = parseTeamMemberInformation(strBuffer);
            bIsErrorNotOccurs = checkIsExceptionNotOccur(memberInformation.at(1));
        }
        if ( false == checkUserInputAvailable(strBuffer) || false == bIsErrorNotOccurs )
            std::cout << "올바른 팀원 정보를 입력해주세요." << std::endl;
    }

    return memberInformation;
}

std::vector<std::string> BaseballTeam::parseTeamMemberInformation(std::string buffer)
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

void BaseballTeam::appendMember(std::string name, float battingAverage)
{
    m_lMemberName.push_back(name);
    m_lMemberBattingAverage.push_back(battingAverage);
}

bool BaseballTeam::checkUserInputAvailable(std::string userInput)
{
    bool bIsAvailable = false;
    unsigned short commaCount = getContainsCharacterCount(userInput, ",");

    if ( 1 == commaCount ) {
        bIsAvailable = true;
    }
    else {
        bIsAvailable = false;
    }

    return bIsAvailable;
}

unsigned short BaseballTeam::getContainsCharacterCount(std::string userInput, std::string delimiter)
{
    unsigned short occurrences = 0;

    std::string::size_type pos = 0;

    while ((pos = userInput.find(delimiter, pos )) != std::string::npos) {
        ++occurrences;
        pos += delimiter.length();
    }

    return occurrences;
}

bool BaseballTeam::checkIsExceptionNotOccur(std::string userInput)
{
    bool result = true;

    try {
        std::stof(userInput);
    }
    catch (std::invalid_argument) {
        result = false;
    }
    catch (std::out_of_range) {
        result = false;
    }

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
