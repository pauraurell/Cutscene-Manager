Hi, I'm [Pau Raurell](https://github.com/pauraurell) and welcome to my Cutscene Manager. This project has been made for the personal research assignment of the subject Project 2 in the [Video Game design and development Degree in CITM, UPC.](https://www.citm.upc.edu/ing/estudis/graus-videojocs/)

### What content can you find here?

* What is a cutscene)
* Types of cutscenes and its pros and cons
* Cutscene Editors
* Code Implementation


# What is a cutscene?

By definition, a cutscene is a not interactive sequence in a video game that breaks up the gameplay. Cutscenes are used to show conversations between characters, set the mood, reward the player, introduce new gameplay elements, show the effects of a player's actions... Although the definition says that cutscenes are not interactive, nowadays we see a lot of videogames with quick time events which basically are cutscenes where the player has to press buttons to continue the scene. 

# Types of cutscene

We can divide cutscenes in three types: Pre-rendered, Real time and Live-action cutscenes.

### Live-action cutscenes

This type of cutscenes are the less common nowadays and they are basicaly videos recorded in the real live with actors, the same as films. Back at the days these cutscenes were the best way of explaining the story of a game and were a great innovation but nowadays it's really rare to find one of this type in a video game.

![Live action](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/gifs/Live-Action%20Cutscene%20Mark%20Hamill.gif?raw=true)

*Wing Commander IV*

**Pros:** 

-You don't have to worry about technical limitations of a CPU.

**Cons:** 

-High disonance with the gameplay.



### Pre-rendered cutscenes

This type of cutscenes are scenes that are already loaded and rendered when the player is seeing them. They can be made with the game engine or, the most common way, with external software. 

![pre](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/gifs/Battlefront%202%20pre-rendered%20cutscene.gif?raw=true)

*Star Wars Battlefront II*


![pre](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/gifs/Attila%20Total%20War%20pre-rendered%20cutscene.gif?raw=true)

*Total War: Attila*


![pre](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/gifs/The%20Force%20Unleashed%202%20pre-rendered%20cutscene.gif?raw=true)

*Star Wars The Force Unleashed II*


**Pros:** 

-You don't have to worry about technical limitations of a CPU, that means that there can be high quality textures, a lot of particles and visual effects, cooler animations... In conclusion, better graphics.

**Cons:** 

-Due to that high quality, a pre-rendered cutscene file usually has a large size. 

-Disonance with the gameplay.

-As it is pre-rendered, the cosmetic modifications in the characters won't be seen (the cutscene will be always the same).

### Real time cutscenes

In the real time cutscenes, what the player sees is being rendered in that moment and obviously these type of cutscenes are made with the game engine. This type is common in cutscenes like conversation or cutscenes that don't take a long, but can be used everywhere.
 
![pre](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/gifs/Red%20Dead%20Redemption%202%20real%20time%20cutscene.gif?raw=true)

*Red Dead Redemption 2*


![pre](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/gifs/Uncharted%204%20real%20time%20cutscene.gif?raw=true)

*Uncharted 4*


**Pros:** 

-There is no disonance between the gameplay and the cutscene and feels fluid.

-Visible cosmetic changes.

-Saves a lot of space. 

**Cons:** 

-Technical limitations. 


### Interactive cutscenes
Quick time events are a type of cutscene where the player has to press a button or a sequence of buttons to do a concrete action.

![interactive](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/gifs/Shadow%20of%20The%20Tomb%20Raider%20interactive%20cutscene.gif?raw=true)

*Shadow of the Tomb Raider* 


# Cutscene Editors

To add a Pre-rendered cutscene in our video game we just have to make a video file with the cutscene we want. There is a lot of programs that allows us to do this, for example a pre-rendered cutscene could be made with After Effects, Adobe Premiere or even Toon Boom for simple and short cutscenes. But what really interests us is how to make real time cutscenes. 


![unity](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/unity.png?raw=true)
![unreal](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/unreal.png?raw=true)

There are game engines with tools that allows us to create cutscenes. For example in Unity we have the Cinemachine tool for free that is really usefull for camera movements and transitions or Cinema Director which is not free that allows you to do more complex cutscenes. 
Unreal Engine has a cutscene tool too, it is called Matinee and it's very similar to Cinema Director in Unity, it allows you to animate actors over time using a timeline and key frames.

# Code Implementation

The objective of this project is to create a basic Cutscene Editor so we can make cutscenes in our 2d Motor. For this basic implementation the cutscenes just move actors from a place to another and shows black bars. We will read the coordinates from a xml so it is really easy to edit a cutscene or create a new one. With this system we can start a cutscene whenever we want or when the player is in a certain position that we will get from the Map tmx.

We will have a module that will handle all the neccesary things to create cutscenes, load them, finish them... In this new module we will have 3 new structs. Every cutscene is divided by steps. A step is just a position and a speed for an object. 

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/Step.PNG?raw=true)

Then, every object involved in a cutscene will have a list of steps, the current step and a bool to indicate if it is active so we can disable the cutscene later. A cutscene object has also a function that updates the current step if it arrives to the desiny point.

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/Object.PNG?raw=true)

The last one is the Black Bars struct.

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/Bars.PNG?raw=true)


As this is a generic approach, in this project there isn't a entity manager or ui elements or sprites/animations so our "characters" or cutscene objects will be as simple as squares created with the DrawQuad function. So the "characters" just have a iPoint position and the CutsceneObject struct.

## Exercice

You can download the excercice here. You will find 6 TODOs and if you complete them all you will be able to create in-game cutscenes in which are the number of actors you want and you will be able to read a trigger tile from the tiled map. The result should be something like this:

## Exercice Solution

TODO 1: The first thing we want to do is reading the xml and store the value of each step in the correspondent step list. To do that you have to do a for loop iterating all the steps of the cutscene and push each step into the list of the objective. 

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/TODO%201%20WEB.PNG?raw=true)

TODO 2: In the second todo we have to move the objective of the cutscene to the position of the current step. The Movement function will look where is the object respect to the step position and will move the speed value for pixel. 

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/TODO%202%20WEB.PNG?raw=true)

TODO 3: This function just updates the step values with the next ones in the list, then pop the last one so the cutscene keep going.

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/TODO%203%20WEB.PNG?raw=true)

TODO 4: Here we just have to check if the object reached its objective to call UpdateStep. If the position reached is the final one call the FinishCutscene function.

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/TODO%204%20WEB.PNG?raw=true)

TODO 5: A simple way to do the fade in and out:

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/TODO%205%20WEB.PNG?raw=true)

TODO 6: To get the tile in which we want to call StartCutscene we have to do a for loop iterating all layers to see if the layer has a cutscene trigger property. Then we want to see if the player is in that tile, and to do that we will see if the tile id is equal to the gid we are looking for, in our case is 2 because it is the second tile in the tilemap. Finally we will start the cutscene desired.

![](https://github.com/pauraurell/Cutscene-Manager/blob/master/docs/TODO%206%20WEB.PNG?raw=true)

## Further improvements

This is just a base of code and a lot of improvements could be made. For example you could add a audio atributte in the xml or a wait time attribute to let a object stay in a position while the rest of the cutscene is playing. The black bars effect could be improved a little bit by doing the fade in/out smoother.
