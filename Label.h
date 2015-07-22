#pragma once
#include "SDL_ttf.h"
#include <String>

using namespace std;

class Label
{
private:
    int fontSize;
    string fontFile;
    string text;
    void loadMedia();
    bool shown;
    SDL_Texture* labelTexture;
    SDL_Color textColor;
    TTF_Font *fontObject;
    int x;
    int y;
    int width;
    int height;

public:
    Label();
    Label(int,int,string,int,SDL_Renderer*);
    void printLabel(SDL_Renderer*);
    void free();
    bool loadFromRenderedText(SDL_Renderer*);
    //bool loadFromFile(SDL_Renderer*);
    bool loadMedia(SDL_Renderer*);
    void createLabel(int ,int, string, int,SDL_Renderer*);
    void setText(string,SDL_Renderer*);
    bool isShown();
    void show();
    void hide();

};

