#include "SDL_Image.h"
#include <String>

class Structure
{
private:
    int structureType;
    SDL_Rect clip;
    SDL_Rect position;
    int tileSizeX;
    int tileSizeY;

public:
    Structure();
    ~Structure();
    Structure(int,int,int);
    void applySurface(SDL_Renderer*, SDL_Texture*,int,int);
    void genStructure();
    void initDefault();
    int getStructureType();
    void setUpStructure(int,int,int);
    void updateStructure(std::string);

};
