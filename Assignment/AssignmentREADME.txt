19982634 Bharath Sukesh
Computer Graphics Assignment #2 -- OpenGL 
2020 Semester 2
--------------------------------------
FILES
sample2.cpp --- This file contains all program code. 
lamp.fs --- Fragment shader file for the Lamp/Light
lamp.vs --- Vertex shader file for the Lamp/Light
sample2.fs --- Fragment shader file for the majority of the program
sample2.vs --- Vertex shader file for the majority of the program
--------------------------------------

To Build: Navigate to the folder: Assignment/build in the Terminal and run the command: "make"
To Run: Navigate to the folder: /Assignment/build/bin/4.assignment in the Terminal and run the command: ./4.assignment__assignment
--------------------------------------
GAME WALKTHROUGH:


The game is set in a mysterious world and the only way to escape this world, is to find a special totem that lies somewhere
randomly on the floor in the map. The difficulty is that you are constantly chased by an angry wolf.


Navigating throughout the map is possible by going up to the Torch (Hint: found behind the spawn position) and pressing (F). 
From here starts the search for the special totem; you may find normal totems coloured in a Brown texture. These are not what you need to find. 
The special totem is a red-coloured totem, and if you are able to locate it, then you can press Spacebar to pick it up.

This totem's powers initiates the portal barrier to be unlocked. However, to win the game, you must go to the portal to escape.

During all this, if the wolf gets too close to you, then you will lose the game. 

If you win the game, you are greeted with a You Win message behind the portal (as you walk through the portal texture, you will see it) as shown: https://i.imgur.com/R1zV4aS.png 
If you lose the game, you are greeted with a You Lost message as you lay up and look at the sky.

If you win the game, the wolf also becomes passive, meaning you can go pat it :)
--------------------------------------