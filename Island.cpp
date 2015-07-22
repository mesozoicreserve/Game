#include "Island.h"
#include "SDL_Image.h"
#include <iostream>


Island::Island()
{
    allocateMemory();

    srand(time(NULL));
    genWorld();
}

void Island::allocateMemory()
{
    grid = (Tile**)malloc(MAP_X * sizeof(Tile*));
    featureGrid = (Tile**)malloc(MAP_X * sizeof(Tile*));

    structureMap = (Structure**)malloc(MAP_X*sizeof(Structure*));

    for (int i=0;i<MAP_X;i++)
    {
        grid[i] = (Tile*)malloc(MAP_Y*sizeof(Tile));
        structureMap[i] = (Structure*)malloc(MAP_Y*sizeof(Structure));
        featureGrid[i] = (Tile*)malloc(MAP_Y*sizeof(Tile));
    }

}
Island::Island(SDL_Renderer* renderer)
{
    allocateMemory();

    srand(time(NULL));

    //load main textures
    backgroundTexture = loadTexture("terrain.bmp",renderer);
    structureTexture = loadTexture("road.bmp",renderer);
    featureTexture = loadTexture("jungle.bmp",renderer);

    selectedIndex = -1;

    //todo: we can move this label back to main
    parkNameLabel.createLabel(995,410,"ISLA DOUCHEBAR",28,renderer);

    guestMouseOverOverlay.createOverlay("GuestMouseOverOverlay",825,400,200,false,renderer);

    personNameLabel.createLabel(840,405," ",12,renderer);
    personAgeLabel.createLabel(840,420," ",12,renderer);

    genWorld();


    for (int i = 0; i < NUM_GUESTS; i++)
    {
        aPerson[i].newPerson((20 * i) + 400 ,400,renderer);
    }
}


Tile Island::getTile(int x, int y)
{
    return grid[x][y];
}
void Island::genWorld()
{
    //GENERATE THE BASE
    for (int i=0;i<MAP_Y;i++)
    {
        for (int j=0;j<MAP_X;j++)
        {
            //j,i does it in the proper left to right format
            genBase(j,i);
            //Set the positions of the tiles
            grid[j][i].setPosition(j*25,i*25);

            //Initialize structure map
            structureMap[j][i].initDefault();
        }
    }
    //SMOOTH THE EDGES
    for (int i=2;i<MAP_Y-3;i++)
    {
        for (int j=2;j<MAP_X-3;j++)
        {
            //j,i does it in the proper left to right format
           smoothMap(j,i);
        }
    }
    //sand
    for (int i=2;i<MAP_Y-3;i++)
    {
        for (int j=2;j<MAP_X-3;j++)
        {
            //j,i does it in the proper left to right format
           genMapDetails(j,i);
        }
    }

    for(int i=2;i<MAP_Y-3;i++)
    {
        for (int j=2;j<MAP_X-3;j++)
        {
            seedMud(j,i);
        }
    }

    //conway that shit
    for (int i=2;i<8;i++)
    {
        runMud();
    }

}

void Island::genMapDetails(int x, int y)
{
    //Sand if touching 3 or more water tiles
    int sandWeight = 0;

        if (grid[x][y].getType() == 2)
        {
            if(grid[x-1][y].getType() == 1)
            {
                sandWeight++;
            }
            if (grid[x+1][y].getType() == 1)
            {
                sandWeight++;
            }
            if (grid[x][y-1].getType() == 1)
            {
                sandWeight++;
            }
            if (grid[x][y+1].getType() == 1)
            {
                sandWeight++;
            }
            if ( grid[x-1][y-1].getType() == 1)
            {
                sandWeight++;
            }
            if (grid[x-1][y+1].getType() == 1)
            {
                sandWeight++;
            }
            if (grid[x+1][y-1].getType() == 1)
            {
                sandWeight++;
            }
        }

    if (sandWeight > 2)
    {
        grid[x][y].setType(3);
    }
}

