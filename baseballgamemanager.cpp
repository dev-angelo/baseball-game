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

void BaseballGameManager::startGame()
{
    std::cout << "신나는 야구 게임!" << std::endl;

    unsigned short selectedMenu = 0;

    while ( 3 != selectedMenu )
    {
        showMenu();
        selectedMenu = receiveUserMenuSelect();
        performUserMenuSelection(selectedMenu);
    }
}

void BaseballGameManager::playInning()
{
    PitchingResult pitchResult = m_pPitchingResultGenerator->generatePitchingResult();

    m_pStatusPrinter->showPitchingResult(m_pScoreBoard->getStrikeCount(), m_pScoreBoard->getBallCount(),
                                         pitchResult);


    bool bEndTheAtBat = m_pOfficialScorer->calculatePitchingResult(pitchResult);

    if ( (true == bEndTheAtBat ) && (false == isGameEnd(m_pScoreBoard->getOutCount())) ) {
        m_pStatusPrinter->showNextBatter();
    }
    else {
        std::cout << std::endl;
    }

    m_pStatusPrinter->showScoreBoard(m_pScoreBoard->getStrikeCount(), m_pScoreBoard->getBallCount(), m_pScoreBoard->getOutCount());
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
    std::cout << "2. 데이터 출력" << std::endl << std::endl;

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
    switch (userInput)
    {
    case 1:
        m_pHomeTeam->inputTeamData();
        m_pAwayTeam->inputTeamData();
        break;
    case 2:
        m_pHomeTeam->showTeamData();
        m_pAwayTeam->showTeamData();
        break;
    default:
        break;
    }
}
