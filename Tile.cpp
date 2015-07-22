#include "Tile.h"

void Tile::setPosition(int iX, int iY)
{
    //Holds the absolute location
    position.x=iX;
    position.y=iY;
    position.w=25;
    position.h=25;

}

SDL_Rect Tile::getPosition()
{
    return position;
}



Tile::Tile()
{
    //Set a default type
    type=1;
}

void Tile::setType(int iT)
{
    type = iT;
}
int Tile::getType()
{
    return type;
}
void Tile::setX(int iX)
{
    x = iX;
}
int Tile::getX()
{
    return x;
}
void Tile::setY(int iY)
{
    y = iY;
}
int Tile::getY()
{
    return y;
}

Tile::~Tile()
{
      type = 0;
      x = 0;
      y = 0;
}
