#include "window.h"
#include "stdio.h"
#include <string>
#include "SDL_Image.h"
#include "SDL_ttf.h"

SDL_Renderer* Window::getRenderer()
{
    return renderer;
}
void Window::initWindow()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf("SDL could not initialize! Error: %s\n",SDL_GetError());
    }
    else
    {
        //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

        window = SDL_CreateWindow("MESOZOIC RESERVE", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,screenWidth,screenHeight,SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! Error:\n %s",SDL_GetError());
        }
        else
        {
            createRenderer();
        }
    }
}

void Window::createRenderer()
{
     //Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				}
			}

}

void Window::scroll(int direction)
{
    //1: up
    //2: down
    //3: left
    //4: right

        switch (direction)
        {
        case 1:
            relativeY+=5;
            break;
        case 2:
            relativeY-=5;
            break;
        case 3:
            relativeX+=5;
            break;
        case 4:
            relativeX-=5;
        }
}

Window::Window()
{
    setWidth(200);
    setHeight(200);
    setFullScreen(false);
    initWindow();
}

Window::Window(int iW,int iH,bool iF)
{

    relativeX=0;
    relativeY=0;

    setWidth(iW);
    setHeight(iH);
    setFullScreen(iF);

    initWindow();
}

int Window::getY()
{
    return relativeY;
}

void Window::setWidth(int iW)
{
    screenWidth = iW;
}
void Window::setHeight(int iH)
{
    screenHeight = iH;
}
void Window::setFullScreen(bool iF)
{
    fullScreen = iF;
}
int Window::getX()
{
    return relativeX;
}

int Window::getWidth()
{
    return screenWidth;
}
int Window::getHeight()
{
    return screenHeight;
}
bool Window::isFullScreen()
{
    return fullScreen;
}

Window::~Window()
{
    if (renderer  != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }

    screenWidth = 0;
    screenHeight = 0;
    fullScreen = false;
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    //Crashes for some reason
    if (screenSurface != NULL)
    {
       // SDL_FreeSurface(screenSurface);
    }
    relativeY = 0;
    relativeX = 0;
}