void Island::seedMud(int x, int y)
{
    if (grid[x][y].getType()== 2)
    {
        int randomNum = rand() % 6 + 1;

        //10% chance of mud
        if (randomNum == 4)
        {
            grid[x][y].setType(4);
        }

    }

}

void Island::runMud()
{
    for (int i=2;i<MAP_Y-3;i++)
    {
        for (int j=2;j<MAP_X-3;j++)
        {
          int mudWeight = 0;

            if (grid[j][i].getType() == 4)
            {
                if(grid[j-1][i].getType() == 4)
                {
                    mudWeight++;
                }
                if (grid[j+1][i].getType() == 4)
                {
                    mudWeight++;
                }
                if (grid[j][i-1].getType() == 4)
                {
                    mudWeight++;
                }
                if (grid[j][i+1].getType() == 4)
                {
                    mudWeight++;
                }
                if ( grid[j-1][i-1].getType() == 4)
                {
                    mudWeight++;
                }
                if (grid[j-1][i+1].getType() == 4)
                {
                    mudWeight++;
                }
                if (grid[j+1][i-1].getType() == 4)
                {
                    mudWeight++;
                }

                if (mudWeight > 3)
                {
                    grid[j][i].setType(4);
                }
                else if (mudWeight < 2)
                {
                    grid[j][i].setType(2);
                }

            }
        }
    }


    for (int i=2;i<MAP_Y-3;i++)
    {
        for (int j=2;j<MAP_X-3;j++)
        {
          int mudWeight = 0;
           if (grid[j][i].getType() == 4)
            {

            }
        }
    }
}

void Island::smoothMap(int x,int y)
{
    int smoothWeight = 0;

        if (grid[x][y].getType() == 2)
        {
            if(grid[x-1][y].getType() == 1)
            {
                smoothWeight++;
            }
            if (grid[x+1][y].getType() == 1)
            {
                smoothWeight++;
            }
            if (grid[x][y-1].getType() == 1)
            {
                smoothWeight++;
            }
            if (grid[x][y+1].getType() == 1)
            {
                smoothWeight++;
            }
            if ( grid[x-1][y-1].getType() == 1)
            {
                smoothWeight++;
            }
            if (grid[x-1][y+1].getType() == 1)
            {
                smoothWeight++;
            }
            if (grid[x+1][y-1].getType() == 1)
            {
                smoothWeight++;
            }
            if (smoothWeight > 4)
            {
                grid[x][y].setType(1);
            }
        }
        else if (grid[x][y].getType() == 1)
        {
            if (grid[x-1][y].getType() == 2)
            {
                smoothWeight++;
            }
            if (grid[x+1][y].getType() == 2)
            {
                smoothWeight++;
            }
            if (grid[x][y-1].getType() == 2)
            {
                smoothWeight++;
            }
            if (grid[x][y+1].getType() == 2)
            {
                smoothWeight++;
            }
            if ( grid[x-1][y-1].getType() == 2)
            {
                smoothWeight++;
            }
            if (grid[x-1][y+1].getType() == 2)
            {
                smoothWeight++;
            }
            if (grid[x+1][y-1].getType() == 2)
            {
                smoothWeight++;
            }
            if (smoothWeight > 6)
            {
                grid[x][y].setType(2);
            }
        }
}

//Map algo here
void Island::genBase(int x, int y)
{

   //Percent chance of tile being land
   int percent;

   if (x < 2 || x > (MAP_X - 3) || y < 2 || y > (MAP_Y -3 ) )
   {
        percent = 0;
   }
   else if (((x >= 2 && x <= 4) || (x >= (MAP_X - 5) && x <= (MAP_X - 3)) || ((y >= 2 && y <= 4) || (y >= (MAP_Y - 5)) && y <= (MAP_Y - 3))))
   {
       percent=50;
   }
   else if (((x >= 5 && x <= 8) || (x >= (MAP_X - 6) && x <= (MAP_X - 7))) || ((y >= 5 && y <= 4) || (y >= (MAP_Y - 6) && y <= (MAP_Y - 7))))
   {
       percent=75;
   }
   else if (((x >= 9 && x <= 11) || (x >= (MAP_X - 10) && x <= (MAP_X - 8)) || ((y >= 9 && y <= 11) || (y >= (MAP_Y - 10) && y <= (MAP_Y - 8)))))
   {
       percent=90;
   }
   else
   {
       percent = 97;
   }

   int randomNum = rand() % 100 + 1;

   if (randomNum <= percent)
    {
        grid[x][y].setType(2);
    }
   else
    {
        grid[x][y].setType(1);
    }

    //make everything forest for now :)
    featureGrid[x][y].setType(100);
}


