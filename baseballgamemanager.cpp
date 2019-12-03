#include "baseballgamemanager.h"

#include "pitchingresultgenerator.h"
#include "scoreboard.h"
#include "officialscorer.h"
#include "statusprinter.h"

#include "pitchingresult.h"

#include "baseballteam.h"

#include <iostream>

#define MAXIMUM_OUT_COUNT 2

BaseballGameManager::BaseballGameManager() :
    m_nSkipInning(0)
{
    m_pPitchingResultGenerator = new PitchingResultGenerator;
    m_pScoreBoard = new ScoreBoard;
    m_pOfficialScorer = new OfficialScorer(m_pScoreBoard);
    m_pStatusPrinter = new StatusPrinter;

    m_pHomeTeam = new BaseballTeam;
    m_pAwayTeam = new BaseballTeam;

    m_pCurrentAttackTeam = m_pHomeTeam;
}

BaseballGameManager::~BaseballGameManager()
{
    delete m_pPitchingResultGenerator;
    delete m_pOfficialScorer;
    delete m_pScoreBoard;
    delete m_pStatusPrinter;
}

void BaseballGameManager::run()
{
    std::cout << "신나는 야구 게임!" << std::endl;

    unsigned short selectedMenu = 0;
    bool bIsUserSelectionAvailable = false;

    while ( (3 != selectedMenu) || (false == bIsUserSelectionAvailable) ) {
        showMenu();
        selectedMenu = receiveUserMenuSelect();

        bIsUserSelectionAvailable = checkUserMenuSelectionAvailable(selectedMenu);

        if ( true == bIsUserSelectionAvailable )
            performUserMenuSelection(selectedMenu);
    }
}

bool BaseballGameManager::isInningEnd(const unsigned short outCount) const
{
    bool result = false;

    if ( MAXIMUM_OUT_COUNT < outCount )
    {
        result = true;
    }
    else
    {
        result = false;
    }

    return result;
}

void BaseballGameManager::showMenu()
{
    std::cout << std::endl;

    std::cout << "1. 데이터 입력" << std::endl;
    std::cout << "2. 데이터 출력" << std::endl;
    std::cout << "3. 시합 시작" << std::endl << std::endl;

    std::cout << "메뉴선택 (1 - 3) : ";
}

unsigned short BaseballGameManager::receiveUserMenuSelect() const
{
    unsigned short userInput = 0;
    std::cin >> userInput;

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    return userInput;
}

void BaseballGameManager::receiveUserMenuSelectInGame(const unsigned short nCurrentInning)
{
    std::string num= "sampleStr";

    while ( (false == num.empty() && 0 == std::atoi(num.c_str())) ||
            ((false == num.empty() && (std::atoi(num.c_str()) < nCurrentInning/2 + 1))) ||
            ((false == num.empty() &&(std::atoi(num.c_str()) > 6))) ) {
        std::cout << "다음 투구 보기(enter) or 스킵하고 X회말 후 투구보기(숫자+enter) ? ";
        std::getline(std::cin, num);
    }

    if ( false == num.empty() && std::atoi(num.c_str()) != 0 ) {
        setSkipInning(static_cast<unsigned short>(std::atoi(num.c_str())));
    }
}

void BaseballGameManager::performUserMenuSelection(const unsigned short userInput)
{
    if ( 1 == userInput ) {
        performInputTeamData();
    }
    else if ( 2 == userInput ) {
        performShowTeamData();
    }
    else {
        startGame();
    }
}

void BaseballGameManager::performInputTeamData()
{
    std::vector<std::string> lTeamName;
    std::vector<std::vector<std::string>> lMemberName;

    m_pHomeTeam->inputTeamData();
    m_pAwayTeam->inputTeamData();

    lTeamName.push_back(m_pHomeTeam->getName());
    lTeamName.push_back(m_pAwayTeam->getName());

    lMemberName.push_back(m_pHomeTeam->getMemberName());
    lMemberName.push_back(m_pAwayTeam->getMemberName());

    m_pScoreBoard->setTeamName(lTeamName);
    m_pScoreBoard->setTeamMemberName(lMemberName);
}

