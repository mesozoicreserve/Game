#include "SDL_Image.h"
#include <string>

class Cursor
{
private:
    SDL_Texture* highlightedTile;
    SDL_Rect cursorPosition;
    int absoluteX;
    int absoluteY;
    int cSize;

public:

    Cursor();
    ~Cursor();
    Cursor(SDL_Renderer*);
    void moveX(int);
    void moveY(int);
    void applySurface(SDL_Renderer*);
    SDL_Texture* loadTexture(SDL_Renderer*,std::string);
    int getX();
    int getY();
    void updateCursorColor(Uint8 r, Uint8 g, Uint8 b);
    int getAbsoluteX();
    int getAbsoluteY();
    void setAbsoluteX(int);
    void setAbsoluteY(int);
    void updateSize (int tileSize);

};

