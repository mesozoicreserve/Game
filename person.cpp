#include "person.h"

Person::Person()
{
    position.x = 0;
    position.y = 0;
    position.w=0;
    position.h=0;
    angle = 180;
    setClip(0);
    genDer();


    genName();
    genAge();

    highlight = 255;
    direction = 1;

    moveQueue.resize(6);

    moveQueue[0].initializeLogic(1,position.x,position.y);
}

bool Person::isClicked()
{
    return clicked;
}
std::string Person::getName()
{
    return name;
}
Person::Person(int x, int y, SDL_Renderer* renderer)
{
   newPerson(x,y,renderer);
}

SDL_Texture* Person::loadTexture( std::string path,SDL_Renderer* renderer )
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

void Person::applySurface(SDL_Renderer* renderer,int x, int y)
{

    SDL_Point* center = NULL;
    SDL_Rect footQuad;
    SDL_Rect renderQuad = { position.x + x,position.y + y, position.w, position.h };


        if (foot >= 15)
        {
            footQuad.x = leftFoot.x + x;
            footQuad.y = leftFoot.y + y;
            footQuad.w = leftFoot.w;
            footQuad.h = leftFoot.h;
        }
        else
        {

            footQuad.x = rightFoot.x + x;
            footQuad.y = rightFoot.y + y;
            footQuad.w = rightFoot.w;
            footQuad.h = rightFoot.h;
        }

   // SDL_RenderCopy(renderer,texture,&frame,&tmppos);

   // SDL_RenderCopyEx(renderer,feetTexture,&feetRect,&footQuad,angle,center,SDL_FLIP_NONE);

    SDL_RenderCopyEx( renderer, texture, &frame, &renderQuad, angle, center, SDL_FLIP_NONE );

}

void Person::setClip(int clipID)
{
    frame.x = 0;
    frame.y = 0;
    frame.w = 17;
    frame.h = 10;

    feetRect.x=0;
    feetRect.y=0;
    feetRect.w=6;
    feetRect.h=9;
}

void Person::newPerson(int x, int y, SDL_Renderer* renderer)
{
   //Set position
    position.x = x;
    position.y = y;
    position.w=9;
    position.h=6;

    leftFoot.x = 0;
    leftFoot.y = 0;
    leftFoot.w=6;
    leftFoot.h=9;

    leftFoot.x = 0;
    leftFoot.y = 0;
    rightFoot.w=6;
    rightFoot.h=9;

    //default clip
    setClip(0);

    highlight = 255;
    direction = 1;
    clicked = false;

    if (gender==1)
    {
        texture = loadTexture("person.bmp",renderer);
    }
    else
    {
        texture = loadTexture("persongirl.bmp",renderer);
    }

    feetTexture = loadTexture("foot.bmp",renderer);

    moveQueue.resize(6);


    moveQueue[0].initializeLogic(1,position.x,position.y);
}

void Person::rotatePerson()
{
    int target = moveQueue[0].getTargetAngle();
    if (angle > target)
    {
        angle-=5;
    }
    if ((angle < target))
    {
        angle+=5;
    }

    setAngle();
}

void Person::setAngle()
{
    //Validate
    if (angle > 360)
    {
        angle=1;
    }
}
Person::~Person()
{
    angle=0;
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
    }

}

void Person::calculateMovements(int up, int down, int left, int right)
{
    if (!moveQueue[0].isAtTargetAngle(angle))
    {
        rotatePerson();
    }
    else
    {

        if (!moveQueue[0].isAtTarget(position.x,position.y))
        {
            if (position.y < moveQueue[0].getTargetY())
            {
                position.y++;
                if (down != 2)
                {
                    cycleMoves();
                }
            }
            if (position.y > moveQueue[0].getTargetY())
            {
                position.y--;
                if (up != 2)
                {
                    cycleMoves();
                }
            }
            if (position.x < moveQueue[0].getTargetX())
            {
                position.x++;
                if (right != 2)
                {
                    cycleMoves();
                }
            }
            if (position.x > moveQueue[0].getTargetX())
            {
                position.x--;
                if (left != 2)
                {
                    cycleMoves();
                }
            }
        }
        else
        {
            //cycle moves
            cycleMoves();
        }

            moveFeet();

    }

}