SDL_Texture* Island::loadTexture( std::string path,SDL_Renderer* renderer )
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

void Island::applySurface(SDL_Renderer* renderer,SDL_Rect clip, SDL_Rect tgt,int scrollWidth, int scrollHeight)
{
            tgt.y += scrollHeight;
            tgt.x += scrollWidth;

            if (backgroundTexture==NULL)
            {
                backgroundTexture=loadTexture("terrain.bmp",renderer);
            }

          //Render Clipping renders a box of 100 pixels out of the screen
            if (tgt.x < (1250 + 100) && abs(scrollWidth) < 1)
            {
                if (tgt.y < 500 + 100 && abs(scrollHeight) < 1)
                {
                    SDL_RenderCopy( renderer,backgroundTexture,&clip,&tgt);
                }
                else if (abs(scrollHeight) >= 1 && tgt.y > -100 && tgt.y < 500 + 100)
                {
                    SDL_RenderCopy( renderer,backgroundTexture,&clip,&tgt);
                }
            }
           else if (abs(scrollWidth) >= 1 && tgt.x > -100 && tgt.x < 1250 + 100)
            {
                if (tgt.y < 500 + 100 && abs(scrollHeight) < 1)
                {
                    SDL_RenderCopy( renderer,backgroundTexture,&clip,&tgt);
                }
                else if (abs(scrollHeight) >= 1 && tgt.y > -100 && tgt.y < 500 + 100)
                {
                    SDL_RenderCopy( renderer,backgroundTexture,&clip,&tgt);
                }
            }

            //render

}

void Island::drawBackground(SDL_Renderer* renderer,int scrollX, int scrollY)
{

    int windowHeight = 500;
    int windowWidth = 1250;

    std::cout << "X " << scrollX << std::endl;
    std::cout << "Y " << scrollY << std::endl;


    for (int i=0;i<MAP_Y;i++)
    {
        for (int j=0;j<MAP_X;j++)
        {
            SDL_Rect clip;

            clip.w=25;
            clip.h=25;
            clip.y=0;

            Tile tileData = getTile(j,i);
            SDL_Rect pos = tileData.getPosition();
            int tileType = tileData.getType();

            clip.x = ((tileType-1)*25);

            applySurface(renderer,clip,pos,scrollX,scrollY);
        }

    }
}

void Island::renderStructures(SDL_Renderer* renderer,int x,int y)
{
    for(int i=0;i<MAP_Y;i++)
    {
        for (int j=0;j<MAP_X;j++)
        {
            if (structureMap[j][i].getStructureType() > 0)
            {
                structureMap[j][i].applySurface(renderer,structureTexture,x,y);
            }
        }
    }
}

//This sets the 2d player placed building array, basically
//tells the game what tiles have what buildings.
void Island::createStructure(int type, int x, int y)
{
    int xpos = x / 25;
    int ypos = y / 25;

    //Road Placement
    if (type == 1)
    {
        structureMap[xpos][ypos].setUpStructure(type,x,y);

        //update the road clip
        updateRoads();
    }
    //Lab placement
    if (type==2)

    {
       for (int i=0;i<4;i++)
        {
            for (int j=0;j<4;j++)
            {
                structureMap[xpos+j][ypos+i].setUpStructure(type,x,y);
            }
        }
    }

    if (type == 3)
    {
        structureMap[xpos][ypos].setUpStructure(type,x,y);
        updateFences();
    }

    if (type == 4)
    {
       for (int i=0;i<5;i++)
        {
            for (int j=0;j<5;j++)
            {
                structureMap[xpos+j][ypos+i].setUpStructure(type,x,y);
            }
        }
    }



}

