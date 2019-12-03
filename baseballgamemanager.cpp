#include "baseballgamemanager.h"

#include "pitchingresultgenerator.h"
#include "scoreboard.h"
#include "officialscorer.h"
#include "statusprinter.h"

#include "pitchingresult.h"

#include "baseballteam.h"

#include <iostream>

#define MAXIMUM_OUT_COUNT 2

BaseballGameManager::BaseballGameManager()
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

bool BaseballGameManager::isGameEnd(const unsigned short outCount) const
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

void BaseballGameManager::performUserMenuSelection(const unsigned short userInput)
{
    if ( 1 == userInput ) {
        m_pHomeTeam->inputTeamData();   m_pAwayTeam->inputTeamData();
    }
    else if ( 2 == userInput ) {
        m_pHomeTeam->showTeamData();    m_pAwayTeam->showTeamData();
    }
    else {
        startGame();
    }
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
        m_pOfficialScorer->setCurrentInning(nCurrentInning);
        m_pCurrentAttackTeam = ((nCurrentInning + 1) % 2 == 1) ? m_pHomeTeam : m_pAwayTeam;
        m_pOfficialScorer->setIsCurrentHomeTeam(((nCurrentInning + 1) % 2 == 1) ? true : false);
        m_pStatusPrinter->showAttackTeam(nCurrentInning, m_pCurrentAttackTeam->getName());

        playInning(m_pCurrentAttackTeam);
        ++nCurrentInning;

        m_pOfficialScorer->clearSBHO();
    }

    m_pStatusPrinter->showGameEndComment(m_pHomeTeam->getName(), m_pAwayTeam->getName(), m_pScoreBoard->getTeamScore(true), m_pScoreBoard->getTeamScore(false));
}

bool BaseballGameManager::playAttack(const double battingAverage) const
{
    bool bEndTheAtBat = false;

    while ( false == bEndTheAtBat ) {
        PitchingResult pitchResult = m_pPitchingResultGenerator->generatePitchingResult(battingAverage);
        m_pStatusPrinter->showPitchingResult(m_pScoreBoard->getStrikeCount(), m_pScoreBoard->getBallCount(), pitchResult);
        bEndTheAtBat = m_pOfficialScorer->calculatePitchingResult(pitchResult);
        m_pScoreBoard->showScoreBoard();
        m_pOfficialScorer->increaseTeamPitchingCount();

        if ( true == bEndTheAtBat )
            break;
    }

    return bEndTheAtBat;
}

void BaseballGameManager::playInning(BaseballTeam* pBaseballTeam)
{
    unsigned short nCurrentBatterIndex = 0;
    bool bEndTheAtBat = false;

    while ( false == isGameEnd(m_pScoreBoard->getOutCount()) )
    {
        m_pStatusPrinter->showBatterEnter(nCurrentBatterIndex, pBaseballTeam->getMemberName(nCurrentBatterIndex));
        bEndTheAtBat = playAttack(pBaseballTeam->getMemberBattingAverage(nCurrentBatterIndex));

        if ( true == bEndTheAtBat ) {
            nCurrentBatterIndex = (nCurrentBatterIndex + 1) % 9;
        }
    }
}
