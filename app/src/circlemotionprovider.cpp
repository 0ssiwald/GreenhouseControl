#include "circlemotionprovider.h"

#include <QtMath>
#include <QtDebug>

namespace logic {

CircleMotionProvider::CircleMotionProvider(float freq, float amp, float off, bool dir) :
    QObject(nullptr), tMSec(0), frequencyHz(freq), amplitudePixel(amp), offsetRadians(off), directionCW(dir)
{
    qDebug() << "Init circle motion provider with" << freq << "Hz frequency," << amp << " pixel amplitude, "
             << off << " radians offset, roating" << (directionCW? "clockwise" : "anti-clockwise");
}

void CircleMotionProvider::setRocket(Rocket * r) {
    rocket = r;
}

Rocket * CircleMotionProvider::getRocket() {
    return rocket;
}

float CircleMotionProvider::getFrequency() const
{
    return frequencyHz;
}

void CircleMotionProvider::setFrequency(float freq)
{
    frequencyHz = freq;
}

float CircleMotionProvider::getAmplitude() const
{
    return amplitudePixel;
}

void CircleMotionProvider::setAmplitude(float amp)
{
    amplitudePixel = amp;
}


float CircleMotionProvider::getOffset() const
{
     return offsetRadians;
}

void CircleMotionProvider::setOffset(float off)
{
    offsetRadians = off;
}

bool CircleMotionProvider::directionIsClockwise() const
{
    return directionCW;
}

void CircleMotionProvider::setRotationClockwise()
{
    directionCW = true;
}

void CircleMotionProvider::setRotationAntiClockwise()
{
    directionCW = false;
}

float CircleMotionProvider::angle() const
{
    // NOTE: The following code does not take care of the wrap-around at max int boundary
    // DO NOT use on systems with <=32 bits int width that run continuously for longer than 49 days
    float angle = 2*M_PI * frequencyHz / 1000 * tMSec + offsetRadians;
    if (directionCW) return -angle;
    else return angle;
}


void CircleMotionProvider::update(int deltaTMSec)
{
    tMSec += deltaTMSec;

    // Determine new cartesian position along a circle path depending on radial position t
    const float w = angle();
    float off_x = amplitudePixel * qSin(w);
    float off_y = amplitudePixel * qCos(w);

    // Store new position in rocket
    if (rocket != nullptr) {
        rocket->setRelativePosition(off_x, off_y);
        rocket->setAngle(w);
    }
}

} // end namespace logic



