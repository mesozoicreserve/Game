//Overlay:
//A Button without clickable things
#pragma once

#include "SDL_Image.h"
#include <String>

class Overlay
{
private:
    SDL_Rect position;
    bool shown;
    std::string name;
    SDL_Texture* overlayTexture;
    std::string resName;
    Uint8 alpha;
    bool locked;

public:
    SDL_Rect getPosition();
    Overlay();
    ~Overlay();
    Overlay(std::string,int,int,Uint8,bool,SDL_Renderer*);
    void genOverlay();
    SDL_Texture* loadTexture(SDL_Renderer* renderer );
    void applySurface(SDL_Renderer* renderer);
    void show();
    void hide();
    bool isShown();
    void createOverlay(std::string,int,int,Uint8,bool,SDL_Renderer*);
    bool isLocked();
    void lock();
    void unLock();
};