void BaseballGameManager::performShowTeamData()
{
    m_pHomeTeam->showTeamData();
    m_pAwayTeam->showTeamData();
}

bool BaseballGameManager::checkUserMenuSelectionAvailable(const unsigned short userInput) const
{
    bool result = false;

    if ( ((2 == userInput) || (3 == userInput)) && (true == m_pHomeTeam->getName().empty()) ) {
        std:: cout << "팀 정보를 입력하세요." << std::endl;
    }
    else if ( (3 < userInput) || (1 > userInput) ) {
        std::cout << "올바르지 않은 번호입니다." << std::endl;
    }
    else {
        result = true;
    }

    return result;
}

void BaseballGameManager::startGame()
{
    unsigned short nCurrentInning = 0;

    while ( 12 > nCurrentInning ) {
        setComponent(nCurrentInning);

        playInning(nCurrentInning);
        ++nCurrentInning;

        m_pOfficialScorer->clearSBHO();

        if ( (11 == nCurrentInning) && (m_pScoreBoard->getTeamScore(false) > m_pScoreBoard->getTeamScore(true)) )
            break;
    }

    m_pStatusPrinter->showGameEndComment(m_pHomeTeam->getName(), m_pAwayTeam->getName(), m_pScoreBoard->getTeamScore(true), m_pScoreBoard->getTeamScore(false));
}

bool BaseballGameManager::playAttack(const unsigned short nCurrentBatterIndex)
{
    bool bEndTheAtBat = false;
    unsigned short strikeCount = m_pScoreBoard->getStrikeCount();
    unsigned short ballCount = m_pScoreBoard->getBallCount();

    PitchingResult pitchResult = m_pPitchingResultGenerator->generatePitchingResult(m_pCurrentAttackTeam->getMemberBattingAverage(nCurrentBatterIndex));

    bEndTheAtBat = m_pOfficialScorer->calculatePitchingResult(pitchResult);
    m_pOfficialScorer->increaseTeamPitchingCount();

    m_pScoreBoard->showScoreBoard();
    m_pStatusPrinter->showBatterEnter(nCurrentBatterIndex, m_pCurrentAttackTeam->getMemberName(nCurrentBatterIndex));
    m_pStatusPrinter->showPitchingResult(strikeCount, ballCount, pitchResult);
    m_pStatusPrinter->showCurrentSBO(m_pScoreBoard->getStrikeCount(), m_pScoreBoard->getBallCount(), m_pScoreBoard->getOutCount());

    return bEndTheAtBat;
}

void BaseballGameManager::setComponent(const unsigned short currentInning)
{
    bool bIsHomeTeam = ((currentInning + 1) % 2 == 1) ? true : false;

    m_pCurrentAttackTeam = (true == bIsHomeTeam) ? m_pHomeTeam : m_pAwayTeam;

    m_pOfficialScorer->setCurrentInning(currentInning);
    m_pOfficialScorer->setIsCurrentHomeTeam(bIsHomeTeam);

    m_pScoreBoard->setIsCurrentHomeTeam(bIsHomeTeam);
    m_pScoreBoard->setCurrentInning(currentInning);
}

void BaseballGameManager::setSkipInning(const unsigned short skipInning)
{
    m_nSkipInning = skipInning;
}

unsigned short BaseballGameManager::getSkipInning() const
{
    return m_nSkipInning;
}

void BaseballGameManager::playInning(unsigned short nCurrentInning)
{
    unsigned short nCurrentBatterIndex = 0;
    bool bEndTheAtBat = false;

    while ( false == isInningEnd(m_pScoreBoard->getOutCount()) ) {
        if ( ( getSkipInning() * 2 - 1 < nCurrentInning) &&(m_pScoreBoard->getTeamPitchingCount(true) != 0))
            receiveUserMenuSelectInGame(nCurrentInning);

        bEndTheAtBat = playAttack(nCurrentBatterIndex);

        if ( true == bEndTheAtBat )
            nCurrentBatterIndex = (nCurrentBatterIndex + 1) % 9;
    }
}
