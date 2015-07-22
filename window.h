#include <SDL.h>
#include <String>

#define MAP_X 200
#define MAP_Y 200

class Window
{
protected:
    int screenWidth;
    int screenHeight;
    bool fullScreen;
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Renderer* renderer;
    void createRenderer();
    int relativeY;
    int relativeX;

public:
    void setWidth(int);
    void setHeight(int);
    void setFullScreen(bool);
    SDL_Renderer* getRenderer();
    SDL_Texture* loadTexture(std::string);

    int getWidth();
    int getHeight();
    bool isFullScreen();

    void initWindow();
    Window();
    ~Window();
    Window(int,int,bool);
    void renderLoop();
    void scroll(int);
    int getY();
    int getX();

};
