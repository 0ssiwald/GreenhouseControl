#include "clock.h"
#include <QtDebug>

namespace physics {

Clock::Clock(int seconds_per_tick) : QObject(nullptr) {
    setSecondsPerTick(seconds_per_tick);
    QObject::connect(&timer_, &QTimer::timeout, this, &Clock::tick);
}

int Clock::getSecondsPerTick() const{
    return timer_.interval() / 1000;
}

void Clock::setSecondsPerTick(int seconds_per_tick) {
    timer_.setInterval(1000 * seconds_per_tick);
}

void Clock::start() {
    emit update(0); //To emit a signal instantly when the clock starts
    timer_.start();
    last_start_time_ = QTime::currentTime();
    qDebug() << "Starting clock with" << getSecondsPerTick() << "seconds per tick";
}

void Clock::stop() {
    timer_.stop();
    qDebug() << "Stopping  clock";
}

void Clock::tick() {
    QTime now = QTime::currentTime();
    int deltaMSec = last_start_time_.msecsTo(now);
    last_start_time_ = now;
    emit update(deltaMSec);
}

} // end namespace physics
