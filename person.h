#include <String>
#include "SDL_Image.h"
#include "guestLogic.h"
#include <iostream>
#include <time.h>
#include <math.h>
#include <deque>

using namespace std;

class Person
{
private:
    int angle;
    SDL_Rect position;
    SDL_Rect frame;
    SDL_Rect feetRect;
    SDL_Rect leftFoot;
    SDL_Rect rightFoot;
    SDL_Texture* texture;
    SDL_Texture* feetTexture;
    Uint8 highlight;
    int direction;
    std::deque<GuestLogic> moveQueue;
    string name;
    bool clicked;
    int age;
    int gender;
    int foot;

public:
    Person();
    ~Person();
    void rotatePerson();
    Person(int,int,SDL_Renderer*);
    void applySurface(SDL_Renderer*,int,int);
    SDL_Texture* loadTexture(std::string,SDL_Renderer*);
    void setClip(int);
    void newPerson(int,int,SDL_Renderer*);
    void setAngle();
    void calculateMovements(int,int,int,int);
    int getX();
    int getY();
    void cycleMoves();
    string getName();
    void genName();
    void notMoving();

    void genAge();
    string getAge();
    void genDer();

    bool isClicked();
    void onMouseOver();
    void onMouseOut();
    void onMouseClick();
    void unClick();

    void moveFeet();
};

