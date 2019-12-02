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

PitchingResult PitchingResultGenerator::generatePitchingResult(float battingAverage)
{
    int nRandomNumber = std::rand() % 4;

    PitchingResult ePitchingResult = static_cast<PitchingResult>(nRandomNumber);

    return ePitchingResult;
}
