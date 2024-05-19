#pragma once

#include <QObject>
#include <QTimer>
#include <QTime>

namespace physics {


class Clock : public QObject {
    Q_OBJECT
public:
    explicit Clock(int secounds_per_tick = 5);
    int getSecondsPerTick() const;
    void setSecondsPerTick(int);

signals:
    void update(int delta_t_msec);

public slots:
    void start();
    void stop();
    void tick();

private:
    QTimer timer;
    QTime lastStartTime;
};


} // end namespace physics

