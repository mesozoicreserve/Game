#include "guestLogic.h"

GuestLogic::GuestLogic()
{
    targetX=0;
    targetY=0;
    logicID = 0;
}


void GuestLogic::initializeLogic(int id,int x,int y)
{
    logicID = id;
    setTarget(x,y);
}

int GuestLogic::getID()
{
    return logicID;
}

bool GuestLogic::isAtTargetAngle(int angle)
{
    if (angle != targetAngle)
    {
        return false;
    }
    return true;
}

int GuestLogic::getTargetAngle()
{
    return targetAngle;
}

void GuestLogic::setTarget(int x,int y)
{

    if (logicID == 1)
    {
        int direction = 0;
        int distance =  0;
        direction = rand() % 4 + 1;
        distance = rand() % 5 + 1;


        switch(direction)
        {
        case 1:
            targetY = (distance*25) + y;
            targetX = x;
            targetAngle = 180;
            break;
        case 2:
            targetY = abs((distance*25) - y);
            targetX = x;
            targetAngle = 0;
            break;
        case 3:
            targetX = (distance*25) + x;
            targetY = y;
            targetAngle = 90;
            break;
        case 4:
            targetX = abs((distance*25) - x);
            targetY = y;
            targetAngle = 270;
            break;
        }

    }
}

bool GuestLogic::isAtTarget(int x, int y)
{
    if (x != targetX)
    {
        return false;
    }
    if (y != targetY)
    {
        return false;
    }

    return true;
}


int GuestLogic::getTargetX()
{
    return targetX;
}

int GuestLogic::getTargetY()
{
    return targetY;
}
