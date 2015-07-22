#include "SDL_Image.h"
#include <String>

class Road
{
private:
    SDL_Rect position;
    SDL_Texture* texture;

public:
    Road(int,int,SDL_Renderer*);
    SDL_Texture* loadTexture(std::string,SDL_Renderer*);
    void applySurface(SDL_Renderer*);

};
