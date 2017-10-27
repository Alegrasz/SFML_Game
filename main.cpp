#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

/*------------------ All main windows for the game --------------------
*   --Note: use CTRL + F then type the name that you want to go too
*
*   * int main
*   * title window
*   * level 1
*   * level 2 --empty/testing
*
*------------------- All main windows above ---------------------------*/


/*--------------- all the functions available are below ---------------*/

int level_2();
int level_1();
void updateMovemnet();
void ground_dectection();
void jumpcounter();

/*--------------- all the functions available are above ---------------*/



float WindowX = 800, WindowY = 600;

sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "The Great Game");
sf::Event event;

// Note: find out how to make objects to inherit gravity

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
            std::cout << Triggered << std::endl;
            return Triggered;
        }
/*---- Note ----*/ // it checks if the object or player is not within the boundary
        if(!((ObjPosX > triggerTopX && ObjPosY > triggerTopY) && (triggerBottomX > ObjPosX && triggerBottomY > ObjPosY)))
        {
            Triggered = false;
            std::cout << Triggered << std::endl;
            return Triggered;
        }
    }
};

class object
{
public:
    void box(float SetPosX, float SetPosY , float sizeX, float sizeY, int R, int G, int B)
    {
        sf::RectangleShape rectan;
        rectan.setPosition(SetPosX, SetPosY);
        rectan.setSize(sf::Vector2f(sizeX, sizeY));
        rectan.setFillColor(sf::Color(R, G, B));
        window.draw(rectan);
    }

    void circle(float SetPosX, float SetPosY, float Radius, int R, int G, int B)
    {
        sf::CircleShape circle;
        circle.setPosition(SetPosX, SetPosY);
        circle.setRadius(Radius);
        circle.setFillColor(sf::Color(R, G, B));
        window.draw(circle);
    }

    void text(std::string TTF, unsigned int TextSize,float SetPosX, float SetPosY, int R, int G, int B)
    {
        sf::Font font;
        sf::Text text;

        if(!font.loadFromFile(TTF + ".ttf"))
        {
            std::cout << "error: " << TTF << ".ttf could not be found" << std::endl;
        }

        text.setFont(font);
        text.setCharacterSize(TextSize);
        text.setPosition(SetPosX, SetPosY);
        text.setFillColor(sf::Color(R, G, B));
        window.draw(text);
    }

    void  camera(float charaPosX, float charaPosY)
    {
        sf::View view;
        view.reset(sf::FloatRect(0, 0, WindowX, WindowY));
        view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

        sf::Vector2f CamPosition(0, 0);

        CamPosition.x = charaPosX;
        CamPosition.y = charaPosY;

            view.move(0, 0);

        window.setView(view);
    }

    void sprite(std::string fileName, float SpritePosX, float SpritePosY)
    {
        sf::Texture texture;
        sf::Sprite sprite;

        if(!texture.loadFromFile(fileName))
        {
            std::cout << "Error file not found" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setPosition(SpritePosX, SpritePosY);
        window.draw(sprite);
    }
};

/*---------------------- int main ------------------------------------*/

int main()
{


    window.setFramerateLimit(60);
    enum PGame{mainScreen, level_01};
    //creates the window size and gives the window a name
    //to creates the circle
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(100,140);
    sf::Font font;
    sf::Text text;
    sf::Text title;
    //checks if the file arial.ttf exists
    if(!font.loadFromFile("arial.ttf"))
    {

        std::cout << "There is an error" << std::endl;
    }

    //This is used to set the position of the button

    float xPos = 300, yPos = 350;

    // sets text with set variables
    text.setFont(font);
    text.setString("Play Game");
    text.setCharacterSize(40);
    text.setColor(sf::Color::Red);
    text.setPosition(xPos, yPos);

    //sets title with set variables
    title.setFont(font);
    title.setString("The Great Game");
    title.setCharacterSize(60);
    title.setColor(sf::Color::Red);
    title.setPosition(150, 200);

    //end of the button creation

    bool MouseButtonPressed = false;

/*------------------------ title window ---------------------------*/

    while (window.isOpen())
    {
       //this gets the coordinates of top left corner of the text
        float textCorY = text.getGlobalBounds().height;
        float textCorX = text.getGlobalBounds().width;

        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // start of the Button
        // put all what is below in a class
        //on click

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            MouseButtonPressed = true;
            if(MouseButtonPressed == 1)
            {
                std::cout << "You clicked the left mouse button" << std::endl;
                if(((mouse.x < textCorX + xPos) && (mouse.y < textCorY + yPos)) && ((mouse.x > xPos) && (mouse.y > yPos + 10)))
                {
                    std::cout << "The button works" <<std::endl;
                    text.setColor(sf::Color::Blue);
                    level_1();
                }

            }
        }

        //On hover:
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            MouseButtonPressed = false;
            //std::cout << "The left button is not pressed" << std::endl;
            if(((mouse.x < textCorX + xPos) && (mouse.y < textCorY + yPos)) && ((mouse.x > xPos) && (mouse.y > yPos + 10)))
                {
                    std::cout << "The button works" <<std::endl;
                    text.setColor(sf::Color::Green);
                }
            if(!(((mouse.x < textCorX + xPos) && (mouse.y < textCorY + yPos)) && ((mouse.x > xPos) && (mouse.y > yPos + 10))))
            {
                std::cout << "This really works" << std::endl;
                text.setColor(sf::Color::Red);
            }
        }
        //end of the button and put all the code that is above in a class

