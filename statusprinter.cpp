#include "statusprinter.h"
#include "pitchingresult.h"

#include <iostream>

StatusPrinter::StatusPrinter()
{

}

StatusPrinter::~StatusPrinter()
{

}

void StatusPrinter::showPitchingResult(unsigned short strike,
                                       unsigned short ball,
                                       PitchingResult pitchingResult)
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

void StatusPrinter::showScoreBoard(unsigned short strikeCount, unsigned short ballCount, unsigned short outCount)
{
    std::cout << strikeCount << "S " << ballCount << "B " << outCount << "O"
              << std::endl << std::endl;
}

void StatusPrinter::showNextBatter()
{
    std::cout << " 다음 타자가 타석에 입장했습니다." << std::endl;
}

void StatusPrinter::showGameEndComment(unsigned short hitsCount)
{
    std::cout << "최종 안타수 : " << hitsCount << std::endl;
    std::cout << "GAME OVER" << std::endl;
}

void StatusPrinter::showStrikeOccurs(unsigned short strike)
{
    std::cout << "스트라이크!" << std::endl;

    if ( 3 == ++strike )
    {
        showThreeStrikeOutOccursComment();
    }
}
void StatusPrinter::showBallOccurs(unsigned short ball)
{
    std::cout << "볼!" << std::endl;

    if ( 4 == ++ball )
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

void StatusPrinter::showBatterEnter(unsigned short batterNumber, std::string batterName)
{
    std::cout << batterNumber + 1 << "번 " << batterName << std::endl;
}

void StatusPrinter::showInningTopBottom(unsigned short inning)
{
    bool bIsTop = (inning + 1) % 2;

    std::cout << (inning / 2) + 1 << "회" << (true == bIsTop ? "초" : "말") << " ";
}

void StatusPrinter::showAttackTeam(std::string teamName)
{
    std::cout << teamName << "의 공격" << std::endl;
}
