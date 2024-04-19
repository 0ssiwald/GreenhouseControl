#pragma once
#include <QObject>

namespace logic {


// The interface
class Rocket : public QObject {
    Q_OBJECT
public:
    Rocket() : QObject(nullptr) {}
    virtual ~Rocket() = default;
    virtual void setRelativePosition(float relativeX, float relativeY) = 0;
    virtual void setAngle(float angle) = 0;
signals:
    void rocketMovementUpdate(float absoluteX, float absoluteY, float angle);
};


// The implementation
class RocketImpl : public Rocket
{
    float xOrigin;
    float yOrigin;
    float xPosition = 0.0;
    float yPosition = 0.0;
    float angleInRadians = 0.0;

public:
    explicit RocketImpl(float originX, float originY);
    virtual ~RocketImpl() = default;

    virtual void setRelativePosition(float relativeX, float relativeY) override;
    virtual void setAngle(float angle) override;
};


} // end namespace logic
