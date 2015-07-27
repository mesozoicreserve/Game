#define BUILDMENU_ITEMS 5
#define LABEL_NUM 4

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
#include "Appointment.h"
#include "MainMenu.h"

using namespace std;

bool checkUICollision(int x, int y, Button buttonToCheck);
void drawBackground(SDL_Renderer*,int,int);
bool isCursorInButton(Button);

SDL_Texture* testButton;

int main (int argc, char* args[])
{

    //Main menu switch
    bool gameStarted = false;

    SDL_Event event;
    bool expired=false;
    const int FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / FPS;

    Window aWindow(1250,500,false);

    SDL_Renderer* renderer = aWindow.getRenderer();

    MainMenu mainMenu(renderer);
    Island gameIsland(renderer);


    gameClock dateTime(8,1,2017,8,0);


    Button aButton("BuildButton",1,455,true);
    Button labButton("LabButton",101,455,true);

    Button buildMenuButtons[BUILDMENU_ITEMS];

    buildMenuButtons[0].newButton("RoadButton",10,370,false);
    buildMenuButtons[1].newButton("FenceButton",10,310,false);
    buildMenuButtons[2].newButton("ResearchLabButton",10,250,false);
    buildMenuButtons[3].newButton("DockButton",10,20,false);
    buildMenuButtons[4].newButton("pathButton",10,90,false);


    Overlay BuildMenuOverlay("SelectionMenu",1,1,200,false,renderer);
    Overlay CornerStatusOverlay("CornerStatus",950,400,200,true,renderer);
    Overlay buildingContextOverlay("BuildContext",189,1,200,false,renderer);

    Label mainLabels[LABEL_NUM];

    mainLabels[0].createLabel(995,410,"ISLA DOUCHEBAR",28,true,renderer);
    mainLabels[1].createLabel(1030,450,dateTime.getDate(),14,true,renderer);
    mainLabels[2].createLabel(1100,450,dateTime.getTime(),14,true,renderer);
    mainLabels[3].createLabel(210,5,"0",16,false,renderer);

    Timer fpsTimer;
    Timer capTimer;

    //Appointment for test
    Appointment genGuests(1);

    //Cursor
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

        //Mouse stuff. Hopefully this works and the mouse gets set every frame. Might cut down on lag?
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

       /*) while (!gameStarted)
        {
                while( SDL_PollEvent( &event ) != 0 )
                {
                    //User requests quit
                    if( event.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if (event.type == SDL_MOUSEMOTION)
                    {
                        //Check to see if Mouse is on a button
                        mainMenu.checkButtonMouseOver(x,y);
                    }

                }
                mainMenu.applySurface(renderer);
                SDL_RenderPresent(renderer);


        }*/


        while( SDL_PollEvent( &event ) != 0 )
        {



        /* ******************************************************
                MAIN GAME SEQUENCE
        */
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                quit = true;
                gameStarted = true;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {

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
                    for (int i=0;i<BUILDMENU_ITEMS;i++)
                    {
                        //Show and update the overlay, also process the color change of the button
                        if (isCursorInButton(buildMenuButtons[i]))
                        {
                            buildingContextOverlay.show();
                            //Update and show Context label
                            mainLabels[3].setText(buildMenuButtons[i].getName(),renderer);
                            mainLabels[3].show();
                            //break from loop (or overlay will turn off)
                            i=1000;
                        }
                        else
                        {
                            //Lock overlay when build mode is on
                            if (buildMode == false)
                            {
                                buildingContextOverlay.hide();
                                mainLabels[3].hide();
                            }
                        }
                    }
                }


            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {

                int x,y;
                SDL_GetMouseState( &x, &y );

//                gameIsland.checkGuestMouseClick();
                //Build mode
                if (buildMode == true && buildingID != 0)
                {
                    for (int i=0; i<BUILDMENU_ITEMS;i++)
                    {
                        //Check if we can build on the tile
                        if (buildMenuButtons[i].isClicked() && gameIsland.isTileBuildable(mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY(),buildingID))
                        {
                            //Build the building
                            gameIsland.createStructure(buildingID,mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY());
                        }
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
                        for (int i=0; i<BUILDMENU_ITEMS;i++)
                        {
                            buildMenuButtons[i].hide();
                            buildMenuButtons[i].onRelease();
                            buildingContextOverlay.hide();
                            mainLabels[3].hide();
                        }
                        BuildMenuOverlay.hide();

                        buildMode = false;
                        mouseCursor.updateCursorColor(255,255,255);

                    }
                    else
                    {
                        //Show Build Menu Elements
                         for (int i=0; i<BUILDMENU_ITEMS;i++)
                        {
                            buildMenuButtons[i].show();
                        }
                        BuildMenuOverlay.show();
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
                        for (int i=0; i<BUILDMENU_ITEMS;i++)
                        {
                            //Start Building Roads
                            if (checkUICollision(x,y,buildMenuButtons[i]) == true)
                            {
                                buildMenuButtons[i].onClick();
                                //Close build menu elements
                                for (int j=0; j<BUILDMENU_ITEMS;j++)
                                {
                                    if (j != i)
                                    {
                                        buildMenuButtons[j].onRelease();
                                    }
                                }
                                SDL_ShowCursor(0);
                                //Toggle Build Mode
                                if (buildMenuButtons[i].isClicked())
                                {
                                    buildMode = true;

                                    switch (i)
                                    {
                                        case 0:
                                            buildingID = 1;
                                            mouseCursor.updateSize(1);
                                            break;
                                        case 1:
                                            buildingID = 3;
                                            mouseCursor.updateSize(1);
                                            break;
                                        case 2:
                                            buildingID = 2;
                                            mouseCursor.updateSize(4);
                                            break;
                                        case 3:
                                            buildingID = 4;
                                            mouseCursor.updateSize(5);
                                            break;
                                        case 4:
                                            buildingID = 5;
                                            mouseCursor.updateSize(1);
                                            break;
                                    }

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

        if (gameIsland.getNumGuests() > 0 )
        {
                    gameIsland.checkGuestMouseOver(mouseCursor.getAbsoluteX(),mouseCursor.getAbsoluteY(),renderer);
                    gameIsland.guestAI();
        }

        //AI

        //Clear screen
        SDL_RenderClear(renderer);

        //draw screen
        //Rendering tasks
        gameIsland.drawBackground(renderer,scrollX,scrollY);
        gameIsland.renderStructures(renderer,scrollX,scrollY);

        if (gameIsland.getNumGuests() > 0 )
        {
            gameIsland.renderPeople(renderer,scrollX,scrollY);
        }

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
         if (buildingContextOverlay.isShown())
         {
             buildingContextOverlay.applySurface(renderer);
         }
         //Build -> road
         for (int i=0;i<BUILDMENU_ITEMS;i++)
         {
             if (buildMenuButtons[i].isShown())
             {
                 buildMenuButtons[i].applySurface(renderer);
             }
         }

         //global ui -> Status backgroun
         if (CornerStatusOverlay.isShown())
         {
             CornerStatusOverlay.applySurface(renderer);
         }


         //labels
         for (int i=0;i<LABEL_NUM;i++)
         {
             if (mainLabels[i].isShown())
             {
                 mainLabels[i].printLabel(renderer);
             }
         }

         //Build mode grid
         if (buildMode == true)
         {
            mouseCursor.applySurface(renderer);
         }

        //Text on screen
        gameIsland.printText(renderer);

        //Flip screen
        SDL_RenderPresent(renderer);


        //Trigger this once per game second, hopefully
        if (countedFrames == 0)
        {
            //Check appointments - do we have to do anything?
            if (genGuests.isActive())
            {
                //Check to see the date is right
                if (dateTime.getDate() == genGuests.getAppDate() || genGuests.getAppDate() == "Daily")
                {
                    //Check the time
                    if (dateTime.getTime() == genGuests.getAppTime())
                    {
                        //Eventually this will call a function to take care of the action,
                        //right now i'm just lazy because there's only one
                        gameIsland.guestGenerator(renderer);
                    }
                }
            }
        }



        countedFrames++;

        if (countedFrames >= 60)
        {
            dateTime.cycleMinute();
            //Update labels
            mainLabels[2].setText(dateTime.getTime(),renderer);
            mainLabels[1].setText(dateTime.getDate(),renderer);

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


    if (gameIsland.getNumGuests() > 0)
    {
        gameIsland.printGuests();
        system("Pause");
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



bool isCursorInButton(Button buttonToCheck)
    {
        int x,y;
        SDL_GetMouseState( &x, &y );

        if (!buttonToCheck.isClicked())
         {
            if(checkUICollision(x,y,buttonToCheck))
            {
                buttonToCheck.mouseIn();
                return true;
            }
            else
            {
                buttonToCheck.mouseOut();
                return false;
            }
         }
    }