        //This used to find the exact position of the button
        //std::cout << mouse.x << " " << mouse.y << std::endl;
        //std::cout << xPos << " " << yPos + 10 << std::endl;
        //std::cout << textCorX + xPos << " " << textCorY + yPos << std::endl;
        //end of finding the exact position of the button
        window.clear();
        //this draws shape title and button to the window

        window.draw(shape);
        window.draw(title);
        window.draw(text);
        window.display();

    }

    return 0;
}

// all the variables for every level

    float moveX = 200, moveY = 400; //sets the position
    float velocityX = 0, velocityY = 0; // sets the velocity
    float accelerationX = 0, accelerationY = 0; // sets the acceleration

    float gravity = 1.5;

    float MasterPosY = 485;

    float boxSetX = 100, boxSetY = MasterPosY; // sets the position of the box

    float characterBottom;

    float jumpcount = 0;

    const float jumped = 1;

    bool isJumping = false;
    bool MAX_Jump = false;
    sf::RectangleShape rect;
    float BoxPosX;
    float BoxPosY;

    std::vector <float> ground;
    std::vector <float>::iterator it;

    bool touchground = true;


/*------------------------ level 1 -------------------------------*/

int level_1()
{


    sf::Vector2f velocity(sf::Vector2f(0,0));

    sf::CircleShape character(30.f);
    character.setFillColor(sf::Color::Red);
    character.setPosition(moveX, moveY);


    rect.setSize(sf::Vector2f(1000, 200));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(boxSetX, boxSetY);


    object *boxA;
    object *boxB;
    object *boxC;
    object *Camera;

    while(window.isOpen())
    {
    // all the set variables

    bool isButtonPressed = false;

    float characterPosX = character.getPosition().x;
    float characterPosY = character.getPosition().y;

    std::cout << characterPosX << " " << characterPosY << std::endl;

    detection TBox;

     bool loadLevel_2 = TBox.triggerBox(characterPosX, characterPosY, 400, 400, 600, 600);

     if(loadLevel_2 == true )
     {
         level_2();
     }

    BoxPosX =  rect.getPosition().x;
    BoxPosY = rect.getPosition().y;


    float sizeofCharX = character.getGlobalBounds().width;
    float sizeofCharY = character.getGlobalBounds().height;

     characterBottom = sizeofCharY + characterPosY;

     //std::cout << characterBottom <<std::endl;


    //std::cout << characterBottom << std::endl;

   // std::cout <<"Char Position in X: " << characterPosX << " Char Position in Y: " << characterPosY << std::endl;
    //std::cout << "Size of character in X: " << sizeofCharX << " Size of character Y: " << sizeofCharY << std::endl;

    float boxPosX = rect.getLocalBounds().width;

    float boxPosY = rect.getLocalBounds().height;



    //std::cout << BoxPosX << " " << BoxPosY << std::endl;

    // to get the position of the mouse
    sf::Vector2i d_mouse = sf::Mouse::getPosition(window);

    //end of all variables



    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // the jumping mechanism
            if(((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)) && MAX_Jump == false)
            {
                velocityY = -20;
                jumpcount += 0;
                isJumping = true;
                touchground = false;
                std::cout << isJumping << std::endl;

            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }

        }

        //std::cout << d_mouse.x << " " << d_mouse.y << std::endl;

        //The usable buttons here

        bool button = false;

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
        {
            velocityX = 0;
        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
        {
            velocityX = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
        {
            velocityX = 5;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocityX = -5;
        }
        /*if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
        {
            velocityY = -2;
        }*/


        //setting a ground

        ground_dectection();

        //end of ground
        updateMovemnet();
        //::cout << moveX << " " << moveY << std::endl;
        character.setPosition(moveX, moveY);
        //gravity(character);

        window.clear();
        boxA->box(0, 0, 800, 600, 244, 200, 155);   // tan
        boxB->box(0, 500, 800, 200, 45, 155, 130);  // dark green
        boxC->box(0, 575, 800, 200, 45, 190, 130);
        object *circle;
        circle->circle(550, 70, 40.f, 255, 0, 0 );  // bright green
        object *cloud;

        cloud->sprite("cloud.png", 50, 90);
        cloud->sprite("cloud.png", 200, 90);
        //Camera->camera();
        window.draw(character);
        //window.draw(rect);
        window.display();
    }

    return 0;
}

void updateMovemnet()
{

    jumpcounter();
    velocityX += accelerationX;
    velocityY += accelerationY;



    moveX += velocityX;
    moveY += velocityY;

    if(moveY < BoxPosY )                  //If you are above ground
        velocityY += gravity;    //Add gravity
     else if(moveY > BoxPosY)             //If you are below ground
        moveY = MasterPosY;

    //std::cout << boxSetY << " " << moveY << std::endl;


}

void ground_dectection()
{

}

void jumpcounter()
{
    //std::cout << "how many jumps has it done: " << jumpcount <<std::endl;

    // gets jump count 1 from spacebar

    float num = MasterPosY;


    if(jumpcount == 0)
    {
                MAX_Jump =  true;


                    if(num == moveY)
                    {
                        isJumping = false;
                        touchground = true;
                        MAX_Jump = false;
                    }

                //std::cout << isJumping << " " << touchground << std::endl;

                if( touchground == true && isJumping == false)
                {
                            //std::cout << "Yaaaaaaay" << std::endl;
                            jumpcount = 0;
                }
    }
}

/*----------------------- Level 2 ---------------------------*/

int level_2()
{
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {

        }
        window.clear();

        window.display();
    }
}

class shooting{

public:

    void fire()
    {

    }

};
