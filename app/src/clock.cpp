#include "clock.h"

#include <QtDebug>

namespace physics {

Clock::Clock(int seconds_per_tick) : QObject(nullptr)
{
    setSecondsPerTick(seconds_per_tick);
    QObject::connect(&timer, &QTimer::timeout, this, &Clock::tick);
}

int Clock::getSecondsPerTick() const
{
    return timer.interval() / 1000;
}

void Clock::setSecondsPerTick(int seconds_per_tick)
{
    timer.setInterval(1000 * seconds_per_tick);
}

void Clock::start()
{
    timer.start();
    lastStartTime = QTime::currentTime();
    qDebug() << "Starting clock with" << getSecondsPerTick() << "seconds per tick";
}

void Clock::stop()
{
    timer.stop();
    qDebug() << "Stopping  clock";
}

void Clock::tick()
{
    QTime now = QTime::currentTime();
    int deltaMSec = lastStartTime.msecsTo(now);
    lastStartTime = now;
    emit update(deltaMSec);
}

} // end namespace physics