//Switches the road to the proper image clip
void Island::updateRoads()
{
    for (int i=0;i<MAP_Y;i++)
    {
        for (int j=0; j<MAP_X;j++)
        {
            //If road
            if (structureMap[j][i].getStructureType() == 1)
            {
                //Set up-down
                if (structureMap[j][i-1].getStructureType()==1 || structureMap[j][i+1].getStructureType() == 1)
                {
                    structureMap[j][i].updateStructure("setRoadVertical");
                }
                //Set left-right
                if (structureMap[j-1][i].getStructureType()==1 || structureMap[j+1][i].getStructureType() == 1)
                {
                    structureMap[j][i].updateStructure("setRoadHorizontal");
                }
                //Set intersetction
                if (structureMap[j-1][i].getStructureType()==1 && structureMap[j+1][i].getStructureType() == 1
                    && structureMap[j][i-1].getStructureType()==1 && structureMap[j][i+1].getStructureType() == 1 )
                {
                    structureMap[j][i].updateStructure("setRoadIntersection");
                }


            }
        }
    }
}

void Island::updateFences()
{
     for (int i=0;i<MAP_Y;i++)
    {
        for (int j=0; j<MAP_X;j++)
        {
            //If fence
            if (structureMap[j][i].getStructureType() == 3)
            {
                //Set up-down
                if (structureMap[j][i-1].getStructureType()==3 || structureMap[j][i+1].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceVertical");
                }
                //Set left-right
                if (structureMap[j-1][i].getStructureType()==3 || structureMap[j+1][i].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceHorizontal");
                }
                //Set corners - check right-down
                if (structureMap[j-1][i].getStructureType() == 3 && structureMap[j][i+1].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceRightDown");
                }
                //Set corners - check left-down
                if (structureMap[j+1][i].getStructureType() == 3 && structureMap[j][i+1].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceLeftDown");
                }
                //Set corners - check right-up
                if (structureMap[j-1][i].getStructureType() == 3 && structureMap[j][i-1].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceRightUp");
                }
                //Set corners - check right-up
                if (structureMap[j+1][i].getStructureType() == 3 && structureMap[j][i-1].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceLeftUp");
                }
                //Set corners - check up-T
                if (structureMap[j+1][i].getStructureType() == 3 && structureMap[j-1][i].getStructureType() == 3 && structureMap[j][i-1].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceUpT");
                }
                //Set corners - check down-T
                if (structureMap[j+1][i].getStructureType() == 3 && structureMap[j-1][i].getStructureType() == 3 && structureMap[j][i+1].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceDownT");
                }
                //Set corners - check Left-T
                if (structureMap[j][i-1].getStructureType() == 3 && structureMap[j][i+1].getStructureType() == 3 && structureMap[j+1][i].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceLeftT");
                }
                //Set corners - check Left-T
                if (structureMap[j][i-1].getStructureType() == 3 && structureMap[j][i+1].getStructureType() == 3 && structureMap[j-1][i].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceRightT");
                }
               //Set corners - check CROSS
                if (structureMap[j][i-1].getStructureType() == 3 && structureMap[j][i+1].getStructureType() == 3 && structureMap[j-1][i].getStructureType() == 3 && structureMap[j-1][i].getStructureType() == 3)
                {
                    structureMap[j][i].updateStructure("setFenceCross");
                }
            }
        }
    }
}

