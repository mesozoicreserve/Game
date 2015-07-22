#include <iostream>
#include <stdio.h>
#include "window.h"
#include "Island.h"
#include "Button.h"
#include "overlay.h"
#include "Road.h"
#include "Cursor.h"
#include "SDL_ttf.h"
#include "SDL_Image.h"
#include "Timer.h"
#include "gameClock.h"
#include "Label.h"

using namespace std;

bool checkUICollision(int x, int y, Button buttonToCheck);
void drawBackground(SDL_Renderer*,int,int);
void isCursorInButton(Button);
SDL_Texture* testButton;

int main (int argc, char* args[])
{

    SDL_Event event;

    const int FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / FPS;

    Window aWindow(1250,500,false);

    SDL_Renderer* renderer = aWindow.getRenderer();

    Island gameIsland(renderer);

    gameClock dateTime(8,1,2017,8,0);


    Button aButton("BuildButton",5,465,true);
    Button labButton("LabButton",76,465,true);
    Button roadButton("RoadButton",10,370,false);
    Button fenceButton("FenceButton",10,310,false);
    Button buildLabButton("ResearchLabButton",10,250,false);
    Button buildDockButton("DockButton",10,20,false);
    Button buildPathButton("pathButton",10,90,false);
    Overlay BuildMenuOverlay("SelectionMenu",1,1,200,false,renderer);
    Overlay CornerStatusOverlay("CornerStatus",950,400,200,true,renderer);

    Label dateLabel(1030,450,dateTime.getDate(),14,renderer);
    Label timeLabel(1100,450,dateTime.getTime(),14,renderer);

    Timer fpsTimer;
    Timer capTimer;

    Person testPerson(100,100,renderer);

    Cursor mouseCursor(renderer);

    bool buildMode = false;

    int screenRelativeX=0;
    int screenRelativeY=0;
    //BEGIN MAIN GAME LOOP
    bool quit = false;
    bool mouseInPerson = false;

    int countedFrames = 0;
    int buildingID = 0;

    //Toggle cursor
    SDL_ShowCursor(1);
    fpsTimer.start();



    while (quit == false)
    {
        capTimer.start();
        while( SDL_PollEvent( &event ) != 0 )
        {
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                int x,y;
                SDL_GetMouseState( &x, &y );

                int relativeX = aWindow.getX();
                int relativeY = aWindow.getY();

                int diffX = (x % 25) - (relativeX % 25);
                int diffY = (y % 25) - (relativeY % 25);

                screenRelativeX=x-diffX;
                screenRelativeY=y-diffY;

                mouseCursor.moveX(screenRelativeX);
                mouseCursor.moveY(screenRelativeY);

                mouseCursor.setAbsoluteX(mouseCursor.getX() - aWindow.getX());
                mouseCursor.setAbsoluteY(mouseCursor.getY() - aWindow.getY());


                //Build mode on = Update mouse highlight with proper color
                if (buildMode == true)
                {
                    //Cursor color
                    if (gameIsland.isTileBuildable(mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY(),buildingID))
                    {
                        mouseCursor.updateCursorColor(0,255,0);
                    }
                    else
                    {
                        mouseCursor.updateCursorColor(255,0,0);
                    }
                }

                //Mouse over main menu buttons
                isCursorInButton(aButton);
                isCursorInButton(labButton);

                //Build menu Highlighting
                bool buildMenuOn = BuildMenuOverlay.isShown();

                if (buildMenuOn)
                {
                    isCursorInButton(roadButton);
                    isCursorInButton(fenceButton);
                    isCursorInButton(buildLabButton);
                    isCursorInButton(buildDockButton);
                }


            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {

                int x,y;
                SDL_GetMouseState( &x, &y );

                gameIsland.checkGuestMouseClick();

                //Build mode
                if (buildMode == true && buildingID != 0)
                {
                    //Build a road
                    if (roadButton.isClicked() && gameIsland.isTileBuildable(mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY(),buildingID))
                    {
                        gameIsland.createStructure(buildingID,mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY());
                    }
                    //Build a Research lab
                      if (buildLabButton.isClicked() && gameIsland.isTileBuildable(mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY(),buildingID))
                    {
                        gameIsland.createStructure(buildingID,mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY());
                    }
                    //Build a dino fence
                    if (fenceButton.isClicked() && gameIsland.isTileBuildable(mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY(),buildingID))
                    {
                        gameIsland.createStructure(buildingID,mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY());
                    }
                    //Build a Dock
                    if (buildDockButton.isClicked() && gameIsland.isTileBuildable(mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY(),buildingID))
                    {
                        gameIsland.createStructure(buildingID,mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY());
                    }
                }

                bool buildMenuOn = BuildMenuOverlay.isShown();

                if (checkUICollision(x,y,aButton) == true)
                {
                    //Build Button Click******
                    aButton.onClick();

                    //Turn overlay on
                    if (buildMenuOn == true)
                    {
                        //Close build menu elements
                        BuildMenuOverlay.hide();
                        fenceButton.hide();
                        roadButton.hide();
                        buildDockButton.hide();
                        buildLabButton.hide();
                        buildPathButton.hide();
                        fenceButton.onRelease();
                        roadButton.onRelease();
                        buildDockButton.onRelease();
                        buildPathButton.onRelease();

                        buildMode = false;
                        mouseCursor.updateCursorColor(255,255,255);

                    }
                    else
                    {
                        //Show Build Menu Elements
                        fenceButton.show();
                        roadButton.show();
                        buildLabButton.show();
                        buildDockButton.show();
                        BuildMenuOverlay.show();
                        buildPathButton.show();
                    }
                    //END Build button click;
                }

                    if (checkUICollision(x,y,labButton) == true)
                    {
                        labButton.onClick();
                    }

                    //Build Menu
                    if (BuildMenuOverlay.isShown())
                    {
                        //Start Building Roads
                        if (checkUICollision(x,y,roadButton) == true)
                        {
                            roadButton.onClick();
                            fenceButton.onRelease();
                            buildLabButton.onRelease();
                            buildDockButton.onRelease();
                            buildPathButton.onRelease();
                            SDL_ShowCursor(0);

                            //Toggle Build Mode
                            if (roadButton.isClicked())
                            {
                                buildMode = true;
                                buildingID = 1;
                                mouseCursor.updateSize(1);

                            }
                            else
                            {
                                buildMode = false;
                                buildingID = 0;
                                mouseCursor.updateCursorColor(255,255,255);
                                mouseCursor.updateSize(1);
                                SDL_ShowCursor(1);

                            }

                        }
                        //Start building fences
                        if (checkUICollision(x,y,fenceButton) == true)
                        {
                            fenceButton.onClick();
                            roadButton.onRelease();
                            buildLabButton.onRelease();
                            buildDockButton.onRelease();
                            SDL_ShowCursor(0);

                             //Toggle Build Mode
                            if (fenceButton.isClicked())
                            {
                                buildMode = true;
                                buildingID = 3;
                                mouseCursor.updateSize(1);
                            }
                            else
                            {
                                buildMode = false;
                                buildingID = 0;
                                mouseCursor.updateCursorColor(255,255,255);
                                mouseCursor.updateSize(1);
                                SDL_ShowCursor(1);

                            }
                        }
                        //Build a lab
                        if (checkUICollision(x,y,buildLabButton) == true)
                        {
                            //Click button, release all others
                            buildLabButton.onClick();
                            roadButton.onRelease();
                            fenceButton.onRelease();
                            buildDockButton.onRelease();
                            SDL_ShowCursor(0);

                            //Toggle Build Mode
                            if (buildLabButton.isClicked())
                            {
                                buildMode = true;
                                buildingID = 2;
                                mouseCursor.updateSize(4);
                            }
                            else
                            {
                                buildMode = false;
                                buildingID = 0;
                                mouseCursor.updateCursorColor(255,255,255);
                                mouseCursor.updateSize(1);
                                SDL_ShowCursor(1);

                            }

                        }

                        //Build a lab
                        if (checkUICollision(x,y,buildDockButton) == true)
                        {
                            //Click button, release all others
                            buildDockButton.onClick();
                            roadButton.onRelease();
                            fenceButton.onRelease();
                            buildLabButton.onRelease();
                            SDL_ShowCursor(0);

                            //Toggle Build Mode
                            if (buildDockButton.isClicked())
                            {
                                buildMode = true;
                                buildingID = 4;
                                mouseCursor.updateSize(5);
                            }
                            else
                            {
                                buildMode = false;
                                buildingID = 0;
                                mouseCursor.updateCursorColor(255,255,255);
                                mouseCursor.updateSize(1);
                                SDL_ShowCursor(1);
                            }
                        }
                }
            }

        }

        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }

        //Window Scroll
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if( currentKeyStates[ SDL_SCANCODE_UP ] )
        {
           aWindow.scroll(1);
        }
        else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
        {
           aWindow.scroll(2);
        }
        else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        {
           aWindow.scroll(3);
        }
         else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        {
           aWindow.scroll(4);
        }
        //Calculate the scroll height
        int scrollY=aWindow.getY();
        int scrollX=aWindow.getX();

        gameIsland.checkGuestMouseOver(mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY(),renderer);

        //AI
        gameIsland.guestAI();

        //Clear screen
        SDL_RenderClear(renderer);

        //draw screen
        //Rendering tasks

        gameIsland.drawBackground(renderer,scrollX,scrollY);
        gameIsland.renderStructures(renderer,scrollX,scrollY);
        gameIsland.renderPeople(renderer,scrollX,scrollY);

        //UI Elements

        //why the fuck did i call something this
         if (aButton.isShown())
         {
            aButton.applySurface(renderer);
         }
         //global ui -> tech
         if (labButton.isShown())
         {
             labButton.applySurface(renderer);
         }
         //Build -> Build menu backgroun
         if (BuildMenuOverlay.isShown())
         {
             BuildMenuOverlay.applySurface(renderer);
         }
         //Build -> road
         if (roadButton.isShown())
         {
             roadButton.applySurface(renderer);
         }
         //build -> Fence
        if (fenceButton.isShown())
         {
             fenceButton.applySurface(renderer);
         }
         //global ui -> Status backgroun
         if (CornerStatusOverlay.isShown())
         {
             CornerStatusOverlay.applySurface(renderer);
         }
         //build -> research lab
         if (buildLabButton.isShown())
         {
             buildLabButton.applySurface(renderer);
         }
         //build -> dock
         if (buildDockButton.isShown())
         {
             buildDockButton.applySurface(renderer);
         }
         //build -> Path
         if (buildPathButton.isShown())
         {
             buildPathButton.applySurface(renderer);
         }

         //labels
         dateLabel.printLabel(renderer);
         timeLabel.printLabel(renderer);

         //Build mode grid
         if (buildMode == true)
         {
            mouseCursor.applySurface(renderer);
         }

        //Text on screen
        gameIsland.printText(renderer);

        //Flip screen
        SDL_RenderPresent(renderer);

        countedFrames++;

        if (countedFrames >= 60)
        {
            dateTime.cycleMinute();
            timeLabel.setText(dateTime.getTime(),renderer);
            dateLabel.setText(dateTime.getDate(),renderer);
            countedFrames = 0;
        }

        //If frame finished early
        int frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICKS_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
        }
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }

    return 0;
}

//Mouse collision with UI elements. Goes through manually
bool checkUICollision(int x, int y, Button buttonToCheck)
{
    SDL_Rect pos = buttonToCheck.getPosition();

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



void isCursorInButton(Button buttonToCheck)
    {
        int x,y;
        SDL_GetMouseState( &x, &y );

        if (!buttonToCheck.isClicked())
         {
            if(checkUICollision(x,y,buttonToCheck))
            {
                buttonToCheck.mouseIn();
            }
            else
            {
                buttonToCheck.mouseOut();
            }
         }
    }