void Person::cycleMoves()
{
        moveQueue.pop_front();
        moveQueue.push_back(GuestLogic());

        //set last undefined move in the queue to be random
        for (int i=0;i<moveQueue.size();i++)
        {
            moveQueue[i].initializeLogic(1,position.x,position.y);
        }

}

void Person::unClick()
{
    clicked = false;
}

void Person::onMouseClick()
{
    if (clicked == true)
    {
        clicked = false;
    }
    else
    {
        clicked = true;
        SDL_SetTextureColorMod(texture,0,0,255);
    }
}

//Person glows when moused over
void Person::onMouseOver()
{
    if (!clicked)
    {

        switch (direction)
        {
        case 0:
            highlight+=10;
            break;
        case 1:
            highlight-=10;
            break;
        }

        if (direction == 0 && highlight >= 255 )
        {
            direction = 1;
        }
        if (direction == 1 && highlight <= 0)
        {
            direction = 0;
        }

        SDL_SetTextureColorMod(texture,highlight,highlight,255);
    }

}

void Person::onMouseOut()
{
    if (!clicked)
    {
        highlight=255;
        SDL_SetTextureColorMod(texture,255,255,255);
    }
}

int Person::getX()
{
    return position.x;
}
int Person::getY()
{
    return position.y;
}


void Person::genName()
{
    string firstNameBank[] = {"Chris","Mark","Randy","Joeseph","Andrew","Ralph","Reggie","Leroy","Steven","Alan",
                            "Jordan","Eric","Keith","Joffery","Jeffery","Alexander","Matthew","Nicholas","Jan","Benjamin",
                            "Dallas","Walter","Jesse","Robert","Riley","Richard","Archibald","Kevin","Pradeep","Mohammed",
                            "Ash","Brock","Gary","Charlie","Dennis","Mac","Frank","Barnaby","Ronald","Harry",
                            "Jamal","Jerome","Dragan","Maury","John","Bort","Rick","Glen","Herschel","Shane"};
    string firstNameBankFemale[] = {"Christine","Nicole","Randi","Amber","Vanessa","Maddie","Becky","Rebecca","Britney","Jamie","Janie",
                                    "Debbie","Mallory","Sarah","Sadie","Tina","Carey","Tracy","Alex","Katy"
                                     ,"Eileen","Doreen","Marlene","Lori","Maggie","Amanda","Kristen","Nancy","Brittany","Kim"};

    string lastNameBank[] = {"Jones","Jameson","Jackson","Jefferson","Miller","Stein","Avery","Kaczmasrk","DeForest","Meyer-Love",
                            "Fannon","Hopkins","GoodStone","Boyd","Reinhart","Wilson","Lee","Albano","Reibow","Gellman",
                            "Draper","Touchstone","Zimmerman","White","Pinkman","Jenkins","Mazor","Feeney","McGarvey","Livingston",
                            "Hughes","Ryans","Andrews","Winters","Thompson","Irwin","Underhill","Oliver","Bush","Ryans",
                            "Potter","Weasley","Granger","Lisi","Ford","Winters","Brooks","Blair","Williams","Bellamy"};


    int randomFirst;

    int randomLast = rand() % 50;


    if (gender == 1)
    {
        randomFirst = rand() % 50;
        name = firstNameBank[randomFirst] + " " + lastNameBank[randomLast];

    }
    //Girl Names
    else
    {
        randomFirst = rand() % 30;
        name = firstNameBankFemale[randomFirst] + " " + lastNameBank[randomLast];
    }

}

void Person::genAge()
{
    age = (rand() % 55) + 4;
}

string Person::getAge()
{
    char buffer[2];
    char *cAge = itoa(age,buffer,10);

    string strAge = string(cAge);

    string stringToPrint = "Age: " + strAge;
    return  stringToPrint;
}

void Person::genDer()
{
    gender = (rand() % 2) + 1;
}

void Person::moveFeet()
{
    //calculate foot positions
    leftFoot.x = position.x;
    leftFoot.y = position.y;

    rightFoot.x = position.x + 7;
    rightFoot.y = position.y;

    foot++;
    if (foot > 31)
    {
        foot = 1;
    }
}

void Person::notMoving()
{
}