bool Island::isTileBuildable(int x, int y, int buildingID)
{
    int xpos = x / 25;
    int ypos = y / 25;

    //Cant build on the following:
    // Water
    //already build buildings

    //1X1 LAND buildings - 1:Road, 3:Fence
    if ( buildingID == 1 || buildingID == 3)
    {
        if (grid[xpos][ypos].getType() == 1)
        {
            return false;
        }
        if (structureMap[xpos][ypos].getStructureType() != 0)
        {
            return false;
        }
    }
    // 4x4 Land buildings - 2:Research Lab
    if (buildingID == 2)
    {
        for (int i=0;i<4;i++)
        {
            for (int j=0;j<4;j++)
            {
                if (structureMap[xpos+j][ypos+i].getStructureType() != 0)
                {
                    return false;
                }
                if (grid[xpos+j][ypos+i].getType() == 1)
                {
                    return false;
                }
            }
        }
    }

    if (buildingID == 4)
    {
        for (int i=0;i<4;i++)
        {
            for (int j=0;j<4;j++)
            {
                if (structureMap[xpos+j][ypos+i].getStructureType() != 0)
                {
                    return false;
                }
                if (grid[xpos+j][ypos+i].getType() == 1)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void Island::renderPeople(SDL_Renderer* renderer, int scrollX, int scrollY)
{
  for (int i=0;i<NUM_GUESTS;i++)
    {
        aPerson[i].applySurface(renderer,scrollX,scrollY);
    }
}

Island::~Island()
{
    if (backgroundTexture != NULL)
    {
        SDL_DestroyTexture(backgroundTexture);
    }
    if (structureTexture != NULL)
    {
        SDL_DestroyTexture(structureTexture);
    }


    free(grid);
    free(structureMap);

    grid = NULL;
    structureMap=NULL;
}

//Guest AI
void Island::guestAI()
{
    for (int i=0;i<NUM_GUESTS;i++)
    {
        int tileX = aPerson[i].getX() / 25;
        int tileY = aPerson[i].getY() / 25;

        //Get types of the tiles up/down/left right for collision detection
        int typeUp = grid[tileX][tileY-1].getType();
        int typeDown = grid[tileX][tileY+1].getType();
        int typeLeft = grid[tileX-1][tileY].getType();
        int typeRight = grid[tileX+1][tileY].getType();


        aPerson[i].calculateMovements(typeUp,typeDown,typeLeft,typeRight);
    }

}

void Island::checkGuestMouseOver(int cursorX,int cursorY,SDL_Renderer* renderer)
{
    bool flagOn = false;

    for (int i=0;i<NUM_GUESTS;i++)
    {
        if ((cursorX <= (aPerson[i].getX() + 17 ) && cursorX >= (aPerson[i].getX() - 10)) && flagOn == false)
        {
            if ((cursorY >= (aPerson[i].getY() - 10) && (cursorY <= aPerson[i].getY() + 15)) && flagOn == false)
            {
                 aPerson[i].onMouseOver();
                 if (guestMouseOverOverlay.isLocked() == false)
                 {
                    personNameLabel.setText(aPerson[i].getName(),renderer);
                    personAgeLabel.setText(aPerson[i].getAge(),renderer);
                 }
                 personNameLabel.show();
                 personAgeLabel.show();
                 guestMouseOverOverlay.show();
                 selectedIndex = i;
                 flagOn = true;
            }
            else
            {
                aPerson[i].onMouseOut();
                if(personNameLabel.isShown())
                {
                    personNameLabel.hide();
                    personAgeLabel.hide();
                    guestMouseOverOverlay.hide();
                    selectedIndex = -1;
                }
            }
        }
        else
        {
            aPerson[i].onMouseOut();
        }

    }
}

void Island::checkGuestMouseClick()
{

  for (int i=0;i<NUM_GUESTS;i++)
  {
    aPerson[i].onMouseOut();
    aPerson[i].unClick();
    guestMouseOverOverlay.unLock();
  }

  if (selectedIndex > -1)
  {
      aPerson[selectedIndex].onMouseClick();
      guestMouseOverOverlay.lock();
  }


}

//Handles the rendered text rendering
void Island::printText(SDL_Renderer* renderer)
{

    parkNameLabel.printLabel(renderer);

    if (guestMouseOverOverlay.isShown() || guestMouseOverOverlay.isLocked())
    {
        guestMouseOverOverlay.applySurface(renderer);
    }
    if (personNameLabel.isShown() || guestMouseOverOverlay.isLocked())
    {
        personNameLabel.printLabel(renderer);
        personAgeLabel.printLabel(renderer);
    }
}
