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
    PitchingResult generatePitchingResult(const double battingAverage) const;
    PitchingResult determinePitchingType(const int generatedRamdomNumber,
                                         const int outValue,
                                         const int battingValue,
                                         const int strikeValue,
                                         const int ballValue) const;

    int generateRandomValue(const int maxSize) const;
};

#endif // PITCHINGRESULTGENERATOR_H

