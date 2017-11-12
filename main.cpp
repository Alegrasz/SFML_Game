#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <SFML/graphics.hpp>
#include <SFML/audio.hpp>

/*

*/

void title();
void level1();

float WindowX = 800, WindowY = 600;

sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "The Great Game");
sf::Event event;

class detection
{
public:
    bool triggerBox(float ObjPosX, float ObjPosY, float triggerTopX, float triggerTopY, float triggerBottomX, float triggerBottomY)
    {
        bool Triggered;
        // it checks if the object is within the set boundaries of the player or object
        if((ObjPosX > triggerTopX && ObjPosY > triggerTopY) && (triggerBottomX > ObjPosX && triggerBottomY > ObjPosY))
        {
            Triggered = true;
            //std::cout << Triggered << std::endl;
            return Triggered;
        }
/*---- Note ----*/ // it checks if the object or player is not within the boundary
        if(!((ObjPosX > triggerTopX && ObjPosY > triggerTopY) && (triggerBottomX > ObjPosX && triggerBottomY > ObjPosY)))
        {
            Triggered = false;
            //std::cout << Triggered << std::endl;
            return Triggered;
        }

    }
};
//-------------------OBJECT CLASS---------------------------------------------------------------------------//
// OBJECT class: There is nothing to update in the object class

class object
{
public:
//--------------------------------------------------------------------
//draw box anywhere you want // DON'T TOUCH THIS AT ALL
    std::pair <float, float > box(float *SetPosX, float *SetPosY , float sizeX, float sizeY, int R, int G, int B)
    {
        sf::RectangleShape rectan;
        rectan.setPosition(*SetPosX, *SetPosY);
        rectan.setSize(sf::Vector2f(sizeX, sizeY));
        rectan.setFillColor(sf::Color(R, G, B));
        std::pair <float, float> Pos(rectan.getPosition().x, rectan.getPosition().y);

        window.draw(rectan);


        return  Pos;
    }
//---------------------------------------------------------------------
//Can place a circle // DON'T TOUCH THIS AT ALL
    void circle(float SetPosX, float SetPosY, float Radius, int R, int G, int B)
    {
        sf::CircleShape circle;
        circle.setPosition(SetPosX, SetPosY);
        circle.setRadius(Radius);
        circle.setFillColor(sf::Color(R, G, B));
        window.draw(circle);
    }
//----------------------------------------------------------------------
// This is used to set the position of the text and write text to screen // DON'T TOUCH THIS AT ALL!!!!!1
    std::pair <float, float> text(std::string TTF, unsigned int TextSize, std::string TypeText, float SetPosX, float SetPosY, int R, int G, int B)
    {
        sf::Font font;
        sf::Text text;

        if(!font.loadFromFile(TTF + ".ttf"))
        {
            std::cout << "error: " << TTF << ".ttf could not be found" << std::endl;
        }

        text.setFont(font);
        text.setCharacterSize(TextSize);
        text.setString(TypeText);
        text.setPosition(SetPosX, SetPosY);
        text.setFillColor(sf::Color(R, G, B));
        window.draw(text);

        float textBoundaryX = text.getLocalBounds().width;
        float textBoundaryY = text.getLocalBounds().height;

        std::pair <float, float> boundary(textBoundaryX, textBoundaryY);

        return boundary;
    }
//-----------------------------------------------------------------------
// This is to set camera position //ALL OF THIS WORKS SO DON'T TOUCH!!!!!
    void  camera(float charPosX, float charPosY)
    {
        sf::View view;
        view.reset(sf::FloatRect(0, 0, WindowX, WindowY));
        view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

            if(charPosX > (WindowX / 2))
            {
                view.setCenter(charPosX, (WindowY /2));
            }

        window.setView(view);
    }
//-----------------------------------------------------------------------
// This is to set sprites  // ALL OF THIS WORKS SO DON'T TOUCH!!!!!!!!
    std::pair <float, float> sprite(std::string fileName, float SpritePosX, float SpritePosY, float updateMovementx, float updateMovementY)
    {
        sf::Texture texture;
        sf::Sprite sprite;

        if(!texture.loadFromFile(fileName))
        {
            std::cout << "Error file not found" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setPosition(SpritePosX, SpritePosY);
        sprite.move(updateMovementx, updateMovementY);
        window.draw(sprite);

        std::pair <float, float> PosOfSprite (SpritePosX, SpritePosY);

        return PosOfSprite;
    }
};

//needs more testing
// two different class needed?
class physics
{
// also contains collision
public:
    std::pair <float, float> gravityF (float *ObjPositionX, float *ObjPositionY, float *SizeOfObjX, float *SizeOfObjY, float posPlatformX, float posPlatformY, float SizeOfPlatformX, float SizeofPlatformY)
    {
        float velocityX = 0, velocityY = 0;
        float accelerationX = -1, accelerationY = 1;
        float gravity = 0;

        *ObjPositionX += accelerationX;
        *ObjPositionY += accelerationY;
        //std::cout << ObjPositionY << std::endl;
        bool offsetX = false;
        //this checks if the object is out of bounds of the box
        if((*ObjPositionX > posPlatformX + SizeOfPlatformX || *ObjPositionX + *SizeOfObjX < posPlatformX ) )
        {
            offsetX = true;
            *ObjPositionY += gravity;

        }
        // this checks if the object is at the same axis in the y coordinates
        //gets disabled to let the object fall off the platform
        else if(*ObjPositionY + *SizeOfObjY < posPlatformY && offsetX == false)
        {
            *ObjPositionY += gravity;
            //std::cout << "it works " << ObjPositionY << std::endl;
        }
        //this keeps it from sinking from the platform
        else if (*ObjPositionY + *SizeOfObjY  > posPlatformY)
        {
            *ObjPositionY = posPlatformY + *SizeOfObjY;
            //std::cout << "triggered" << std::endl;
        }
        std::pair <float, float> PositionUpdate(*ObjPositionX, *ObjPositionY);
        return PositionUpdate;
    }

