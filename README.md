# Faster Than Wind 

More up to date: https://github.com/Hopson97/Ancient-Projects/tree/master/c%2B%2B/faster-than-wind

### An experimental Faster Than Light Clone I am making for fun

I started working on this around the 15th December 2015.

## The Ship Editor

![alt tag](http://puu.sh/mKzOv/4b20f531ab.jpg "The ship editor.")

When I first started making it I realised that I would need to be able to create ships, so I spent about 25 hours working on a ship editor for the game.


When you first open the ship editor, you'll have to enter some console commands. 

The first command is just asking whether you make a new ship, or loading a current ship.

Then you simply tell it about the texture, which should be stored at ../FasterThanWind/Resources/Textures/Ships

It only will take in the .png file format, you just need to tell the filename of said texture.

![alt tag](http://puu.sh/mKztb/31a9b0fbcc.png "The ship editor start up,")

###Using the ship Editor

Using the ship editor is very simple. Infact, the controls are told to you when you load up or create a new ship. 

![alt tag](http://puu.sh/mKAbl/e976eb63df.png "The ship editor controls,")

In case that doesn't work for some reason, these are the controls:


CONTROLS:                                                                           
                                                                    
Controls for 'room mode':                                                           
Left Click: Add room                                                                
Right Click: Remove room                                                            
R Button: Roll over a room and press 'r' to rotate the room 90 degrees.             
Use the menu below to switch to a new room type.                                    
Pressing the 'switch to wall mode' button will allow placement/ removal of doors    
\n                                                                                  
Controls for 'wall mode':                                                           
Left Click: on a wall (yellow) to turn it into a door.                              
Right Click: on a door (red) to revert back to a wall.                              
R Button: Pressing 'r' will rotate the selection, so you can switch between vertical and horizontal doors/ walls
Pressing the 'switch to room mode' button will allow placement/ removal of rooms    
\n                                                                                  
General controls:                                                                   
Press 's' to save your ship!                                                        



###Challenges I faced creating the editor

Making the ship editor was rather fustrating at times (thanks c++)

#### Doors

There were several problems with doors

The way I made the editor was so that rooms were 38x38 px and walls were 1x40 (so there were 2 walls betweem rooms). 

This means that creating a door would actually be changing the state of two walls to be doors, one for each room.

This means that when I deleted a room that had a door to another room, I would have a door going to no where! 
This directly leads to the second problem: I don't want to be adding a door to no where (aka if only one wall is selected.) This was my solution:

Lets have a peek at some of the Ship.cpp code, specifically the part that removes rooms.

```C++

void Ship::removeRoom(const sf::RectangleShape& rect)
{
    for (unsigned int tId = 0; tId < mRoomMap.size(); tId++){                                   //Go through each room
        if (mRoomMap[tId]->getSprite().getGlobalBounds().intersects(rect.getGlobalBounds())){   //If intersecting between room and selection rectangle
            for(auto& wall : mRoomMap[tId]->getWalls()) {           //Go through the walls of the room
                if (wall->getType() == typeDoor) {                  //If the wall is a door
                    wall->getOtherWall()->setType(typeWall);        //Set it's neighbouring door into a wall
                    wall->getOtherWall()->setOtherId(0);            //Set it's "other ID" to 0, as it no longer has a neighbour door
                }//if
            }//for
            mRoomMap.erase(mRoomMap.begin() + tId);                 //Remove it.
        }//if
    }//for
}
```

Probably not the best way of doing it, but it works (instantly).

The first 2 lines inside of the method just check if which rooms are being selected. (This allows removal of multiple rooms "similtaniously")
Then it cycles through every wall of that room. If the type of the wall is a door, then it sets its neighbouring door to be a wall, and resets its ID. 
Then it just erases that room from existance.

Hang on a minute? ID? Other Walls? 

```C++
void Ship::checkForWallorDoor(const sf::RectangleShape& rect, const WallOrDoor checkingFor, const WallOrDoor changingTo)
{
    std::shared_ptr<Wall> wall1 = nullptr;      //Pointer to first wall
    std::shared_ptr<Wall> wall2 = nullptr;      //Pointer to second wall

    int numWalls = 0;                           //Number of walls detected

    for (auto& room : mRoomMap) {               //For each room in the ship
        for (auto& wall : room->getWalls()) {       //iterate though each wall of said room

            if (wall->getType() == checkingFor)  {      //If the type of room is the room being checked for

                if(rect.getGlobalBounds().intersects(wall->getRect().getGlobalBounds() ) ) {    //and has an intersection with the "ghost"

                    numWalls++;                     //Increase the number of walls this is true to by 1
                    if (numWalls == 1) {            //If the number of walls this is true to in the loop is equal to 1
                        wall1 = wall;               //Set the wall1 pointer to point to the wall
                    }
                    else if (numWalls == 2) {       //If the number of walls this is true to in the loop is equal to 2
                        wall2 = wall;               //Set the wall2 pointer to point to the second wall
                    }
                }//Intersection check end
            }//Type of wall check end
        }//For each wall loop end
    }//For each room loop end

    if (numWalls == 2) {                //If two rooms were checked
        wall1->setType(changingTo);     //Set the first room to be a door or a wall
        wall2->setType(changingTo);     //Do for second room as well

        wall1->setOtherWall(wall2);
        wall2->setOtherWall(wall1);

        wall1->setOtherId   (wall2->getId());
        wall2->setOtherId   (wall1->getId());
    }
}
```

The comments probably say quite a lot. The method has two jobs, depending on the input.

Job 1 -> Turning walls into doors

Job 2 -> Turning doors int walls

Hence the second argument. It first creates two shared pointers (Shared between the "other wall" and the room it belongs to). These will be pointing at the two walls.

It then has a nested for loop to iterate between each wall of each room. If that wall is a selected wall of the kind being checked for, it then does some checks.
Firstly, it counts the number of walls that have been found so far. Depending on the number of walls found, it points the pointers to the wall "active" in the current iteration of the for loop.

If only 1 wall was found during the nested for loop, then it means that it was wall going to no where, and so nothing happens.

However, if two walls were found:
it sets each wall to whatever it is meant to be changing to.
Sets the neighbouring wall.. well.. to be the neighbouring wall.
Then sets the IDs as seen in the code. (This is used in the process of saving and loading ships, so that they can be matched up with eachother when loaded/ saved)

## The Game

The game is very simple in its current states, seeing as it is an unfinished project.

It has a has main menu, a ship selection screen with some music playing in the background

![alt tag](http://puu.sh/nVANA/6e4dc31862.jpg "Main menu,")

![alt tag](http://puu.sh/nVAOM/a120e9c70f.jpg "Ship Selector,")

Video: https://vid.me/jMhx
