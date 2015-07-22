#include "Cursor.h"
void Cursor::moveX(int iX)
{
    cursorPosition.x = iX;
}
void Cursor::moveY(int iY)
{
    cursorPosition.y = iY;
}

int Cursor::getX()
{
    return cursorPosition.x;
}

int Cursor::getY()
{
    return cursorPosition.y;
}

SDL_Texture* Cursor::loadTexture(SDL_Renderer* renderer, std::string path)
{
    //The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
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
	SDL_SetTextureAlphaMod(newTexture,100);

	return newTexture;
}

Cursor::Cursor()
{

}

Cursor::Cursor(SDL_Renderer* renderer)
{
    highlightedTile = NULL;
    highlightedTile = loadTexture(renderer,"cursor.bmp");

    cursorPosition.x=0;
    cursorPosition.y=0;
    cursorPosition.w=25;
    cursorPosition.h=25;
}

void Cursor::updateCursorColor(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod( highlightedTile, r, g, b );
}
void Cursor::applySurface(SDL_Renderer* renderer)
{
        //render
        SDL_RenderCopy( renderer,highlightedTile,NULL,&cursorPosition);
}

int Cursor::getAbsoluteX()
{
    return absoluteX;
}
int Cursor::getAbsoluteY()
{
    return absoluteY;
}

void Cursor::setAbsoluteX(int iX)
{
    absoluteX = iX;
}
void Cursor::setAbsoluteY(int iY)
{
    absoluteY = iY;
}

Cursor::~Cursor()
{
    if (highlightedTile != NULL)
    {
        SDL_Texture* highlightedTile;
    }
    absoluteX = 0;
    absoluteY = 0;
}

void Cursor::updateSize(int iSize)
{
    cSize = iSize;
    cursorPosition.h = 25 * cSize;
    cursorPosition.w = 25 * cSize;
}
