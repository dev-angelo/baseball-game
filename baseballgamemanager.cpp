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

    while ( 5 != selectedMenu )
    {
        showMenu();
        selectedMenu = receiveUserMenuSelect();
        performUserMenuSelection(selectedMenu);
    }
}

bool BaseballGameManager::isGameEnd(unsigned short outCount)
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
    std::cout << "1. 데이터 입력" << std::endl;
    std::cout << "2. 데이터 출력" << std::endl;
    std::cout << "3. 시합 시작" << std::endl << std::endl;

    std::cout << "메뉴선택 (1 - 2) : ";
}

unsigned short BaseballGameManager::receiveUserMenuSelect()
{
    unsigned short userInput = 0;
    std::cin >> userInput;

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    return userInput;
}

void BaseballGameManager::performUserMenuSelection(unsigned short userInput)
{
    if ( 1 == userInput ) {
        m_pHomeTeam->inputTeamData();   std::cout << std::endl;
        m_pAwayTeam->inputTeamData();
    }
    else if ( 2 == userInput ) {
        m_pHomeTeam->showTeamData();    std::cout << std::endl;
        m_pAwayTeam->showTeamData();
    }
    else {
        startGame();
    }
}

void BaseballGameManager::startGame()
{
    unsigned short nCurrentInning = 0;

    while ( 13 > nCurrentInning )
    {
        m_pCurrentAttackTeam = (nCurrentInning % 2 == 0) ? m_pHomeTeam : m_pAwayTeam;
        m_pStatusPrinter->showInningTopBottom(nCurrentInning);
        m_pStatusPrinter->showAttackTeam(m_pCurrentAttackTeam->getName());

        playInning(m_pCurrentAttackTeam);
        ++nCurrentInning;

        m_pOfficialScorer->clearSBO();
    }
}

bool BaseballGameManager::playAttack(float battingAverage)
{
    bool bEndTheAtBat = false;

    while ( false == bEndTheAtBat )
    {
        PitchingResult pitchResult = m_pPitchingResultGenerator->generatePitchingResult(battingAverage);

        m_pStatusPrinter->showPitchingResult(m_pScoreBoard->getStrikeCount(), m_pScoreBoard->getBallCount(), pitchResult);
        bEndTheAtBat = m_pOfficialScorer->calculatePitchingResult(pitchResult);
        m_pStatusPrinter->showScoreBoard(m_pScoreBoard->getStrikeCount(), m_pScoreBoard->getBallCount(), m_pScoreBoard->getOutCount());

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
