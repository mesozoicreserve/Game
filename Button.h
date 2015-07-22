#include "SDL_Image.h"
#include <String>

class Button
{
private:
    SDL_Rect position;
    bool shown;
    std::string name;
    SDL_Texture* buttonTexture;
    std::string resName;
    Uint8 alpha;
    bool in;
    bool clicked;
    std::string IMG_DIR;

public:
    SDL_Rect getPosition();
    Button();
    Button(std::string,int,int,bool);
    void newButton(std::string,int,int,bool);
    void genButton();
    SDL_Texture* loadTexture( std::string path,SDL_Renderer* renderer );
    void applySurface(SDL_Renderer* renderer);
    void mouseIn();
    void mouseOut();
    void onClick();
    void onRelease();
    bool isClicked();
    bool isShown();
    void hide();
    void show();
};
