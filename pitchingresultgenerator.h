#ifndef PITCHINGRESULTGENERATOR_H
#define PITCHINGRESULTGENERATOR_H

enum class PitchingResult;

class PitchingResultGenerator
{

public:
    PitchingResultGenerator();
    ~PitchingResultGenerator();

    /**
     * Generate Pitching Result
     *
     * @return Result of pitching. (please refer to pitchingresult.h)
     */
    PitchingResult generatePitchingResult(float battingAverage);
};

#endif // PITCHINGRESULTGENERATOR_H
