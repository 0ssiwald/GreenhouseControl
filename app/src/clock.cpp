#include "clock.h"

#include <QtDebug>

namespace physics {

Clock::Clock(int framerate) : QObject(nullptr)
{
    setFramerate(framerate);
    QObject::connect(&timer, &QTimer::timeout, this, &Clock::tick);
}

int Clock::getFramerate() const
{
    return 1000 / timer.interval();
}

void Clock::setFramerate(int perSecondsGoal)
{
    timer.setInterval(1000 / perSecondsGoal);
}

void Clock::start()
{
    timer.start();
    lastStartTime = QTime::currentTime();
    qDebug() << "Starting simulation clock with" << getFramerate() << "fps";
}

void Clock::stop()
{
    timer.stop();
    qDebug() << "Stopping simulation clock";
}

void Clock::tick()
{
    QTime now = QTime::currentTime();
    int deltaMSec = lastStartTime.msecsTo(now);
    lastStartTime = now;
    emit update(deltaMSec);
}

} // end namespace physics
