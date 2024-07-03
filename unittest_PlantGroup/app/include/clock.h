#pragma once

#include <QObject>
#include <QTimer>
#include <QTime>

namespace physics {


class Clock : public QObject {
    Q_OBJECT
public:
    explicit Clock(int secounds_per_tick);
    int getSecondsPerTick() const;
    void setSecondsPerTick(int);
    QTimer timer_;
    QTime last_start_time_;

signals:
    void update(int delta_t_msec);

public slots:
    void start();
    void stop();
    void tick();

};

} // end namespace physics

