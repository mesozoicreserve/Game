#define MAP_X 200
#define MAP_Y 200
#define NUM_GUESTS 150

#include "Tile.h"
#include "Structure.h"
#include <cstdlib>
#include <time.h>
#include <math.h>
#include "SDL_Image.h"
#include "person.h"
#include "Label.h"
#include "overlay.h"
#include <string>


class Island
{
private:
    Tile **grid;
    Tile **featureGrid;
    Structure **structureMap;
    SDL_Texture* backgroundTexture;
    SDL_Texture* structureTexture;
    SDL_Texture* featureTexture;
    Person aPerson[NUM_GUESTS];
    int selectedIndex;

    //UI elements bound to the game world
    Overlay guestMouseOverOverlay;
    Label personNameLabel;
    Label personAgeLabel;
    Label parkNameLabel;
public:
    Island();
    void allocateMemory();
    ~Island();
    Island(SDL_Renderer*);
    void drawBackground(SDL_Renderer*,int,int);
    void genWorld();
    void genBase(int,int);
    void smoothMap(int,int);
    void genMapDetails(int,int);
    void seedMud(int,int);
    void runMud();
    Tile getTile(int,int);
    void applySurface(SDL_Renderer* renderer,SDL_Rect clip, SDL_Rect tgt,int, int);
    SDL_Texture* loadTexture(std::string,SDL_Renderer* );
    void renderStructures(SDL_Renderer*,int,int);
    void createStructure(int,int,int);
    void updateRoads();
    bool isTileBuildable(int,int,int);
    void renderPeople(SDL_Renderer*,int,int);
    void guestAI();
    void checkGuestMouseOver(int cursorX,int cursorY,SDL_Renderer*);
    void checkGuestMouseClick();
    void printText(SDL_Renderer* renderer);
    void updateFences();
};
