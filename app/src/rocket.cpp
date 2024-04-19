#include "rocket.h"

namespace logic {

RocketImpl::RocketImpl(float originX, float originY) : xOrigin(originX), yOrigin(originY)
{

}

void RocketImpl::setRelativePosition(float relativeX, float relativeY)
{
    xPosition = relativeX;
    yPosition = relativeY;

    emit rocketMovementUpdate(xOrigin + xPosition, yOrigin + yPosition, angleInRadians);
}

void RocketImpl::setAngle(float angle)
{
    angleInRadians = angle;

    emit rocketMovementUpdate(xOrigin + xPosition, yOrigin + yPosition, angleInRadians);
}


} // end namespace logic
