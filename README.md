# flappy-birds
A simple game mimit based Win32 SDK imitating the flappy birds.It is finished at the 2014/3/2.

## Screenshot

![img1](https://raw.githubusercontent.com/cporoske/flappy-birds/master/images/flappy-1.png "img1")
![img2](https://raw.githubusercontent.com/cporoske/flappy-birds/master/images/flappy-2.png  "img2")
![img2](https://raw.githubusercontent.com/cporoske/flappy-birds/master/images/flappy-3.png  "img2")

## Structure of Program
* `AppOption.h` defines the configuration of the game, such as `windowName`,`windowWidth`,etc.And in this file, it defines a simple macro to judge whether the role is hitting or not.
* `MyBitmap.h` defines a class to load and draw image to a `HDC`.
* `MyBkSky.h` defines a class to implement a background that can move alone with time.
* `MyClock.h`seemly defines a class to clock, but I don't know what it is for.
* `Myfont.h` defines a class to create and use font, it is just a wrapper to Windows Font API.
* `MyGame.h` defines a class to manage the whole game logic and defines several suructure and game states.This class mainly switches between game state and receives the keyboard and mouse event to interact with game.**So** basicly you can read through the entire logic of the game.

## Conclude
This game can still **be compiled on VS2019**, but the code is written very poorly.**So** please be very careful.