#pragma once
#include <QObject>
#include "rocket.h"

namespace logic {

class CircleMotionProvider : public QObject
{
    Q_OBJECT

public:

    explicit CircleMotionProvider(float frequency = 1.0, float amplitude = 100.0,
                                  float offset = 0.0, bool direction = true);

    Rocket * getRocket();
    void setRocket(Rocket * r); // used for dependency injection

    float getFrequency() const;
    void setFrequency(float freq);

    float getAmplitude() const;
    void setAmplitude(float amp);

    float getOffset() const;
    void setOffset(float off);

    bool directionIsClockwise() const;
    void setRotationClockwise();
    void setRotationAntiClockwise();

    float angle() const; // current angle of circular motion in radians

public slots:
    void update(int deltaTMSec);

private:

    int tMSec;  // accumulates time in milliseconds

    float frequencyHz;
    float amplitudePixel;
    float offsetRadians;
    bool directionCW;   // true if clockwise

    Rocket * rocket; // Association to single Rocket object
};

} // end namespace logic

