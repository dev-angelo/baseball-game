#include "statusprinter.h"
#include "pitchingresult.h"

#include <iostream>

StatusPrinter::StatusPrinter()
{

}

StatusPrinter::~StatusPrinter()
{

}

void StatusPrinter::showPitchingResult(const unsigned short strike,
                                       const unsigned short ball,
                                       const PitchingResult pitchingResult)
{
    if ( PitchingResult::STRIKE == pitchingResult ) {
        showStrikeOccurs(strike);
    }
    else if ( PitchingResult::BALL == pitchingResult ) {
        showBallOccurs(ball);
    }
    else if ( PitchingResult::HITS == pitchingResult ) {
        showHitsOccurs();
    }
    else if ( PitchingResult::OUT == pitchingResult ) {
        showOutOccurs();
    }
}

void StatusPrinter::showScoreBoard(const unsigned short strikeCount,
                                   const unsigned short ballCount,
                                   const unsigned short outCount)
{
    std::cout << strikeCount << "S " << ballCount << "B " << outCount << "O"
              << std::endl << std::endl;
}

void StatusPrinter::showNextBatter()
{
    std::cout << " 다음 타자가 타석에 입장했습니다." << std::endl;
}

void StatusPrinter::showGameEndComment(const std::string homeTeamName,
                                       const std::string awayTeamName,
                                       const unsigned short homeTeamScore,
                                       const unsigned short awayTeamScore)
{
    std::cout << std::endl << "경기 종료" << std::endl << std::endl;
    std::cout << homeTeamName << " VS " << awayTeamName << std::endl;
    std::cout << homeTeamScore << " : " << awayTeamScore << std::endl;

    if ( homeTeamScore == awayTeamScore )
        std::cout << "무승부입니다!" << std::endl;

    std::cout << "Thank you!" << std::endl;
}

void StatusPrinter::showStrikeOccurs(const unsigned short strike)
{
    std::cout << "스트라이크!" << std::endl;

    if ( 3 == strike + 1)
    {
        showThreeStrikeOutOccursComment();
    }
}
void StatusPrinter::showBallOccurs(const unsigned short ball)
{
    std::cout << "볼!" << std::endl;

    if ( 4 == ball + 1 )
    {
        showFourBallHitsOccursComment();
    }
}

void StatusPrinter::showHitsOccurs()
{
    std::cout << "안타!" << std::endl;
}

void StatusPrinter::showOutOccurs()
{
    std::cout << "아웃!" << std::endl;
}

void StatusPrinter::showThreeStrikeOutOccursComment()
{
    std::cout << std::endl << "아웃! (삼진)" << std::endl;
}

void StatusPrinter::showFourBallHitsOccursComment()
{
    std::cout << std::endl << "안타! (4볼)" << std::endl;
}

void StatusPrinter::showBatterEnter(const unsigned short batterNumber, const std::string batterName)
{
    std::cout << batterNumber + 1 << "번 " << batterName << std::endl;
}

void StatusPrinter::showInningTopBottom(const unsigned short inning)
{
    bool bIsTop = (inning + 1) % 2;

    std::cout << (inning / 2) + 1 << "회" << (true == bIsTop ? "초" : "말") << " ";
}

void StatusPrinter::showAttackTeam(const std::string teamName)
{
    std::cout << teamName << "의 공격" << std::endl;
}
