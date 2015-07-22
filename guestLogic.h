#include "SDL_Image.h"
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <iostream>

class GuestLogic
{
private:
    int targetX;
    int targetY;
    int targetAngle;
    int logicID;
public:
    GuestLogic();
    void initializeLogic(int,int,int);
    bool isAtTarget(int,int);
  //  bool isFacingTheRightWay(int);
    void setTarget(int,int);
    SDL_Point getTarget();
    int getYDelta(int);
    int getTargetX();
    int getTargetY();
    int getID();
    int getTargetAngle();
    bool isAtTargetAngle(int);
};
