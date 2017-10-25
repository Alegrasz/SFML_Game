#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "button.h"

int level_1();
void updateMovemnet();

float WindowX = 800, WindowY = 600;

sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "The Great Game");
sf::Event event;
int main()
{
    window.setFramerateLimit(60);
    enum PGame{mainScreen, level_01};
    //creates the window size and gives the window a name

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
    text.setFont(font);
    text.setString("Play Game");
    text.setCharacterSize(40);
    text.setColor(sf::Color::Red);
    text.setPosition(xPos, yPos);
    title.setFont(font);
    title.setString("The Great Game");
    title.setCharacterSize(60);
    title.setColor(sf::Color::Red);
    title.setPosition(150, 200);
    //end of the button creation
    bool MouseButtonPressed = false;
    while (window.isOpen())
    {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        float textCorY = text.getGlobalBounds().height;
        float textCorX = text.getGlobalBounds().width;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            std::cout << "it works" << std::endl;
        }
        // start of the Button
        // put all what is below in a class
        //on click

        //Test of button

        //end of test button
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
                    //text.setPosition(100000, 100000);
                    //title.setPosition(100000, 100000);
                    //shape.setPosition(100000, 100000);
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

    float moveX = 200, moveY = 400;
    float velocityX = 0, velocityY = 0;
    float accelerationX = 0, accelerationY = 0;

    float gravity = 1;

    float boxSetX = 0, boxSetY = 500;

int level_1()
{



    bool isJumping = false;

    sf::Vector2f velocity(sf::Vector2f(0,0));

    sf::CircleShape character(30.f);
    character.setFillColor(sf::Color::Red);
    character.setPosition(moveX, moveY);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(1000, 200));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(boxSetX, boxSetY);



    while(window.isOpen())
    {
    // all the set variables

    bool isButtonPressed = false;



    float characterPosX = character.getPosition().x;
    float characterPosY = character.getPosition().y;

    float sizeofCharX = character.getGlobalBounds().width;
    float sizeofCharY = character.getGlobalBounds().height;

   // std::cout <<"Char Position in X: " << characterPosX << " Char Position in Y: " << characterPosY << std::endl;
    std::cout << "Size of character in X: " << sizeofCharX << " Size of character Y: " << sizeofCharY << std::endl;

    float boxPosX = rect.getGlobalBounds().width;
    float boxPosY = rect.getGlobalBounds().height;
    //std::cout << boxPosX << " " << boxPosY << std::endl;

    //end of all variables



    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                velocityY = -20;
            }
        }

        //The usable buttons here

        bool button = false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
        {
            velocityX = 8;
            button = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocityX = -8;
            button = true;

        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (button == true))
        {
                button = false;
        }
        /*if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
        {
            velocityY = -2;
        }*/


        //setting a ground



        //end of ground

        updateMovemnet();
        character.setPosition(moveX, moveY);
        //gravity(character);
        window.clear();
        window.draw(character);
        //window.draw(rect);
        window.display();
    }

    return 0;
}



void updateMovemnet()
{
     if(moveY < boxSetY )                  //If you are above ground
        velocityY += gravity;    //Add gravity
    else if(moveY > boxSetY)             //If you are below ground
        moveY = 500;

    velocityX += accelerationX;
    velocityY += accelerationY;

    moveX += velocityX;
    moveY += velocityY;
}
