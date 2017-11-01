#include <iostream>
#include <utility>
#include <SFML/graphics.hpp>

void title();
void level_1();
void controls();
void jump_count(bool isJumping, bool isLanded);
std::pair <float, float> updateMovement(float x, float y, float MasterPosObjX, float MasterPosObjY);

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
            std::cout << Triggered << std::endl;
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

class object
{
public:
    std::pair <float, float > box(float SetPosX, float SetPosY , float sizeX, float sizeY, int R, int G, int B)
    {
        sf::RectangleShape rectan;
        rectan.setPosition(SetPosX, SetPosY);
        rectan.setSize(sf::Vector2f(sizeX, sizeY));
        rectan.setFillColor(sf::Color(R, G, B));

        std::pair <float, float> Pos(rectan.getPosition().x, rectan.getPosition().y);

        window.draw(rectan);


        return  Pos;
    }

    void circle(float SetPosX, float SetPosY, float Radius, int R, int G, int B)
    {
        sf::CircleShape circle;
        circle.setPosition(SetPosX, SetPosY);
        circle.setRadius(Radius);
        circle.setFillColor(sf::Color(R, G, B));
        window.draw(circle);
    }

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

class physics
{
public:

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

        bool clicked = false;

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
        //The objects that will printed to the screen
        win->circle(180, 120, 80.0f, 0, 0, 255);
        win->text("arial", 45, "The Great Game", 240, 180, 255, 0, 0);
        //This makes the button
        std::pair <float, float> boundaryPlay = win->text("arial", 45, "Play Game", 290, 300, 255, 0, 0);

        //std::cout << boundaryPlay.first << " " << boundaryPlay.second << std::endl;

        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        //std::cout << mouse.x << " " << mouse.y << std::endl;

        bool button = triggerBox->triggerBox(mouse.x, mouse.y, 290, 300, (290 + boundaryPlay.first), (300 + boundaryPlay.second));

        if((button == true))
        {
            win->text("arial", 45, "Play Game", 290, 300, 0, 255, 0);
        }
        if(clicked == true && button == true)
        {
            level_1();
        }
        window.display();
    }
}

float velocityX = 0, velocityY = 0;
float accelerationX = 0, accelerationY = 0;
float gravity = 1;

float CharMoveX = 0;
float CharMoveY = 0;

float sizeCharX = 40;
float sizeCharY = 40;
float CharPosX = 50;
float CharPosY = 460;

    object *object;
    sf::RectangleShape newChar;

    bool isJumping = false;
    bool isLanded = true;
    bool Max_jump = false;

void level_1()
{
    //std::cout << "loaded level 1" << std::endl;

    newChar.setPosition(CharMoveX, CharPosY);
    newChar.setSize(sf::Vector2f(sizeCharX, sizeCharY));
    newChar.setFillColor(sf::Color::Red);

    sizeCharX = newChar.getGlobalBounds().width;
    sizeCharY = newChar.getGlobalBounds().height;

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space && Max_jump == false)
                {
                    velocityY = -20;
                    isJumping = true;
                    isLanded = false;
                }
            }

           if(event.type == sf::Event::Closed)
           {
              window.close();
           }
        };

        window.clear();
        object->box(0,500, 800, 300, 0, 255, 0); // green box

        controls();
        jump_count(isJumping, isLanded);
        std::pair <float, float> PosUpdate = updateMovement(CharPosX, CharPosY, 0, 0 );

        std::cout << PosUpdate.first << " " << PosUpdate.second << std::endl;

        object->camera(PosUpdate.first, PosUpdate.second);

        newChar.setPosition(PosUpdate.first, PosUpdate.second);

        window.draw(newChar);

        window.display();
    }
}

void controls()
{
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D)){velocityX = 0;}

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A)){velocityX = 0;}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){velocityX = 5;}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){velocityX = -5;}
}

std::pair <float, float> updateMovement(float x, float y, float MasterPosObjX, float MasterPosObjY)
{
    //std::cout << x << " " << y << std::endl;
    //::cout << x << " " << y << std::endl;
    velocityX += accelerationX;
    velocityY += accelerationY;



    CharPosX += velocityX;
    CharPosY += velocityY;

    if(460 > CharPosY)
    {
        velocityY += gravity;
    }
    else if (CharPosY >= 460)
    {
        CharPosY = 460;
        isLanded = true;
    }

    std::pair <float, float> newPos (x, y);

    return newPos;
}

void jump_count(bool isJumping, bool isLanded)
{
    if(isJumping == true)
    {
        Max_jump = true;
        if(isLanded == true)
        {
            Max_jump = false;
        }
    }
}
