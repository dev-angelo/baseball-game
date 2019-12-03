#include "pitchingresultgenerator.h"
#include "pitchingresult.h"

#include <cstdlib>
#include <ctime>

PitchingResultGenerator::PitchingResultGenerator()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

PitchingResultGenerator::~PitchingResultGenerator()
{

}

PitchingResult PitchingResultGenerator::generatePitchingResult(const double battingAverage) const
{
    int nStrikeValue = static_cast<int>(((1 - battingAverage)/2 - 0.05)*10000);
    int nBallValue = static_cast<int>(((1 - battingAverage)/2 - 0.05)*10000);
    int nOutValue = static_cast<int>(0.1 * 10000);
    int nBattingValue = static_cast<int>(battingAverage * 10000);
    int nPivotValue = nStrikeValue + nBallValue + nOutValue + nBattingValue;
    int nRandomNumber = std::rand();

    PitchingResult ePitchingResult = determinePitchingType(nRandomNumber, nOutValue, nBattingValue, nStrikeValue, nBallValue, nPivotValue);

    return ePitchingResult;
}

PitchingResult PitchingResultGenerator::determinePitchingType(const int generatedRamdomNumber,
                                                              const int outValue,
                                                              const int battingValue,
                                                              const int strikeValue,
                                                              const int ballValue,
                                                              const int pivotValue) const
{
    PitchingResult ePitchingResult = PitchingResult::STRIKE;

    if ( 0 <= generatedRamdomNumber && generatedRamdomNumber < 32767 * outValue/pivotValue)
        ePitchingResult = PitchingResult::OUT;
    else if ( 32767 * outValue/pivotValue <= generatedRamdomNumber && generatedRamdomNumber < 32767 * (outValue + battingValue)/pivotValue )
        ePitchingResult = PitchingResult::HITS;
    else if ( 32767 * (outValue + battingValue)/pivotValue <= generatedRamdomNumber && generatedRamdomNumber < 32767 * (outValue + battingValue + strikeValue)/pivotValue )
        ePitchingResult = PitchingResult::STRIKE;
    else if ( 32767 * (outValue + battingValue + strikeValue)/pivotValue <= generatedRamdomNumber && generatedRamdomNumber < 32767 * (outValue + battingValue + strikeValue + ballValue)/pivotValue )
        ePitchingResult = PitchingResult::BALL;

    return ePitchingResult;
}
