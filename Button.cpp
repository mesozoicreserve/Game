
#include "Button.h"
#include <iostream>
SDL_Rect Button::getPosition()
{
    return position;
}

Button::Button()
{
    //undefined
    position.x=0;
    position.y=0;
    position.w=0;
    position.h=0;

    name="undefined";
    shown=false;
    in = false;
    clicked = false;

    IMG_DIR = "res/img/";
}

void Button::onClick()
{
    if (clicked == true)
    {
        clicked = false;
        SDL_SetTextureColorMod( buttonTexture, 255, 255, 255 );

    }
    else if (clicked == false )
    {
        clicked = true;
        SDL_SetTextureColorMod( buttonTexture, 255, 0, 0 );

    }
}

void Button::onRelease()
{
      clicked = false;
      SDL_SetTextureColorMod( buttonTexture, 255, 255, 255 );

}

Button::Button(std::string buttonName,int iX, int iY, bool vis)
{
    newButton(buttonName,iX,iY,vis);
}

void Button::newButton(std::string buttonName, int iX, int iY, bool vis)
{
    name=buttonName;
    position.x=iX;
    position.y=iY;
    shown = vis;
    buttonName="undefined";
    clicked=false;

    IMG_DIR = "res/img/";


    genButton();
}
void Button::genButton()
{
    buttonTexture = NULL;
    if(name == "BuildButton" )
    {
        position.w=100;
        position.h=45;
        resName = IMG_DIR + "buttons/build.bmp";
        alpha=255;
        buttonName="Build";
    }

    if(name == "LabButton" )
    {
        position.w=100;
        position.h=45;
        resName = IMG_DIR + "buttons/lab.bmp";
        alpha=255;
        buttonName="Research";
    }
    if(name == "RoadButton" )
    {
        position.w=50;
        position.h=50;
        resName = IMG_DIR + "buttons/roadbutton.bmp";
        alpha=255;
        buttonName="Paved Road";
    }
    if(name == "FenceButton" )
    {
        position.w=50;
        position.h=50;
        resName = IMG_DIR + "buttons/fence.bmp";
        alpha=255;
        buttonName="Chain-link Fence";
    }
    if(name == "ResearchLabButton" )
    {
        position.w=50;
        position.h=50;
        resName = IMG_DIR + "buttons/researchlabbutton.bmp";
        alpha=255;
        buttonName="Laboratory";
    }
    if(name == "DockButton" )
    {
        position.w=50;
        position.h=50;
        resName = IMG_DIR + "buttons/dockbutton.bmp";
        alpha=255;
        buttonName="Wharf";
    }
    if(name == "pathButton" )
    {
        position.w=50;
        position.h=50;
        resName = IMG_DIR + "buttons/pathbutton.bmp";
        alpha=255;
        buttonName="Dirt Path";
    }
    if(name=="StartGame")
    {
        position.w=115;
        position.h=35;
        resName = IMG_DIR + "buttons/newgame.bmp";
        alpha = 255;
        buttonName="New Game";
    }
    if(name=="MainMenuLoadGame")
    {
        position.w=115;
        position.h=35;
        resName = IMG_DIR + "buttons/loadgame.bmp";
        alpha = 255;
        buttonName="New Game";
    }
    if(name=="MainMenuOptions")
    {
        position.w=115;
        position.h=35;
        resName = IMG_DIR + "buttons/options.bmp";
        alpha = 255;
        buttonName="New Game";
    }
}


SDL_Texture* Button::loadTexture( std::string path,SDL_Renderer* renderer )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified pathC:\park\Park\main.cpp
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );


	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
	    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
	{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}		//Get rid of old loaded surface
            SDL_FreeSurface( loadedSurface );
	}

    //Transperancy	//Set blending function
	SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );
	SDL_SetTextureAlphaMod(newTexture,alpha);

	return newTexture;
}

void Button::applySurface(SDL_Renderer* renderer)
{
            if (buttonTexture == NULL)
            {
               buttonTexture = loadTexture(resName,renderer);
            }
            else
            {
                SDL_RenderCopy(renderer,buttonTexture,NULL,&position);
            }
}

void Button::mouseIn()
{
    SDL_SetTextureColorMod( buttonTexture, 0, 255, 0 );
}
void Button::mouseOut()
{
    SDL_SetTextureColorMod( buttonTexture, 255, 255, 255 );
}

bool Button::isClicked()
{
    return clicked;
}

bool Button::isShown()
{
    return shown;
}

void Button::show()
{
    shown = true;
}
void Button::hide()
{
    shown = false;
}
std::string Button::getName()
{
    return buttonName;
}

