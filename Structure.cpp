#include "Structure.h"

Structure::Structure()
{
    structureType = 0;
    genStructure();
}

Structure::Structure(int type,int xPos, int yPos)
{

    structureType = type;
    position.x = xPos;
    position.y = yPos;

    genStructure();
}

void Structure::genStructure()
{
    //Set up attributes
    switch(structureType)
    {
        case 0:
            position.h=0;
            position.w=0;
            clip.h=0;
            clip.w=0;
            clip.x=0;
            clip.y=0;
            tileSizeX=0;
            tileSizeY=0;
            break;
        //Road
        case 1:
            position.h=25;
            position.w=25;

            updateStructure("setRoadHorizontal");

            tileSizeX = 1;
            tileSizeY = 1;
            break;
        case 2:
            position.h=100;
            position.w=100;
            tileSizeX=4;
            tileSizeY=4;

            updateStructure("setResearchLab");
            break;
        case 3:
            position.h=25;
            position.w=25;
            updateStructure("setFenceHorizontal");
            tileSizeX=1;
            tileSizeY=1;
            break;
        case 4:
            position.h=150;
            position.w=150;
            updateStructure("setDock");
            tileSizeX=5;
           // system("pause");
            tileSizeY=5;
            break;
    }
}

//This method supplies the clip info for player placed buildings.

void Structure::updateStructure(std::string updateName)
{
    if (updateName == "setRoadVertical")
    {
            clip.h=25;
            clip.w=25;
            clip.x=0;
            clip.y=0;
    }
    if (updateName == "setRoadHorizontal")
    {
            clip.h=25;
            clip.w=25;
            clip.x=25;
            clip.y=0;
    }
    if (updateName == "setRoadIntersection")
    {
            clip.h=25;
            clip.w=25;
            clip.x=50;
            clip.y=0;
    }
    if (updateName == "setResearchLab")
    {
        clip.h=100;
        clip.w=100;
        clip.x=100;
        clip.y=0;
    }
    if (updateName == "setFenceHorizontal")
    {
        clip.h=25;
        clip.w=25;
        clip.x=75;
        clip.y=25;
    }
    if (updateName == "setFenceVertical")
    {
        clip.h=25;
        clip.w=25;
        clip.x=75;
        clip.y=0;
    }
    if (updateName == "setFenceRightDown")
    {
      clip.h=25;
      clip.w=25;
      clip.x=25;
      clip.y=25;
   }
    if (updateName == "setFenceLeftDown")
    {
        clip.h=25;
        clip.w=25;
        clip.x=0;
        clip.y=25;
    }
    if (updateName == "setFenceRightUp")
    {
        clip.h=25;
        clip.w=25;
        clip.x=50;
        clip.y=25;
    }
    if (updateName == "setFenceLeftUp")
    {
        clip.h=25;
        clip.w=25;
        clip.x=0;
        clip.y=50;
    }
    if (updateName == "setFenceUpT")
    {
        clip.h=25;
        clip.w=25;
        clip.x=25;
        clip.y=50;
    }
    if (updateName == "setFenceDownT")
    {
        clip.h=25;
        clip.w=25;
        clip.x=50;
        clip.y=50;
    }
    if (updateName == "setFenceLeftT")
    {
        clip.h=25;
        clip.w=25;
        clip.x=75;
        clip.y=50;
    }
    if (updateName == "setFenceLeftT")
    {
        clip.h=25;
        clip.w=25;
        clip.x=0;
        clip.y=75;
    }
    if (updateName == "setFenceCross")
    {
        clip.h=25;
        clip.w=25;
        clip.x=25;
        clip.y=75;
    }
    if (updateName == "setDock")
    {
        clip.h=150;
        clip.w=150;
        clip.x=200;
        clip.y=0;
    }
}
void Structure::applySurface(SDL_Renderer* renderer,SDL_Texture* texture,int x, int y)
{
    SDL_Rect tmppos = position;
    tmppos.x +=x;
    tmppos.y +=y;
    SDL_RenderCopy(renderer,texture,&clip,&tmppos);

}

void Structure::initDefault()
{
    structureType = 0;
    genStructure();
}

int Structure::getStructureType()
{
    return structureType;
}

void Structure::setUpStructure(int type,int xPos, int yPos)
{

    structureType = type;
    position.x = xPos;
    position.y = yPos;

    genStructure();
}

Structure::~Structure()
{
    structureType = 0;
    tileSizeX = 0;
    tileSizeY = 0;
}
