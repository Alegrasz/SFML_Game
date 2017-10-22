#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class button
{
    private:

    public:

};

int main()
{

    enum PGame{mainScreen, level_01};
    //creates the window size and gives the window a name
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Great Game");

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


        sf::Event event;
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
