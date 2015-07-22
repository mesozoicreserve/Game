#include "overlay.h"

SDL_Rect Overlay::getPosition()
{
    return position;
}

Overlay::Overlay()
{
    //undefined
    position.x=0;
    position.y=0;
    position.w=0;
    position.h=0;

    name="undefined";
    shown=false;
}

void Overlay::show()
{
    shown=true;
}
void Overlay::hide()
{
    shown= false;
}

Overlay::Overlay(std::string olName,int iX, int iY,Uint8 iA, bool vis,SDL_Renderer* renderer)
{

    createOverlay(olName,iX,iY,iA,vis,renderer);

}

void Overlay::createOverlay(std::string olName,int iX, int iY,Uint8 iA, bool vis,SDL_Renderer* renderer)
{
    alpha=iA;
    name=olName;
    position.x=iX;
    position.y=iY;
    shown = vis;
    locked = false;
    genOverlay();

    overlayTexture = loadTexture(renderer);

}

void Overlay::genOverlay()
{
    if (name == "SelectionMenu")
    {
        position.w=187;
        position.h=450;
        resName="BuildOverlay.bmp";
    }
    if (name == "CornerStatus")
    {
        position.w=300;
        position.h=100;
        resName="Corner.bmp";
    }
    if (name == "GuestMouseOverOverlay")
    {
        position.w=125;
        position.h=100;
        resName="GuestMouseOverOverlay.bmp";
    }

    if(name == "BuildContext" )
    {
        position.w=150;
        position.h=100;
        resName = "buildcontext.bmp";
    }
}


SDL_Texture* Overlay::loadTexture(SDL_Renderer* renderer )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( resName.c_str() );

	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", resName.c_str(), IMG_GetError() );
	}
	else
	{
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
	{
			printf( "Unable to create texture from %s! SDL Error: %s\n", resName.c_str(), SDL_GetError() );
	}		//Get rid of old loaded surface
            SDL_FreeSurface( loadedSurface );
	}

    //Transperancy	//Set blending function
	SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );
	SDL_SetTextureAlphaMod(newTexture,alpha);

	return newTexture;
}

bool Overlay::isShown()
{
    return shown;
}

void Overlay::applySurface(SDL_Renderer* renderer)
{
        //render
        SDL_RenderCopy( renderer,overlayTexture,NULL,&position);
}

Overlay::~Overlay()
{
    shown = false;
    name = "";
    if (overlayTexture != NULL)
    {
        SDL_DestroyTexture(overlayTexture);
    }
    resName = "";
    alpha = NULL;
}

void Overlay::lock()
{
    locked = true;
}

void Overlay::unLock()
{
    locked = false;
}

bool Overlay::isLocked()
{
    return locked;
}