    std::pair <float, float> gravityT (float *ObjPositionX, float *ObjPositionY, float *SizeOfObjX, float *SizeOfObjY, float posPlatformX, float posPlatformY, float SizeOfPlatformX, float SizeofPlatformY)
    {

        //std::cout << ObjPositionY << std::endl;
        bool offsetX = false;
        //this checks if it is out of bounds
        if((*ObjPositionX > posPlatformX + SizeOfPlatformX || *ObjPositionX + *SizeOfObjX < posPlatformX ) )
        {
            std::cout << "first" << std::endl;
        }
        // this is within bounds
        else if(*ObjPositionY + *SizeOfObjY < posPlatformY)
        {
            std::cout << "second" << std::endl;
        }
        //this keeps it from sinking from the platform
        /*else if (*ObjPositionY + *SizeOfObjY  > posPlatformY)
        {

        }*/

        std::pair <float, float> PositionUpdate(*ObjPositionX, *ObjPositionY);

        return PositionUpdate;
    }
};

class Collision
{
public:
    bool collision(float *ObjX, float *ObjY, float *ObjSizeX, float *ObjSizeY, float PlatformX, float PlatformY, float PlatformSizeX, float PlatformSizeY )
    {
        bool collided = false;
        bool outofbounds = false;
        bool isActivated = false;

        if((*ObjX > PlatformX) && (*ObjX < PlatformX + PlatformSizeX) && isActivated == false)
        {
            outofbounds = true;
            //return outofbounds;
        }
        else if(*ObjY == PlatformY)
        {
            std::cout << "it activated" << std::endl;
            isActivated = true;
            collided = true;
            //return collided;
        }
    }



};

class pureGravity
{
public:
    std::pair <float, float> PGravity (float *posObjX, float *posObjY, bool collided)
    {
        float gravity = 8;
        float accelerationX = -3, accelerationY= 0;

        *posObjX += accelerationX;
        *posObjY += accelerationY;
        if( collided == false)
        {
            //std::cout << "activated" << std::endl;
            *posObjY += gravity;

        }
        if (collided == true){std::cout << "Deactiveted" << std::endl;}

        std::pair<float, float> NewPosition (*posObjX, *posObjY);

        return NewPosition;
    }
};

class purecollision
{
public:
        bool isCollisionTrue(float ObjPosX, float ObjPosY, float SizeOfObjX, float SizeOfObjY, float platformPosX, float platformPosY, float SizeOfplatformX, float SizeOfplatformY)
        {
            bool collided = false;
            if(ObjPosX + SizeOfObjX > platformPosX && ObjPosX < platformPosX +  SizeOfplatformX)
            {
                //std::cout << "first activated in the collision" << std::endl;
                if(ObjPosY + SizeOfObjY > platformPosY)
                {
                    //std::cout << "The Second also works" << std::endl;
                    collided = true;
                    return collided;
                }
                else if(ObjPosY  < platformPosY)
                {
                    collided = false;
                    return collided;
                }
            }
        }
};


int main()
{
    window.setFramerateLimit(60);
    title();
    return 0;
}

void title()
{
    while (window.isOpen())
    {
        bool clicked;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
            {
                clicked = true;
            }
        }

        object *win;
        detection *triggerBox;

        window.clear();

        win->circle(180, 120, 80.0f, 0, 0, 255);
        win->text("arial", 45, "The Great Game", 240, 180, 255, 0, 0);
        //This makes the button
        std::pair <float, float> boundaryPlay = win->text("arial", 45, "Play Game", 290, 300, 255, 0, 0);

        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        bool button = triggerBox->triggerBox(mouse.x, mouse.y, 290, 300, (290 + boundaryPlay.first), (300 + boundaryPlay.second));

        if((button == true))
        {
            win->text("arial", 45, "Play Game", 290, 300, 0, 255, 0);
        }
        if(clicked == true && button == true)
        {
           // std::cout << "it works" << std::endl;
            level1();
        }
        window.display();
    }
}
float BoxPosX = 500;
float BoxPosY = 200;
float platformX = 400, platformY = 300;
float sizeBoxX = 50;
float sizeBoxY = 50;
float sizeofPlatormX = 400;
float sizeofPlatormY = 40;


