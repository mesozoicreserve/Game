#include "Label.h"

void Label::createLabel(int ix,int iy, string itext, int isize,SDL_Renderer* renderer)
{
    fontFile="GenBasB.ttf";

    text = itext;
    x = ix;
    y = iy;
    fontSize=isize;

    shown = true;

    textColor.a=255;
    textColor.r=195;
    textColor.g=195;
    textColor.b=195;


    if(loadMedia(renderer))
    {
        printf("SUCCESS");
    }
    else
    {
        printf("FAIL");
    }
}


Label::Label(int ix,int iy, string itext, int isize,SDL_Renderer* renderer)
{
    createLabel(ix,iy,itext,isize,renderer);
}


Label::Label()
{
    x=0;
    y=0;
    text="undefined";
}


bool Label::loadFromRenderedText(SDL_Renderer* renderer)
{

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( fontObject, text.c_str(), textColor );

	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
	    width=textSurface->w;
	    height=textSurface->h;
		//Create texture from surface pixels
        labelTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

		if( labelTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

     //BLENDMODE_BLEND gets rid of background in letters
     SDL_SetTextureBlendMode( labelTexture, SDL_BLENDMODE_BLEND);

	//Return success
	return labelTexture != NULL;
}

void Label::printLabel(SDL_Renderer* renderer)
{

    SDL_Rect src = {0,0,width,height};

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };
	//Render to screen
	SDL_RenderCopy( renderer, labelTexture,&src, &renderQuad );
}

void Label::free()
{
	//Free texture if it exists
	if( labelTexture != NULL )
	{
		SDL_DestroyTexture( labelTexture );
		labelTexture = NULL;
	}
}


bool Label::loadMedia(SDL_Renderer* renderer)
{
	//Loading success flag
	bool success = true;

	//Open the font
	fontObject = TTF_OpenFont( fontFile.c_str(),fontSize );

	if( fontObject == NULL )
	{
		printf( "Failed to load  font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
      if( !loadFromRenderedText(renderer) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
		else
        {
            printf("Texture created successfully");
        }
	}

	return success;
}

void Label::setText(string itext, SDL_Renderer* renderer)
{
    text = itext;
    bool test = loadFromRenderedText(renderer);
}

bool Label::isShown()
{
    return shown;
}

void Label::show()
{
    shown = true;
}
void Label::hide()
{
    shown = false;
}
