//This is going to be Mainly Static so it will be fairly hardcoded for now and mostly simple
class MainMenu
{
private:
    SDL_Texture* background;
    Button startButton;
    Button loadButton;
    Button optionsButton;
public:
    void applySurface(SDL_Renderer*);
    SDL_Texture* loadTexture(std::string,SDL_Renderer*);
    MainMenu();
    MainMenu(SDL_Renderer*);
    bool checkButtonMouseOver(int,int,bool);
    bool mmCheckUICollision(int x, int y);

};


MainMenu::MainMenu()
{
   // background = loadTexture("title.bmp",render);
    startButton.newButton("StartGame",0,0,true);
}
MainMenu::MainMenu(SDL_Renderer* renderer)
{
    background = loadTexture("title.bmp",renderer);
    startButton.newButton("StartGame",375,400,true);
    loadButton.newButton("MainMenuLoadGame",510,400,true);
    optionsButton.newButton("MainMenuOptions",635,400,true);

}

SDL_Texture* MainMenu::loadTexture( std::string path,SDL_Renderer* renderer )
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


	return newTexture;
}

void MainMenu::applySurface(SDL_Renderer* renderer)
{
    SDL_Rect tgt = {0,0,1250,500};
    SDL_Rect renderQuad = { 0,0,823, 421 };
    SDL_RenderCopy( renderer, background, &renderQuad ,&tgt);

    //Buttons
    startButton.applySurface(renderer);
    loadButton.applySurface(renderer);
    optionsButton.applySurface(renderer);
}


bool MainMenu::checkButtonMouseOver(int x, int y, bool clickflag)
{
    if (!startButton.isClicked())
         {
             //Check mouse over, no click
            if(mmCheckUICollision(x,y) && clickflag == false)
            {
                startButton.mouseIn();
                return false;
            }
            //button clicked
            else if (mmCheckUICollision(x,y) && clickflag==true)
            {
                //START GAME
                startButton.onClick();
                return true;
            }
            //otherwise mouseout
            else
            {
                startButton.mouseOut();
                return false;
            }
         }

}

//Mouse collision with UI elements. Goes through manually
bool MainMenu::mmCheckUICollision(int x, int y)
{
    SDL_Rect pos = startButton.getPosition();

    bool in = true;
    if (x < pos.x)
    {
        in = false;
    }
    if (x > pos.x + pos.w)
    {
        in = false;
    }
    if (y < pos.y)
    {
        in = false;
    }
    if (y > pos.y + pos.h)
    {
        in = false;
    }

    return in;

}