float platform1X = 100, platform1Y = 500;
float sizeofPlatorm1X = 400, sizeofPlatorm1Y = 40;


void level1()
{
     while (window.isOpen())
    {
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }
        object *platform;
        object *fallingObj;
        physics *AddGravity;
        pureGravity *addgravityTo;
        purecollision *collided;
        window.clear();

        //std::pair <float, float> newPosofBox = AddGravity->gravityF(&BoxPosX, &BoxPosY, &sizeBoxX, &sizeBoxY, platformX, platformY, sizeofPlatormX, sizeofPlatormY);
        //std::cout << newPosofBox.first << " " << newPosofBox.second << std::endl;
        bool CollisionIs = collided->isCollisionTrue(BoxPosX, BoxPosY, sizeBoxX,sizeBoxY, platformX, platformY, sizeofPlatormX, sizeofPlatormY);
        bool CollisionIsBox = collided->isCollisionTrue(BoxPosX, BoxPosY, sizeBoxX,sizeBoxY, platform1X, platform1Y, sizeofPlatorm1X, sizeofPlatorm1Y);
        // put all the bools in a array?
        float arrayOFCollision[2] = {CollisionIs, CollisionIsBox};
        int i = 0;

        if(arrayOFCollision[1] == true)
        {
            i = 1;
        }
        std::cout << arrayOFCollision[0] << std::endl;
        std::pair <float, float> newPosofBox = addgravityTo->PGravity(&BoxPosX, &BoxPosY, arrayOFCollision[i]);
        //addgravityTo->PGravity(&BoxPosX, &BoxPosY, CollisionIsBox);
        fallingObj->box(&newPosofBox.first,&newPosofBox.second, sizeBoxX, sizeBoxY, 255, 0, 255);

        //AddGravity->gravityF(&BoxPosX, &BoxPosY, &sizeBoxX, &sizeBoxY, WindowX, WindowY, platform1X, platform1Y, sizeofPlatorm1X, sizeofPlatorm1Y);
        platform->box(&platformX, &platformY, sizeofPlatormX,sizeofPlatormY , 0, 255, 0);
        platform->box(&platform1X, &platform1Y, sizeofPlatorm1X,sizeofPlatorm1Y , 0, 255, 0);

        window.display();
    }


}
