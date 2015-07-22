#include <string>
#include "SDL_Image.h"
class Tile
{
  private:
      int type;
      int x;
      int y;
      SDL_Rect position;

  public:
      Tile();
      ~Tile();
      void setType(int);
      int getType();
      void setX(int);
      int getX();
      void setY(int);
      int getY();
      void setPosition(int,int);
      SDL_Rect getPosition();
};

