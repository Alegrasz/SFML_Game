

# How to add gravity

We will be using the gravity class with the function called gravityA()


```cpp
/*
//-----------------------
---- NOTE: The playerPositionXY, boxSize, platformPositionXY, and platformRedSize have to be outside of the level_1 function so the objects can move accross the screen
//------------------------
*/

        // player box size and position
        std::pair <float, float> PlayerPositionXY (330, 200); // this is how I would set the position of the player. You can do float playerPositionX and float playerPositionY they are the same
        std::pair <float, float> boxSize (20.0f, 20.0f); // Then I set the size of the box 
        // end of box size and position

        // start of red of platform
        std::pair <float, float> platformRedPositionXY (300, 350); // sets the position of the platform
        std::pair <float, float> platformRedSize(200.0f, 20.0f); // sets the size of the platform
        // end of red platform

void level_1()
{

while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

         object *Player; 
         object *Platform;
         gravity *updatePlayerPosition;

        window.clear();

        //platform red
        //This draws a red box
        
        Platform->box(&platformRedPosXY.first, &platformRedPosXY.second, platformRedSize.first, platformRedSize.second, 255, 0, 0); // Thus draws the red platform
        
        // End of platform red
        
        //start of gravity
        //This updates the players movement
        
        std::pair <float, float> getNewPosition = updatePlayerPosition->gravityA(&PlayerPositionXY.first, &PlayerPositionXY.second, &boxSize.first, &boxSize.second, platformRedPos.first, platformRedPos.second, platformRedSize.first, platformRedSize.second);
        
        //This updates Player->box()
        //it gets the new position via std::pair <float, float> getNewPosition
       // end of gravity
       
       //Start of Player
       // here I set the the position in the exact order as seen bellow
       // The position of the box gets updated by the getNewPosition which makes it move 
        Player->box(&getNewPosition.first, &getNewPosition.second, boxSize.first, boxSize.second, 255, 153, 255);
       //end of Player

        window.display();
    }

}

```
