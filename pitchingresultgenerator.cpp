#include "pitchingresultgenerator.h"
#include "pitchingresult.h"

#include <cstdlib>
#include <ctime>

#include <random>
#include <chrono>

PitchingResultGenerator::PitchingResultGenerator()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

PitchingResultGenerator::~PitchingResultGenerator()
{

}

PitchingResult PitchingResultGenerator::generatePitchingResult(const double battingAverage) const
{
    int nStrikeValue = static_cast<int>(((1 - battingAverage)/2 - 0.05)*100);
    int nBallValue = static_cast<int>(((1 - battingAverage)/2 - 0.05)*100);
    int nOutValue = static_cast<int>(0.1 * 100);
    int nBattingValue = static_cast<int>(battingAverage * 100);
    int nMaxSize = nStrikeValue + nBallValue + nOutValue + nBattingValue;
    int nRandomNumber = generateRandomValue(nMaxSize);

    PitchingResult ePitchingResult = determinePitchingType(nRandomNumber, nOutValue, nBattingValue, nStrikeValue, nBallValue);

    return ePitchingResult;
}

PitchingResult PitchingResultGenerator::determinePitchingType(const int generatedRamdomNumber,
                                                              const int outValue,
                                                              const int battingValue,
                                                              const int strikeValue,
                                                              const int ballValue) const
{
    PitchingResult ePitchingResult = PitchingResult::STRIKE;

    if ( 0 <= generatedRamdomNumber && generatedRamdomNumber < outValue)
        ePitchingResult = PitchingResult::OUT;
    else if ( outValue <= generatedRamdomNumber && generatedRamdomNumber < outValue + battingValue )
        ePitchingResult = PitchingResult::HITS;
    else if ( outValue + battingValue <= generatedRamdomNumber && generatedRamdomNumber < outValue + battingValue + strikeValue )
        ePitchingResult = PitchingResult::STRIKE;
    else if ( outValue + battingValue + strikeValue <= generatedRamdomNumber && generatedRamdomNumber < outValue + battingValue + strikeValue + ballValue )
        ePitchingResult = PitchingResult::BALL;

    return ePitchingResult;
}

int PitchingResultGenerator::generateRandomValue(const int maxSize) const
{
    auto curTime = std::chrono::system_clock::now();
    auto duration = curTime.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    std::mt19937 rnd( millis );

    std::uniform_int_distribution<int> range(1, maxSize);

    return range( rnd );
}
